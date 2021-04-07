#include "term.h"

string gettype(string token) {
    if(token.compare("true") == 0) {
        return "true";
    }
    else if(token.compare("false") == 0) {
        return "false";
    }
    else if(token.compare("0") == 0) {
        return "zero";
    }
    else if(token.compare("if") == 0) {
        return "if";
    }
    else if(token.compare("then") == 0) {
        return "then";
    }
    else if(token.compare("else") == 0) {
        return "else";
    }
    else if(token.compare("iszero") == 0) {
        return "iszero";
    }
    else if(token.compare("pred") == 0) {
        return "pred";
    }
    else if(token.compare("succ") == 0) {
        return "succ";
    }
    return "";
}

TrueTerm::TrueTerm() {
    this->value = "true";
    this->type = gettype(value);
}

FalseTerm::FalseTerm() {
    this->value = "false";
    this->type = gettype(value);
}

ZeroTerm::ZeroTerm() {
    this->value = "0";
    this->type = gettype(value);
}

IfThenElseTerm::IfThenElseTerm() {
    this->value = "if-then-else";
    this->type = gettype(value);
    t1 = NULL;
    t2 = NULL;
    t3 = NULL;
}

IsZeroTerm::IsZeroTerm() {
    this->value = "iszero";
    this->type = gettype(value);
}

PredTerm::PredTerm() {
    this->value = "pred";
    this->type = gettype(value);
}

SuccTerm::SuccTerm() {
    this->value = "succ";
    this->type = gettype(value);
}

