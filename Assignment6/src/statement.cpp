/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "simpio.h"
#include "parser.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

PrintStmt::PrintStmt(TokenScanner &scanner) {
    exp = readE(scanner, 0);
    if (scanner.hasMoreTokens()) {
        error("Extraneous token " + scanner.nextToken());
    }
}

PrintStmt::~PrintStmt() {
    delete exp;
}

void PrintStmt::execute(EvalState &state) {
    cout << exp->eval(state) << endl;
}

RemStmt::RemStmt(TokenScanner &scanner) {

}

void RemStmt::execute(EvalState &state) {

}

LetStmt::LetStmt(TokenScanner &scanner) {
    identifier = scanner.nextToken();
    op = scanner.nextToken();
    exp = readE(scanner, 0);
    if (scanner.hasMoreTokens()) {
        error("Extraneous token " + scanner.nextToken());
    }
}

LetStmt::~LetStmt() {
    delete exp;
}

void LetStmt::execute(EvalState &state) {
    int value = exp->eval(state);
    state.setValue(identifier, value);
}

InputStmt::InputStmt(TokenScanner &scanner) {
    identifier = scanner.nextToken();
    if (scanner.hasMoreTokens()) {
        error("Extraneous token " + scanner.nextToken());
    }
}

InputStmt::~InputStmt() {

}

void InputStmt::execute(EvalState &state) {
    int value = getInteger(" ? ");
    state.setValue(identifier, value);
}

GotoStmt::GotoStmt(TokenScanner &scanner) {
    lineNumber = stringToInteger(scanner.nextToken());
    if (scanner.hasMoreTokens()) {
        error("Extraneous token " + scanner.nextToken());
    }
}

GotoStmt::~GotoStmt() {

}

void GotoStmt::execute(EvalState &state) {
    state.setCurrentLine(lineNumber);
}

IfStmt::IfStmt(TokenScanner &scanner) {
    lhs = readE(scanner, 0);
    op = scanner.nextToken();
    rhs = readE(scanner, 0);
    if (scanner.nextToken() != "THEN") {
        error("Syntax error! Invalid IF statement!");
    }
    nextLine = stringToInteger(scanner.nextToken());
    if (scanner.hasMoreTokens()) {
        error("Extraneous token " + scanner.nextToken());
    }
}

IfStmt::~IfStmt() {
    delete lhs;
    delete rhs;
}

void IfStmt::execute(EvalState &state) {
    if (op == "=") {
        if (lhs->eval(state) == rhs->eval(state))
            state.setCurrentLine(nextLine);
    }
    else if (op == ">") {
        if (lhs->eval(state) > rhs->eval(state))
            state.setCurrentLine(nextLine);
    }
    else if (op == "<") {
        if (lhs->eval(state) < rhs->eval(state))
            state.setCurrentLine(nextLine);
    }
}

EndStmt::EndStmt(TokenScanner &scanner) {
    if (scanner.hasMoreTokens()) {
        error("Extraneous token " + scanner.nextToken());
    }
}

void EndStmt::execute(EvalState &state) {
    state.setCurrentLine(-1);
}
