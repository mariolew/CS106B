/*
 * File: KarelGoesHome.cpp
 * -----------------------
 * Starter file for the KarelGoesHome problem.
 */

#include <iostream>
#include <iomanip>
#include "console.h"
using namespace std;

/* Constants about maps */

const int GRID_SIZE = 6;
const int FIELD_SIZE = 6;

/* Function prototypes */

int countPaths(int street, int avenue);

/* Main program */

int main() {
   // [Fill this in with a test program]
   for(int street = GRID_SIZE; street > 0; street--) {
       for(int avenue = 1; avenue <= GRID_SIZE; avenue++) {
           cout << right << setw(FIELD_SIZE) << countPaths(street, avenue);
       }
       cout << endl;
   }
   return 0;
}

/*
 * Function: countPaths
 * Usage: int nPaths = countPaths(street, avenue);
 * -----------------------------------------------
 * Counts the paths from a particular street/avenue position in
 * Karel's world to the origin, subject to the restriction that
 * Karel can move only west and south.
 */

int countPaths(int street, int avenue) {
   // [Fill this in]
   if(street == 1 || avenue == 1)
       return 1;
   return countPaths(street - 1, avenue) + countPaths(street, avenue - 1);
}
