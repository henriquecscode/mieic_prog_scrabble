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
        vector<vector<Info>> boardBuilder(string name);
        void setWord(vector<vector<Info>> &vectorBoard, string coordinates, char orientation, string word);
        vector<string> getWords() const;
        map<string, vector<string>> getWordData() const;
    private:
        string boardName;
        vector<string> locations; //This will store all the information from the file
        vector<char> orientations;
        vector<string> words;
        map<string, vector<string>> wordData;
};