#include "main.h"
#include "utilities.h"

using namespace std;

vector<string> parser(string line,char token){
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
