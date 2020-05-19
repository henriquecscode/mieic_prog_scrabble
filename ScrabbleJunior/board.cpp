#include "board.h"


vector<string> Board::getWords() const{
    return words;
}

map<string, vector<string>> Board::getWordData() const{
    return wordData;
}

pair<int, int> Board::getSize() const{
    return make_pair(lines - 1, cols - 1);
}

void Board::setWord(vector<vector<Info>> &vectorBoard, string coordinates, char orientation, string word){
    map<char, int> code{{'A', 0},{'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19}, {'a', 0},{'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9}, {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14}, {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19}};
    map<int, string> revCode0{{0, "A"},{1, "B"}, {2, "C"}, {3, "D"}, {4, "E"}, {5, "F"}, {6, "G"}, {7, "H"}, {8, "I"}, {9, "J"}, {10, "K"}, {11, "L"}, {12, "M"}, {13, "N"}, {14, "O"}, {15, "P"}, {16, "Q"}, {17, "R"}, {18, "S"}, {19, "T"}};
    map<int, string> revCode1{{0, "a"},{1, "b"}, {2, "c"}, {3, "d"}, {4, "e"}, {5, "f"}, {6, "g"}, {7, "h"}, {8, "i"}, {9, "j"}, {10, "k"}, {11, "l"}, {12, "m"}, {13, "n"}, {14, "o"}, {15, "p"}, {16, "q"}, {17, "r"}, {18, "s"}, {19, "t"}};
    int line = code[coordinates.at(0)], col = code[coordinates.at(1)]; //line and collumn declaration;
    if (orientation == 'H'){
        //Horizontal means we have to traverse collumns - second dimension;
        for (int i = 0; i < word.size(); i++){
            wordData[word].push_back(revCode0[line] + revCode1[col + i]);
            vectorBoard[line][col + i].words.push_back(word);
            vectorBoard[line][col + i].letter = word.at(i);
        }
    } else if (orientation == 'V'){ //vertical means we have to traverse lines - first dimension;
        for (int i = 0; i < word.size(); i++){
            wordData[word].push_back(revCode0[line + i] + revCode1[col]);
            vectorBoard[line + i][col].words.push_back(word);
            vectorBoard[line + i][col].letter = word.at(i);
        } 
    }
}

vector<vector<Info>> Board::boardBuilder(){
    string fileLine, boardName;
    ifstream file; //File variable;
    stringstream filestr; //b
    int x, y; //Respectively, vertical and horizontal dimensions;
    char separator;

    cout << "Please input the name of the board (include the file extension .txt): ";
    cin >> boardName; //Getting the board name.
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    file.open(boardName);

    while (true){
        if (file.is_open())
        {
            break;
        } else {
            cout << "Input a valid board name: ";
            cin >> boardName;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            file.open(boardName);
        }
    }

    getline(file, fileLine);
    filestr << fileLine; //Passing all file contents to a stringstream;
    filestr >> x >> separator >> y;
    lines = x;
    cols = y;

    while (!file.eof()){
        getline(file, fileLine);
        locations.push_back(fileLine.substr(0, 2));
        orientations.push_back(fileLine.at(3));
        words.push_back(fileLine.substr(5, fileLine.size()-1));
    }

    //Time to actually form the board.
    int length = words.size();
    Info info;
    info.letter = ' ';
    vector<vector<Info>> vectorBoard(lines, vector<Info>(cols, info));

    for (int i = 0; i < length; i++){
        setWord(vectorBoard, locations[i], orientations[i], words[i]);
    }

    return vectorBoard; 
}

/*int main(){
    string name = "BOARD.txt";
    Board board;
    board.boardBuilder(name);

}*/