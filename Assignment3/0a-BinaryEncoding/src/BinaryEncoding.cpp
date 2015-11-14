/*
 * File: BinaryEncoding.cpp
 * ------------------------
 * Starter file for the binary encoding problem on Assignment #3.
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "error.h"
using namespace std;

/* Function prototypes */

void generateBinaryCode(int nBits);
void generateBinaryCodePrefix(int nBits, string prefix);

/* Main program */

int main() {
   int nBits = getInteger("Number of bits: ");
   generateBinaryCode(nBits);
   return 0;
}

/*
 * Function: generateBinaryCode
 * Usage: generateBinaryCode(nBits);
 * ---------------------------------
 * Lists all the binary values containing the specified number of bits.
 */

void generateBinaryCode(int nBits) {
   // Fill this in
   if(nBits <= 0) error("Number of bits must be greater than zero");
   generateBinaryCodePrefix(nBits, "");
}

/*
 * Function: generateBinaryCodePrefix
 * Usage: generateBinaryCodePrefix(nBits, prefix)
 * ------------------------------------------------
 * Lists all the binary values recursively using prefix
 * */

void generateBinaryCodePrefix(int nBits, string prefix) {
    if(nBits == 0)
        cout << prefix << endl;
    else {
        generateBinaryCodePrefix(nBits - 1, prefix + '0');
        generateBinaryCodePrefix(nBits - 1, prefix + '1');
    }
}
