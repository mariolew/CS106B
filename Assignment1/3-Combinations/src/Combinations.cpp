/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the recursive combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include <assert.h>
using namespace std;
int combination(int n, int k) {
    if(k > n) {cout << "k shouldn't be greater than n" <<endl; exit(0);}
    if(n == k || k == 0) return 1;
    return combination(n - 1, k - 1) + combination(n - 1, k);
}

int main() {
   // [TODO: fill in the code]
   for(int i = 0; i < 10; i++){
       for(int k = 0; k < 10 - i; k++)
           cout << " ";
       for(int j = 0; j < i + 1; j++) {
           if(j != i){
               if(combination(i, j + 1) > 9) cout << combination(i, j) << " ";
               else cout << combination(i, j) << "  ";
           }
           else cout << combination(i, j) << "  ";
       }
       cout << endl;
   }
   return 0;
}
