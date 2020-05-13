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
    void beginningInstructions();
    int getIndex(int size);
    void game(Board &board, vector<Player> &players);
    void checkPlays(string &p1, string &p2);
    void prepGame(Board &board);
    void executePlay(string play, Player &player);
    void getNewPool(Player &player);
    void printPool(Player &player);
    void checkPool(Player &player);
    void checkWords(Info &letter, Player &player, string play);
    int findIndex(vector<string> &vect, string &findee);
    void checkCapture(string word, Player &player);
    void makePlay(Player &player, pair<string, string> plays);
    pair<string, string> getPlay(Player &player);
    void captureLetter(Info &letter, Player &player, string play);
    void exchangeChip(Player &player);
    void exchangeChips(Player &player);
    void declareWinner();
    void execute();
    void abruptEnd();
    void printBoard() const;

    //Auxiliar functions for print board
    void setcolor(unsigned int color) const;
    void setcolor(unsigned int color, unsigned int background_color) const;
    void setColorNormal() const;
    void setColorBoard() const;
    void setColorCaptured() const;
    void setColorNotCaptured() const;

private:
    int playerCount, bagSize, boardSize;
    vector<Player> players;
    string boardName;
    vector<char> letterBag;
    vector<string> boardWords;
    vector<vector<Info>> vectorBoard;
    map<char, int> code{{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20},  {'V', 21},  {'W', 22},  {'X', 23},  {'Y', 24},  {'Z', 26}, {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9}, {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14}, {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19}, {'u', 20}, {'v', 21},  {'w', 22},  {'x', 23},  {'y', 24},  {'z', 26}};
    map<string, vector<string>> wordData;
    bool unique = false, end = false;
};