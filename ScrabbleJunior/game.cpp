#include "game.h"
using namespace std;

void Game::beginningInstructions()
{
    //Let's just start with some information for the players.
    setColorNormal();
    
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
    sort(vecWo.begin(), vecWo.end());
    boardWords = vecWo;

    for (int i = 0; i < boardWords.size(); i++)
    {
        for (int j = 0; j < boardWords[i].size(); j++)
        {
            lBagSet.insert(boardWords[i].at(j));
        }
    }

    //From here we create the vector with all characters.
    letterBag.assign(lBagSet.begin(), lBagSet.end());
    bagSize = letterBag.size();

    for (int i = 0; i < players; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            int index = rand() % bagSize;
            playerPool[i].push_back(letterBag[index]);
        }
    }
    printBoard();
}

void Game::getNewPool(int player)
{
    srand(time(NULL));
    for (int j = 0; j < 6; j++)
    {
        int index = rand() % bagSize;
        playerPool[player].push_back(letterBag[index]);
    }
}

void Game::printPool(int player)
{
    cout << "POOL [0-6] = "; //printing the pool;
    for (int i = 0; i <= 6; i++)
    {
        cout << " " << playerPool[player][i] << " ";
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

pair<string, string> Game::getPlay(int player)
{
    string play1, play2;
    cout << "It's your turn, player " << player + 1 << ". Use ZZ as a play to exchange chips!" << endl;
    checkPool(player);
    printPool(player);
    cout << endl;
    cout << "Please input your plays: ";
    cin >> play1 >> play2;
    return make_pair(play1, play2);
}

void Game::exchangeChip(int player)
{
    srand(time(NULL));
    int ind1; //Index of the chip to switch in the playerPool.
    cout << "Hey, player " << player + 1 << ". Let's do some chip switchin', shall we?" << endl;
    cout << "NOTE: You cannot exchange an invalid/empty chip (it's represented as a -)." << endl;
    cout << "Below, is your letter pool." << endl;
    printPool(player);
    cout << endl;
    cout << "Input the index of the chip you wish to switch: ";
    cin >> ind1;
    while (cin.fail())
    {
        cout << "Input the index of the chip you wish to switch: ";
        cin >> ind1;
    }

    int index = rand() % bagSize;
    playerPool[player][ind1] = letterBag[index];
    printPool(player);
    cout << endl;
}

void Game::exchangeChips(int player)
{
    srand(time(NULL));
    int ind1, ind2; //Index of the chip to switch in the playerPool.
    cout << "Hey, player " << player + 1 << ". Let's do some chip switchin', shall we?" << endl;
    cout << "NOTE: You cannot exchange an invalid/empty chip (it's represented as a -)." << endl;
    cout << "Below, is your letter pool." << endl;
    printPool(player);
    cout << endl;
    cout << "Input the indexes of the chips you wish to switch (put a space between them!): ";
    cin >> ind1 >> ind2;
    while (cin.fail())
    {
        cout << "Input the indexes of the chips you wish to switch (put a space between them!): ";
        cin >> ind1 >> ind2;
    }

    int index = rand() % bagSize;
    playerPool[player][ind1] = letterBag[index];
    index = rand() % bagSize;
    playerPool[player][ind2] = letterBag[index];
    printPool(player);
    cout << endl;
}

void Game::checkCapture(string word, int player)
{
    vector<string> a = wordData[word];
    if (a.size() == 0)
    {
        scoreBoard[player]++;
        int index = 0;
        index = findIndex(boardWords, word);
        boardWords.erase(boardWords.begin() + index);
    }
}

int Game::findIndex(vector<string> &vect, string &findee)
{
    int bottom = 0;
    int top = vect.size() - 1;
    int middle;
    while (bottom <= top){
        middle = (bottom + top) / 2;
        if (vect[middle] > findee)
        {
            top = middle - 1;
        }
        else if (vect[middle] < findee)
        {
            bottom = middle + 1;
        }
        else
        { 
            return middle;
        }
    }
    return -1;
}

void Game::checkWords(Info &letter, int player, string play)
{
    vector<char>::iterator it = find(playerPool[player].begin(), playerPool[player].end(), letter.letter);

    if (letter.words.size() == 1)
    {
        vector<string> a = wordData[letter.words[0]]; //a is now the list of coordinates.
        int index = findIndex(a, play);
        if (index == 0)
        {
            a.erase(a.begin() + index);
            wordData[letter.words[0]] = a;
            playerPool[player][distance(playerPool[player].begin(), it)] = '-';
            checkCapture(letter.words[0], player);
        }
        else
        {
            letter.state = false;
            cout << "You can't capture that letter, Player " << player + 1 << ". Be more careful next time!" << endl;
        }
    }
    else if (letter.words.size() == 2)
    {
        vector<string> a = wordData[letter.words[0]];
        int index = findIndex(a, play);

        if (index == 0)
        {
            vector<string> b = wordData[letter.words[1]];
            int index2 = findIndex(b, play);

            a.erase(a.begin() + index);
            b.erase(b.begin() + index2);
            wordData[letter.words[0]] = a;
            wordData[letter.words[1]] = b;
            playerPool[player][distance(playerPool[player].begin(), it)] = '-';
            checkCapture(letter.words[0], player);
            checkCapture(letter.words[1], player);
        }
        else if ((index != 0) && (index != -1))
        {
            vector<string> b = wordData[letter.words[1]];
            int index2 = findIndex(b, play);

            if (index2 == 0)
            {
                a.erase(a.begin() + index);
                b.erase(b.begin() + index2);
                wordData[letter.words[0]] = a;
                wordData[letter.words[1]] = b;
                playerPool[player][distance(playerPool[player].begin(), it)] = '-';
                checkCapture(letter.words[0], player);
                checkCapture(letter.words[1], player);
            }
            else
            {
                letter.state = false;
                cout << "You can't capture that letter (" << play << "), Player " << player + 1 << ". You have to do it in order!" << endl;
            }
        }
    }
}

void Game::captureLetter(Info &letter, int player, string play)
{
    if ((find(playerPool[player].begin(), playerPool[player].end(), letter.letter) != playerPool[player].end()) && (letter.state == false) && (letter.letter != ' '))
    {
        letter.state = true;
        checkWords(letter, player, play);
    }
    else
    {
        cout << "That wasn't a valid play, player " << player + 1 << ". No capturing for you!" << endl;
    }
}

void Game::makePlay(int player, pair<string, string> plays)
{
    char p1_line = code[plays.first.at(0)], p1_col = code[plays.first.at(1)], p2_line = code[plays.second.at(0)], p2_col = code[plays.second.at(1)];
    bool p1 = true, p2 = true;
    while (true)
    {
        //Let's start by checking if the player wants to do any switching.
        if (((plays.first == "Zz") || (plays.first == "ZZ") || (plays.first == "zz") || (plays.first == "zZ")) && ((plays.second == "Zz") || (plays.second == "ZZ") || (plays.second == "zz") || (plays.second == "zZ")))
        {
            exchangeChips(player);
            p1 = false;
            p2 = false;
            ;
        }
        else if ((plays.first == "Zz") || (plays.first == "ZZ") || (plays.first == "zz") || (plays.first == "zZ"))
        { //Checking if we have a "I need new chips" situation;
            exchangeChip(player);
            p1 = false;
        }
        else if ((plays.second == "Zz") || (plays.second == "ZZ") || (plays.second == "zz") || (plays.second == "zZ"))
        {
            exchangeChip(player);
            p2 = false;
        }
        break;
    }

    if ((p1 == true) && (p2 == true))
    {
        captureLetter(vectorBoard[p1_line][p1_col], player, plays.first);
        captureLetter(vectorBoard[p2_line][p2_col], player, plays.second);
    }
    else if (p1 == true)
    {
        captureLetter(vectorBoard[p1_line][p1_col], player, plays.first);
    }
    else if (p2 == true)
    {
        captureLetter(vectorBoard[p2_line][p2_col], player, plays.second);
    }
}

void Game::game(Board &board, int &players, vector<int> &scoreBoard)
{
    bool end = false;
    while (!end)
    {
        for (int i = 0; i < players; i++)
        {
            cout << endl;
            pair<string, string> plays = getPlay(i);
            makePlay(i, plays);
            printBoard();

            if (boardWords.size() == 0)
            {
                end = true;
                break;
            }
        }

    }
}

void Game::declareWinner(){
    int max = *max_element(scoreBoard.begin(), scoreBoard.end());
    vector<int> winners;

    for (int i = 0; i < scoreBoard.size(); i++){
        if (scoreBoard[i] == max){
            winners.push_back(i);
        }
    }

    if (winners.size() != 1){
        cout << "Congratulations, Players ";
        for (int j = 0; j < winners.size(); j++){
            if (j == winners.size()-2){
                cout << winners[j] + 1 << " and ";
                continue;
            } else if (j == winners.size() - 1){
                cout << winners[j] + 1;
                continue;
            }
            cout << j + 1 << ", ";
        }
        cout << ", you're all winners!" << endl;
    } else {
        cout << "Congratulations, Player " << winners[0] + 1 << ", you're the winner!" << endl;
    }
}

void Game::execute()
{
    beginningInstructions();
    Board board;
    prepGame(board);
    game(board, players, scoreBoard);
    declareWinner();
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
        std::cout << std::setw(2) << char(ASCII_A + i);
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
    unsigned int final_color = color + background_color * 16;
    SetConsoleTextAttribute(hCon, final_color);
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
    setcolor(RED, LIGHTGRAY);
}

void Game::setColorNotCaptured() const
{
    setcolor(BLACK, LIGHTGRAY);
}

int main()
{
    Game game;
    game.execute();
    exit(1);
    return EXIT_SUCCESS;
}