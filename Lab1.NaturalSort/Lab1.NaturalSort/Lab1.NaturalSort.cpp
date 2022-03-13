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
int main()
{
	createFileWithRandomNumbers("test1.txt", 10, 100);
	split("test1.txt", "Sort1.txt", "Sort2.txt");
	return 0;
}
