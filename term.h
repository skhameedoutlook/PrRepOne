#ifndef TERMS
#define TERMS

#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

const int TRUE=1, FALSE=2, ZERO=3, IF=4,
THEN=5, ELSE=6, ISZERO=7, PRED=8,
SUCC=9, IFTHENELSE=10;

string gettype(string token);

class Term {
public:
    string value;
    string type;
};

class TrueTerm: public Term {
public:
    TrueTerm();
};

class FalseTerm: public Term {
public:
    FalseTerm();
};

class ZeroTerm: public Term {
public:
    ZeroTerm();
};

class IfThenElseTerm: public Term {
public:
    Term* t1;
    Term* t2;
    Term* t3;
    IfThenElseTerm();
};

class IsZeroTerm: public Term {
public:
    Term* t;
    IsZeroTerm();
};

class PredTerm: public Term {
public:
    Term* t;
    PredTerm();
};

class SuccTerm: public Term {
public:
    Term* t;
    SuccTerm();
};

class SpecialOpTerm: public Term {
public:
    Term *t1;
    Term *t2;
    Term *t3;
    SpecialOpTerm();
};

#endif
