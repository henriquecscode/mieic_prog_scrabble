#include <iomanip>
#include <iostream>
#include <vector>
// PROG - MIEIC
// JAS
// Example of a program that prints colored characters on the console (in text mode)
#include <cstdlib>
#include <windows.h>
using namespace std;
//==========================================================================================
//COLOR CODES: (alternative: use symbolic const’s)
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

typedef struct // Cria uma STRUCT para armazenar os dados de uma pessoa
{
    char letter;          //a letra
    vector<string> words; // vetor com as palavras em que a char aparece;
    bool state = false;   // estado da letra
} Info;
/*
//==========================================================================================
void clrscr(void)
{
    COORD coordScreen = {0, 0}; // upper left corner
    DWORD cCharsWritten;
    DWORD dwConSize;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hCon, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    // fill with spaces
    FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hCon, &csbi);
    FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    // cursor to upper left corner
    SetConsoleCursorPosition(hCon, coordScreen);
}
//==========================================================================================
// Position the cursor at column 'x', line 'y'
// The coodinates of upper left corner of the screen are (x,y)=(0,0)
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
*/
//==========================================================================================
// Set text color
void setcolor(unsigned int color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}
//==========================================================================================
// Set text color & background
void setcolor(unsigned int color, unsigned int background_color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    if (background_color == BLACK)
        SetConsoleTextAttribute(hCon, color);
    else
        SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN |
                                          BACKGROUND_RED);
}
//==========================================================================================
// Fill the screen with colored numbers

void setColorNormal()
{
    setcolor(WHITE, BLACK);
}

void setColorBoard()
{
    setcolor(BLACK, LIGHTGRAY);
}

void setColorCaptured()
{
    setcolor(RED);
}

void setColorNotCaptured()
{
    setcolor(BLACK);
}

void printBoard()
{
    static const int ASCII_A = 65;
    static const int ASCII_a = 97;
    int size = 10;
    //X coordinates
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
            if (board[i][j].state == true)
            {
                setColorCaptured();
            }
            std::cout << std::setw(2);
            std::cout << board[i][j].letter;
        }
        std::cout << '\n';
    }
    setColorNormal();
}

int main()
{
    printBoard();
}

#include <cstdlib>
#include <windows.h>
#include <iomanip>

// Set text color
void setcolor(unsigned int color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}
//==========================================================================================
// Set text color & background
void setcolor(unsigned int color, unsigned int background_color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    if (background_color == BLACK)
        SetConsoleTextAttribute(hCon, color);
    else
        SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN |
                                          BACKGROUND_RED);
}
//==========================================================================================
// Fill the screen with colored numbers
#include <iomanip>
#include <cstdlib>
#include <windows.h>

#define BLACK 0
#define RED 4
#define LIGHTGRAY 7
#define WHITE 15
#define ASCII_A 65
#define ASCII_a 97

void setColorNormal()
{
    setcolor(WHITE, BLACK);
}

void setColorBoard()
{
    setcolor(BLACK, LIGHTGRAY);
}

void setColorCaptured()
{
    setcolor(RED);
}

void setColorNotCaptured()
{
    setcolor(BLACK);
}

void printBoard()
{
    int size = 10;
    //X coordinates
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
            if (board[i][j].state == true)
            {
                setColorCaptured()
            }
            std::cout << std::setw(2);
            std::cout << board[i][j].letter;
        }
        std::cout << '\n';
    }
    setColorNormal();
}