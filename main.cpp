/*
 Filename: main.cpp
 Description: Main, reads and verifies user input
 Author: Rami Isaac
 Date: 06/12/2020
 Course: Data Structures II
*/

#include <iostream>
#include <string>
using namespace std;

#include "tree.h"

bool fileExists(string fileName);

int main(int argc, char* argv[]){

    string action,
           inputFile,
           outputFile;

    if(argc < 4){
        cout << "You've used too few parameters." << endl;
    } else if (argc == 4){

        string temp = argv[1];
        if (temp == "-encode" || temp == "-decode") {
            action = argv[1];
        } else {
            cout << "You must use -encode or -decode" << endl;
            return 0;
        }

        if(fileExists(argv[2]) && !fileExists(argv[3])){
            inputFile = argv[2];
            outputFile = argv[3];
            cout << "Encoding " << inputFile << "and saving to " << outputFile << endl;

            Tree build; /* Build Tree */
            build.handleAction(inputFile, outputFile, action); /* Action Handler */

        } else {
            cout << "Please make sure input file EXISTS and output file DOES NOT." << endl;
        }
        return 0;
    } else {
        cout << "You've used too many parameters." << endl;
        return 0;
    }
}

bool fileExists(string fileName){
    ifstream inFile;
    inFile.open(fileName);
    if(inFile.fail()){
        return false;
    } else {
        return true;
    }
}