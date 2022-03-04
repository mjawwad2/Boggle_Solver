/**
 * Created by Varick Erickson on 2/9/2021.
 *
 * You should not remove or change any of the tests in this file.
 * These are the same tests that will be used to grade your assignment.
 * If you want to run your own tests, it is recommended you use the provided
 * my_tests.cpp file.
 *
 * Provides utility functions for the tests. DO NOT MODIFY!
 */

#ifndef UNIT_UTILS_H
#define UNIT_UTILS_H

#include <iostream>
#include <fstream>
#include <vector>


// Read words from a file.  Ignores extra white space.
vector<string> read_words(string filename) {
    ifstream dictFile;
    dictFile.open(filename);
    if (dictFile.fail()) {
        INFO(filename << " did not open.  Did you move the file?");
        FAIL();
    }

    vector<string> words;
    string word;
    while(dictFile >> word) {
        if (word.back() == '\r')
            word.pop_back();
        words.push_back(word);
        for (int i = 0; i < word.length(); i++) {
            int index = (int) word[i] - (int) 'a';
            // Check to make sure we only have valid characters
            if (index < 0 || index > 25) {
                cout << word << endl;
            }
        }
    }

    return words;
}

// Compare files.  Ignores whitespace.
void compare_files(string filename, string test_data_filename) {
    // Open file your SaveSolve produced.
    ifstream inFile;
    inFile.open(filename);
    if (inFile.fail()) {
        INFO(filename << " failed to open.");
        FAIL();
    }

    // Open known "good" output
    ifstream inTest;
    inTest.open(test_data_filename);
    if (inTest.fail()) {
        INFO(test_data_filename << " failed to open.");
        INFO("Did you move the file from the test_data folder?");
        FAIL();
    }

    // Compare word by word.
    string line, testLine;
    while (inFile >> line && inTest >> testLine) {
        if (testLine.back() == '\r') {
            testLine.pop_back();
        }
        if(line != testLine) {
            INFO("Files do not match");
            INFO("Your line: " << line);
            INFO(" Expected: " << testLine);
            FAIL();
        }
    }

    if (inFile >> line) {
        INFO("More lines found than expected " << filename);
        FAIL();
    }

    // Try to read another line from the known test file.  If there
    // are more, then your output file did not find all the words
    // or did not output anything to a file.
    if (inTest >> line) {
        INFO("Too few lines found in " << filename << ".");
        FAIL();
    }
}
// Checks file line by line. Formatting is checked.
void check_print_output(string filename, string test_data_filename) {
    // Open file your SaveSolve produced.
    ifstream inFile;
    inFile.open(filename);
    if (inFile.fail()) {
        INFO(filename << " failed to open.");
        INFO("Did you implement the SaveSolve?");
        FAIL();
    }

    // Open known "good" output
    ifstream inTest;
    inTest.open(test_data_filename);
    if (inTest.fail()) {
        INFO(test_data_filename << " failed to open.");
        INFO("Did you move the file from the test_data folder?");
        FAIL();
    }

    // Compare line by line.  This check does take formatting into account.
    string line, testLine;
    while (getline(inFile, line) && getline(inTest,testLine)) {
        // Fix for windows \r\n
        if (testLine.back() == '\r') {
            testLine.pop_back();
        }
        if(line != testLine) {
            INFO("PrintedBoard output does not match");
            INFO("Your line: " << line);
            INFO(" Expected: " << testLine);
            FAIL();
        }
    }

    // Try to read another line from your file.  If there is more,
    // then your program has more output than expected.
    if (getline(inFile, line)) {
        INFO("More lines found than expected " << filename);
        INFO("Are you outputting duplicate words?");
        FAIL();
    }

    // Try to read another line from the known test file.  If there
    // are more, then your output file did not find all the words
    // or did not output anything to a file.
    if (getline(inTest, line)) {
        INFO("Too few lines found in " << filename << ".");
        INFO("You may not be finding all the words on the board.");
        INFO("It could also be that your program is not writing to " << filename << ".");
        FAIL();
    }
}



#endif
