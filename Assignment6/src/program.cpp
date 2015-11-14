/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
   // Replace this stub with your own code
   initProgram();
}

Program::~Program() {
   // Replace this stub with your own code
    clear();
}

void Program::clear() {
   // Replace this stub with your own code
    SourceLine * cursor = head->next;
    while (cursor != NULL) {
        map.remove(cursor->lineNumber); //Can be removed since the map will take care of itself.
        SourceLine * follow = cursor->next;
        delete cursor->stmt;
        delete cursor;
        cursor = follow;
    }
    delete head;
    initProgram();
}

void Program::addSourceLine(int lineNumber, string line) {
   // Replace this stub with your own code
    SourceLine * cursor = head;
    SourceLine * follow = head->next;
    while (follow != NULL) {
        if (follow->lineNumber > lineNumber)
            break;
        cursor = follow;
        follow = follow->next;
    }
    if (cursor->lineNumber == lineNumber) {
        if (cursor->stmt != NULL) {
            delete cursor->stmt;
            cursor->stmt = NULL;
        }
        cursor->lineNumber = lineNumber;
        cursor->source = line;
    }
    else {
        SourceLine * newLine = new SourceLine;
        newLine->lineNumber = lineNumber;
        newLine->source = line;
        newLine->stmt = NULL;
        newLine->next = follow;
        cursor->next = newLine;
        map.add(lineNumber, newLine);
    }
}

void Program::removeSourceLine(int lineNumber) {
   // Replace this stub with your own code
    if (map.containsKey(lineNumber)) {
        map.remove(lineNumber);
        SourceLine * cursor = head;
        SourceLine * cp = cursor->next;
        while (cp->lineNumber != lineNumber) {
            cursor = cp;
            cp = cp->next;
        }
        cursor->next = cp->next;
        delete cp->stmt;
        delete cp;
    }
}

string Program::getSourceLine(int lineNumber) {
   if (map.containsKey(lineNumber)) {
       return map.get(lineNumber)->source;
   }
   return "";    // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   // Replace this stub with your own code
    if (!map.containsKey(lineNumber))
        error("setParsedStatement: No such line number.");
    SourceLine * cp = map.get(lineNumber);
    if (cp->stmt != NULL)
        delete cp->stmt;
    cp->stmt = stmt;
}

Statement *Program::getParsedStatement(int lineNumber) {
   if (map.containsKey(lineNumber)) {
       return map.get(lineNumber)->stmt;
   }
   return NULL;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
   if (head->next != NULL) {
       return head->next->lineNumber;
   }// Replace this stub with your own code
   return -1;
}

int Program::getNextLineNumber(int lineNumber) {
   SourceLine * cur = map.get(lineNumber)->next;
   if (cur != NULL) {
       return cur->lineNumber;     // Replace this stub with your own code
   }
   return -1;
}

void Program::initProgram() {
    head = new SourceLine;
    head->lineNumber = -1;
    head->stmt = NULL;
    head->next = NULL;
}
