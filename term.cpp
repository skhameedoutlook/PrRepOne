#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class Term {
public:
    string value;
    string type;
};

class TrueTerm:Term {
public:
    TrueTerm() {

    }
};

class FalseTerm:Term {
public:
    FalseTerm() {

    }
};

class ZeroTerm:Term {
public:
    ZeroTerm() {

    }
};

class IfThenElseTerm:Term {
public:
    IfThenElseTerm() {

    }
};

class IsZeroTerm:Term {
public:
    IsZeroTerm() {

    }
};

class PredTerm:Term {
public:
    PredTerm() {

    }
};

class SuccTerm:Term {
public:
    SuccTerm() {

    }
};