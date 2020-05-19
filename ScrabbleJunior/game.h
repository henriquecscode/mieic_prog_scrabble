#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <set>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <iomanip>
#include <stdio.h>
#include <ctype.h>

#include <bits/stdc++.h> // To remove later
#include "board.h"
using namespace std;

//Color codes for board printing
#define BLACK 0
#define RED 4
#define LIGHTGRAY 7
#define WHITE 15

//Constant ascii values
#define ASCII_A 65
#define ASCII_a 97

typedef struct
{
    string name;
    int score = 0;
    vector<char> pool;
} Player;

class Game
{
public:
    /** 
        * Prints/outputs instructions for the players, right in the beginning.
    */
    void beginningInstructions();

    /** 
        * Returns a random index used for exchanging chips and also to create the letter pool in the beginning of the game.
        * @param size: an integer number that will be used to keep the generated integer within the recquired range (like the size of the letter pool, for example).
        * @return: an integer number that will be used for reassignment of chips or to add letters to the game's pool (in the beginning).
    */
    int getIndex(int size);

    /** 
        * Void function that executes each round of turns!
        * @param players: a Player struct vector passed by reference that contains data from each player (i.e. name, letter pool and current score).
    */
    void game(vector<Player> &players);

    /** 
        * Checks if the strings containing the plays from a player are in the recquired format (i.e. uppercase letter followed by lowercase letter).
        * @param p1: string passed by reference which contains the first play inputed by the player. Passed by reference so any changes to it are kept.
        * @param p2: string passed by reference which contains the second play inputed by the player. Passed by reference so any changes to it are kept.
    */
    void checkPlays(string &p1, string &p2);

    /** 
        * Creates and sets all variables and data structures needed to advance the game.
        * @param board: an object of type Board which is used to get all data from a specific board (i.e. needed vectors and variables). Passed by reference so it keeps changes done by the function.
    */
    void prepGame(Board &board);

    /** 
        * Gives a player a new pool.
        * @param player: a struct of type Player which contains a player's name, score and letter pool. Passed by reference to keep changes done to the pool.
    */
    void getNewPool(Player &player);

    /** 
        * Outputs the letter pool from a specific player to inform him of the letters he can play.
        * @param player: a struct of type Player which contains a player's name, score and letter pool. It's passed by reference so changes to the pool are kept after reaching the end of the function.
    */
    void printPool(Player &player);

    /** 
        * Checks if a letter pool from a specific player is empty.
        * @param player: a struct of type Player which contains a player's name, score and letter pool. It's passed by reference so changes are kept in case the function leads to the player getting a new pool.
    */
    void checkPool(Player &player);

    /** 
        * Checks all words that contain the coordinate given by the string play, checking if a word has been fully captured.
        * @param letter: an struct of type Info passed by reference in order for potential changes (there's a case contemplated in this function which results to reversing the capture state of the letter).
        * @param player: a struct of type Player which contains a player's name, score and letter pool (which will be empty if it only contains chars '-'). It's passed by reference so any changes to it are kept.
        * @param play: a string containing the coordinates for a play.
    */
    void checkWords(Info &letter, Player &player, string play);

    /** 
        * A binary search function to find a certain element (findee) within an ordered string vector.
        * @param vect: a string vector possibly containing the element in findee.
        * @param findee: a string of the element we're trying to find in vect.
        * @return: the function returns the corresponding integer index of the element findee within the vector if it finds it, -1 otherwise.
    */
    int findIndex(vector<string> vect, string findee);

    /** 
        * Checks if a word (word) has been fully captured. If it is, the corresponding player gets 1 point added to their score and the word is eliminated from the boardWords vector.
        * @param word: a string containing the potentially fully captured word.
        * @param player: a struct of type Player passed by reference in case a word has been fully captured - which results in said player gaining a point (his score is incremented by 1).
    */
    void checkCapture(string word, Player &player);

