/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "console.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);
void runProgram(Program & program, EvalState & state);
void dspHelp();
void listCmd(Program & program);

/* Main program */

int main() {
   EvalState state;
   Program program;
   cout << "Simple implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
//   Expression *exp = parseExp(scanner);
//   int value = exp->eval(state);
//   cout << value << endl;
//   delete exp;
   if (!scanner.hasMoreTokens()) {
       return;
   }
   string firstToken = toUpperCase(scanner.nextToken());
   if (firstToken == "RUN") {
       runProgram(program, state);
   }
   else if (firstToken == "QUIT") {
       exit(0);
   }
   else if (firstToken == "HELP") {
       dspHelp();
   }
   else if (firstToken == "CLEAR") {
       program.clear();
   }
   else if (firstToken == "LIST") {
       listCmd(program);
   }
   else if (firstToken == "INPUT" || firstToken == "PRINT" || firstToken == "LET") {
       scanner.saveToken(firstToken);
       Statement * stmt = parseStatement(scanner);
       stmt->execute(state);
       delete stmt;
   }
   else {
       int lineNumber = stringToInteger(firstToken);
       if (!scanner.hasMoreTokens()) {
           program.removeSourceLine(lineNumber);
       }
       else {
           int length = firstToken.length();
           string source = line.substr(length);
           program.addSourceLine(lineNumber, source);
           Statement * stmt = parseStatement(scanner);
           program.setParsedStatement(lineNumber, stmt);
       }
   }
}

void runProgram(Program & program, EvalState & state) {
    int lineNumber = program.getFirstLineNumber();
    while (lineNumber != -1) {
        Statement * stmt = program.getParsedStatement(lineNumber);
        state.setCurrentLine(program.getNextLineNumber(lineNumber));
        stmt->execute(state);
        lineNumber = state.getCurrentLine();
    }
}

void dspHelp() {
    cout << "List of command:" << endl;
    cout << "  HELP - Display help (this menu) (D)" << endl;
    cout << "  RUN - Run the program (D)" << endl;
    cout << "  CLEAR - Clear the program lines (D)" << endl;
    cout << "  QUIT - Exit, all data lost (D)" << endl;
    cout << "  LIST - Display program (D)" << endl;
    cout << "  PRINT - Display statement (D)(P)" << endl;
    cout << "  LET - Assign statement (D)(P)" << endl;
    cout << "  INPUT - Get integer statement (D)(P)" << endl;
    cout << "  GOTO n - Move to line n (P)" << endl;
    cout << "  IF stmt (comp) stmt THEN n - Compare and go to line n (P)" << endl;
    cout << "  END - Stop execution (optional at the end) (P)" << endl;
    cout << "  REM - Comment line, do not trigger anything (P)" << endl;
    cout << "(D) = direct mode / (P) = program mode" << endl;
}

void listCmd(Program & program) {
    int lineNumber = program.getFirstLineNumber();
    if (lineNumber == -1) {
        cout << "Empty program!" << endl;
    }
    else {
        while (lineNumber != -1) {
            string line = program.getSourceLine(lineNumber);
            cout << lineNumber << line << endl;
            lineNumber = program.getNextLineNumber(lineNumber);
        }
    }
}
