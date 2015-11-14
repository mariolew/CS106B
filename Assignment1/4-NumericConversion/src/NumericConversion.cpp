/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <cstring>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
   // [TODO: fill in the code]
   cout << stringToInt("-1987") << " " << intToString(-1982) << endl;
   return 0;
}
//learn to cast char to string, just use string() + ch
string intToString(int n){
    if(n == 0) return string() + '0';
    if(n < 0) {
        n *= -1;
        return '-' + intToString(n);
    }
    if(n >= 10) return intToString(n / 10) + (char)('0' + (n % 10));
    else return string() + (char)('0' + n);
}

int stringToInt(string str) {
    int len = str.length();
    if(len == 1) return str[0] - 48;
    if(str[0] == '-') return -1 * stringToInt(str.substr(1));
    return str[len - 1] - 48 + 10*stringToInt(str.substr(0, len - 1));
}

