#include "Dictionary.h"
#include "Boggle.h"

// Your code here


// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}

Boggle::Boggle() {
    dict.LoadDictionaryFile("dictionary.txt");      //loading the dictionary using dictionary load function
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){      //setting the board empty
            board[i][j] = "";
        }
    }
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){      //setting visited spaces in board to 0/false
            visited[i][j] = 0;
        }
    }
}

Boggle::Boggle(string filename) {
    dict.LoadDictionaryFile(filename);      //loading the dictionary with words
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){      //setting the board empty
            board[i][j] = "";
        }
    }
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){      //setting visited spaces in board to 0/false
            visited[i][j] = 0;
        }
    }
}

void Boggle::SetBoard(string (*board)[4]) {     //loading the board according to the user request
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            this->board[i][j] = board[i][j];    //deepcopy if setting board with for loop. instead of this->board=board
        }
    }
}

void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);        //saving the words found through solve helper using save func from dictionary
}

void Boggle::PrintBoard(ostream &output) {
    output << "Number of Words: " << wordsFound.WordCount() << endl;        //print the tables if the user requests y
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {      //printing the words found in table
            if (visited[i][j] != 0) {
                output << " '" << board[i][j] << "' ";  //print with ' ' if the letters forms a word
            } else {
                output << "  " << board[i][j] << "  ";      //print without ' ' if its just the rest of letters
            }
        }
        output << "\t";
        for (int j = 0; j < BOARD_SIZE; j++) {          //second part of the board is the numbers showing the order of letter
            output << "  " << visited[i][j] << "  ";
        }
        output << endl;
    }
    output << endl;         //skip a line before printing the next table
}

void Boggle::SolveBoard(bool printBoard, ostream &output) {     //wrapper func for solve
    wordsFound.MakeEmpty();         //before using the wordfound txt make it empty
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            SolveBoardHelper(i, j, "", 0, output, printBoard);      //calls the solve helper from each letter position in the table
        }
    }
}

void Boggle::SolveBoardHelper(int i,int j, string word, int num, ostream &output, bool print) {     //solve helper recurrsivly checks all positions
    if (i >= BOARD_SIZE || i < 0 || j >= BOARD_SIZE || j < 0)       //if the direction being searched is out of bound return
        return;
    if(visited[i][j]!=0)        //to prevent the letter being used twice or more in a word. so return if the visited has been used for the curr word
        return;
    if(!dict.IsPrefix(word))        //not necessary but prevents doing extra search in addword to save runtime
        return;                     //it will check if the string  is going to potentially form a word or not
    word+=board[i][j];          //add the current letter to the string
    visited[i][j]=num+1;           // set visited to the number in order to print the second table later

    if (dict.IsWord(word) && !wordsFound.IsWord(word))  {      // if the string does form a word and is not already found. do the following
        wordsFound.AddWord(word);       //put word in wordsfound txt
        if(print) {     //if the user requested a print. then go into the print function and print all the tables and the order the words were found
            output << "Word: " << word << endl;
            PrintBoard(output);
        }else{
            output << wordsFound.WordCount();       //if the user doesnt want to print the tables. print the list of words without table//this will display the number of the word in list
            output << "\t" << word << endl;     //space between the number and word
        }
    }
    SolveBoardHelper(i-1, j, word,num+1, output, print);        //check all these directions to see if a word could be formed
    SolveBoardHelper(i-1, j+1, word,num+1, output, print);      //these functions are calling this same function recursively
    SolveBoardHelper(i, j+1, word,num+1, output, print);        //until all positions from that certain letter have been checked
    SolveBoardHelper(i+1, j+1, word, num+1, output, print);
    SolveBoardHelper(i+1, j, word, num+1, output, print);
    SolveBoardHelper(i+1, j-1, word, num+1, output, print);
    SolveBoardHelper(i, j-1, word, num+1, output, print);
    SolveBoardHelper(i-1, j-1, word,num+1, output, print);
    visited[i][j] = 0;      //set the visited to 0 before going to next word
}