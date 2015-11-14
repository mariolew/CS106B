/*
 * File: PQTest.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This is the starter file for the test program for Assignment #5.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "pqueue.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "tokenscanner.h"
using namespace std;

/* Function prototypes */

void helpCommand();
int makeChoice(string command);
void list(PriorityQueue & pq);
/* Main program */

int main() {
   PriorityQueue pq;
   while (true) {
      string cmd = getLine("> ");
//      if (cmd == "help") {
//         helpCommand();
//      } else {
//         cout << "Undefined command: " << cmd << endl;
//      }
      Vector<string> cmdVec;
      TokenScanner scanner(cmd);
      scanner.ignoreWhitespace();
      while (scanner.hasMoreTokens()) {
          cmdVec.add(scanner.nextToken());
      }
      string command = cmdVec[0];
      int choice = makeChoice(command);
      switch (choice) {
          case 0:
              helpCommand();
              break;
          case 1:
              //cout << cmdVec[1] << stringToDouble(cmdVec[2]) << endl;
              pq.enqueue(cmdVec[1], stringToDouble(cmdVec[2]));
              break;
          case 2:
              cout << pq.dequeue() << endl;
              break;
          case 3:
              cout << pq.peek() << endl;
              break;
          case 4:
              cout << pq.peekPriority() << endl;
              break;
          case 5:
              pq.clear();
              break;
          case 6:
              cout << pq.size() << endl;
              break;
          case 7:
              if (pq.isEmpty()) cout << "True" << endl;
              else cout << "False" << endl;
              break;
          case 8:
              list(pq);
              break;
          case 9:
             return 0;
             break;
          default:
              cout << "Undefined command: " << command << endl;
              break;
      }
   }
   return 0;
}

/*
 * Function: helpCommand
 * ---------------------
 * Displays a list of the required commands.  If you extend this program,
 * you should add new entries to this function.
 */

void helpCommand() {
   cout << "enqueue value priority -- Enqueues value at priority" << endl;
   cout << "dequeue -- Dequeues the most urgent item" << endl;
   cout << "peek -- Peeks at the first item without removing it" << endl;
   cout << "peekPriority -- Reports the priority of the first item" << endl;
   cout << "clear -- Clears the queue" << endl;
   cout << "size -- Reports the size of the queue" << endl;
   cout << "isEmpty -- Reports whether the queue is empty" << endl;
   cout << "list -- Lists the elements of the queue" << endl;
   cout << "help -- Prints this message" << endl;
   cout << "quit -- Quit the program" << endl;
}


int makeChoice(string command) {
    if (command == "help") return 0;
    if (command == "enqueue") return 1;
    if (command == "dequeue") return 2;
    if (command == "peek") return 3;
    if (command == "peekPriority") return 4;
    if (command == "clear") return 5;
    if (command == "size") return 6;
    if (command == "isEmpty") return 7;
    if (command == "list") return 8;
    if (command == "quit") return 9;
    return -1;
}

void list(PriorityQueue & pq) {
    PriorityQueue cp = pq;
   // cout << cp.dequeue() << endl;
    while (!cp.isEmpty()) {
        cout << cp.dequeue() << " ";
    }
    cout << endl;
}
