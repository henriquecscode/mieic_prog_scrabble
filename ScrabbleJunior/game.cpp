#include "game.h"
using namespace std;

int Game::getIndex(int size)
{
    int result = rand() % size; //getting an index;
    return result;
}

void Game::abruptEnd(){
    string fin;
    if (end == true){
        declareWinner();
    } else {
        cout << "This game is a tie!" << endl;
        
        for (int i = 0; i < players.size(); i++){
            cout << players[i].name << ", you finished with " << players[i].score << " points." << endl;
        }
        cout << "Great job, everyone!" << endl;
    }

    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Input anything to close the game! " << endl;
    cin >> fin;
    exit(0);
}

void Game::checkPlays(string &p1, string &p2){
    if (isupper(p1[1])){
        p1[1] = p1[1] + 32;
    }

    if (isupper(p2[1])){
        p2[1] = p2[1] + 32;
    }

    if (islower(p1[0])){
        p1[0] = p1[0] - 32;
    }

    if (islower(p2[0])){
        p2[0] = p2[0] - 32;
    }

    if ((p1 == "Yy") || (p2 == "Yy")){
        abruptEnd();
    }
}

void Game::beginningInstructions()
{
    //Let's just start with some information for the players.
    setColorNormal();

    cout << "Hi, welcome to SCRABBLE JUNIOR!" << endl;
    cout << "In this game, you'll have a board with words to fill, letter by letter." << endl;
    cout << "Each finished turn may award you with 1 to 2 points (depending on the number of words completed in that turn)." << endl;
    cout << "Per turn, you MUST input 2 plays, which only recquires you to input coordinates of VALID non-captured letters." << endl;
    cout << "Always capture letters by order!" << endl;
    cout << "A coordinate is just an uppercase letter (line) followed by a lowercase letter (collumn)." << endl;
    cout << "If you can only play one letter, play it and you'll get a new pool from the bag." << endl;
    cout << "If your pool doesn't have any letters you can play, you'll have to swap some of them." << endl;
    cout << "You can only play letters you have in your pool into non-captured spaces of the board" << endl;
    cout << "It's on you to know if you have chips to play or not, so input 'Zz' whenever you wish to exchange chips (max. of 2)." << endl;
    cout << "Switching chips counts as a turn!" << endl;
    cout << "We advise you to play whenever you know you can, so don't fool yourself by trying to be 'sneaky'." << endl;
    cout << "Everytime you have no chips, you'll get new ones automatically." << endl;
    cout << "If you wish to end a game before it declares a winner, input Yy as a play in a turn!" << endl;
    cout << "This GAME OVER will be declared as a tie." << endl;
    cout << endl;
}

void Game::prepGame(Board &board)
{
    vector<vector<Info>> vecBo = board.boardBuilder();
    vectorBoard = vecBo; //we get the actual board;
    wordData = board.getWordData(); //and this transfers

    cout << "Number of players: ";
    cin >> playerCount; //and number of players.

    while ((cin.fail()) || (playerCount > 4) || (playerCount < 2)) //dealing with invalid input
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Input a valid number of players (max: 4, min: 2): ";
        cin >> playerCount;
    }

    players.resize(playerCount); //we adjust the players vector

    for (int i = 0; i < playerCount; i++) //getting player's names
    {
        string name;
        cout << "What's your name, player " << i + 1 << "? ";
        cin >> name;
        players[i].name = name;

        while (cin.fail()) //dealing with invalid input
        {
            cout << "What's your name, player " << i + 1 << "? ";
            cin >> players[i].name;
        }
    }

    //Getting all letters in a set so we can create a pool for each player.
    set<char> lBagSet; 
    vector<string> vecWo = board.getWords(); //getting the board words
    boardDim = board.getSize(); //the size of the board will start counting from 0
    sort(vecWo.begin(), vecWo.end()); //sorting the words
    boardWords = vecWo; //passing the words into a private element of the class
    int letterCount = 0;

    for (int i = 0; i < boardWords.size(); i++)
    {
        for (int j = 0; j < boardWords[i].size(); j++)
        {
            lBagSet.insert(boardWords[i].at(j)); //creating a set of all letters in the board (no repetition)
        }
    }

    vector<char> bag;
    bag.assign(lBagSet.begin(), lBagSet.end());

    for (int i = 0; i < vectorBoard.size(); i++)
    {
        for (int j = 0; j < vectorBoard[i].size(); j++)
        {
            if (vectorBoard[i][j].letter != ' ')
            {
                letterCount++; //number of letters (intersecting letters only count once) in the board
            }
        }
    }

    if (letterCount < 14){ //minimum of letters!
        letterCount = 14;
    }

    letterCount = letterCount + playerCount*7; //to compensate for the letter pool!

    int bagSize = bag.size();
    for (int k = 0; k < letterCount; k++)
    {
        int index = getIndex(bagSize);
        letterBag.push_back(bag[index]); //this creates a pool with letterCount number of letters;
    }

    for (int i = 0; i < playerCount; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            int index = getIndex(letterBag.size()); //a random index
            players[i].pool.push_back(letterBag[index]); //we insert a random chip into the player's pool
            letterBag.erase(letterBag.begin() + index); //and erase it from the letter bag
        }
    }
    printBoard();
}

