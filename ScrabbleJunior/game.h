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


class Game
{
public:
    void beginningInstructions();
    void game(Board &board, int &players, vector<int> &scoreBoard);
    void prepGame(Board &board);
    void printBoard(vector<vector<Info>> &vectorBoard);
    void executePlay(string play, int &player);
    void getNewPool(int player);
    void printPool(int player);
    void checkPool(int player);
    void checkWords(Info &letter, int player, string play);
    int findIndex(vector<string> &vect, string &findee);
    void checkCapture(string word, int player);
    void makePlay(int player, pair<string, string> plays);
    pair<string, string> getPlay(int player);
    void captureLetter(Info &letter, int player, string play);
    void exchangeChip(int player);
    void exchangeChips(int player);
    void declareWinner();
    void execute();

    void printBoard() const;

    //Auxiliar functions for print board
    void setcolor(unsigned int color) const;
    void setcolor(unsigned int color, unsigned int background_color) const;
    void setColorNormal() const;
    void setColorBoard() const;
    void setColorCaptured() const;
    void setColorNotCaptured() const;

private:
    int players, bagSize;
    string boardName;
    vector<int> scoreBoard;
    vector<vector<char>> playerPool;
    vector<char> letterBag;
    vector<string> boardWords;
    vector<vector<Info>> vectorBoard;
    map<char, int> code{{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19}, {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9}, {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14}, {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19}};
    map<string, vector<string>> wordData;
};