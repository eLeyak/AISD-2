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

void firstSplit(const string& fileInput, const string& fileOutputOne, const string& fileOutputTwo, int steps) {
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
}
void mergeAndSplit(const string& fileInputOne, const string& fileInputTwo, const string& fileOutputOne, const string& fileOutputTwo, int steps) {
	ifstream inputOne(fileInputOne);
	if (!inputOne.is_open()) {
		cout << "Can't open " << fileInputOne << endl;
		return;
	}

	ifstream inputTwo(fileInputTwo);
	if (!inputTwo.is_open()) {
		cout << "Can't open " << fileInputTwo << endl;
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

	int bufferOne;
	int bufferTwo;
	int counterOne;
	int counterTwo;
	int inputStopOne;
	int inputStopTwo;

	int fileOfOutput = 0;
	int universalCounter = 0;
	int endOfFile = 0;

	while (!endOfFile) {
		bufferOne = -1;
		bufferTwo = -1;
		counterOne = 0;
		counterTwo = 0;
		inputStopOne = 0;
		inputStopTwo = 0;

		while (counterOne < steps || counterTwo < steps) {
			if (universalCounter % (steps * 2) == 0) {
				fileOfOutput++;
			}

			if (counterOne < steps && !inputStopOne) {
				inputOne >> bufferOne;
			}
			else if (counterOne == steps) {
				while (counterTwo < steps) {
					if (!inputTwo.eof()) {
						if (fileOfOutput % 2) {
							outputOne << bufferTwo << " ";
						}
						else {
							outputTwo << bufferTwo << " ";
						}
						counterTwo++;
						universalCounter++;
						if (counterTwo < steps) {
							inputTwo >> bufferTwo;
						}
					}
				}
			}

			if (counterTwo < steps && !inputStopTwo) {
				inputTwo >> bufferTwo;
			}
			else if (counterTwo == steps) {
				while (counterOne < steps) {
					if (!inputOne.eof()) {
						if (fileOfOutput % 2) {
							outputOne << bufferOne << " ";
						}
						else {
							outputTwo << bufferOne << " ";
						}
						counterOne++;
						universalCounter++;
						if (counterOne < steps) {
							inputOne >> bufferOne;
						}
					}
				}
			}

			if (!inputOne.eof() && !inputTwo.eof() && counterOne < steps && counterTwo < steps) {
				if (bufferOne < bufferTwo) {
					if (fileOfOutput % 2) {
						outputOne << bufferOne << " ";
					}
					else {
						outputTwo << bufferOne << " ";
					}
					counterOne++;
					universalCounter++;
					inputStopTwo = 1;
					inputStopOne = 0;
				}
				else {
					if (fileOfOutput % 2) {
						outputOne << bufferTwo << " ";
					}
					else {
						outputTwo << bufferTwo << " ";
					}
					counterTwo++;
					universalCounter++;
					inputStopOne = 1;
					inputStopTwo = 0;
				}
			}
			else if (inputOne.eof()) {
				while (!inputTwo.eof()) {
					if (fileOfOutput % 2) {
						outputOne << bufferTwo << " ";
					}
					else {
						outputTwo << bufferTwo << " ";
					}
					inputTwo >> bufferTwo;
				}
				endOfFile = 1;
				break;
			}
			else if (inputTwo.eof()) {
				while (!inputOne.eof()) {
					if (fileOfOutput % 2) {
						outputOne << bufferOne << " ";
					}
					else {
						outputTwo << bufferOne << " ";
					}
					inputOne >> bufferOne;
				}
				endOfFile = 1;
				break;
			}
			else {
				break;
			}
		}
	}
	

	

	


		
	}

int main()
{
	createFileWithRandomNumbers("test1.txt", 2, 100);
	firstSplit("test1.txt", "test2.txt", "test3.txt", 1);
	mergeAndSplit("test2.txt", "test3.txt", "test4.txt", "test5.txt", 1);
	mergeAndSplit("test4.txt", "test5.txt", "test6.txt", "test7.txt", 2);
	mergeAndSplit("test6.txt", "test7.txt", "test8.txt", "test9.txt", 4);
	mergeAndSplit("test8.txt", "test9.txt", "test10.txt", "test11.txt", 8);
	if (isFileContainsSortedArray) {
		cout << "success";
	}
	else {
		cout << "fail";
	}



	return 0;
}