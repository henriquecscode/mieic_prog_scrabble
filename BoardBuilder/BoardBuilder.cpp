#include "BoardBuilder.h"

BoardBuilder::BoardBuilder()
{
    setFile();
    readFile();
    setSize();
    setBoard();
    saveBoard();
}

void BoardBuilder::setFile()
{
    std::string filename;
    do
    {
        std::cout << "Input a valid filename" << '\n';
        std::cin >> filename;
        dict_file.open(filename);

    } while (!dict_file.is_open() && !std::cin.eof());
}

void BoardBuilder::readFile()
{
    std::string word;
    while (getline(dict_file, word))
    {
        if (word.length() > 2)
        { //Only allows words with more than 2 letters
            dictionary.push_back(word);
        }
    }
    dict_file.close();
}

void BoardBuilder::showDictionary() const
{
    for (auto it = dictionary.begin(); it != dictionary.end(); it++)
    {
        std::cout << *it << '\n';
    }
}

void BoardBuilder::setSize()
{
    do
    {
        std::cout << "Input a board size [5,20]\n";
        size = readInt();
    } while (size <= 4 || size > 20);
    constructBoard();
}

void BoardBuilder::setBoard()
{
    std::string word;

    std::cout << "Input a word in lower case to set the board. Ctrl^Z to end\n";
    word = readWord();
    while (!std::cin.eof())
    {
        word = getWord(word);

        if (word != "")
        {
            std::cout << "The word is:" << word << '\n'; // Debugging;

            //Proceed
            setWordInBoard(word);
        }
        else
        {
            std::cout << "Invalid selection\n";
        }

        std::cout << "Input a word in lower case to set the board. Ctrl^Z to end\n";
        word = readWord();
    }
}

void BoardBuilder::setWordInBoard(std::string word)
{
    printBoard(); //Let the user know how the board looks like at time of editing

    int x, y;
    askCoordinate(x, y);
    orientation word_orientation = askOrientation();

    bool successful = insertWord(word, x, y, word_orientation);
    if (successful)
    {
        std::cout << "Your word was successfully added\n";
        printBoard();
    }
    else
    {
        std::cout << "Error adding word. Please verify the position you are inserting in is valid\n";
    }
}

void BoardBuilder::printBoard() const
{
    std::cout << "  ";
    for (int i = 0; i < size; i++)
    {
        std::cout << std::setw(2) << char(ASCII_a + i);
    }
    std::cout << '\n';

    for (int i = 0; i < size; i++)
    {
        std::cout << std::setw(2) << char(ASCII_A + i);
        for (int j = 0; j < size; j++)
        {
            std::cout << std::setw(2);
            std::cout << board[i][j];
        }
        std::cout << '\n';
    }
}

void BoardBuilder::saveBoard() const
{
    std::ofstream outputfile;
    std::string filename;
    std::cout << "Input the name of the file to save the board to\n";
    std::cin.clear();
    std::cin >> filename;

    outputfile.open(filename + ".txt");

    saveData(outputfile);
    outputfile.close();
}

void BoardBuilder::constructBoard()
{
    // Construct an empty board after knowing what size it will be
    board = std::vector<std::vector<char>>(size, std::vector<char>(size, ' '));
    board_coord_to_word = std::vector<std::vector<std::vector<BoardWord>>>(size, std::vector<std::vector<BoardWord>>(size, std::vector<BoardWord>()));
}

std::string BoardBuilder::getWord(const std::string &expected_word) const
{
    int index = binarySearch(expected_word);
    if (dictionary[index] == expected_word)
    {
        return expected_word;
    }

    return getIncorrectWord(index);
}

std::string BoardBuilder::getIncorrectWord(const int &index) const
{
    //Could go in a function
    std::cout << "Couldn't find the word. Did you mean:\n"
              << "0: " << dictionary[index] << '\n'
              << "1: "
              << dictionary[index + 1] << '\n'
              << "Press any other key if not\n";

    int answer;
    std::cin >> answer;
    if (std::cin.fail() || std::cin.eof())
    {
        return "";
    }
    if (answer == 0)
    {
        return dictionary[index];
    }
    if (answer == 1)
    {
        return dictionary[index + 1];
    }
    return "";
}

