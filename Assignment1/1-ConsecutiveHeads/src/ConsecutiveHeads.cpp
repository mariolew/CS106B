/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the coin-flipping problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
using namespace std;

int main() {
   // [TODO: fill in the code]
   int cnt = 0;
   //bool prev = true;
   int num = 0;
   while(cnt < 3){
       if(randomChance(0.5)) {
           cout << "heads" << endl;
           cnt++;
       }
       else {
           cout << "tails" <<endl;
           //prev = false;
           cnt = 0;
       }
       num++;
   }
   cout << "It tooks " << num << " flips to get 3 consecutive heads" <<endl;
   return 0;
}
