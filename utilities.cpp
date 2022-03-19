#include "main.h"
#include "utilities.h"

using namespace std;

vector<string> parser(string line,char token){
    int pos=0;
    
    vector<string> tokens;

    if (line.find(token) != string::npos) {
        while ((pos = line.find(token)) != string::npos) {
            tokens.push_back(line.substr(0, pos));
            line.erase(0, ++pos);
        }
    }
    else {
        tokens.push_back(line);
    }

    return tokens;
}
