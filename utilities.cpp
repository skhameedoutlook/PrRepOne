#include "term.cpp"

Term* temp = NULL;

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

int isTerm(vector<SymtabEntry>& symtab, int start, Term*& t) {
    if(start >= symtab.size()) return start;
    int status;
    if(symtab[start].type == TRUE) {
        t = new TrueTerm();
        return start+1;
    }
    else if(symtab[start].type == FALSE) {
        t = new FalseTerm();
        return start+1;
    }
    else if(symtab[start].type == ZERO) {
        t = new ZeroTerm();
        return start+1;
    }
    else if(symtab[start].type == IF) {
        t = new IfThenElseTerm();
        status = isTerm(symtab, start+1, static_cast<IfThenElseTerm*>(t)->t1);
        if(status == start+1) return -1;
        if(start >= symtab.size()) return -1;
        if(symtab[status].type != THEN) return -1;
        start = status;
        status = isTerm(symtab, start+1, static_cast<IfThenElseTerm*>(t)->t2);
        if(status == start+1) return -1;
        if(start >= symtab.size()) return -1;
        if(symtab[status].type != ELSE) return -1;
        
        start = status;
        status = isTerm(symtab, start+1, static_cast<IfThenElseTerm*>(t)->t3);
        
        if(status == start+1) return -1;
        return status;
    }
    else if(symtab[start].type == ISZERO) {
        t = new IsZeroTerm();
        status = isTerm(symtab, start+1, static_cast<IsZeroTerm*>(t)->t);
        if(status == start+1) return -1;
        return status;
    }
    else if(symtab[start].type == PRED) {
        t = new PredTerm();
        status = isTerm(symtab, start+1, static_cast<PredTerm*>(t)->t);
        if(status == start+1) return -1;
        return status;
    }
    else if(symtab[start].type == SUCC) {
        t = new SuccTerm();
        status = isTerm(symtab, start+1, static_cast<SuccTerm*>(t)->t);
        if(status == start+1) return -1;
        return status;
    }
    return -1;
}

void traverse(Term* root) {
    if(root == NULL)  return;
    cout << root->value << "->";
    if(root->value.compare("0") == 0 || (root->value.compare("true") == 0) || (root->value.compare("false") == 0)) {
        return;
    }
    else if(root->value.compare("succ") == 0) {
        traverse(static_cast<SuccTerm*>(root)->t);
    }
    else if(root->value.compare("pred") == 0) {
        traverse(static_cast<PredTerm*>(root)->t);
    }
    else if(root->value.compare("iszero") == 0) {
        traverse(static_cast<IsZeroTerm*>(root)->t);
    }
    else if(root->value.compare("if-then-else") == 0) {
        traverse(static_cast<IfThenElseTerm*>(root)->t1);
        traverse(static_cast<IfThenElseTerm*>(root)->t2);
        traverse(static_cast<IfThenElseTerm*>(root)->t3);
    }
}

void interpret(string& line) {
    vector<SymtabEntry> symtab;
    Term* root = NULL;
    temp = NULL;
    int status;
    string ans = "";
    status = lexicalanalyze(line, symtab);
    if(status == -1) {
        cout << "Error while building tokens" << endl;
        return;
    }
    status = isTerm(symtab, 0, root);
    if(status != symtab.size()) {
        cout << "Syntax Error found" << endl;
        return;
    }
    ans = evaluate(root);
    // cout<<"Traverse Start" << endl;
    // traverse(root);
    // cout<<"Traverse End" << endl;
    // cout << endl;
    if(ans.length() == 0) {
        cout <<line << " =  " <<"No output" << endl;
        return;
    } 
    cout <<line << ": " << ans << endl;
}