void Game::getNewPool(Player &player)
{

    char answer;
    if (letterBag.size() >= 7) //when the letter bag allows it, we generate a new pool
    {
        for (int j = 0; j <= 6; j++)
        {
            int index = getIndex(letterBag.size()); //a random index
            player.pool[j] = letterBag[index]; //we change the invalid chip
            letterBag.erase(letterBag.begin() + index); //and erase it from the game's pool
        }
    }
    else //other wise, the game will give the players a choice to end the game right then and there
    {
        cout << "You were supposed to get a new set of chips, but there aren't enough letters left in the pool!";
        cout << "Would you like to end the game now or go until the automatic END (empty pool) (Y/N)? ";
        cin >> answer;

        while (cin.fail() || ((answer != 'Y') && (answer != 'y') && (answer != 'N') && (answer != 'n'))) //to deal with bad input
        {
            cout << "Couldn't get that! Try again: ";
            cin >> answer;
        }

        if ((answer = 'Y') || (answer = 'y'))
        {
            end = true;
            abruptEnd();
        }
    }
}

void Game::printPool(Player &player)
{
    cout << "POOL [0-6] = "; //printing the pool;
    for (int i = 0; i <= 6; i++)
    {
        cout << " " << player.pool[i] << " ";
    }
}

void Game::checkPool(Player &player)
{
    int count = 0;
    sort(player.pool.begin(), player.pool.end());
    for (int i = 0; i <= 6; i++) 
    {
        if (player.pool[i] == '-')
        {
            count++; //+1 for each invalid (-) chip;
        }
    }
    if (count == 7) //if all chips are invalid, the player needs a new pool;
    {
        getNewPool(player);
    }
    else if (count == 6) //if there's only one invalid chip, output will be readjusted;
    {
        unique = true;
    }
}

pair<string, string> Game::getPlay(Player &player)
{
    string play1, play2;
    cout << "It's your turn, " << player.name << ". Use ZZ as a play to exchange chips!" << endl;
    cout << "The pool has " << letterBag.size() << " letters, beware of that!" << endl;
    checkPool(player); //getting information from the pool
    printPool(player); //printing it
    cout << endl;
    cout << "Current Score: " << player.score << endl;
    if (unique) //in case the player only has one valid chip
    {
        unique = false;
        cout << endl;
        cout << "Please input your play: ";
        cin >> play1;
        play2 = "Uu"; //this is a special play, that the game will recognize as nothing, basically
        int p1_1 = code[play1.at(0)], p1_2 = code[play1.at(1)];

        while (cin.fail() || (((p1_1 > boardDim.first) || (p1_2 > boardDim.second)) && (play1 != "Zz")))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Input a valid play (with letters as coordinates): ";
            cin >> play1;

            p1_1 = code[play1.at(0)]; //setting these variables because they're part of the conditions for the cycle
            p1_2 = code[play1.at(1)];
        }
    }
    else //when a player can do 2 plays
    {
        cout << endl;
        cout << "Please input your plays: ";
        cin >> play1 >> play2;
        checkPlays(play1, play2);
        int p1_1 = code[play1.at(0)], p1_2 = code[play1.at(1)], p2_1 = code[play2.at(0)], p2_2 = code[play2.at(1)];

        //Dealing with bad input
        while (cin.fail() || (((p1_1 > boardDim.first) || (p1_2 > boardDim.second)) && (play1 != "Zz")) || (((p2_1 > boardDim.first) || (p2_2 > boardDim.second)) && (play2 != "Zz")))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Input valid plays (with letters as coordinates): ";
            cin >> play1 >> play2;

            p1_1 = code[play1.at(0)]; //setting these variables because they're part of the conditions for the cycle
            p1_2 = code[play1.at(1)];
            p2_1 = code[play2.at(0)];
            p2_2 = code[play2.at(1)];
        }
    }

    checkPlays(play1, play2); //this rearranges the plays into the prefered format
    return make_pair(play1, play2);
}

