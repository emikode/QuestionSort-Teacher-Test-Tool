#include "main.h"
#include "utilities.h"

using namespace std;

int main(void) {
	setlocale(LC_ALL, "it_IT.utf8");

	const string emptyLine = "__________________________________________";
	const char token = '|';
	int INDEX = -1;
	size_t pos = 0;
	string firstLine, secondLine;
	vector<pair<string, vector<string>>> singleQuestions; //first element is the question, second element is an array containing the answers.
	fstream MasterKey("MasterKey.qsrt", ios::in); //file with form
	fstream Answers("ForTeachers.qsrt", ios::out); //file with answers,for teacher to correct.

	if (!MasterKey.fail() && !Answers.fail()) {
		while (INDEX++, getline(MasterKey, firstLine) && getline(MasterKey, secondLine)) { //read two lines from file
			singleQuestions.push_back(make_pair(firstLine, parser(secondLine, token))); //filling singleQuestions with couple of question - answer(s)

			cout << "\n" << singleQuestions[INDEX].first << endl; //printing question to screen
			Answers << "Risposta corretta per la domanda: \"" << singleQuestions[INDEX].first << "\" -> "; //print answer to file for teacher.

			if (singleQuestions[INDEX].second.size() > 1) { //if vector with answers contains more than a question,this means it's a multiple choice question, so i have to print all of them
				for (auto answer : singleQuestions[INDEX].second) {
					if ((pos=answer.find('#')) != string::npos) { //correct answer
						answer.replace(pos,1,""); //i remove '#' from string, to show it on the file (otherwise, students would have known which is the correct answer.
						Answers << answer << endl;
					}
					cout << "[] " << answer << endl; //printing answer(s).
				}
			}
			else {
				//otherwise, vector with answer contains only one correct answer, that has to be written by the student.
				Answers << singleQuestions[INDEX].second[0] << endl;
				cout << emptyLine << endl;//open questions.
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
