#pragma once
#include "main.h"

using namespace std;

extern const string emptyLine;
extern const char token;

class FileManager{

public:
	bool getHeaderHTML(string& myHeader);

	vector<string> parser(string line);
};
