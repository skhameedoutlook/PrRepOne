#include "utilities.h"
#include "term.h"

Term* temp = NULL;

map<string, int> symbols;

bool isnv(Term* t) {
    if(t == NULL) return false;
    if(t->value.compare("0") == 0) return true;
    if(t->value.compare("succ") == 0) return isnv(static_cast<SuccTerm*>(t)->t);
    if(t->value.compare("pred") == 0) return isnv(static_cast<PredTerm*>(t)->t);
    return false;
}

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

string stripspaces(string s) {
    string result = "";
    for(int i = 0; i < s.length(); i++) {
        if(s[i] != ' ') {
            result += s[i];
        }
    }
    return result;
}

string makeproperstring(string s) {
    string result = "";
    if(s.length() == 0) return result;
    for(int i = 0; i < s.length(); i++) {
        if(i > 0 && s[i] == s[i-1] && s[i] == ' ') {
            continue;
        }

        result += s[i];
    }
    if(result[0] == ' ') result = result.substr(1, s.length()-1);

    if(result[result.length()-1] == ' ') result = result.substr(0, result.length()-1);

    return result;
}

string evaluate(Term* root) {

    if(root == NULL) return "";
    if(root->value.compare("0") == 0 || (root->value.compare("true") == 0) || (root->value.compare("false") == 0)) {

        return " "+root->value;
    }
    else if(root->value.compare("succ") == 0) {
        string s = evaluate(static_cast<SuccTerm*>(root)->t);
        string s2 = stripspaces(s);
        return " succ " + s;
    }
    else if(root->value.compare("specialop") == 0) {
        string s1 = evaluate(static_cast<SpecialOpTerm*>(root)->t1);
        if(stripspaces(s1).compare("true") == 0) {
            return evaluate(static_cast<SpecialOpTerm*>(root)->t2);
        }
        else if(stripspaces(s1).compare("false") == 0) {
            return evaluate(static_cast<SpecialOpTerm*>(root)->t3);
        }
        string s2 = evaluate(static_cast<SpecialOpTerm*>(root)->t2);
        string s3 = evaluate(static_cast<SpecialOpTerm*>(root)->t3);
        return  " if "+s1 + " then "+s2+" else "+s3;
        /* old code
        string t1value = evaluate(static_cast<SpecialOpTerm*>(root)->t1);

        string t2value = evaluate(static_cast<SpecialOpTerm*>(root)->t2);


        string t3value = evaluate(static_cast<SpecialOpTerm*>(root)->t3);

        if(t1value.compare(t2value) == 0) {
            return " false";
        }
        else {
            return " "+t3value;
        }
        */
    }
    else if(root->value.compare("pred") == 0) {
        string s = evaluate(static_cast<PredTerm*>(root)->t);
        string s2 = stripspaces(s);
        if(s2.compare("0") == 0) {
            return " 0";
        }
        if(s2.length() > 4 && s2.substr(0, 4).compare("succ") == 0) {
            int found = s.find("succ");
            if(!isnv(static_cast<PredTerm*>(root)->t)) {
                return " pred " + s;
            }
            s = s.substr(found+4, s.length()-(found+4));
            return s;
        }
        return " pred " + s;
    }
    else if(root->value.compare("iszero") == 0) {
        string s = evaluate(static_cast<IsZeroTerm*>(root)->t);
        string s2 = stripspaces(s);
        if(s2.compare("0") == 0) {
            return " true";
        }
        if(isnv(static_cast<IsZeroTerm*>(root)->t)) {
            return "false";
        }
        return " iszero " + s;
    }
    else if(root->value.compare("if-then-else") == 0) {
        string s1 = evaluate(static_cast<IfThenElseTerm*>(root)->t1);
        if(stripspaces(s1).compare("true") == 0) {
            return evaluate(static_cast<IfThenElseTerm*>(root)->t2);
        }
        else if(stripspaces(s1).compare("false") == 0) {
            return evaluate(static_cast<IfThenElseTerm*>(root)->t3);
        }
        string s2 = evaluate(static_cast<IfThenElseTerm*>(root)->t2);
        string s3 = evaluate(static_cast<IfThenElseTerm*>(root)->t3);
        return  " if "+s1 + " then "+s2+" else "+s3;
    }
    return "";
}

int lexicalanalyze(string& line, vector<SymtabEntry>& symtab) {
    string token = "";
    string type;
    SymtabEntry s;
    int i = 0;
    while(i < line.length()) {
        if(line[i] != ' ') token += line[i];
        else {
            if(token.length() > 0) {
                type = gettype(token);
                if(type.length() == 0) return -1;
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
        if(type.length() == 0) return -1;
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
    if(symtab[start].type.compare("true") == 0) {
        t = new TrueTerm();
        return start+1;
    }
    else if(symtab[start].type.compare("false") == 0) {
        t = new FalseTerm();
        return start+1;
    }
    else if(symtab[start].type.compare("zero") == 0) {
        t = new ZeroTerm();
        return start+1;
    }
    else if(symtab[start].type.compare("specialop") == 0) {
        t = new SpecialOpTerm();
        status = isTerm(symtab, start+1, static_cast<SpecialOpTerm*>(t)->t1);
        if(status == start+1) return -1;
        if(start >= symtab.size()) return -1;

        start = status;
        status = isTerm(symtab, start, static_cast<SpecialOpTerm*>(t)->t2);
        if(status == start) return -1;
        if(start >= symtab.size()) return -1;
        start = status;
        status = isTerm(symtab, start, static_cast<SpecialOpTerm*>(t)->t3);
        if(status == start) return -1;
        if(start >= symtab.size()) return -1;


        if(status == start) return -1;
        return status;
    }
    else if(symtab[start].type.compare("if") == 0) {
        t = new IfThenElseTerm();
        status = isTerm(symtab, start+1, static_cast<IfThenElseTerm*>(t)->t1);
        if(status == start+1) return -1;
        if(start >= symtab.size()) return -1;
        if(symtab[status].type.compare("then") != 0) return -1;
        start = status;
        status = isTerm(symtab, start+1, static_cast<IfThenElseTerm*>(t)->t2);
        if(status == start+1) return -1;
        if(start >= symtab.size()) return -1;
        if(symtab[status].type.compare("else") != 0) return -1;

        start = status;
        status = isTerm(symtab, start+1, static_cast<IfThenElseTerm*>(t)->t3);

        if(status == start+1) return -1;
        return status;
    }
    else if(symtab[start].type.compare("iszero") == 0) {
            t = new IsZeroTerm();
        status = isTerm(symtab, start+1, static_cast<IsZeroTerm*>(t)->t);
        if(status == start+1) return -1;
        return status;
    }
    else if(symtab[start].type.compare("pred") == 0) {
        t = new PredTerm();
        status = isTerm(symtab, start+1, static_cast<PredTerm*>(t)->t);
        if(status == start+1) return -1;
        return status;
    }
    else if(symtab[start].type.compare("succ") == 0) {
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
    /* Display symbol table
    for(int i = 0; i < symtab.size(); i++) {
        cout << symtab[i].type << " " << symtab[i].val << endl;
    }
    */
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
        cout <<"No output" << endl;
        return;
    }

    //cout << ans << " | " << endl;
    cout <<makeproperstring(ans) << endl;
}




