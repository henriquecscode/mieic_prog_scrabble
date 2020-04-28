#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <locale>

#define ASCII_A 65
#define ASCII_a 97

typedef enum {
    vertical = 'V',
    horizontal = 'H'
} orientation;

struct BoardWord
{
    char coords[2];
    orientation position;
    std::string word;
};

class BoardBuilder
{
public:
    BoardBuilder();
    void setFile();
    void readFile();
    void showDictionary() const;
    void setSize();
    void setBoard();
    void setWordInBoard(std::string word);
    void printBoard() const;
    void saveBoard() const;
    void constructBoard();
    std::string getWord(const std::string &expected_word) const;
    std::string getIncorrectWord(const int &index) const;
    bool insertWord(std::string word, int x, int y, orientation word_orientation);
    int binarySearch(const std::string &word) const;
    void saveData(std::ofstream &file) const;
    void saveWord(std::string word, int x, int y, orientation word_orientation, int versor[2]);
    int readInt();
    std::string readWord() const;
    void askCoordinate(int &x, int&y) const;
    orientation askOrientation() const;
    void toUpper(std::string &word) const;

private:
    int size;
    std::ifstream dict_file;
    std::vector<std::string> dictionary;
    std::vector<std::vector<char>> board;
    std::vector<BoardWord> used_words;
};