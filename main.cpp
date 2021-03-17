#include "utilities.cpp"

int main() {
    initSymbols();
    // vector<string> lines = {"true", "false", "0", "iszero 0", "pred 0", "succ 0", "pred succ 0", "succ pred 0", "if succ pred succ pred if true then true else true then true else false", "if if true then true else false then true else false"};
    vector<string> lines = {"if iszero succ succ 0 then if true then true else true else false"};
    for(int i = 0; i < lines.size(); i++) {
        interpret(lines[i]);
    }

    return 0;
}