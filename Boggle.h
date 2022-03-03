#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:
    Boggle();
    explicit Boggle(string filename);

    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);

    void SolveBoard(bool printBoard, ostream& output);

    void SaveSolve(string filename);   // Saves all the words from the last solve.

    Dictionary GetDictionary();
    Dictionary WordsFound();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];

    void PrintBoard(ostream& output);
    void SolveBoardHelper(int, int, string, int, ostream&, bool);
};

#endif //BOGGLE_BOGGLE_H
