#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int gettype(string token) {
    return symbols[token];
}

enum types {TRUE=1, FALSE=2, ZERO=3, IF=4, 
THEN=5, ELSE=6, ISZERO=7, PRED=8, 
SUCC=9, IFTHENELSE=10};

class Term {
public:
    string value;
    string type;
};

class TrueTerm:Term {
public:
    TrueTerm() {
        this->value = "true";
        this->type = symbols[value];
    }
};

class FalseTerm:Term {
public:
    FalseTerm() {
        this->value = "false";
        this->type = symbols[value];
    }
};

class ZeroTerm:Term {
public:
    ZeroTerm() {
        this->value = "0";
        this->type = symbols[value];
    }
};

class IfThenElseTerm:Term {
public:
    Term* t1;
    Term* t2;
    Term* t3;
    IfThenElseTerm(value) {
        this->value = "if-then-else";
        this->type = symbols[value];
    }
};

class IsZeroTerm:Term {
public:
    Term* t;
    IsZeroTerm() {
        this->value = "iszero";
        this->type = symbols[value];
    }
};

class PredTerm:Term {
public:
    Term* t;
    PredTerm() {
        this->value = "pred";
        this->type = symbols[value];
    }
};

class SuccTerm:Term {
public:
    Term* t;
    SuccTerm() {
        this->value = "succ";
        this->type = symbols[value];
    }
};