    /** 
        * This function sets the flow of a player's full turn and calls all functions needed to execute the plays accordingly.
        * @param player: a struct of type Player which contains a player's name, score and letter pool.
        * @param plays: a pair of strings containing each play from the player, already reformatted by checkPlays.
    */
    void makePlay(Player &player, pair<string, string> plays);

    /** 
        * Collects plays from a player and returns their plays in a pair<string, string>.
        * @param player: a struct of time Player which contains a player's name, score and letter pool. It's passed by reference so it can be easily passed to other functions.
        * @return: a pair of strings containing the player's plays (already reformatted by checkPlays).
    */
    pair<string, string> getPlay(Player &player);

    /** 
        * Captures a word, contemplating the following invalid capturing situations: player doesn't have the letter recquired in their pool, play points to an empty space on the board or play points to an already captured letter.
        * @param letter: an struct of type Info passed by reference in order for potential changes.
        * @param player: a struct of type Player which contains a player's name, score and letter pool. It's passed by reference so any changes to it are kept.
        * @param play: a string containing the coordinates for a play.
    */
    void captureLetter(Info &letter, Player &player, string play);

    /** 
        * Allows exchange of a sole valid chip from a player's pool!
        * @param player: a struct of type Player which contains a player's name, score and letter pool. It's passed by reference so any changes to the pool are kept.
    */
    void exchangeChip(Player &player);

    /** 
        * Allows exchange of 2 chips from a player's pool!
        * @param player: a struct of type Player which contains a player's name, score and letter pool. It's passed by reference so any changes to the pool are kept.
    */
    void exchangeChips(Player &player);

    /** 
        * Finds the game's winners and outputs them.
    */
    void declareWinner();

    /** 
        * Executes the game.
        * @param player: a struct of type Player which contains a player's name, score and letter pool. It's passed by reference so any changes to the pool are kept.
    */
    void execute();

    /** 
        * Ends the game abruptly according to contemplated cases, them being: all words captured, player wants to declare a tie, letter pool is empty.
    */
    void abruptEnd();

    /** 
        * Outputs the board.
    */
    void printBoard() const;

    //Auxiliar functions for print board

    /** 
        * Sets the text color.
        * @param color: an unsigned int that refers to the desired color.
    */
    void setcolor(unsigned int color) const;

    /** 
        * Sets the text color and text background color.
        * @param color: an unsigned int that refers to the desired text color.
        * @param background_color: an unsigned int that refers to the desired background color.
    */      
    void setcolor(unsigned int color, unsigned int background_color) const;

    /** 
        * Reverts the color back to standard black-and-white output.
    */  
    void setColorNormal() const;

    /** 
        * Sets the output color for the board.
    */  
    void setColorBoard() const;

    /** 
        * Sets the color for captured letters.
    */  
    void setColorCaptured() const;

    /** 
        * Sets the color for non-captured letters.
    */  
    void setColorNotCaptured() const;

private:
    int playerCount, bagSize; //playerCount stores the number of players, bagSize stores the number of different letters in the board
    pair<int, int> boardDim; //a pair of ints containing the dimensions of the board
    vector<Player> players; //a vector of Player structs, each containing the recquired data for each player (name, score and letter pool)
    string boardName; //a string containing the board file's name
    vector<char> letterBag; //a char vector that's used as a game's pool
    vector<string> boardWords; //a string vector containing all words placed in a board
    vector<vector<Info>> vectorBoard; //a bidimensional vector containg Info structs that's used as the actual board
    map<char, int> code{{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20},  {'V', 21},  {'W', 22},  {'X', 23},  {'Y', 24},  {'Z', 26}, {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9}, {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14}, {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19}, {'u', 20}, {'v', 21},  {'w', 22},  {'x', 23},  {'y', 24},  {'z', 26}}; //a map used to turn chars into numbers, which is recquired for most computations like making plays and capturing letters
    map<string, vector<string>> wordData; //a map whose keys are the words in a board and their respective values are string vectors containing all coordinates a word occupies - this is used to keep track of capturing;
    bool unique = false, end = false; //unique is used whenever a player can only do 1 play and end is used to check if the game's finished.
};