/*
 * File: ListCompletions.cpp
 * -------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the cell phone mind-reading problem
 * from Assignment #3
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
using namespace std;

/* Constant */
const string alphabet = "abcdefghijklmnopqrstuvwxyz";

/* Function prototypes */

void listCompletions(string digits, Lexicon & lex);
void prefixToWord(string prefix, Lexicon & lex);
string digitLetters(char digit);
void recListCompletions(string rest, Lexicon & lex, string prefix);

/* Main program */

int main() {
   Lexicon english("EnglishWords.dat");
   cout << "Cell phone mind-reading problem" << endl;
   while (true) {
      cout << "Enter a set of digits: ";
      string digits = getLine();
      if (digits == "" || digits == "quit") break;
      cout << "The words beginning with those digits are:" << endl;
      listCompletions(digits, english);
   }
   return 0;
}

/*
 * Function: listCompletions
 * Usage: listCompletions(digits, lexicon);
 * ----------------------------------------
 * Lists all the words in the lexicon that begin with the letters
 * corresponding to the specified digits on a telephone keypad.
 */

void listCompletions(string digits, Lexicon & lexicon) {
   // [TODO: Complete the code]
   recListCompletions(digits, lexicon, "");
}


/*
 * Function: digitLetters
 * Usage: string letters = digitLetters(digits)
 * -------------------------------------------
 */

string digitLetters(char digit) {
    string letter;
    switch(digit) {
        case '2':
            letter = "abc";
            break;
        case '3':
            letter = "def";
            break;
        case '4':
            letter = "ghi";
            break;
        case '5':
            letter = "jkl";
            break;
        case '6':
            letter = "mno";
            break;
        case '7':
            letter = "pqrs";
            break;
        case '8':
            letter = "tuv";
            break;
        case '9':
            letter = "wxyz";
            break;
        default:
            break;
    }
    return letter;
}

/*
 * Function: recListCompletions
 * Usage: recListCompletions(rest, lex, prefix)
 * ----------------------------------------------
 * list completions recursively
 */

void recListCompletions(string rest, Lexicon & lex, string prefix) {
    if(rest.length() == 0)
        prefixToWord(prefix, lex);
    else {
        string options = digitLetters(rest[0]);
        for(int i = 0; i < options.length(); i++) {
            recListCompletions(rest.substr(1), lex, prefix + options[i]);
        }
    }
}

/*
 * Function: prefixToWord
 * Usage: prefixToWord(prefix, lex);
 * ----------------------------------------------
 * translate prefix to word recursively
 */

void prefixToWord(string prefix, Lexicon &lex) {
    if(lex.contains(prefix)) cout << prefix << endl;
        if(lex.containsPrefix(prefix)){
            for(int i = 0; i < alphabet.length(); i++) {
                prefixToWord(prefix + alphabet[i], lex);
            }
        }
}