void Game::exchangeChip(Player &player)
{
    int bagSize = letterBag.size(); //in order for the following code to work, we need to create a local variable
    if (bagSize >= 1) //checking if it's possible to exchange one chip
    {
        int ind1; //Index of the chip to switch in the playerPool.
        cout << "Hey, " << player.name << ". Let's do some chip switchin', shall we?" << endl;
        cout << "NOTE: You cannot exchange an invalid/empty chip (it's represented as a -)." << endl;
        cout << "Below, is your letter pool." << endl;
        printPool(player);
        cout << endl;
        cout << "Input the index of the chip you wish to switch: ";
        cin >> ind1;

        while ((cin.fail()) || (ind1 > 6) || (ind1 < 0)) //dealing with bad input
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Input the index of the chip you wish to switch: ";
            cin >> ind1;
        }

        if (player.pool[ind1] != '-')
        { //No invalid chips allowed, here.
            int index = getIndex(letterBag.size()); //geting the index
            player.pool[ind1] = letterBag[index]; // setting the new chip
            letterBag.erase(letterBag.begin() + index); //erasing it from the game's pool;
            printPool(player); //print pool, to show the changes!
        }
        else
        //if the player inputs the index of an invalid chip, he's done for
        {
            cout << "Invalid chip. No chip switching for you!" << endl;
        }

        cout << endl;
    }
    else //otherwise, the game will give an apology to the player!
    {
        cout << "The pool is empty. The game will end after this turn!" << endl;
        cout << "Play your chips, if you can. Otherwise, do an invalid play!" << endl;
    }
}

void Game::exchangeChips(Player &player)
{
    int bagSize = letterBag.size();
    if (bagSize >= 2)
    {
        int ind1, ind2; //Index of the chip to switch in the playerPool.
        cout << "Hey, player " << player.name << ". Let's do some chip switchin', shall we?" << endl;
        cout << "NOTE: You cannot exchange an invalid/empty chip (it's represented as a -)." << endl;
        cout << "Below, is your letter pool." << endl;
        printPool(player);
        cout << endl;
        cout << "Input the indexes of the chips you wish to switch (put a space between them!): ";
        cin >> ind1 >> ind2;

        while ((cin.fail()) || (ind1 > 6) || (ind1 < 0) || (ind2 > 6) || (ind2 < 0))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Input the indexes of the chips you wish to switch (put a space between them!): ";
            cin >> ind1 >> ind2;
        }

        if ((player.pool[ind1] != '-') && (player.pool[ind2] != '-'))
        {                                               //1 invalid chip = no switches.
            int index = getIndex(letterBag.size());                     //get index
            player.pool[ind1] = letterBag[index];       //give new letter
            letterBag.erase(letterBag.begin() + index); //delete from pool

            index = getIndex(letterBag.size()); //repeat
            player.pool[ind2] = letterBag[index];
            letterBag.erase(letterBag.begin() + index);

            //and let the player see his new pool!
            printPool(player);
        }
        else
        {
            cout << "You can't exchange invalid (-) chips. No switching for you!" << endl;
        }
        cout << endl;
    }
    else //if the pool no longer has the chips for a double switch, the player will be warned about it!
    {
        cout << "It's not possible to exchange 2 chips." << endl;
        cout << "Play the chips you have, if you can. Otherwise, do invalid plays!" << endl;
    }
}

void Game::checkCapture(string word, Player &player)
{
    vector<string> a = wordData[word];
    if (a.size() == 0) //if the coordinate vector is empty -> the word has been fully captured!
    {
        player.score++; 
        int index = 0;
        index = findIndex(boardWords, word);
        boardWords.erase(boardWords.begin() + index);
    }
}

