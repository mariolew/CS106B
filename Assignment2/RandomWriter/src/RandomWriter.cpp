/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "error.h"
#include "foreach.h"
using namespace std;

// Function prototypes
string promptUserForFile(ifstream & infile, string prompt = "");
Map<string, Vector<char> > analyseFile(ifstream & infile);
void randomWriter(Map<string, Vector<char> > & dict);

int main() {
	// [TODO: fill in the code]
    ifstream infile;
    promptUserForFile(infile, "Input file: ");
    Map<string, Vector<char> > dict = analyseFile(infile);
    randomWriter(dict);
    infile.close();
	return 0;
}


/* Function promptUserForFile
 * usage: string filename = promptUserForFile(infile, prompt);
 * -----------------------------------------------------------
 * Ask the user for the file name and open it
 * */

string promptUserForFile(ifstream & infile, string prompt) {
    while(true) {
        cout << prompt;
        string filename;
        getline(cin, filename);
        infile.open(filename.c_str());
        if(!infile.fail()) return filename;
        infile.clear();
        cout << "Unable to open that file. Please try again" << endl;
        if(prompt == "") prompt = "Input file: ";
    }
}

/* Function analyseFile
 * usage: Map<Vector<string> > dict = analyseFile(infile);
 * -------------------------------------------------------
 * to analyse the input file stream
 * */
Map<string, Vector<char> > analyseFile(ifstream & infile) {
    Map<string, Vector<char> > dict;
    cout << "Please choose a number (1-10)";
    int number;
    cin >> number;
    char ch;
    string seed;
    for(int i = 0;i < number; i++) {
        if(!infile.get(ch)) error("File length beyond the number");
        seed = seed + ch;
    }
    while (infile.get(ch)) {
        dict[seed].add(ch);
        seed = seed.substr(1) + ch;
    }
    return dict;
}

/* Function randomWriter
 * usage: randomWriter(infile)
 * --------------------------------------------------------------
 * randomly generate 2000 words according to the input file stream
 * */

void randomWriter(Map<string, Vector<char> > &dict) {
    int frequency = 0;
    string seed;//cout<<dict["er"].get(0);
    foreach(string word in dict) {
        //cout << word << dict[word].size() <<endl;
        if(dict[word].size() > frequency) {
            frequency = dict[word].size();
            seed = word; //cout << seed <<endl;
        }
    }
    cout << seed;
    for(int count = 0; count < 2000; count++) {
        //cout <<seed;
        if(dict[seed].isEmpty()) break;
        int rand_int = randomInteger(0, dict[seed].size() - 1);//cout<<rand_int<<endl;

        cout << dict[seed].get(rand_int);
        seed = seed.substr(1) + dict[seed].get(rand_int);//cout<<seed<<endl;
    }

}



