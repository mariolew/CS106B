/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */
 
#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
#include "strlib.h"
#include "set.h"
#include "foreach.h"
using namespace std;

/* Structs */
struct Cube {
    int row;
    int col;
};

/* Constants */
const int BOARD_SIZE = 4;
const int BIG_BOARD_SIZE = 5;
const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
Grid<char> boggleSetup();
bool userInput();
Vector<string> userInputCubes();
Vector<string> stringToVector(string &str);//
Vector<string> stringArrayToVector(const string cubes[], int board_size);//
void shuffle(Vector<string> &cubes);//
void fillBoggle(Vector<string> &cubes, Grid<char> &board);//
char chooseRandomFace(string cube);
void drawBoggle(Grid<char> &board);//
Lexicon humanTurn(Grid<char> &board, Lexicon &dict);
bool findWordOnBoard(string word, Grid<char> &board);
bool findWordPath(string word, Grid<char> &board, Cube cube, Vector<Cube> &word_path);
void highlightBoard(Vector<Cube> &word_path);
Vector<Cube> findNextCube(Cube cube, Vector<Cube> &word_path, Grid<char> &board);
bool contain_cube(Vector<Cube> &word_path, Cube next_cube);
bool cubeInBound(Cube next_cube, Grid<char> &board);
void computerTurn(Lexicon &dict, Lexicon &used_words, Grid<char> &board);
void findAllWords(string prefix, Lexicon &dict, Lexicon &used_words, Grid<char> &board,
                  Cube cube, Vector<Cube> &word_path);
void playBoggle(GWindow &gw);

/* Main program */

int main() {
   GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
   initGBoggle(gw);
   welcome();
   giveInstructions();
   /*Grid<char> board = boggleSetup();
   Lexicon dict("EnglishWords.dat");
   //if(dict.contains("apple")) cout<<"haha"<<endl;
   Lexicon used_words = humanTurn(board, dict);
   computerTurn(dict, used_words, board);*/
   playBoggle();
   getLine();
   return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
   cout << "Welcome!  You're about to play an intense game ";
   cout << "of mind-numbing Boggle.  The good news is that ";
   cout << "you might improve your vocabulary a bit.  The ";
   cout << "bad news is that you're probably going to lose ";
   cout << "miserably to this little dictionary-toting hunk ";
   cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
   cout << endl;
   cout << "The boggle board is a grid onto which I ";
   cout << "I will randomly distribute cubes. These ";
   cout << "6-sided cubes have letters rather than ";
   cout << "numbers on the faces, creating a grid of ";
   cout << "letters on which you try to form words. ";
   cout << "You go first, entering all the words you can ";
   cout << "find that are formed by tracing adjoining ";
   cout << "letters. Two letters adjoin if they are next ";
   cout << "to each other horizontally, vertically, or ";
   cout << "diagonally. A letter can only be used once ";
   cout << "in each word. Words must be at least four ";
   cout << "letters long and can be counted only once. ";
   cout << "You score points based on word length: a ";
   cout << "4-letter word is worth 1 point, 5-letters ";
   cout << "earn 2 points, and so on. After your puny ";
   cout << "brain is exhausted, I, the supercomputer, ";
   cout << "will find all the remaining words and double ";
   cout << "or triple your paltry score." << endl << endl;
   cout << "Hit return when you're ready...";
   getLine();
}

// [TODO: Fill in the rest of the code]
/*
 * Function: boggleSetup
 * Usage: Grid<char> board = boggleSetup();
 * -----------------------------------------
 * Cube setup, board drawing, cube shaking
 */

Grid<char> boggleSetup() {
    // TODO: to be changeable
    drawBoard(4, 4);
    // using data structures like below for cube and board
    Vector<string> cubes;
    Grid<char> board(4, 4);
    bool user_input = userInput();
    if(user_input) {
        cubes = userInputCubes();
    }
    else {
        cubes = stringArrayToVector(STANDARD_CUBES, BOARD_SIZE);
        shuffle(cubes);
    }
    fillBoggle(cubes, board);
    drawBoggle(board);
    return board;
}

/*
 * Function: userInput
 * Usage: bool user_input = userInput();
 * -----------------------------------------
 * Get whether user input for the board
 */

bool userInput() {
    bool force_input = false;
    while(true) {
        string response = getLine("User input or not? (y/n) ");
        response = toLowerCase(response);
        if(response == "y" || response == "yes") {
            force_input = true;
            break;
        }
        if(response == "n" || response == "no") {
            break;
        }
    }
    return force_input;
}

/*
 * Function: userInputCubes
 * Usage: cubes = userInputCubes();
 * -----------------------------------------
 * Get user input as cubes
 */

