#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <bits/stdc++.h> 
#include <utility>
#include <vector>
using namespace std;

typedef struct // Cria uma STRUCT para armazenar os dados de uma letra.
{
    char letter; //a letra
    vector<string> words;   // vetor com as palavras em que a char aparece;
    bool state = false;    // estado da letra
} Info;

class Board{
    public:
        /** 
            * Creates the board - in a bidimensional vector.
            * @return: returns a bidimensional vector of elements from the class Info.
        */
        vector<vector<Info>> boardBuilder();

        /** 
            * Sets a word on the board (bidimensional vector of elements from the class Info).
            * @param vectorBoard: passed by reference that represents the board containing information for each letter and word on it. This element allows the changes to be saved on the board.
            * @param coordinates: a string that expresses the coordinates of the first letter from the word being set on the board.
            * @param orientation: a char that represents the orientation to set the word in - just from it we can figure out how to traverse the board and set the word.
            * @param word: a string containing the word intended to be set.
        */
        void setWord(vector<vector<Info>> &vectorBoard, string coordinates, char orientation, string word);

        /** 
            * Returns a vector containing each word from the board (each in a string).
            * @return: a vector of strings containing all words from the board
        */
        vector<string> getWords() const;

        /** 
            * Returns a map containing information necessary to track the captured letters and words during a game.
            * @return: A map where the keys correspond to words on the board and for each key a vector of strings containing all coordinates occupied by the word.
        */
        map<string, vector<string>> getWordData() const;

        /** 
            * Returns the dimensions of the board.
            * @return: a pair containing the dimensions of the board (through integer numbers).
        */
        pair<int, int> getSize() const;

    private:
        string boardName; /*A string containing the name of the board*/
        vector<string> locations; /*A string vector containing the first coordinate of each word*/
        vector<char> orientations; /*A char vector containing the orientation of each word*/
        vector<string> words; /*A string vector with all words for a board*/
        map<string, vector<string>> wordData; /*A map containing strings as keys (corresponding to words on the board) and a string vector containing all coordinates which that word occupies*/
        int lines = 0, cols = 0;
};