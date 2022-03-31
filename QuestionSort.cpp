#include "main.h"
#include "utilities.h"

using namespace std;

int main(void) {
	srand(time(NULL));

	string fileNameTest = "Test";
	string firstLine, secondLine, header = "", dummystr;

	int numberOfTestsToWrite = 0;

	vector<pair<string, vector<string>>> singleQuestions; //first element is the question, second element is an array containing the answers.

	fstream MasterKey("MasterKey.qsrt", ios::in); //file with form
	fstream Answers("ForTeachers.qsrt", ios::out); //file with answers,for teacher to correct.
	fstream Tests;

	FileManager myManager;


	if (!MasterKey.bad() && !Answers.bad() && !myManager.getHeaderHTML(header)) {

		//filling vector
		while (getline(MasterKey, firstLine) && getline(MasterKey, secondLine) && !MasterKey.fail()) { //read two lines from file
			singleQuestions.push_back(make_pair(firstLine, myManager.parser(secondLine))); //filling singleQuestions with couple of question - answer(s)
		}

		do {
			cin.clear();
			cout << "How many tests do you want to prepare? ";
			cin >> numberOfTestsToWrite;
		} while (cin.fail());

		for (int i = 1; i <= numberOfTestsToWrite; i++) {
			//open file
			Tests.open((fileNameTest + to_string(i) + ".html"), ios::out);
			if (!Tests.bad()) {
				Tests << header; //inserting header in each test

				myManager.shuffler(singleQuestions); //shuffles both quetions and multiple choice answers

				if (!myManager.WriteQuestionsOnFile(singleQuestions, Answers, Tests,i==1)) {
					Tests.close();
				}
				else {
					cout << "An Error occurred while writing tests...";
					exit(EXIT_FAILURE);
				}
			}
		}
		MasterKey.close();
		Answers.close();
	}
	else {
		cout << "An Error occurred while opening the files...";
	}

	return 0;
}
