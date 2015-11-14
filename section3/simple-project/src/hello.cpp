#include <iostream>
#include <string>
#include "hello.h"
#include "console.h"
#include "vector.h"
#include "direction.h"
#include "maze.h"
#include "gwindow.h"
#include "point.h"
#include "lexicon.h"
using namespace std;

/* Function Prototypes */
bool isMeasurable(int target, Vector<int> & weights);
int shortestPathLength(Maze & maze, Point start);
Point adjacentPoint(Point start, Direction dir);
void fillRegion(Grid<bool> & pixels, int row, int col);
bool findAnagram(string letters, Lexicon & english,
Vector<string> & words);
bool findAnagramRec(string prefix, string rest,
                    Lexicon & english, Vector<string> & words);

/* CONSTANS */
const int MIN_LEN = 4;

int main() {
    cout << "Hello, World!" << endl;
    /* test prog for section3 problem 1
    Vector<int> weights;
    weights.add(1);
    weights.add(3);
    if (isMeasurable(5, weights))
        cout << "Thank you!" << endl; */

    // test prog for section3 problem 2
    GWindow gw;
    Maze maze("SampleMaze.txt", gw);
    int shortest = shortestPathLength(maze, maze.getStartPosition());
    cout << "The shortest path is: " \
         << shortest << endl;
    getchar();

    /* test prog for section3 problem 3
    Lexicon english("EnglishWords.dat");
    string line;
    Vector<string> words;
    while (true) {

        cout << "Please enter a string of letters: ";
        getline(cin, line);
        if (line == "") break;
        if (findAnagram(line, english, words)) {
            for (int i = 0; i < words.size(); i++) {
                cout << words[i] << " ";
            }
        }
        else {
            cout << "No anagram found";
        }
        cout << endl;
        words.clear();
    }*/
    return 0;
}


bool isMeasurable(int target, Vector<int> & weights) {
    if (weights.isEmpty()) {
        return target == 0;
    }
    int first = weights[0];
    Vector<int> rest = weights;
    rest.remove(0);
    return isMeasurable(target, rest) ||\
            isMeasurable(target - first, rest) ||\
            isMeasurable(target + first, rest);
}

int shortestPathLength(Maze & maze, Point start) {
    if (maze.isOutside(start)) return 0;
    if (maze.isMarked(start)) return -1;
    maze.markSquare(start);
    int shortest = -1;
    for (Direction dir = NORTH; dir <= WEST; dir++) {
        if (!maze.wallExists(start, dir)) {
            int len = shortestPathLength(maze, adjacentPoint(start, dir)) + 1;
            if (len > 0) {
                if (shortest == -1 || len < shortest)
                    shortest = len;
            }
        }
    }
    if (shortest == -1) {
        maze.unmarkSquare(start);
    }
    return shortest;
}

Point adjacentPoint(Point start, Direction dir) {
   switch (dir) {
    case NORTH: return Point(start.getX(), start.getY() - 1);
    case EAST:  return Point(start.getX() + 1, start.getY());
    case SOUTH: return Point(start.getX(), start.getY() + 1);
    case WEST:  return Point(start.getX() - 1, start.getY());
   }
   return start;
}


void fillRegion(Grid<bool> & pixels, int row, int col) {
    if (pixels.inBounds(row, col) && !pixels[row][col]) {
        pixels[row][col] = true;
        fillRegion(pixels, row + 1, col);
        fillRegion(pixels, row, col - 1);
        fillRegion(pixels, row - 1, col);
        fillRegion(pixels, row, col + 1);
    }
}

bool findAnagram(string letters, Lexicon & english,
Vector<string> & words) {
    return findAnagramRec("", letters, english, words);
}

bool findAnagramRec(string prefix, string rest,
                    Lexicon & english, Vector<string> & words) {
    if (!english.containsPrefix(prefix)) return false;
    if (english.contains(prefix) && prefix.length() >= MIN_LEN) {
        if (rest == "" || findAnagramRec("", rest, english, words)) {
            words.add(prefix);
            return true;
        }
    }
    for (int i = 0; i < rest.length(); i++) {
        string others = rest.substr(0, i) + rest.substr(i + 1);
        if (findAnagramRec(prefix + rest[i], others, english, words))
            return true;
    }
    return false;
}
