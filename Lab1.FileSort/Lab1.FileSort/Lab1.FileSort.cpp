#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool createFileWithRandomNumbers(const string& fileName, const int numbersCount, const int maxNumberValue) {
	ofstream file(fileName);

	if (!file.is_open()) {
		cout << "Can't create " << fileName << endl;
		return false;
	}

	int buf;
	srand(time(NULL));
	for (int i = 0; i < numbersCount ; i++) {
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

int main()
{
	createFileWithRandomNumbers("t0ast.txt", 10, 100);
	int a = isFileContainsSortedArray("t0ast.txt");
	cout << a;
	return 0;
}
