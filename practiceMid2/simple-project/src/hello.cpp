#include <iostream>
#include "hello.h"
#include "console.h"
#include "vector.h"
#include "map.h"
using namespace std;


/* Function Prototypes */
string removeDoubledLetters(string str);
void tryAllOperators(string exp, int target);
void tryAllOperatorsRec(string prefix, string rest, int target);
Vector<int> extract3x3Subsquare(Grid<int> & grid,int bigRow,
                                                int bigCol);
int countHailstoneSteps(int n, Map<int,int> & cache);
int countHailstoneStepsRec(int n, Map<int,int> & cache);

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}


string removeDoubledLetters(string str) {
    if (str.length() <= 1) return str;
    else {
        if (str[0] == str[1]) return removeDoubledLetters(str.substr(1));
        else return str[0] + removeDoubledLetters(str.substr(1));
    }
}

void tryAllOperators(string exp, int target) {
    tryAllOperatorsRec("", exp, target);
}

void tryAllOperatorsRec(string prefix, string rest, int target) {
    if (evaluateExpression(prefix) == target && rest == "")
        cout << prefix << endl;
    if (rest[0] == '?') {
        rest = rest.substr(1);
        tryAllOperatorsRec(prefix + '+', rest, target);
        tryAllOperatorsRec(prefix + '-', rest, target);
        tryAllOperatorsRec(prefix + '*', rest, target);
        tryAllOperatorsRec(prefix + '/', rest, target);
    }
    else {
        tryAllOperatorsRec(prefix + rest[0], rest.substr(1), target);
    }
}


Vector<int> extract3x3Subsquare(Grid<int> & grid,int bigRow,
                                            int bigCol) {
    Vector<int> subsquare;
    for (int i = bigRow * 3; i < bigRow * 4; i++) {
        for (int j = bigCol * 3; j < bigRow * 4; j++) {
            subsquare.add(grid[i][j]);
        }
    }
    return subsquare;
}

int countHailstoneSteps(int n, Map<int,int> & cache) {
    int len = 0;
    while (n != 1) {
        if (cache.containsKey(n)) {
            len += cache[n];
            break;
        }
        else {
            if (n % 2 == 0)
                n /= 2;
            else
                n = 3 * n + 1;
            len++;
        }
    }
    if (!cache.containsKey(n))
        cache[n] = len;
    return len;
}

int countHailstoneStepsRec(int n, Map<int,int> & cache) {
    if (cache.containsKey(n)) return cache[n];
    if (n == 1)
        return 0;
    else {
        int count = 0;
        if (n % 2 ==0) {
            count = countHailstoneStepsRec(n / 2, cache) + 1;
        }
        else {
            count = countHailstoneStepsRec(3 * n + 1, cache) + 1;
        }
        cache[n] = count;
        return count;
    }
}