bool BoardBuilder::insertWord(std::string word, int x, int y, orientation word_orientation)
{
    int word_len = word.length();

    //Versor to know the direction of the word
    int versor[2] = {word_orientation == horizontal, word_orientation == vertical};

    //Check if the word is inside the board
    if (x + versor[0] * word_len >= size || y + versor[1] * word_len >= size)
    {
        // Out of bounds
        return false;
    }

    //Check for words in the same orientation (on the start)
    if (x * versor[0] + y * versor[1] == 0)
    {
        // Means that the word is against one of the margins
        // No need to check if it is adjacent with a word on the same direction
    }
    else
    {
        if (board[y - versor[1]][x - versor[0]] != ' ')
        {
            // Our word is starting right after another, which is impossible
            return false;
        }
    }

    //Check for words in the same orientation (on the end)
    if (x * versor[0] + y * versor[1] == size - 1)
    {
        // Means that the word is against one of the margins
        // No need to check if it is adjacent with a word on the same direction
    }
    else
    {
        if (board[y + versor[1]][x + versor[0]] != ' ')
        {
            // Our word is ending right before another, which is impossible
            return false;
        }
    }

    for (int i = 0; i < word_len; i++)
    {
        int this_x = x + versor[0] * i;
        int this_y = y + versor[1] * i;

        //Check for problems in the word itself
        if (board[this_y][this_x] != ' ')
        {
            //There was already a letter there

            for (auto it = board_coord_to_word[this_y][this_x].begin(); it != board_coord_to_word[this_y][this_x].end(); it++)
            //Iterator to the vector on the current position (Max size is 2)
            {
                if (it->word_orientation == word_orientation)
                {
                    //There is already a word with the same orientation here
                    return false;
                }
            }

            if (board[this_y][this_x] != word[i])
            {
                //We are missmatching words
                return false;
            }
        }
        bool proceed = true;
        //Let's check for problems in it's footprint: the coordinates adjacent in the perpendicular direction
        if ((x - versor[1]) * versor[1] + (y - versor[0]) * versor[0] >= 0)
        {
            // We can check the footprint in the left/up side
            std::vector<BoardWord> footprint_words = board_coord_to_word[this_y - versor[0]][this_x - versor[1]];
            proceed = proceed && checkWordFootprint(this_x - versor[1], this_y - versor[0], footprint_words, word_orientation);
        }
        if ((x + versor[1]) * versor[1] + (y + versor[0]) * versor[0] <= size - 1)
        {
            // We can check the footprint in the right/down side
            std::vector<BoardWord> footprint_words = board_coord_to_word[this_y + versor[0]][this_x + versor[1]];
            proceed = proceed && checkWordFootprint(this_x + versor[1], this_y + versor[0], footprint_words, word_orientation);
        }

        //Check the conditions
        if (proceed)
        {
            continue;
        }
        else
        {
            //A condition was not met
            return false;
        }
    }

    //Passed all conditions, we need to add the word to the board and to the final vector
    saveWord(word, x, y, word_orientation, versor);
    return true;
}

bool BoardBuilder::checkWordFootprint(int footprint_x, int footprint_y, std::vector<BoardWord> footprint_words, orientation word_orientation) const
{
    for (auto it = footprint_words.begin(); it != footprint_words.end(); it++)
    {
        if (it->word_orientation == word_orientation)
        {
            return false;
        }

        int footprint_word_versor[2] = {it->word_orientation == horizontal, it->word_orientation == vertical};
        int footprint_word_last_x = it->num_coords[0] + (it->word.size() - 1) * footprint_word_versor[0];
        int footprint_word_last_y = it->num_coords[1] + (it->word.size() - 1) * footprint_word_versor[1];
        if (footprint_word_last_x == footprint_x && footprint_word_last_y == footprint_y)
        {
            // The word ends adjacent to the word we are trying to insert
            return false;
        }
    }
    return true;
}

int BoardBuilder::binarySearch(const std::string &word) const
{
    int bottom = 0;
    int top = dictionary.size() - 1;
    int middle;
    while (bottom <= top)
    {

        middle = (bottom + top) / 2;
        if (dictionary[middle] > word)
        {
            top = middle - 1;
        }
        else if (dictionary[middle] < word)
        {
            bottom = middle + 1;
        }
        else
        { //Found
            return middle;
        }
    }

    //Exception handling for -1
    if (top < 0)
    {
        top = 0;
    }
    if (top == dictionary.size() - 1)
    {
        top -= 1;
    }
    return top;
}

void BoardBuilder::saveData(std::ofstream &file) const
{
    //Still missing conversion to upper case
    file << size << " x " << size;
    for (auto it = used_words.begin(); it != used_words.end(); it++)
    {
        file << '\n'
             << char(it->coords[0]) << char(it->coords[1]) << ' ' << char(it->word_orientation) << ' ' << toUpper(it->word);
    }
}

void BoardBuilder::saveWord(std::string word, int x, int y, orientation word_orientation, int versor[2])
{

    // Remove from dictionary to prevent reuse
    // We calculate the index again which is not perfect
    // I didn't want to keep track of the index in a private variable or has a parameter in every function
    dictionary.erase(dictionary.begin() + binarySearch(word));

    //Put word in the storage array
    BoardWord word_to_save = {{char(y + ASCII_A), char(x + ASCII_a)}, {x, y}, word_orientation, word};
    used_words.push_back(word_to_save);
    BoardWord this_word = used_words.back(); //Reference to the word we just modified

    int this_x, this_y;
    //Put the word in the board
    for (int i = 0; i < word.length(); i++)
    {
        this_x = x + versor[0] * i;
        this_y = y + versor[1] * i;
        board[this_y][this_x] = word[i];
        board_coord_to_word[this_y][this_x].push_back(this_word); //Save the word in this board position
    }
}

int BoardBuilder::readInt()
{
    int x;
    do
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> x;

    } while (std::cin.fail());

    return x;
}

std::string BoardBuilder::readWord() const
{
    std::string word;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> word;

    return word;
}

void BoardBuilder::askCoordinate(int &x, int &y) const
{

    char column, row;
    do
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Which row will the word start" << '\n';
        std::cin >> row;
    } while (row < ASCII_A || row >= ASCII_A + size);

    do
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Which column will the word start" << '\n';
        std::cin >> column;
    } while (column < ASCII_a || column >= ASCII_a + size);

    //Now we have both chars, and we need to pass them to int
    x = column - ASCII_a;
    y = row - ASCII_A;
}

orientation BoardBuilder::askOrientation() const
{
    char x;
    do
    {
        std::cout << "The word will be horizontal(H) or vertical(V)" << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> x;
    } while (std::cin.fail() || (x != vertical && x != horizontal));

    orientation word_orientation = static_cast<orientation>(x);
    return word_orientation;
}

std::string BoardBuilder::toUpper(std::string word) const
{
    //http://www.cplusplus.com/reference/locale/toupper/
    std::locale loc;
    for (int i = 0; i < word.length(); i++)
    {
        word[i] = std::toupper(word[i], loc);
    }
    return word;
}