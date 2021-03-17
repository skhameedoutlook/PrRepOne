#include "term.cpp"

void initSymbols() {
    symbols["true"] = TRUE;
    symbols["false"] = FALSE;
    symbols["0"] = ZERO;
    symbols["if"] = IF;
    symbols["then"] = THEN;
    symbols["else"] = ELSE;
    symbols["iszero"] = ISZERO;
    symbols["pred"] = PRED;
    symbols["succ"] = SUCC;
    symbols["if-then-else"] = IFTHENELSE;
}

struct SymtabEntry {
    int num;
    string val;
    int type;
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

int lexicalanalyze(string& line, vector<SymtabEntry>& symtab) {
    string token = "";
    int type;
    SymtabEntry s;
    int i = 0;
    while(i < line.length()) {
        if(line[i] != ' ') token += line[i];
        else {
            if(token.length() > 0) {
                type = gettype(token);
                if(type == 0) return -1;
                s.num = symtab.size()+1;
                s.type = type;
                s.val = token;
                symtab.push_back(s);
                token = "";
            }
        }
        i++;
    }
    if(token.length() > 0) {
        type = gettype(token);
        if(type == 0) return -1;
        s.num = symtab.size()+1;
        s.type = type;
        s.val = token;
        symtab.push_back(s);
        token = "";
    }
    return 1;
}

int isTerm(vector<SymtabEntry>& symtab, int start, Term* t) {
    if(start >= symtab.size()) return start;
    int status;
    if(symtab[start].type == TRUE) {
        return start+1;
    }
    else if(symtab[start].type == FALSE) {
        return start+1;
    }
    else if(symtab[start].type == ZERO) {
        return start+1;
    }
    else if(symtab[start].type == IF) {
        
        status = isTerm(symtab, start+1, t);
        
        if(status == start+1) return -1;
        if(start >= symtab.size()) return -1;
        if(symtab[status].type != THEN) return -1;
        
        start = status;
        status = isTerm(symtab, start+1, t);
        
        if(status == start+1) return -1;
        if(start >= symtab.size()) return -1;
        if(symtab[status].type != ELSE) return -1;
        
        start = status;
        status = isTerm(symtab, start+1, t);
        
        if(status == start+1) return -1;
        return status;
    }
    else if(symtab[start].type == ISZERO) {
        status = isTerm(symtab, start+1, t);
        if(status == start+1) return -1;
        return status;
    }
    else if(symtab[start].type == PRED) {
        status = isTerm(symtab, start+1, t);
        if(status == start+1) return -1;
        return status;
    }
    else if(symtab[start].type == SUCC) {
        status = isTerm(symtab, start+1, t);
        if(status == start+1) return -1;
        return status;
    }
    else if(symtab[start].type == FALSE) {
        status = isTerm(symtab, start+1, t);
        if(status == start+1) return -1;
        return status;
    }
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

    status = isTerm(symtab, 0, root);
    cout << status << endl;
    if(status != symtab.size()) {
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

