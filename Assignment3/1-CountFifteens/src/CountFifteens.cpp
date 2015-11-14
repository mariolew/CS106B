/*
 * File: CountFifteens.cpp
 * -----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter code for the CountFifteens problem from
 * Assignment #3.
 * [TODO: extend the documentation]
 */

#include <exception>
#include <iostream>
#include <string>
#include "card.h"
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "vector.h"
using namespace std;

/* Function prototypes */

int countFifteens(Vector<Card> & cards);
int countFifteensFromIndex(int amount, Vector<Card> & cards, int startIndex);

/*
 * Main program
 * ------------
 * This test program does no error-checking on the input.  One of the
 * extensions you might consider is adding code to this program (and
 * possibly to the Card class) to allow the program to report errors.
 */

int main() {
   while (true) {
      string line = getLine("Enter a hand of cards: ");
      if (line == "") break;
      TokenScanner scanner(line);
      scanner.ignoreWhitespace();
      int count = 0;
      Vector<Card> hand;
      while (scanner.hasMoreTokens()) {
         hand.add(Card(scanner.nextToken()));
         count++;
      }
      if(count != 5) {
          cout << "Please enter five cards again" << endl;
          continue;
      }
      int nWays = countFifteens(hand);
      string plural = (nWays == 1) ? "" : "s";
      cout << nWays << " way" << plural << endl;
   }
   return 0;
}

/*
 * Counts the number of ways of making a total of 15 from the vector of
 * cards.
 */

int countFifteens(Vector<Card> & cards) {
   // [TODO: Fill this in]
   return countFifteensFromIndex(15, cards, 0);
   return 0;
}

/*
 * Function: countFifteensFromIndex
 * Usage: int nWays = countFifteensFromIndex(cards, startIndex)
 * -----------------------------------------------------------
 */

int countFifteensFromIndex(int amount, Vector<Card> &cards, int startIndex) {
    if(amount == 0) return 1;
    if(cards.size() == startIndex) return 0;
    else {
        int value = cards[startIndex].getRank() > 9 ? 10:cards[startIndex].getRank();
        int withFirstCard = countFifteensFromIndex(amount - value, cards, startIndex + 1);
        int withoutFirstCard = countFifteensFromIndex(amount, cards, startIndex + 1);
        return withFirstCard + withoutFirstCard;
    }

}
