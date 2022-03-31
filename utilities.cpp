#include "main.h"
#include "utilities.h"

using namespace std;

const string emptyLine = "__________________________________________";
const char token = '|';

bool FileManager::getHeaderHTML(string& myHeader) {
	size_t pos = 0;
	string dummyStr;

	fstream Header; //file with answers,for teacher to correct.
	Header.open("TEMPLATE.html", ios::in);

	if (!Header.bad()) {
		while (!Header.fail() && getline(Header, dummyStr)) {
			myHeader += dummyStr;
		}
		Header.close();
	}
	else {
		return true;
	}

	//input test name
	cout << "Name of the test? ";
	getline(cin, dummyStr);

	//change test name in header
	while ((pos = myHeader.find('*', ++pos)) != string::npos) {
		myHeader.insert(++pos, dummyStr + "*");
		pos += dummyStr.length();
	}
	return false;
}

vector<string> FileManager::parser(string line) {
	size_t pos = 0;

	vector<string> tokens;

	if (line.find(token) != string::npos) { //if it's a multiple choice answer

		while ((pos = line.find(token)) != string::npos) { //split pieces of answer
			tokens.push_back(line.substr(0, pos));
			line.erase(0, ++pos);
		}

	}
	else {
		tokens.push_back(line); //insert open answer
	}

	return tokens;
}

void FileManager::shuffler(vector<pair<string, vector<string>>>& fillWithQuestions) {
	random_shuffle(fillWithQuestions.begin(), fillWithQuestions.end(), [](int i) -> int { return rand() % i; }); //shuffling questions

	for (int i = 0; i < fillWithQuestions.size(); i++) {
		random_shuffle(fillWithQuestions[i].second.begin(), fillWithQuestions[i].second.end()); //shuffling answers (the second vector inside the pair)
	}
}

bool FileManager::WriteQuestionsOnFile(vector<pair<string, vector<string>>>& singleQuestions, fstream& Answers, fstream& Tests,bool writeAnswersFile) {
	size_t pos = 0;
	for (int INDEX = 0; INDEX < singleQuestions.size() && !Tests.fail() && !Answers.fail(); INDEX++) {
		Tests << "<br>" << singleQuestions[INDEX].first << "<br>"; //writing question
		if(writeAnswersFile)
			Answers << "Risposta corretta per la domanda: \"" << singleQuestions[INDEX].first << "\" -> "; //print answer to file for teacher.

		if (singleQuestions[INDEX].second.size() > 1) { //if vector with answers contains more than a question,this means it's a multiple choice question, so i have to print all of them
			for (auto answer : singleQuestions[INDEX].second) {
				if ((pos = answer.find('#')) != string::npos) { //correct answer
					answer.replace(pos, 1, ""); //i remove '#' from string, to show it on the file (otherwise, students would have known which is the correct answer.
					if (writeAnswersFile)
						Answers << answer << endl;
				}
				Tests << "[] " << answer << "<br>"; //printing answer(s).
			}
		}
		else {
			//otherwise, vector with answer contains only one correct answer, that has to be written by the student.
			if (writeAnswersFile)
				Answers << singleQuestions[INDEX].second[0] << endl;
			Tests << emptyLine << endl;//open questions.
		}
	}

	return Tests.fail()||Answers.fail();
}