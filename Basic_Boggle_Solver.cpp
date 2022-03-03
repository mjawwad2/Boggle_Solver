/*
 * Start here for Part B of the assignment.
 *
 * You should make this part work first before
 * trying to pass any of the unit tests.
 *
 * You can change anything you want in this file.
 * It will not be used for grading.
 */

#include <iostream>
#include "Boggle.h"
#include "Dictionary.h"

using namespace std;

void GetBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
    cout << "Enter Board" << endl;
    cout << "-----------" << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << "Row " << i << ": ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            cin >> board[i][j];
        }
    }
    cout << endl;
}

void HardCodedBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
    board[0][0] = "a";
    board[0][1] = "u";
    board[0][2] = "c";
    board[0][3] = "o";

    board[1][0] = "n";
    board[1][1] = "l";
    board[1][2] = "n";
    board[1][3] = "i";

    board[2][0] = "o";
    board[2][1] = "s";
    board[2][2] = "a";
    board[2][3] = "e";

    board[3][0] = "m";
    board[3][1] = "a";
    board[3][2] = "i";
    board[3][3] = "e";
}

int main() {
    Boggle boggle;

    string board[BOARD_SIZE][BOARD_SIZE];

    HardCodedBoard(board);      // Provides a hard coded board
    //GetBoard(board);          // Gets a board from a user

    cout << boggle.GetDictionary().WordCount() << " words loaded." << endl << endl;

    boggle.SetBoard(board);

    string yesno;
    cout << "Show board? (y/n):  ";
    getline(cin, yesno);
    cout << endl;

    // Output to the screen.  Notice we pass in cout.
    boggle.SolveBoard(yesno == "y", cout);

    // Output to a file.  Notice we pass in a file.
    ofstream solveOutput;
    solveOutput.open("solve_output_basic.txt");
    boggle.SolveBoard(yesno == "y", solveOutput);
    solveOutput.close();

    // We can also save the words found this way.
    boggle.WordsFound().SaveDictionaryFile("solve_dictionary.txt");

    return 0;
}