int Game::findIndex(vector<string> vect, string findee)
{
    //Simple binary search function
    int bottom = 0;
    int top = vect.size() - 1;
    int middle;
    while (bottom <= top)
    {
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

void Game::checkWords(Info &letter, Player &player, string play)
{
    //this function uses the letter's WORDS vector to check if it's a valid play
    vector<char>::iterator it = find(player.pool.begin(), player.pool.end(), letter.letter);

    if (letter.words.size() == 1) //if the letter only belongs to one word...
    {
        vector<string> a = wordData[letter.words[0]]; //a is now the list of coordinates.
        int index = findIndex(a, play);
        if (index == 0) //the index must be 0 (which means it'd be the first uncaptured letter - making it a valid play)
        {
            a.erase(a.begin() + index);
            wordData[letter.words[0]] = a;
            player.pool[distance(player.pool.begin(), it)] = '-';
            checkCapture(letter.words[0], player);
        }
        else //if the index isn't 0, it means the player is trying to capture a middle letter that's not the first uncaptured letter in the word!
        {
            letter.state = false;
            cout << "You can't capture that letter (" << play << "), " << player.name << ". Be more careful next time!" << endl;
        }
    }
    else if (letter.words.size() == 2) //if the letter belongs to 2 words, it's a little more complicated
    {   //at least one of the letters must be the first uncaptured letter in a word, otherwise it's an invalid play!
        vector<string> a = wordData[letter.words[0]];
        int index = findIndex(a, play);

        if (index == 0) //same logic as before, only with double the stuff!
        {
            vector<string> b = wordData[letter.words[1]];
            int index2 = findIndex(b, play);

            a.erase(a.begin() + index);
            b.erase(b.begin() + index2);
            wordData[letter.words[0]] = a;
            wordData[letter.words[1]] = b;
            player.pool[distance(player.pool.begin(), it)] = '-';
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
                player.pool[distance(player.pool.begin(), it)] = '-';
                checkCapture(letter.words[0], player);
                checkCapture(letter.words[1], player);
            }
            else //if the letter does not belong to a word (i.e. it's already been captured), it's an invalid play!
            {
                letter.state = false; //reverting back the letter's state
                cout << "You can't capture that letter (" << play << "), " << player.name << ". You have to do it in order!" << endl;
            }
        }
    }
}

void Game::captureLetter(Info &letter, Player &player, string play) //this captures letters
{
    if ((find(player.pool.begin(), player.pool.end(), letter.letter) != player.pool.end()) && (letter.state == false) && (letter.letter != ' '))
    {
        letter.state = true;
        checkWords(letter, player, play);
    }
    else if ((find(player.pool.begin(), player.pool.end(), letter.letter) == player.pool.end()) || (letter.state != false) || (letter.letter == ' '))
    {
        cout << "That wasn't a valid play (" << play << "), "  << player.name << ". No capturing for you!" << endl;
    }
}

void Game::makePlay(Player &player, pair<string, string> plays)
{
    char p1_line = code[plays.first.at(0)], p1_col = code[plays.first.at(1)], p2_line = code[plays.second.at(0)], p2_col = code[plays.second.at(1)];
    bool p1 = true, p2 = true;
    while (true)
    {
        //Let's start by checking if the player wants to do any switching.
        if ((plays.first == "Zz") && (plays.second == "Zz")) 
        {
            exchangeChips(player);
            p1 = false;
            p2 = false;
        }
        else if (plays.first == "Zz")
        { //Checking if we have a "I need new chips" situation;
            exchangeChip(player);
            p1 = false;
        }
        else if (plays.second == "Zz")
        {
            exchangeChip(player);
            p2 = false;
        }
        else if ((plays.second == "Uu") && (plays.first == "Zz"))
        {
            p2 = false;
            exchangeChip(player);
        }
        else if ((plays.second == "Uu") && (plays.first != "Zz"))
        {
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

void Game::game(vector<Player> &players)
{
    while (!end)
    {
        for (int i = 0; i < players.size(); i++)
        {
            cout << endl;
            pair<string, string> plays = getPlay(players[i]);
            makePlay(players[i], plays);
            printBoard();

            if ((boardWords.size() == 0) || (letterBag.size() == 0))
            {
                end = true;
                abruptEnd();
            }
        }
    }
}

void Game::declareWinner()
{
    vector<int> finalScores;
    vector<Player> winners;

    for (int i = 0; i < playerCount; i++)
    {
        finalScores.push_back(players[i].score);
    }

    int max = *max_element(finalScores.begin(), finalScores.end());

    for (int i = 0; i < finalScores.size(); i++)
    {
        if (finalScores[i] == max)
        {
            winners.push_back(players[i]);
        }
    }

    if (winners.size() != 1)
    {
        cout << "Congratulations, ";
        for (int j = 0; j < winners.size(); j++)
        {
            if (j == winners.size() - 2)
            {
                cout << winners[j].name << " and ";
                continue;
            }
            else if (j == winners.size() - 1)
            {
                cout << winners[j].name;
                continue;
            }
            cout << players[j].name << ", ";
        }
        cout << ", you're all winners!" << endl;
    }
    else
    {
        cout << "Congratulations, " << winners[0].name << ", you're the winner!" << endl;
    }
}

void Game::execute()
{
    beginningInstructions();
    Board board;
    prepGame(board);
    game(players);
    declareWinner();
}

void Game::printBoard() const
{
    setColorNormal();
    std::cout << endl;
    std::cout << "  ";
    for (int i = 0; i <= boardDim.second; i++)
    {
        std::cout << std::setw(2) << char(ASCII_a + i);
    }
    std::cout << '\n';

    for (int i = 0; i <= boardDim.first; i++)
    {
        setColorNormal();
        std::cout << std::setw(2) << char(ASCII_A + i);
        setColorBoard();
        for (int j = 0; j <= boardDim.second; j++)
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
    string fin;
    Game game;
    srand(time(NULL));
    game.execute();
    cout << "Input anything to close the game! " << endl;
    cin >> fin;
    exit(1);
    return EXIT_SUCCESS;
}
