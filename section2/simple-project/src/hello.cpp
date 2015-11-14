#include <iostream>
#include "hello.h"
#include "grid.h"
#include "console.h"
#include "queue.h"
#include "stack.h"
#include "map.h"
#include "error.h"
#include "strlib.h"
#include "lexicon.h"
using namespace std;

/* Function Prototypes */
void fixCounts(Grid<bool> & mines, Grid<int> & counts);
int countNearbyMines(int row, int col, Grid<bool> & mines);
void reverseQueue(Queue<string> & q);
Map<string,string> createMorseCodeMap();
Map<string,string> invertMap(const Map<string, string> & letter_map);
string letterToMorse(string line);
string morseToLetter(string line);
bool isPalindrome(string word);
void printPalindrome(Lexicon & dict);

/* CONSTANTS */
const Map<string, string> LETTER_MAP = createMorseCodeMap();
const Map<string, string> MORSE_MAP = invertMap(LETTER_MAP);

int main() {
    /* test prog for section2 problem1
    cout << "Hello, World!" << endl;
    const bool mine[] = {
      true, false, false, false, false, true,
        false, false, false, false, false, true,
        true, true, false, true, false, true,
        true, false, false, false, false, false,
        false, false, true, false, false, false,
        false, false, false, false, false, false

    };
    Grid<bool> mines(6, 6);
    for (int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            mines[i][j] = mine[i*6 + j ];
        }
    }
    Grid<int> counts;
    fixCounts(mines, counts);
    cout << counts.toString2D() << endl; */

    /* test prog for section2 problem3
    cout << "Morse letter translator" << endl;

    string line;
    while (true) {
        cout << "> ";
        getline(cin, line);
        if (line == "") break;
        if (line[0] == '.' || line[1] == '-') {
            cout << morseToLetter(line) << endl;
        }
        else {
            if((line[0] >= 'A' && line[0] <= 'Z') || \
                (line[0] >= 'a' && line[0] <= 'z')){
            cout << letterToMorse(line) << endl;
            }
            else {
                cout << "Invalid input, you should input letter or morse code only." << endl;
            }
        }
    } */

    Lexicon dict("EnglishWords.dat");
    printPalindrome(dict);
    return 0;
}


/*
 * Function fixCounts();
 * creates a grid of integers storing the number of mines in each neighborhood
 */
void fixCounts(Grid<bool> &mines, Grid<int> &counts) {
    int nRows = mines.numRows();
    int nCols = mines.numCols();
    counts.resize(nRows, nCols);
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            counts[i][j] = countNearbyMines(i, j, mines);
        }
    }
}

int countNearbyMines(int row, int col, Grid<bool> & mines) {
    int count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (mines.inBounds(row + i, col + j)) {
                if(mines[row + i][col + j])
                    count++;
            }
        }
    }
    return count;
}


void reverseQueue(Queue<string> & q) {
    Stack<string> s;
    while (!q.isEmpty()) {
        s.push(q.dequeue());
    }
    while(!s.isEmpty()) {
        q.enqueue(s.pop());
    }
}

Map<string, string> createMorseCodeMap() {
    Map<string,string> map;
    map["A"] = ".-";  map["J"] = ".---";  map["S"] = "...";
    map["B"] = "-...";  map["K"] = "-.-";  map["T"] = "-";
    map["C"] = "-.-.";  map["L"] = ".-..";  map["U"] = "..-";
    map["D"] = "-..";  map["M"] = "--";  map["V"] = "...-";
    map["E"] = ".";  map["N"] = "-.";  map["W"] = ".--";
    map["F"] = "..-.";  map["O"] = "---";  map["X"] = "-..-";
    map["G"] = "--.";  map["P"] = ".--.";  map["Y"] = "-.--";
    map["H"] = "....";  map["Q"] = "--.-";  map["Z"] = "--..";
    map["I"] = "..";  map["R"] = ".-.";
    return map;
}

Map<string, string> invertMap(const Map<string, string> &letter_map) {
    Map<string, string> morse_map;
    for (string key : letter_map) {
        string value = letter_map.get(key);
        if (letter_map.containsKey(value)) {
            error("Invalid map!");
        }
        morse_map[value] = key;
    }
    return morse_map;
}

string letterToMorse(string line) {
    string morse;
    for (int i = 0; i < line.length(); i++) {
        string letter = toUpperCase(line.substr(i,1));
        if (LETTER_MAP.containsKey(letter)) {
            if (!morse.empty()) morse += " ";
            morse += LETTER_MAP.get(letter);
        }
    }
    return morse;
}

string morseToLetter(string line) {
    line += " ";
    string letter;
    string morse;
    for (int i = 0; i < line.length(); i++) {
        char ch = line[i];
        if (ch == '.' || ch == '-')
            morse += ch;
        else if (ch == ' ') {
            if (MORSE_MAP.containsKey(morse))
                letter += MORSE_MAP.get(morse);
            else {
                letter += '?';
            }
            morse.clear();
        }
    }
    return letter;
}




bool isPalindrome(string word) {
    int len = word.length();
    if (len <= 1)
        return true;
    else {
        return word[0] == word[len - 1] && isPalindrome(word.substr(1, len - 2));
    }
}

void printPalindrome(Lexicon & dict) {
    for (string word : dict) {
        if (isPalindrome(word))
            cout << word << endl;
    }
}
