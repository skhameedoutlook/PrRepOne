#include "utilities.h"
#include "term.h"
#include <fstream>

int main() {
    initSymbols();
    // vector<string> lines = {"true", "false", "0", "iszero 0", "pred 0", "succ 0", "pred succ 0", "succ pred 0", "if succ pred succ pred if true then true else true then true else false", "if if true then true else false then true else false"};
    // vector<string> lines = {"if iszero succ succ 0 then if true then true else true else false"};
    // for(int i = 0; i < lines.size(); i++) {
    //     interpret(lines[i]);
    // }
    ifstream myfile ("input1.txt");
    string line = "";

    //cout << "----Untyped Arithmetic Expressions Language v1.0---" << endl;
    //cout << "Type q to quit"<< endl;
    //cout << endl;
    //cout << ">>> ";
    /*
    while(getline(myfile, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        if(line.compare("q") == 0) break;
        interpret(line);
    }
    myfile.close();
    */

    cout << "----Untyped Arithmetic Expressions Language v1.0---" << endl;
    cout << "Type q to quit"<< endl;
    cout << endl;
    cout << ">>> ";
    while(getline(cin, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        if(line.compare("q") == 0) break;
        interpret(line);
        cout << ">>> ";
    }


    return 0;
}

