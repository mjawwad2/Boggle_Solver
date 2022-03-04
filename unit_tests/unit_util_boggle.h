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

#ifndef UNIT_UTIL_BOGGLE_H
#define UNIT_UTIL_BOGGLE_H

void read_board(string board[BOARD_SIZE][BOARD_SIZE], string filename) {
    ifstream boardFile;
    boardFile.open(filename);
    if (boardFile.fail()) {
        INFO(filename << " did not open.  Did you move the file?");
        FAIL();
    }

    // read the board from the file
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            boardFile >> board[row][col];
        }
    }
}

// Not used in the end.  Keeping here just in case it becomes useful.
void check_solve(string boardname, string test_data_filename) {
    string board[BOARD_SIZE][BOARD_SIZE];

    // Test using board_4
    read_board(board, boardname);
    Boggle boggle;
    boggle.SetBoard(board);

    ofstream solveOut;
    solveOut.open("solve_output_test.txt");
    boggle.SolveBoard(false,solveOut);
    solveOut.close();
    check_print_output("solve_output_test.txt",test_data_filename);
}

#endif //BOGGLE_UNIT_UTIL_BOGGLE_H
