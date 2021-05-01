#ifndef UTILITIES
#define UTILITIES

#include "term.h"

bool isnv(Term* t);

void initSymbols();

struct SymtabEntry {
    int num;
    string val;
    string type;
};

string stripspaces(string s);
string makeproperstring(string s);

string evaluate(Term* root);

int lexicalanalyze(string& line, vector<SymtabEntry>& symtab);
int isTerm(vector<SymtabEntry>& symtab, int start, Term*& t);

void traverse(Term* root);

void interpret(string& line);

string isTypeSafe(Term* root, vector<string>& typestack);

#endif
