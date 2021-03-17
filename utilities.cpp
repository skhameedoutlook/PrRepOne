#include "term.cpp"

enum types {TRUE=1, FALSE=2, ZERO=3, IFTHENELSE=4, ISZERO=5, PRED=6, SUCC=7};

map<string, types> symbols;

void initSymbols() {
    symbols["true"] = TRUE;
    symbols["false"] = FALSE;
    symbols["0"] = ZERO;
    symbols["if"] = IFTHENELSE;
    symbols["then"] = IFTHENELSE;
    symbols["else"] = IFTHENELSE;
    symbols["iszero"] = SUCC;
    symbols["pred"] = PRED;
    symbols["succ"] = SUCC;
}

struct SymtabEntry {
    int num;
    string val;
    string type;
};

string stripspaces(string& s) {
    string result = "";
    for(int i = 0; i < s.length(); i++) {
        if(s[i] != ' ') {
            result += s[i];
        }
    }
    return result;
}

string evaluate(Term* t) {
    if(t == NULL) return "";
    return "value";
}

int gettype(string token) {
    return symbols[token];
}

int lexicalanalyze(string& line, vector<SymtabEntry>& symtab) {
    string token = "";
    int type = "";
    SymtabEntry s;
    int i = 0;
    while(i < line.length()) {
        if(line[i] != ' ') token += line[i];
        else {
            if(token.length() > 0) {
                type = gettype(token);
                if(type) == 0) return -1;
                s.num = symtab.size()+1;
                s.type = type;
                s.val = token;
                symtab.push_back(s);
            }
        }
        i++;
    }
    if(token.length() > 0) {
        type = gettype(token);
        if(type) == 0) return -1;
        s.num = symtab.size()+1;
        s.type = type;
        s.val = token;
        symtab.push_back(s);
    }
    return 1;
}

int isTerm(vector<SymtabEntry>& symtab, int start) {
    return 1;
}

void interpret(string& line) {
    vector<SymtabEntry> symtab;
    Term* root = NULL;
    int status;
    string ans = "";
    status = lexicalanalyze(line, symtab);
    if(status == -1) {
        cout << "Error while building tokens" << endl;
        return;
    }
    status = isTerm(symtab, 0);
    if(status == -1) {
        cout << "Syntax Error found" << endl;
        return;
    }
    ans = evaluate(root);
    if(ans.length() == 0) {
        cout << "No output" << endl;
        return;
    } 
    cout << ans << endl;
}

