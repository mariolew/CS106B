#include <iostream>
#include <fstream>
#include "hello.h"
#include "console.h"
#include "exp.h"
#include "parser.h"
#include "simpio.h"
using namespace std;

string convertToRPN(Expression * exp);
Expression * foldConstants(Expression * exp);
void compile(istream & infile, ostream & outfile);
void compileExp(Expression * exp, ostream & outfile);
string operatorToString(string op);

int main() {
    /* cout << "This program convert expressions to RPN." << endl;
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    while (true) {
        string line = getLine("=> ");
        scanner.setInput(line);
        if (line == "quit") break;
        Expression * exp = parseExp(scanner);
        cout << convertToRPN(exp) << endl;
        delete exp;
    }*/
    ifstream infile;
    infile.open("file.txt");
    if (infile.fail()) cout << "fail" << endl;
    ofstream outfile("D:\\out.txt");
    //outfile.put('d');
    //outfile <<"dd" << endl;
    compile(infile, outfile);
    infile.close();
    outfile.close();
    return 0;
}

string convertToRPN(Expression * exp) {
    if (exp->getType() == COMPOUND) {
        string op = ((CompoundExp *)exp)->getOp();
        Expression * lhs = ((CompoundExp *)exp)->getLHS();
        Expression * rhs = ((CompoundExp *)exp)->getRHS();
        return convertToRPN(lhs) + ' ' + convertToRPN(rhs) + ' ' + op;
    }
    else {
        return exp->toString();
    }
}

Expression * foldConstants(Expression * exp) {
    EvalState state;
    if (exp->getType() == CONSTANT) {
        return new ConstantExp(exp->eval(state));
    }
    else if (exp->getType() == IDENTIFIER) {
        return new IdentifierExp(((IdentifierExp *) exp)->getName());
    }
    else {
        Expression * lhs = ((CompoundExp *)exp)->getLHS();
        Expression * rhs = ((CompoundExp *)exp)->getRHS();
        if (lhs->getType() == CONSTANT && rhs->getType() == CONSTANT) {
            int value = exp->eval(state);
            delete lhs;
            delete rhs;
            return new ConstantExp(value);
        }
        else {
            string op = ((CompoundExp *)exp)->getOp();
            return new CompoundExp(op, lhs, rhs);
        }
    }
}

void compile(istream & infile, ostream & outfile) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(infile);
    while (scanner.hasMoreTokens()) {
        //string token = scanner.nextToken();
        //cout << token << endl;
        //scanner.saveToken(token);
        Expression * exp = readE(scanner, 0);
        compileExp(exp, outfile);
        outfile << "DISPLAY" << endl;
    }
}

void compileExp(Expression *exp, ostream &outfile) {
    ExpressionType type = exp->getType();
    if (type == CONSTANT) {
        outfile << "LOAD #" << exp->toString() << endl;
    }
    else if (type == IDENTIFIER) {
        outfile << "LOAD " << exp->toString() << endl;
    }
    else {
        Expression * lhs = ((CompoundExp *)exp)->getLHS();
        Expression * rhs = ((CompoundExp *)exp)->getRHS();
        string op = ((CompoundExp *)exp)->getOp();
        if (op == "=") {
            compileExp(rhs, outfile);
            outfile << "STORE " << ((IdentifierExp *)lhs)->getName() << endl;
        }
        else {
            compileExp(lhs, outfile);
            compileExp(rhs, outfile);
            outfile << operatorToString(op) << endl;
        }
    }
}


string operatorToString(string op) {
    if (op == "*") return "MUL";
    if (op == "+") return "ADD";
    if (op == "/") return "DIV";
    if (op == "-") return "SUB";
    else return "";
}
