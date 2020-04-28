
#include "game.h"
using namespace std;

void Game::beginningInstructions()
{
    //Let's just start with some information for the players.
    cout << "Hi, welcome to SCRABBLE JUNIOR!" << endl;
    cout << "In this game, you'll have a board with words to fill, letter by letter." << endl;
    cout << "Each finished turn may award you with 1 to 2 points (depending on the number of words completed in that turn)." << endl;
    cout << "Per turn, you MUST input 2 plays, which only recquires you to input coordinates of non-captured letters." << endl;
    cout << "A coordinate is just an uppercase letter (line) followed by a lowercase letter (collumn)." << endl;
    cout << "If you can only play one letter, you'll get another one from the bag." << endl;
    cout << "If your pool doesn't have any letters you can play, you'll have to swap some of them." << endl;
    cout << "You can only play letters you have in your pool into non-captured spaces of the board" << endl;
    cout << "It's on you to know if you have chips to play or not, so input 'Zz' whenever you wish to exchange chips (max. of 2)." << endl;
    cout << "Switching chips counts as a turn!" << endl;
    cout << "We advise you to play whenever you know you can, so don't fool yourself by trying to be 'sneaky'." << endl;
    cout << "Everytime you have no chips, you'll get new ones automatically." << endl;
    cout << endl;
}

void Game::prepGame(Board &board)
{
    srand(time(NULL));
    cout << "So now, please input the name of the board (include the file extension .txt): ";
    cin >> boardName; //Getting the board name.
    cout << "Number of players: ";
    cin >> players; //And number of players.

    scoreBoard.resize(players, 0); //Sets the scoreboard and playerPool vectors to the right size.
    playerPool.resize(players);

    vector<vector<Info>> vecBo = board.boardBuilder(boardName);
    vectorBoard = vecBo; //We create the actual board;
    wordData = board.getWordData();

    //Getting all letters in a set so we can create a pool for each player.
    set<char> lBagSet;
    vector<string> vecWo = board.getWords();
    boardWords = vecWo;
    for (int i = 0; i < boardWords.size(); i++)
    {
        for (int j = 0; j < boardWords[i].size(); j++)
        {
            lBagSet.insert(boardWords[i].at(j));
        }
    }

    //From here we create the vector with all characters.
    vector<char> letterBag(lBagSet.begin(), lBagSet.end());
    for (int i = 0; i < players; i++)
    {
        for (int j = 0; j < playerPool[i].size(); j++)
        {
            int index = rand() % letterBag.size();
            playerPool[i].push_back(letterBag[index]);
        }
    }
}

void Game::getNewPool(int player)
{
    for (int j = 0; j < 6; j++)
    {
        int index = rand() % letterBag.size();
        playerPool[player].push_back(letterBag[index]);
    }
}

void Game::printPool(int player)
{
    cout << "POOL [0-6] = "; //printing the pool;
    for (int i = 0; i <= 6; i++)
    {
        cout << "|" << playerPool[player][i] << "| ";
    }
}

void Game::checkPool(int player)
{
    int count = 0;
    for (int i = 0; i < 6; i++)
    {
        if (playerPool[player][i] == '-')
        {
            count++;
        }
    }
    if (count == 6)
    {
        getNewPool(player);
    }
}

void Game::getPlay(int player)
{
    cout << "It's your turn, player " << player + 1 << ". Use ZZ as a play to exchange chips!" << endl;
    checkPool(player);
    printPool(player);
    cout << endl;
    cout << "Please input your plays: ";
    cin >> play1 >> play2;
}

void Game::exchangeChip(int player)
{
    int ind1; //Index of the chip to switch in the playerPool.
    cout << "Hey, player " << player + 1 << ". Let's do some chip switchin', shall we?" << endl;
    cout << "NOTE: You cannot exchange an invalid/empty chip (it's represented as a -)." << endl;
    cout << "Below, is your letter pool." << endl;
    printPool(player);
    while (cin.fail())
    {
        cout << "Input the index of the chip you wish to switch: ";
        cin >> ind1;
    }

    int index = rand() % letterBag.size();
    playerPool[player][ind1] = letterBag[index];
}

