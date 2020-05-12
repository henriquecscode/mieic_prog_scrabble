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
        dictionary.push_back(word);
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
        std::cout << "Input a board size [1,20]\n";
        size = readInt();
    } while (size <= 0 || size > 20);
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

    //X coordinates
    std::cout << ' ';
    for (int i = 0; i < size; i++)
    {
        std::cout << char(ASCII_a + i);
    }
    std::cout << '\n';

    for (int i = 0; i < size; i++)
    {
        std::cout << char(ASCII_A + i);
        for (int j = 0; j < size; j++)
        {
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
        if (board[x - versor[0]][y - versor[1]] != ' ')
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
        if (board[x + versor[0]][y + versor[1]] != ' ')
        {
            // Our word is ending right before another, which is impossible
            return false;
        }
    }

    for (int i = 0; i < word_len; i++)
    {
        int this_x = x + versor[0] * i;
        int this_y = y + versor[1] * i;
        if (board[this_x][this_y] == ' ')
        {
            continue;
        }
        else
        {
            if (board[this_x][this_y] != word[i])
            {
                //We are missmatching words
                return false;
            }
        }
    }

    //Passed all conditions, we need to add the word to the board and to the final vector
    saveWord(word, x, y, word_orientation, versor);
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
        file  << '\n' << char(it->coords[0]) << char(it->coords[1]) << ' ' << char(it->position) << ' ' << it->wordgit ;
    }
}

void BoardBuilder::saveWord(std::string word, int x, int y, orientation word_orientation, int versor[2])
{

    int this_x, this_y;
    //Put the word in the board
    for (int i = 0; i < word.length(); i++)
    {
        this_x = x + versor[0] * i;
        this_y = y + versor[1] * i;
        board[this_y][this_x] = word[i];
    }

    // Remove from dictionary to prevent reuse
    // We calculate the index again which is not perfect
    // I didn't want to keep track of the index in a private variable or has a parameter in every function
    dictionary.erase(dictionary.begin() + binarySearch(word));

    //Put word in the storage array
    toUpper(word);
    BoardWord word_to_save = {{char(y + ASCII_A), char(x + ASCII_a)}, word_orientation, word};
    used_words.push_back(word_to_save);
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

void BoardBuilder::toUpper(std::string &word) const{
    //http://www.cplusplus.com/reference/locale/toupper/
    std::locale loc;
    for(int i = 0; i < word.length(); i++){
        word[i] = std::toupper(word[i], loc);
    }
}