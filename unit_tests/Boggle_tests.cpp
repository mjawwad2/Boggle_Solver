/**
 * Created by Varick Erickson on 2/24/2021.
 *
 * You should not remove or change any of the tests in this file.
 * These are the same tests that will be used to grade your assignment.
 *
 * The purpose of this file is to test the boggle object.
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "../Boggle.h"
#include "unit_util_dictionary.h"
#include "unit_util_boggle.h"

TEST_CASE("Boggle Tests") {
    SECTION("Default constructor - 2pts") {
        Boggle boggle;

        Dictionary dict = boggle.GetDictionary();
        // Default dictionary should have 127142 words
        REQUIRE(dict.WordCount() == 127142);

        vector<string> words = read_words("dictionary.txt");
        for (auto word: words) {
            REQUIRE(dict.IsWord(word));
        }
    }

    SECTION("Boggle(string filename) constructor - 2pts") {
        Boggle boggle("test_data/pokemon.txt");

        // Should have 698 words
        Dictionary dict = boggle.GetDictionary();
        REQUIRE(boggle.GetDictionary().WordCount() == 698);

        vector<string> words = read_words("test_data/pokemon.txt");
        for (auto word: words) {
            REQUIRE(dict.IsWord(word));
        }
    }

    SECTION("SetBoard - 2pts") {
        // Read board 2
        string board[BOARD_SIZE][BOARD_SIZE];
        read_board(board, "test_data/board_2.txt");

        // Set the board. If this works properly, it should be a deep copy.
        Boggle boggle;
        boggle.SetBoard(board);

        // Read another board.
        read_board(board, "test_data/board_4.txt");

        // This should solve the board using board_2.txt data.
        // If it solve it with board_4.txt, then you did a shallow copy.
        boggle.SolveBoard(false,cout);
        boggle.SaveSolve("SetBoard_test.txt");

        // These files should be identical
        compare_files("SetBoard_test.txt", "test_data/words_found_2.txt");
    }

    SECTION("SolveBoard Test - 8pts") {

        // Check the solver with four different boards
        string board[BOARD_SIZE][BOARD_SIZE];
        for (int i = 1; i <= 4; i++) {
            string boardname = "test_data/board_"+to_string(i) + ".txt";
            read_board(board, boardname);
            Boggle boggle;
            boggle.SetBoard(board);

            ofstream solveOut;
            solveOut.open("solve_output_test.txt");
            boggle.SolveBoard(false,solveOut);
            solveOut.close();

            string test_data_filename = "test_data/solve_output_"+to_string(i)+".txt";
            check_print_output("solve_output_test.txt",test_data_filename);
        }
    }

    SECTION("SolveBoard Print Test - 8pts") {

        // Test four different boards
        string board[BOARD_SIZE][BOARD_SIZE];
        for (int i = 1; i <= 4; i++) {
            string boardname = "test_data/board_" + to_string(i) + ".txt";
            read_board(board, boardname);
            Boggle boggle;
            boggle.SetBoard(board);

            ofstream solveOut;
            solveOut.open("solve_output_test.txt");
            boggle.SolveBoard(true, solveOut);
            solveOut.close();

            check_print_output("solve_output_test.txt",
                               "test_data/solve_output_print_"+to_string(i)+".txt");
        }
    }

    SECTION("WordsFound - 8pts") {
        // Test four different boards
        string board[BOARD_SIZE][BOARD_SIZE];
        for (int i = 1; i <= 4; i++) {
            string boardname = "test_data/board_" + to_string(i) + ".txt";
            read_board(board, boardname);
            Boggle boggle;
            boggle.SetBoard(board);

            boggle.SolveBoard(false,cout);
            Dictionary wordsFound = boggle.WordsFound();

            wordsFound.SaveDictionaryFile("words_found_test.txt");

            compare_files("words_found_test.txt",
                          "test_data/words_found_"+to_string(i)+".txt");
        }
    }




}