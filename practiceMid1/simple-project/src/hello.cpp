#include <iostream>
#include "hello.h"
#include "console.h"
#include "stack.h"
#include "vector.h"
#include "map.h"
#include "lexicon.h"
#include "error.h"
using namespace std;


struct Domino{
    int leftDots;
    int rightDots;
};

/* Function Prototypes */

void roll(Stack<char> & s, int n, int k);
Vector<string> generateCompletions(string digits, Lexicon & lex,
Map<string, Vector<string> > & cache);
bool matchDightsWord(string digits, string word);
int raiseIntToPower(int n, int k);
bool formsDominoChain(Vector<Domino> & dominos);
bool formsDominoChainRec(Vector<Domino> & dominos, int lastDot);

int main() {
    cout << "Hello, World!" << endl;
    /* test prog for mid problem 4
    int n = 2, k = 4;
    cout << n << "^" << k << " " << endl;
    cout << raiseIntToPower(n, k) << endl; */
    int leftDot;
    int rightDot;
    Vector<Domino> dominos;
    while (true) {
        cout << "Please input a domino" << endl;
        cout << "Left dot: ";
        cin >> leftDot;
        cout << "Right dot: ";
        cin >> rightDot;
        if (leftDot < 1 || rightDot < 1) break;
        Domino domino;
        domino.leftDots = leftDot;
        domino.rightDots = rightDot;
        dominos.add(domino);
    }
    if (formsDominoChain(dominos)) {
        cout << "Can form a domino chain." << endl;
    }
    return 0;
}




void roll(Stack<char> & s, int n, int k) {
    if (n < 0 || k < 0 || n > s.size())
        error("roll: argument out of range");
    else {
//        Queue<char> top_n;
//        Stack<char> tmp;
//        for (int i = 0; i < n; i++) {
//            top_n.enqueue(s.pop());
//        }
//        for (int j = 0; j < k; i++) {
//            char first = top_n.dequeue();
//            top_n.enqueue(first);
//        }
//        while (!top_n.isEmpty()) {
//            tmp.push(top_n.dequeue());
//        }
//        while (!tmp.isEmpty()) {
//            s.push(tmp.pop());
//        }
        Vector<char> top_n;
        for (int i = 0; i < n; i++) {
            top_n.add(s.pop());
        }
        for (int i = n - 1; i >= 0; i--) {
            s.push(top_n[(i + k) % n]);
        }
    }
}


Vector<string> generateCompletions(string digits, Lexicon & lex,
Map<string, Vector<string> > & cache) {
    if (cache.containsKey(digits)) return cache.get(digits);
    Vector<string> dict;
    for (string word : lex) {
        if (matchDightsWord(digits, word)) {
            dict.add(word);
        }
    }
    cache[digits] = dict;
    return dict;
}


bool matchDightsWord(string digits, string word) {
    if (digits.length() > word.length()) return false;
    string all_digits = "22233344455566677778889999";
    for (int i = 0; i < digits.length(); i++) {
        char digit = all_digits[word[i] - 'a'];
        if (digit != digits[i]) return false;
    }
    return true;
}


int raiseIntToPower(int n, int k) {
    if (k == 0) return 1;
    else {
        int num = raiseIntToPower(n, k / 2);
        int result = num * num;
        if (k % 2 ==1)
            result *= n;
        return result;
    }
}

bool formsDominoChain(Vector<Domino> & dominos) {
    return formsDominoChainRec(dominos, -1);
}

bool formsDominoChainRec(Vector<Domino> & dominos, int lastDot) {
    if (dominos.isEmpty()) return true;
    else {

        for (int i = 0; i < dominos.size(); i++) {
            Vector<Domino> rest = dominos;
            rest.remove(i);
            if (lastDot == -1 || dominos[i].leftDots == lastDot) {
                if (formsDominoChainRec(rest, dominos[i].rightDots)) return true;
            }
            if (lastDot == -1 || dominos[i].rightDots == lastDot) {
                if (formsDominoChainRec(rest, dominos[i].leftDots)) return true;
            }
        }
    }
    return false;
}
