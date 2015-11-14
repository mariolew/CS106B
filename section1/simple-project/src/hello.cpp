#include <iostream>
#include <string>
#include <console.h>
#include <fstream>
#include <error.h>
using namespace std;
/* Function Prototypes */

string censorString1(string text, string remove);
void censorString2(string & text, string remove);
void readStats(string fname, int & min, int & max, double & mean);
int cannonball(int height);

/* Main entry */

int main() {
    /* test for section1 problem 1
    string text = "Stanford University";
    string remove = "nt";
    cout << censorString1(text, remove) << endl;
    censorString2(text, remove);
    cout << text << endl; */
    /* test for section1 problem 2
    int min, max;
    double mean;
    readStats("num.txt", min, max, mean);
    cout << min << " " << max << " " << mean << endl; */
    cout << cannonball(-1) << endl;
    return 0;
}


/*
 * Function: censorString1(text, remove)
 * remove every character in string remove from string text
 */

string censorString1(string text, string remove) {
    string result;
    int text_len = text.length();
    //int rm_len = remove.length();
    for (int i = 0; i < text_len; i++) {
//        bool flag = true;
//        for(int j = 0; j < rm_len; j++) {
//            if(text[i] == remove[j]) {
//                flag = false;
//                break;
//            }
//        }
//        if(flag) {
//            result += text[i];
//        }
        if (remove.find(text[i]) == string::npos) {
            result += text[i];
        }
    }
    return result;
}


void censorString2(string &text, string remove) {
    int text_len = text.length();
    for (int i = 0; i < text_len; i++) {
        if (remove.find(text[i]) != string::npos) {
            text.replace(i, 1, "");
            i--;
        }
    }
}

/*
 * Function: readStats(fname, min, max, mean)
 * read a file of scores and count the min, max and mean
 */

void readStats(string fname, int & min, int & max, double & mean) {
    ifstream infile;
    infile.open(fname.c_str());
    if (infile.fail()) {
        error("No such file" + fname);
    }
    int count = 0;
    double sum = 0;
    while (true) {
        int score;
        infile >> score;
        if (infile.fail()) break;
        if (score < 0 || score > 100) error("Score out of range!");
        if (count == 0 || score < min) min = score;
        if (count == 0 || score > max) max = score;
        sum += score;
        count++;
    }
    mean = (double)sum / count;
    infile.close();
}

/*
 * Function: cannonball(height)
 * return the number of cannonballs of level height
 */

int cannonball(int height) {
    if (height < 0) {
        cout << "Height should be non-negative." << endl;
        return -1;
    }
    if (height == 0) {
        return 0;
    }
    else {
        return height * height + cannonball(height - 1);
    }
}
