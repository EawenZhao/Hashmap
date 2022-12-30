#include <iostream>
#include "driver.h"    // declares hashmapDriver class


unsigned long hash_func::operator()(const string& key) {
    unsigned long total = 0;
    for (int i = 0; i < key.size(); ++i) {
        total = total * 131 + key[i];
    }
    return total;
}


void HashMapDriver::setUpFiles() {
    const string INFILE_PROMPT =
            "Please enter the path for the input file: ";

    const string IN_FAILURE =
            "*** Error opening input file: ";

    string inFileName;

    cout << INFILE_PROMPT;
    cin >> inFileName; //get input file path and name
    inFile.open(inFileName.c_str(), ios::in); //open input file

    while (inFile.fail()) {
        cout << endl << IN_FAILURE << inFileName << endl;
        cout << endl << INFILE_PROMPT;
        cin >> inFileName;
        inFile.open(inFileName.c_str(), ios::in); //open input file
    } // if input file incorrect

    getline(cin, inFileName);//eat ENTER key
} // setUpFiles


void HashMapDriver::readAndProcess() {
    string curr_line;

    while (getline(inFile, curr_line)){ //repeatealy read a new line into curr_line   //from input file until EOF  //and meanwhile set up the dictionary
        int position = 0;

        for (int i = 0; curr_line[i] != ' '; i++) {
            position++;
        }

        string word = curr_line.substr(0, position);
        string definition = curr_line.substr(position + 1, curr_line.size());
        const key_value_pair<const string, string> valuePair(word, definition);
        dict.insert(valuePair);
    } // while

    inFile.close(); //close input file
} // readAndProcess

void HashMapDriver::testDictionary() {
    system("chcp 65001"); //set the encoding of console to UTF-8 if necessary

    string word;

    while (true){
        cout << endl << "Please input a word; input QUIT to quit." << endl;
        getline(cin, word); //read a new word from user input

        if (word == "QUIT")
            break;

        hash_map<string, string , hash_func>::iterator iterator = dict.find(word);
        if (iterator != dict.end()){
            cout << (*iterator).second << endl;
        } else{
            cout << "Oops, this word is not found in the dictionary, please try again!" << endl;
        }

    }
    //please implement the testing!
}