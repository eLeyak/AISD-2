#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool createFileWithRandomNumbers(const string& fileName, const int numbersCount, const int maxNumberValue) {
	ofstream file(fileName);
	if (!file.is_open()) {
		cout << "Can't create " << fileName << endl;
		return false;
	}

	int buf;
	srand(time(NULL));
	for (int i = 0; i < numbersCount; i++) {
		buf = rand() % (maxNumberValue + 1);
		file << buf << ' ';
	}

	file.close();
	return true;
}
bool isFileContainsSortedArray(const string& fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Can't open " << fileName << endl;
		return false;
	}

	int current = -1;
	int previous;
	while (!file.eof()) {
		previous = current;
		file >> current;
		if (current < previous) {
			return false;
		}
	}

	file.close();
	return true;
}
void split(const string& fileInput, const string& fileOutputOne, const string& fileOutputTwo) {
	ifstream input(fileInput);
	if (!input.is_open()) {
		cout << "Can't open " << fileInput << endl;
		return;
	}

	ofstream outputOne(fileOutputOne);
	if (!outputOne.is_open()) {
		cout << "Can't open " << fileOutputOne << endl;
		return;
	}

	ofstream outputTwo(fileOutputTwo);
	if (!outputOne.is_open()) {
		cout << "Can't open " << fileOutputTwo << endl;
		return;
	}

	ofstream* output;
	output = &outputOne;

	int outputSwitch = 0;

	int current = -1;
	int previous = -1;

	input >> current;
	while (!input.eof()) {
		if (current < previous) {
			if (outputSwitch % 2) {
				output = &outputOne;
			}
			else {
				output = &outputTwo;
			}
			outputSwitch++;
		}
		*output << current << " ";
		previous = current;
		input >> current;
	}

	input.close();
	outputOne.close();
	outputTwo.close();
}
void sortAndSplit(ifstream& inputOne, ifstream& inputTwo, ofstream& outputOne, ofstream& outputTwo) {
	int currentOne = -1;
	int previousOne = -1;
	int currentTwo = -1;
	int previousTwo = -1;
	int inputStopOne = 0;
	int inputStopTwo = 0;
	int currentOneIsPrinted = 0;
	int currentTwoIsPrinted = 0;
	int endOfFile = 0;
	int outputSwitch = 0;

	ofstream* output;
	output = &outputOne;

	inputOne >> currentOne;
	inputTwo >> currentTwo;
	while (1) {
		if (inputOne.eof()) {
			endOfFile = 1;
			break;
		}
		if (inputTwo.eof()) {
			endOfFile = 2;
			break;
		}
		
		if (currentOne < currentTwo) {
			*output << currentOne << " ";
			inputStopOne = 0;
			inputStopTwo = 1;
			currentOneIsPrinted = 1;
		}
		else {
			*output << currentTwo << " ";
			inputStopOne = 1;
			inputStopTwo = 0;
			currentTwoIsPrinted = 1;
		}

		if (!inputStopOne) {
			previousOne = currentOne;
			inputOne >> currentOne;
			currentOneIsPrinted = 0;
		}
		if (!inputStopTwo) {
			previousTwo = currentTwo;
			inputTwo >> currentTwo;
			currentTwoIsPrinted = 0;
		}

		if (currentOne < previousOne) {
			while (currentTwo >= previousTwo && !inputTwo.eof()) {
				*output << currentTwo << " ";
				previousTwo = currentTwo;
				inputTwo >> currentTwo;
			}
			if (inputTwo.eof()) {
				endOfFile = 2;
					break;
			}

			previousOne = -1;
			previousTwo = -1;

			if (outputSwitch % 2) {
				output = &outputOne;
			}
			else {
				output = &outputTwo;
			}
			outputSwitch++;
		}
		if (currentTwo < previousTwo) {
			while (currentOne >= previousOne && !inputOne.eof()) {
				*output << currentOne << " ";
				previousOne = currentOne;
				inputOne >> currentOne;
			}
			if (inputOne.eof()) {
				endOfFile = 1;
				break;
			}

			previousOne = -1;
			previousTwo = -1;

			if (outputSwitch % 2) {
				output = &outputOne;
			}
			else {
				output = &outputTwo;
			}
			outputSwitch++;
		}
	}

	if (endOfFile == 1) {

		if (currentTwoIsPrinted) {
			previousTwo = currentTwo;
			inputTwo >> currentTwo;
		}
		while (!inputTwo.eof()) {
			if (currentTwo < previousTwo) {
				if (outputSwitch % 2) {
					output = &outputOne;
				}
				else {
					output = &outputTwo;
				}
				outputSwitch++;
			}
			*output << currentTwo << " ";
			previousTwo = currentTwo;
			inputTwo >> currentTwo;
		}
		return;
	}
	else if (endOfFile == 2) {
		if (currentOneIsPrinted) {
			previousOne = currentOne;
			inputOne >> currentOne;
		}
		while (!inputOne.eof()) {
			if (currentOne < previousOne) {
				if (outputSwitch % 2) {
					output = &outputOne;
				}
				else {
					output = &outputTwo;
				}
				outputSwitch++;
			}
			*output << currentOne << " ";
			previousOne = currentOne;
			inputOne >> currentOne;
		}
		return;
	}

}
void naturalMerge(const string& fileInput) {
	split(fileInput, "sort1.txt", "sort2.txt");

	int fileSwitch = 1;
	int fileCheck = 0;

	while (fileSwitch) {
		if (fileSwitch % 2) {
			ifstream inputOne("sort1.txt");
			if (!inputOne.is_open()) {
				cout << "Can't open " << "sort1.txt" << endl;
				return;
			}

			ifstream inputTwo("sort2.txt");
			if (!inputTwo.is_open()) {
				cout << "Can't open " << "sort2.txt" << endl;
				return;
			}

			ofstream outputOne("sort3.txt");
			if (!outputOne.is_open()) {
				cout << "Can't open " << "sort3.txt" << endl;
				return;
			}

			ofstream outputTwo("sort4.txt");
			if (!outputOne.is_open()) {
				cout << "Can't open " << "sort4.txt" << endl;
				return;
			}

			inputTwo >> fileCheck;
			if (inputTwo.eof()) {
				fileCheck = 1;
				break;
			}
			else {
				inputTwo.seekg(0);
			}

			sortAndSplit(inputOne, inputTwo, outputOne, outputTwo);

			inputOne.close();
			inputTwo.close();
			outputOne.close();
			outputTwo.close();
		}
		else {
			ifstream inputOne("sort3.txt");
			if (!inputOne.is_open()) {
				cout << "Can't open " << "sort1.txt" << endl;
				return;
			}

			ifstream inputTwo("sort4.txt");
			if (!inputTwo.is_open()) {
				cout << "Can't open " << "sort2.txt" << endl;
				return;
			}

			ofstream outputOne("sort1.txt");
			if (!outputOne.is_open()) {
				cout << "Can't open " << "sort3.txt" << endl;
				return;
			}

			ofstream outputTwo("sort2.txt");
			if (!outputOne.is_open()) {
				cout << "Can't open " << "sort4.txt" << endl;
				return;
			}

			inputTwo >> fileCheck;
			if (inputTwo.eof()) {
				fileCheck = 3;
				break;
			}
			else {
				inputTwo.seekg(0);
			}

			sortAndSplit(inputOne, inputTwo, outputOne, outputTwo);

			inputOne.close();
			inputTwo.close();
			outputOne.close();
			outputTwo.close();
		}
		fileSwitch++;
	}

	int buffer;

	if (fileCheck == 1) {
		ifstream input("sort1.txt");
		if (!input.is_open()) {
			cout << "Can't open " << "sort1.txt" << endl;
			return;
		}

		ofstream output("output.txt");
		if (!output.is_open()) {
			cout << "Can't open " << "output.txt" << endl;
			return;
		}

		input >> buffer;
		while (!input.eof()) {
			output << buffer << " ";
			input >> buffer;
		}
	}
	else {
		ifstream input("sort3.txt");
		if (!input.is_open()) {
			cout << "Can't open " << "sort3.txt" << endl;
			return;
		}

		ofstream output("output.txt");
		if (!output.is_open()) {
			cout << "Can't open " << "output.txt" << endl;
			return;
		}

		input >> buffer;
		while (!input.eof()) {
			output << buffer << " ";
			input >> buffer;
		}
	}
	

	
}

int main()
{
	for (int i = 0; i < 100; i++) {
		createFileWithRandomNumbers("test1.txt", 100, 100);
		naturalMerge("test1.txt");
		if (isFileContainsSortedArray("output.txt")) {
			cout << "success" << endl;
		}
		else {
			cout << "fail" << endl;
		}
	}
	return 0;
}
