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

void split(const string& fileInput, const string& fileOutputOne, const string& fileOutputTwo, int steps) {
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

	int buffer;
	while (!input.eof()) {
		for (int i = 0; i < steps && !input.eof(); i++) {
			input >> buffer;
			if (!input.eof()) {
				outputOne << buffer << " ";
			}
		}
		for (int i = 0; i < steps && !input.eof(); i++) {
			input >> buffer;
			if (!input.eof()) {
				outputTwo << buffer << " ";
			}
		}
	}

	input.close();
	outputOne.close();
	outputTwo.close();
}
int sortAndMergeASegment(ifstream &inputOne, ifstream & inputTwo, ofstream& output, int steps) {
	int bufferOne = -1;
	int bufferTwo = -1;
	int readCounterOne = 0;
	int readCounterTwo = 0;
	int printCounterOne = 0;
	int printCounterTwo = 0;
	int inputStopOne = 0;
	int inputStopTwo = 0;
	int endOfSegemnt = 0;
	int endOfFile = 0;
	
	while (!endOfSegemnt) {
		if (readCounterOne < steps && !inputStopOne) {
			inputOne >> bufferOne;
			if (inputOne.eof()) {
				endOfFile = 1;
				break;
			}
			readCounterOne++;
		}
		else if (printCounterOne == steps) {
			endOfSegemnt = 1;
			break;
		}

		if (readCounterTwo < steps && !inputStopTwo) {
			inputTwo >> bufferTwo;
			if (inputTwo.eof()) {
				endOfFile = 2;
				break;
			}
			readCounterTwo++;
		}
		else if (printCounterTwo == steps) {
			endOfSegemnt = 2;
			break;
		}

		if (bufferOne < bufferTwo) {
			output << bufferOne << " ";
			inputStopOne = 0;
			inputStopTwo = 1;
			printCounterOne++;
		}
		else {
			output << bufferTwo << " ";
			inputStopOne = 1;
			inputStopTwo = 0;
			printCounterTwo++;
		}
	}

	if (endOfFile == 1) {
		if (printCounterTwo < readCounterTwo) {
			output << bufferTwo << " ";
		}
		inputTwo >> bufferTwo;
		while (!inputTwo.eof()) {
			output << bufferTwo << " ";
			inputTwo >> bufferTwo;
		}
		return 1;
	}
	else if (endOfFile == 2) {
		if (printCounterOne < readCounterOne) {
			output << bufferOne << " ";
		}
		inputOne >> bufferOne;
		while (!inputOne.eof()) {
			output << bufferOne << " ";
			inputOne >> bufferOne;
		}
		return 1;
	}

	if (endOfSegemnt == 1) {
		if (printCounterTwo < readCounterTwo) {
			output << bufferTwo << " ";
			printCounterTwo++;
		}
		while (printCounterTwo < steps) {
			inputTwo >> bufferTwo;
			output << bufferTwo << " ";
			printCounterTwo++;
		}
	}
	else {
		if (printCounterOne < readCounterOne) {
			output << bufferOne << " ";
			printCounterOne++;
		}
		while (printCounterOne < steps) {
			inputOne >> bufferOne;
			output << bufferOne << " ";
			printCounterOne++;
		}
	}

	return 0;
}
void mergeSort(const string& fileInput) {
	split(fileInput, "sort1.txt", "sort2.txt", 1);
	
	int fileSwitch = 1;
	int outputSwitch = 1;
	int steps = 1;
	int fileCheck = 0;

	int flag;

	while (fileSwitch) {
		flag = 0;
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

			while (!flag) {
				if (outputSwitch % 2) {
					flag = sortAndMergeASegment(inputOne, inputTwo, outputOne, steps);
				}
				else {
					flag = sortAndMergeASegment(inputOne, inputTwo, outputTwo, steps);
				}
				outputSwitch++;
			}

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

			while (!flag) {
				if (outputSwitch % 2) {
					flag = sortAndMergeASegment(inputOne, inputTwo, outputOne, steps);
				}
				else {
					flag = sortAndMergeASegment(inputOne, inputTwo, outputTwo, steps);
				}
				outputSwitch++;
			}

			inputOne.close();
			inputTwo.close();
			outputOne.close();
			outputTwo.close();
		}
		fileSwitch++;
		steps = steps << 1;
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
		mergeSort("test1.txt");
		if (isFileContainsSortedArray("output.txt")) {
			cout << "success" << endl;
		}
		else {
			cout << "fail" << endl;
		}
	}
	return 0;
}