void Game::exchangeChips(int player)
{
    int ind1, ind2; //Index of the chip to switch in the playerPool.
    cout << "Hey, player " << player + 1 << ". Let's do some chip switchin', shall we?" << endl;
    cout << "NOTE: You cannot exchange an invalid/empty chip (it's represented as a -)." << endl;
    cout << "Below, is your letter pool." << endl;
    printPool(player);
    while (cin.fail())
    {
        cout << "Input the indexes of the chips you wish to switch (put a space inbetween them!): ";
        cin >> ind1 >> ind2;
    }

    int index = rand() % letterBag.size();
    playerPool[player][ind1] = letterBag[index];
    index = rand() % letterBag.size();
    playerPool[player][ind2] = letterBag[index];
}

//YOU WERE HERE
void Game::checkWords(Info letter, int player)
{
    for (int i = 0; i < letter.words.size(); i++)
    {
        //GET THE LIST FROM THE MAP, CHANGE IT HOWEVER YOU NEED AND THEN UPDATE IT IN THE MAP
        wordData.at(letter.words[i]);
    }
}

void Game::captureLetter(Info letter, int player)
{
    if ((letter.state == false) && (letter.letter != ' '))
    {
        letter.state = true;
        checkWords(letter, player);
    }
    else
    {
        cout << "That wasn't a valid play, player " << player + 1 << ". No capturing for you!" << endl;
    }
}

void Game::makePlay(int player)
{
    char p1_line = code[play1.at(0)], p1_col = code[play1.at(1)], p2_line = code[play2.at(0)], p2_col = code[play2.at(1)];
    bool p1 = true, p2 = true;
    while (true)
    {
        //Let's start by checking if the player wants to do any switching.
        if ((play1 == "ZZ") && (play2 == "Zz"))
        {
            exchangeChips(player);
            p1 = false;
            p2 = false;
            ;
        }
        else if ((play1 == "Zz"))
        { //Checking if we have a "I need new chips" situation;
            exchangeChip(player);
            p1 = false;
        }
        else if (play2 == "Zz")
        {
            exchangeChip(player);
            p2 = false;
        }
        break;
    }

    if ((p1 == true) && (p2 == true))
    {
        captureLetter(vectorBoard[p1_line][p1_col], player);
        captureLetter(vectorBoard[p2_line][p2_col], player);
    }
    else if (p1 == true)
    {
        captureLetter(vectorBoard[p1_line][p1_col], player);
    }
    else if (p2 == true)
    {
        captureLetter(vectorBoard[p2_line][p2_col], player);
    }
}

void Game::game(Board &board, int &players, vector<int> &scoreBoard)
{
    while (!end)
    {
        for (int i = 0; i < players; i++)
        {
            getPlay(i);
            makePlay(i);
        }
    }
}

void Game::execute()
{
    beginningInstructions();
    Board board;
    prepGame(board);
    game(board, players, scoreBoard);
}

void Game::printBoard() const
{
    static int size = vectorBoard.size();
    setColorNormal();
    std::cout << "  ";
    for (int i = 0; i < size; i++)
    {
        std::cout << std::setw(2) << char(ASCII_a + i);
    }
    std::cout << '\n';

    for (int i = 0; i < size; i++)
    {
        setColorNormal();
        std::cout << char(ASCII_A + i);
        setColorBoard();
        for (int j = 0; j < size; j++)
        {
            setColorNotCaptured();
            if (vectorBoard[i][j].state == true)
            {
                setColorCaptured();
            }
            std::cout << std::setw(2);
            std::cout << vectorBoard[i][j].letter;
        }
        std::cout << '\n';
    }
    setColorNormal();
}


// Set text color
void Game::setcolor(unsigned int color) const
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}
//==========================================================================================
// Set text color & background
void Game::setcolor(unsigned int color, unsigned int background_color) const
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    if (background_color == BLACK)
        SetConsoleTextAttribute(hCon, color);
    else
        SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN |
                                          BACKGROUND_RED);
}
void Game::setColorNormal() const
{
    setcolor(WHITE, BLACK);
}

void Game::setColorBoard() const
{
    setcolor(BLACK, LIGHTGRAY);
}

void Game::setColorCaptured() const
{
    setcolor(RED);
}

void Game::setColorNotCaptured() const
{
    setcolor(BLACK);
}



int main()
{
    Game game;
    game.execute();
    exit(1);
    return EXIT_SUCCESS;
}