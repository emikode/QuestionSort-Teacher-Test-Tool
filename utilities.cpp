#include "main.h"
#include "utilities.h"

using namespace std;

const string emptyLine = "__________________________________________";
const char token = '|';

	bool FileManager::getHeaderHTML(string&myHeader){
		size_t pos=0;
		string dummyStr;

		fstream Header; //file with answers,for teacher to correct.
		Header.open("TEMPLATE.html",ios::in);

		if(!Header.bad()){
			while(!Header.fail()&&getline(Header,dummyStr)){
				myHeader += dummyStr;
			}
		}

		if(!Header.fail()){
			//input test name
			cout << "Name of the test? ";
			getline(cin,dummyStr);

			//change test name in header
			while((pos=myHeader.find('*',++pos))!=string::npos){
				myHeader.insert(++pos,dummyStr+"*");
				pos+=dummyStr.length();
			}

			Header.close();
			return true;
		}

		return false;

	}

	vector<string> FileManager::parser(string line){
		size_t pos=0;

		vector<string> tokens;

		if (line.find(token) != string::npos) {

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