Vector<string> userInputCubes() {
    Vector<string> cubes;
    string letters;
    while(true) {
        cout << "Please enter a " << BOARD_SIZE * BOARD_SIZE << " long string as cubes: ";
        letters = getLine();
        if(letters.length() >= BOARD_SIZE * BOARD_SIZE) {
            break;
        }
        cout << "Invalid cube length. Try again! :)" << endl;
    }
    letters = toUpperCase(letters.substr(0, 16));
    cubes = stringToVector(letters);
    return cubes;
}

/*
 * Function: stringArrayToVector
 * Usage: cube_vec = stringArrayToVector(cubes, board_size);
 * -----------------------------------------
 * convert the default string array into vector
 */

Vector<string> stringArrayToVector(const string cubes[], int board_size) {
    Vector<string> cube_vec;
    for(int i = 0; i < board_size * board_size; i++) {
        cube_vec.add(cubes[i]);
    }
    return cube_vec;
}

/*
 * Function: stringToVector
 * Usage: cube_vec = stringToVector(str);
 * -----------------------------------------
 * convert the user input string into vector
 */

Vector<string> stringToVector(string &str) {
    Vector<string> cube_vec;
    for(int i = 0; i < str.length(); i++) {
        cube_vec.add(str.substr(i, 1));
    }
    return cube_vec;
}

/*
 * Function: shuffle
 * Usage: shuffle(cubes);
 * -----------------------------------------
 * shake the cubes to make the game a bit random
 */

void shuffle(Vector<string> &cubes) {
    for(int i = 0; i < cubes.size(); i++) {
        int r = randomInteger(i, cubes.size()-1);
        string temp = cubes[i];
        cubes[i] = cubes[r];
        cubes[r] = temp;
    }
}

/*
 * Function: fillBoggle
 * Usage: fillBoggle(cubes, board);
 * -----------------------------------------
 * fill board according to the cubes
 */

void fillBoggle(Vector<string> &cubes, Grid<char> &board) {
    int index = 0;
    //cout << cubes[0].length() <<endl;
    for(int i = 0; i < board.numRows(); i++) {
        for(int j = 0; j < board.numCols(); j++) {
            string cube = cubes[index];
            board[i][j] = chooseRandomFace(cube);
            index++;
        }
    }
}

/*
 * Function: chooseRandomFace
 * usage: board[i][j] = chooseRandomFace(cube);
 * -------------------------------------------
 * Choose a random face of the cube to show.
 */

char chooseRandomFace(string cube) {
    return cube[randomInteger(0, cube.length()-1)];
}

/*
 * Function: drawBoggle
 * Usage: drawBoggle(board);
 * -----------------------------------------
 * draw Boggle with characters
 */

void drawBoggle(Grid<char> &board) {
    for(int i = 0; i < board.numRows(); i++) {
        for(int j = 0; j < board.numCols(); j++) {
            char ch = board[i][j];
            labelCube(i, j, ch);
        }
    }
}

/*
 * Function: humanTurn
 * Usage: used_words = humanTurn(board, dict);
 * -----------------------------------------
 * Play human's turn
 */

Lexicon humanTurn(Grid<char> &board, Lexicon &dict) {
    Player player = HUMAN;
    cout << "Now, it's your turn!" << endl;
    Lexicon used_words; // store already included words
    while(true) {
        string word = getLine("Enter a word: ");
        word = toUpperCase(word);
        if(word.empty())
            return used_words;
        if(word.length() < 4 || !dict.contains(word)) {
            cout << "Invalid word! Try again!" << endl;
            continue;
        }
        if(used_words.contains(word)) {
            cout << "Already included! Try some new words!" << endl;
            continue;
        }
        if(findWordOnBoard(word, board)) {
            //highLightBoard();
           // cout << "apple" << endl;
            recordWordForPlayer(word, player);
            used_words.add(word);
        }
    }
    return used_words;
}

/*
 * Function: findWordOnBoard
 * Usage: if(findWordOnBoard(word, board)) do-sth;
 * -----------------------------------------
 * Check if the word is on the board and find the path.
 */

bool findWordOnBoard(string word, Grid<char> &board) {
   // Vector<Cube> used_cubes;
    Vector<Cube> word_path;
    Cube cube;
    bool flag = false;
    for(int i = 0; i < board.numRows(); i++) {
        for(int j = 0; j < board.numCols(); j++) {
            if(board[i][j] == word[0]) {
                cube.row = i;
                cube.col = j;
                flag = findWordPath(word, board, cube, word_path);
                if(flag) {
                    highlightBoard(word_path);
                    return flag;
                }
            }
        }
    }
    return flag;
}

/*
 * Function: findWordPath
 * Usage: if(findWordPath(word, board, cube, used_cubes)) do-sth;
 * -----------------------------------------
 * Find the word path recursively.
 */

bool findWordPath(string word, Grid<char> &board, Cube cube, Vector<Cube> &word_path) {
    if(word.empty()) return true;
    if(word[0] != board[cube.row][cube.col]) return false;

    word_path.add(cube);
    Vector<Cube> next = findNextCube(cube, word_path, board);
    foreach(Cube next_cube in next) {
        if(findWordPath(word.substr(1), board, next_cube, word_path)) {
            return true;
        }
    }
    word_path.remove(word_path.size() - 1);
    return false;
}

