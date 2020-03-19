#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std;

void getTokens(const string& intermediate, vector<string>& tokens);

int main() {
    string input  = "(first (list 1 (+ 2 3) 9))";
    stringstream str_stream(input);
    string intermediate;
    vector<string> tokens;
    while(getline(str_stream, intermediate, ' ')) {
        getTokens(intermediate, tokens);
    }
    for (auto &token : tokens) {
        cout << token << " ";
    }
    cout << endl;
}

