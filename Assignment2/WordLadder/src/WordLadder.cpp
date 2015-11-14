/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
using namespace std;
Lexicon seen;
Lexicon english("EnglishWords.dat");
Vector<string> wordLadder(string &word, string &dest){
    Vector<string> ladder;
    seen.add(word);
    ladder.add(word);
    Queue<Vector<string> > ladderQueue;
    ladderQueue.add(ladder);
    while(!ladderQueue.isEmpty()){
        ladder = ladderQueue.dequeue();
        if(ladder[ladder.size()-1] == dest)
            return ladder;
        for(int i = 0; i < word.size(); i++){
            for(int j = 0; j < 26; j++){
                string newWord = ladder[ladder.size() - 1];
                newWord[i] = (char)('a' + j);
                if(!seen.contains(newWord) && english.contains(newWord)){
                    seen.add(newWord);
                    Vector<string> copyLadder = ladder;
                    copyLadder.add(newWord);
                    ladderQueue.add(copyLadder);
                }
            }
        }
    }
    cout << "No word-ladder can be found" << endl;
    ladder.clear();
    return ladder;
}

int main() {
	// [TODO: fill in the code]
    string word, dest;
    while(true){
        cout << "Enter start word (RETURN to quit): ";
        cin >> word; cout << endl;
        if(word == "RETURN") break;
        cout << "Enter destination word : ";
        cin >> dest; cout << endl;
        Vector<string> ladder = wordLadder(word, dest);
        if(ladder.isEmpty()) cout << "No ladder found" << endl;
        else{
            cout << "Found ladder: ";
            for(Vector<string>::iterator iter = ladder.begin(); iter != ladder.end(); ++iter)
                cout<< *iter << " ";
        }
        cout << endl;
    }
	return 0;
}
