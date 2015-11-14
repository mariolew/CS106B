/*
 * File: Obenglobish.java
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Obenglobish problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

/* Main program */
bool isVowel(char ch) {
    switch (ch) {
     case 'A': case 'E': case 'I': case 'O': case 'U':
     case 'a': case 'e': case 'i': case 'o': case 'u':
        return true;
     default:
        return false;
    }
}

int findFirstVowel(string word){
    for(int i = 0; i < word.length(); i++) {
        if(isVowel(word[i])) return i;
    }
    return -1;
}


string obenglobish(string word){
    int vp = findFirstVowel(word);
    if(vp == -1) return word;
    if((vp == word.length() - 1)) {
        if(word[vp] == 'e')return word;
        else return word.substr(0, vp) + "ob" + word[vp];
    }
    int vpr = 1;
    while(vp + vpr <word.length() && findFirstVowel(word.substr(vp + vpr)) == 0) {
        vpr ++;
    }
    //string s = word.substr(3, 4);
    //cout << s << " "<<word <<" "<<vp <<" "<<vpr<<endl;
    return word.substr(0, vp) + "ob" + word.substr(vp, vpr) + obenglobish(word.substr(vp + vpr));
}

int main() {
   // [TODO: fill in the code]
   while (true) {
       string word = getLine("Enter a word: ");
       if(word == "") break;
       string trans = obenglobish(word);
       cout << word << "->" << trans << endl;
   }
   return 0;
}