/*
 * Function: findNextCube
 * Usage: next = findNextCube(cube, used_cubes, board);
 * -----------------------------------------
 * Find all possible next cube.
 */

Vector<Cube> findNextCube(Cube cube, Vector<Cube> &word_path, Grid<char> &board) {
    Vector<Cube> next;
    Cube next_cube;
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            if(i == 0 && j == 0) continue;
            next_cube.row = cube.row + i;
            next_cube.col = cube.col + j;
            if(cubeInBound(next_cube, board) && !contain_cube(word_path, next_cube)) {
                next.add(next_cube);
                //cout << next_cube.row << " " << next_cube.col << endl;
            }
        }
    }
    return next;
}

/*
 * Function: contain_cube
 * Usage: if(contain_cube(word_path, next_cube)) do-sth;
 * ----------------------------------------------------
 * return whether a cube has already been in the word path.
 */

bool contain_cube(Vector<Cube> &word_path, Cube next_cube) {
    for(int i = 0; i < word_path.size(); i++) {
        if(word_path[i].row == next_cube.row && word_path[i].col == next_cube.col)
            return true;
    }
    return false;
}

/*
 * Function: cubeInBound
 * Usage: if(cubeInBound(next_cube, board)) do-sth;
 * -----------------------------------------
 * return whether a cube is in bound.
 */

bool cubeInBound(Cube next_cube, Grid<char> &board) {
    return (next_cube.row >= 0 && next_cube.row < board.numRows() && next_cube.col >=0 && next_cube.col < board.numCols());
}

/*
 * Function: highlightBoard
 * Usage: highlightBoard(used_cubes);
 * -----------------------------------------
 * Highlight the word path on the board.
 */

void highlightBoard(Vector<Cube> &word_path) {
    for(int i = 0; i < word_path.size(); i++) {
        highlightCube(word_path[i].row, word_path[i].col, true);
    }
    pause(500);
    for(int i = 0; i < word_path.size(); i++) {
        highlightCube(word_path[i].row, word_path[i].col, false);
    }
}

/*
 * Function: computerTurn
 * Usage: computerTurn(dict, used_words, board)
 * -----------------------------------------
 * Play a computer's turn.
 */

void computerTurn(Lexicon &dict, Lexicon &used_words, Grid<char> &board) {
    cout << "Now it's computer's turn!" << endl;
    for(int i = 0; i < board.numRows(); i++) {
        for(int j = 0; j < board.numCols(); j++) {
            char ch = board[i][j];
            string prefix = charToString(ch);
            //cout << board[i][j] << endl;
            //cout << prefix << endl;
            Vector<Cube> word_path;
            Cube cube;
            cube.row = i;
            cube.col = j;
            findAllWords(prefix, dict, used_words, board, cube, word_path);
        }
    }
    //findAllWords("", dict, used_words, board, cube, word_path);
}

/*
 * Function: findAllWords
 * Usage: findAllWords(prefix, dict, used_words, board, cube, word_path);
 * -----------------------------------------
 * Find all words recursively for a computer's turn.
 */

void findAllWords(string prefix, Lexicon &dict, Lexicon &used_words,
                  Grid<char> &board, Cube cube, Vector<Cube> &word_path) {
    Player player = COMPUTER;
    //cout << prefix << endl;
    if(!dict.containsPrefix(prefix)) return;
    if(!used_words.contains(prefix) && dict.contains(prefix) && prefix.length() > 3) {
        used_words.add(prefix);
        recordWordForPlayer(prefix, player);
    }
    word_path.add(cube);
    Vector<Cube> next = findNextCube(cube, word_path, board);
    foreach(Cube next_cube in next) {
        string str = prefix + board[next_cube.row][next_cube.col];
        //cout << str << endl;
        findAllWords(str, dict, used_words, board, next_cube, word_path);
    }
    word_path.remove(word_path.size() - 1);
}



void playBoggle(GWindow &gw) {
    Grid<char> board = boggleSetup();
    Lexicon dict("EnglishWords.dat");
    //if(dict.contains("apple")) cout<<"haha"<<endl;
    while(true) {
        Lexicon used_words = humanTurn(board, dict);
        computerTurn(dict, used_words, board);
        used_words.clear();
        cout << "Try again?" << endl;
        string play_again = getLine("Press 'n' to quit, else continue");
        play_again = toLowerCase(play_again);
        if(play_again == "n" || play_again == "no") return;
        string setup_again = getLine("Wanna set up again? (y/n) ");
        setup_again = toLowerCase(setup_again);
        if(setup_again == "y" || setup_again == "yes") {
            board = boggleSetup();
        }
        initGBoggle(gw);
        //eraseOldScores();
    }
}


