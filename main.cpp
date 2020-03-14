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
    for(auto token : tokens) {
        cout << token << " ";
    }
    cout << endl;
}

void getTokens(const string& intermediate, vector<string>& tokens) {
    // TODO: Use state machine to capture different states
    enum StreamState { InsideOfToken, OutsideOfToken };
    StreamState stream_state = OutsideOfToken;
    string current_token;
    for(auto c : intermediate) {
        assert(c != ' ');
       if(stream_state == OutsideOfToken) {
           assert(current_token.empty());
           if(c == '(' || c == ')') {
               tokens.push_back(string(1, c));
           } else {
               current_token += c;
               stream_state = InsideOfToken;
           }
       } else {
           if(c == '(' || c == ')') {
               tokens.push_back(current_token);
               tokens.push_back(string(1, c));
               stream_state = OutsideOfToken;
               current_token = "";
           } else {
               current_token += c;
           }
       }
    }
    if(!current_token.empty()) {
        tokens.push_back(current_token);
    }
}
