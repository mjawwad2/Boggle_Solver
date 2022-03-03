#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>
#include <aclui.h>

// Your code here


// The copy constructor is complete.
// However, the operator= must be completed for it to work.
Dictionary::Dictionary(const Dictionary &otherDict) {
    root = new Node;        //constructor setting the new node to null
    numWords = 0;
    *this = otherDict;      //copying the other dict into this pointer
}

Dictionary::Dictionary(){           //setting the nodes and the isword to to null
    root = new Node;
    root->isWord = false;
    numWords = 0;
}

Dictionary::~Dictionary() {     //deleting the dictionary by calling the make empty func that is written in this program
    MakeEmpty();
    delete root;        //deleting the root of the table to campletely kaboooom it
}

Dictionary::Dictionary(string filename) {   //opening the file and calling load dictionary function to load the wrds from txt file
    root = new Node;
    root->isWord = false;
    numWords = 0;

    ifstream inFile;
    inFile.open(filename);
    LoadDictionaryFile(filename);
}

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {    //setting the words from other dict to this dictionary
    MakeEmpty();        //make the dictionary empty first
    numWords = otherDict.numWords;  //copying over the number of words before copying it over
    copyHelper(root, otherDict.root);   //copy the dictionary over using recusion to make a deep copy
    return *this;   //return this pointer
}

void Dictionary::LoadDictionaryFile(string filename) {  //loading the dictionary
    string read;
    ifstream inFile;
    inFile.open(filename);  //opening the file to read all the words from it
        while(!inFile.eof()) {  //while its not end of dictionary. keep traversing
            inFile >> read;     //read the word in current line and send it addword to be added
            AddWord(read);
        }
}

void Dictionary::SaveDictionaryFile(basic_string<char> filename) {
    Node *curr = root;
    ofstream outFile;
    outFile.open(filename);     //open the file to write in and save all the words using recursion
    if (!outFile.is_open()) {       //if the file fails to open throw an error
        throw DictionaryError(filename + " failed to open");
    }
    SaveDictionaryHelper(curr, "", outFile);    //call the recursive function to load it up with the words
    outFile.close();        // close the file
}

void Dictionary::AddWord(string word) {
    Node *curr = root;      //start at root and look for where the word should be added
    int count = word.size();        //taking the size of string for the for loop
    for (int i=0; i<count; i++){        //  start at beginning and go throuhg the pointers of this certain word
        int h = (int)word[i]-(int)'a';
        if (h>=NUM_CHARS || h<0 ){      //if the characters are out of range throw error
            throw DictionaryError("Invalid character");
        }
        if(curr->branch[h]==NULL){      //if the path  is null make a new node at this pointer
            curr->branch[h] = new Node();
        }
        curr = curr -> branch[h];       //if the pointer is not null then assign it the letter in the word
    }
    curr->isWord = true;        // set the last letter to true because that indicate its a word
    numWords++;     //increase the word count by 1
}

void Dictionary::MakeEmpty() {
    destroyHelper(root);        //start at root and make dictionary empty
    root = new Node;        //set the nodes and is word to null
    root->isWord = false;
    numWords = 0;       //resetting the number of words as well
}

bool Dictionary::IsWord(string word) {      //check if the word in the dictionary is word with the help bool isword
    Node *curr = root;      //start at root and check if the word passed forms a word by going down the specific path of pointers
    int count = word.size();    // take the size of string for the for loop
    for (int i=0; i < count; i++){
        int h = (int)word[i]-(int)'a';

        if (h >= NUM_CHARS || h<0 ){      //if the characters are out of bound. throw an error
            throw DictionaryError("Invalid character");
        }
        if(curr->branch[h]==NULL){      //if the pointers bool is null return it wasnt a word
            return false;
        }
        curr = curr -> branch[h];   //set the pointer to next specific character
    }
    return curr->isWord;        //if it doesnt return false then the last pointer should return whether it be a false or true
}

bool Dictionary::IsPrefix(string word) {        // check if the path already exists
    Node *curr = root;      //start at root
    int count = word.size();        // take the size of string for the for loop
    for (int i=0; i<count; i++){
        int h = (int)word[i]-(int)'a';

        if (h>=NUM_CHARS || h<0 ){      //if the characters are out of bound. throw an error
            throw DictionaryError("Invalid character");
        }
        if(curr->branch[h] == NULL){
            return false;               //if the path doesnt return false at one of the pointers
        }
        curr = curr -> branch[h];   //traverse through the list
    }
    return true;        //if none of the nodes in the path is null. then there has to be a word
}

int Dictionary::WordCount() {   //return the word count of the dictionary
    return numWords;
}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {        //destroy helper uses recursion to make the dictionary empty
    if (thisTree == nullptr) {      //if tree is null then return
        return;
    }

    for (int i=0; i<NUM_CHARS; i++) {       //uses recursion to go through the nodes and delete them
        destroyHelper(thisTree->branch[i]);
    }
    delete thisTree;        //delete the current tree
}

void Dictionary::copyHelper(Dictionary::Node *&thisTree, Node *otherTree) {     //helps copy over the tree using recursion
    if(otherTree == nullptr){
        thisTree = nullptr;
        return;
    }       //if other tree has no nodes. set this one to null and return
    thisTree = new Node;
    thisTree->isWord = otherTree->isWord;       //copy over if the other tree forms a word
    for (int i=0; i < NUM_CHARS; i++) {     //use for loop to do deep copy and set the nodes same as other tree
        copyHelper(thisTree->branch[i], otherTree->branch[i]);
    }
}

void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
    if (curr == nullptr){       //save opens a certain file of user choice to put all the words in dictionary in there
        return;     //if the list is empty return
    }
    if(curr->isWord){       //if it forms a word add it to the dictionary
        outFile << currPrefix << endl;
    }
    for(int i=0; i< NUM_CHARS; i++){        //if the path of word is not null add the curr character to word and call this function recursively
        if(curr->branch[i]!=nullptr)        //after adding them. it will add the words to dictionary if it passes the isword test
            SaveDictionaryHelper(curr->branch[i], currPrefix+char(i+int('a')), outFile);
    }

}
