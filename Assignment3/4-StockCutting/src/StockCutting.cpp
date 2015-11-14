/*
 * File: StockCutting.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter code for the stock-cutting problem
 * fron Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "vector.h"
#include "tokenscanner.h"
#include "strlib.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

int cutStock(Vector<int> & requests, int stockLength);
void cutStockRec(Vector<int> & requests, int stockLength, Vector<int> & pipes, int start, int &min);
void initRequests(Vector<int> & requests);
/* Main program */

int main() {
   // [TODO: Create a suitable test program]
   int stockLength;
   Vector<int> requests;
   while(true) {
       requests.clear();
       string line = getLine("Enter requests separated by spaces: ");
       if (line == "") break;
       TokenScanner scanner(line);
       scanner.ignoreWhitespace();
       while(scanner.hasMoreTokens()){
           string str = scanner.nextToken();
           int request = stringToInteger(str);
           requests.add(request);
       }
       string stock = getLine("Please enter the stock length: ");
       stockLength = stringToInteger(stock);
       int units = cutStock(requests, stockLength);
       cout << units << " pipes." << endl;
   }
   return 0;
}

/*
 * Function: cutStock
 * Usage: int units = cutStock(requests, stockLength);
 * ---------------------------------------------------
 * Computes the minimum number of stock pipes required to satisfy
 * the vector of requests of individual pieces.
 */

int cutStock(Vector<int> & requests, int stockLength) {
   // [TODO: Fill in the code]
   Vector<int> pipes;
   int min = stockLength;
   cutStockRec(requests, stockLength, pipes, 0, min);
   return min;
   return 0;
}

/*
 * Function: cutStockRec
 * Usage: cutStockRec(requests, stockLength, pipes, start, min);
 * ---------------------------------------------------
 * Computes the minimum number of stock pipes required to satisfy
 * the vector of requests of individual pieces recursively.
 */

void cutStockRec(Vector<int> & requests, int stockLength, Vector<int> &pipes, int start, int &min) {
    if(requests.size() == start) {
        int numPipes = pipes.size();
        if(min > numPipes)
            min = numPipes;
        return;
    }
    // If there is rest stock length, try all possible cases
    for(int i = 0; i < pipes.size(); i++) {
        if(pipes[i] + requests[start] <= stockLength) {
            pipes[i] += requests[start];
            cutStockRec(requests, stockLength, pipes, start + 1, min);
            pipes[i] -= requests[start];
        }
    }
    // Try case that use a new pipe
    pipes.add(requests[start]);
    cutStockRec(requests, stockLength, pipes, start + 1, min);
    pipes.remove(pipes.size() - 1);
}

/*
 * Function: initRequests
 * Usage: initRequests(requests)
 * -------------------------------
 * init the vector requests
 */
void initRequests(Vector<int> & requests) {
    /*cout << "Enter requests separated by spaces: ";
    while(true) {
        int request;
        cin >> request;
        if(request < 0) break;
        requests.add(request);
    }*/
    string line = getLine("Enter requests separated by spaces: ");
    if (line == "") return;
    TokenScanner scanner(line);
    scanner.ignoreWhitespace();
    while(scanner.hasMoreTokens()){
        string str = scanner.nextToken();
        int request = stringToInteger(str);
        requests.add(request);
    }
}
