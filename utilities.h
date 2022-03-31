#pragma once
#include "main.h"

using namespace std;

extern const string emptyLine;
extern const char token;

class FileManager {

public:
	bool getHeaderHTML(string& myHeader);
	void shuffler(vector<pair<string, vector<string>>>& fillWithQuestions);
	bool WriteQuestionsOnFile(vector<pair<string, vector<string>>>& singleQuestions, fstream& Answers, fstream& Tests, bool writeAnswersFile);
	vector<string> parser(string line);
};
