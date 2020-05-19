#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <locale>

#define ASCII_A 65
#define ASCII_a 97

/** 
 * Enumeration of possible word orientations
*/
typedef enum
{
    vertical = 'V',  /**< Vertical orientation*/
    horizontal = 'H' /**< Horizontal orientation*/
} orientation;

/** 
 * Struct defining how a word is stored
*/
struct BoardWord
{
    char coords[2];               /**< Alphabetical line and column in the board*/
    int num_coords[2];            /**< Numeric x and y coordinate in the board*/
    orientation word_orientation; /**< Orientation of the word in the board*/
    std::string word;             /**< Word in the board*/
};

class BoardBuilder
{
public:
    /**
     * Constructs the board
    */
    BoardBuilder();

    /**
     * Asks for and opens dictionary file
    */
    void setFile();

    /**
     * Reads the dictionary file
    */
    void readFile();

    /**
     * Gets and set board dimensions
    */
    void setDimensions();

    /**
     * Asks for words and tries to insert them in the board
    */
    void setBoard();

    /** 
     * Given a viable word and position, puts the word in the board
     * @param word: word to be put in the board
    */
    void setWordInBoard(std::string word);

    /**
     * Prints the board in the console
     */
    void printBoard() const;

    /** 
     * Saves the state of the board to a file that is to be specified
    */
    void saveBoard() const;

    /**
     * Creates an empty board with the given size
     */
    void constructBoard();

    /** 
     * Verify if the word the user gave is possible to use. Otherwise, provide an alternative 
     * @param expected_word: Check if this word is in the dictionary
     * @return: A word if function was successful. Otherwise an empty string
    */
    std::string getWord(const std::string &expected_word) const;

    /** 
     * User chooses a word from the dictionary given an index.
     * @param index: Index of the closest possible word in the dictionary
     * @return: A corret word if function was successful. Otwherwise, and empty string
    */
    std::string getIncorrectWord(const int &index) const;

    /** 
     * Inserts the word given in the board, if possible
     * @param word: Word to be inserted
     * @param x: x coordinate of the first letter of the word
     * @param y: y coordinate of the first letter of the word
     * @param word_orientation: Orientation of the word in the board
     * @return: true if was able to save the word in the board. false otherwise
    */
    bool insertWord(std::string word, int x, int y, orientation word_orientation);

    /** 
     * Footprint: Tiles adjacent to those occupied by the word. Only in the direction perpendicular to the word's
     * Checks if there is a word in the footprint tile that may be prevent the word from being inserted
     * @param footprint_x: x coordinate of the footprint tile
     * @param footprint_y: y coordinate of the footprint tile
     * @param footprint_words: words that may cross this footprint tile
     * @param footprint_left_up: true if the footprint tile is on the left or above the word. false if otherwise
     * @param word_orientation: Orientation of the word in the board
     * @return 
    */
    bool checkWordFootprint(int footprint_x, int footprint_y, std::vector<BoardWord> footprint_words, bool footprint_left_up, orientation word_orientation) const;

    /** 
     * Checks if a word is in the dictionary. Returns the index if so. Otherwise index of the first word that is smaller than the word given (Edge cases return 0 or size-1)
     * @param  word: Check if word is in the dictionary
     * @return Index of the word in the dictionary. If word is not in the dictionary index of the first word that is smaller than the word given (Edge cases return 0 or size-1)
    */
    int binarySearch(const std::string &word) const;

    /** 
     * Saves the state of the board in the specified file
     * @param file: File to save the state of the board to
    */
    void saveData(std::ofstream &file) const;

    /** 
     * Permanently stores the word in a data structure
     * @param word: Word to save
     * @param x: x coordinate of the first letter of the word to save
     * @param y: y coordinate of the first letter of the word to save
     * @param word_orientation: Orientation of the word in the board
     * @param versor: Versor describing the direction of the word
    */
    void saveWord(std::string word, int x, int y, orientation word_orientation, int versor[2]);

    /** 
     * Asks the user for an integer
     * @return integer given by the user 
    */
    int readInt();

    /** 
     * Asks the user for a word
     * @return: word given by the user
    */
    std::string readWord() const;

    /** 
     * Asks the user for a x and y coordinate
     * @param x: x coordinate to be altered
     * @param y: y coordinate to be altered
    */
    void askCoordinate(int &x, int &y) const;

    /** 
     * Asks the user for an orientation
     * @return orientation given by the user
    */
    orientation askOrientation() const;

    /** 
     * Converts a string to upper case
     * @param word: word to be converted
     * @return: word in upper case
    */
    std::string toUpper(std::string word) const;

private:
    int width;  /**< Width of the board*/
    int height; /**< Height of the board*/
    std::ifstream dict_file;  /**< File with the words of the dictionary*/
    std::vector<std::string> dictionary;  /**< Dictionary of the possible words*/
    std::vector<std::vector<char>> board;  /**< Characters in each position of the board*/
    std::vector<std::vector<std::vector<BoardWord>>> board_coord_to_word;  /**< Words that pass through each position of the board */
    std::vector<BoardWord> used_words;  /**< Stored words inserted in the board*/
};