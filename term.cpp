#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int TRUE=1, FALSE=2, ZERO=3, IF=4, 
THEN=5, ELSE=6, ISZERO=7, PRED=8, 
SUCC=9, IFTHENELSE=10;

map<string, int> symbols;

int gettype(string token) {
    return symbols[token];
}

class Term {
public:
    string value;
    string type;
};

class TrueTerm: public Term {
public:
    TrueTerm() {
        this->value = "true";
        this->type = symbols[value];
    }
};

class FalseTerm: public Term {
public:
    FalseTerm() {
        this->value = "false";
        this->type = symbols[value];
    }
};

class ZeroTerm: public Term {
public:
    ZeroTerm() {
        this->value = "0";
        this->type = symbols[value];
    }
};

class IfThenElseTerm: public Term {
public:
    Term* t1;
    Term* t2;
    Term* t3;
    IfThenElseTerm() {
        this->value = "if-then-else";
        this->type = symbols[value];
        t1 = NULL;
        t2 = NULL;
        t3 = NULL;
    }
};

class IsZeroTerm: public Term {
public:
    Term* t;
    IsZeroTerm() {
        this->value = "iszero";
        this->type = symbols[value];
    }
};

class PredTerm: public Term {
public:
    Term* t;
    PredTerm() {
        this->value = "pred";
        this->type = symbols[value];
    }
};

class SuccTerm: public Term {
public:
    Term* t;
    SuccTerm() {
        this->value = "succ";
        this->type = symbols[value];
    }
};