#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "../headers/Board.h"
#include "../headers/Square.h"
#include "../headers/Dictionary.h"
#include "../headers/Tile.h"

using namespace std;

Board::Board (string board_file_name)
{
    isFirstMove = true;
    ifstream boardFile (board_file_name.c_str());
    string row;

    _x = _y = _startx = _starty = 0; // to appease compiler
    if (!boardFile.is_open())
        throw invalid_argument("Cannot open file: " + board_file_name);
    getline (boardFile, row);
    stringstream s1 (row);
    s1 >> _x >> _y;
    getline (boardFile, row);
    stringstream s2 (row);
    s2 >> _startx >> _starty;
    _startx --; _starty --;  // coordinates from 0 in array

    // Initialize board grid
    boardVect.resize(_y);
    for (int i = 0 ; i < _y; ++ i)
    {
        getline (boardFile, row);
        boardVect[i].resize(_x);
        for (int j = 0; j < _x; ++ j)
        {
            // Fill in the following based on how you store the board.
            // Starting position is 'S'
            if (i == _starty && j == _startx) 
            { 
                Square *s = new Square(i, j, "***", "2n");
                boardVect[i][j] = s; 
            }
            else switch (row[j]) {
            case '.' :
            {
                Square *s = new Square(i, j, "[.]", "1");
                boardVect[i][j] = s;
                break;
            } 
            case '2' : 
            {
                Square *s = new Square(i, j, "2L ", "2");
                boardVect[i][j] = s;
                break;
            } 
            case '3' : 
            {
                Square *s = new Square(i, j, "3L ", "3");
                boardVect[i][j] = s;
                break;
            } 
            case 'd' : 
            {
                Square *s = new Square(i, j, "2W ", "2n");
                boardVect[i][j] = s;
                break;
            } 
            case 't' : 
            {
                Square *s = new Square(i, j, "3W ", "3n");
                boardVect[i][j] = s;
                break;
            } 
            default:
                string error = "Improper character in Board file: ";
                throw invalid_argument(error + row[j]);
            }
        }
    }
    boardFile.close ();
}

// Delete all dynamically allocated squares that make up the board
Board::~Board()
{
    for (int i = 0; i < _y; ++i){
        for(int j = 0; j < _x; ++j){
            delete boardVect[i][j];
        }
    }
}

int Board::getRowSize()
{
    return _x;
}

int Board::getColSize()
{
    return _y;
}

int Board::getStartX()
{
    return _startx;
}

int Board::getStartY()
{
    return _starty;
}

// This function finds vertical words connected to newly placed horizontal tiles
string Board::vertWord(Tile* t, int row, int col, int& points)
{
    string word = t->isBlank() ? t->getUse() : t->getLetter(); // Initialize word with tile letter
    points += t->getPoints();
    int up = row - 1;
    int down = row + 1;
    while(up >= 0 && boardVect[up][col]->occupied()){
        word = boardVect[up][col]->getValue() + word;
        points += boardVect[up][col]->returnPoints();
        up--;
    }    
    while(down <= _x - 1 && boardVect[down][col]->occupied()){
        word += boardVect[down][col]->getValue();
        points += boardVect[down][col]->returnPoints();
        down++;
    }
    return word;
}

// This function finds horizontal words connected to newly placed vertical tiles
string Board::horizWord(Tile* t, int row, int col, int& points)
{
    string word = t->isBlank() ? t->getUse() : t->getLetter(); // Initialize word with tile letter
    points += t->getPoints();
    int right = col + 1;
    int left = col - 1;
    while(left >= 0 && boardVect[row][left]->occupied()){
        word = boardVect[row][left]->getValue() + word;
        points += boardVect[row][left]->returnPoints();
        left--;
    }    
    while(right <= _y - 1 && boardVect[row][right]->occupied()){
        word += boardVect[row][right]->getValue();
        points += boardVect[row][right]->returnPoints();
        right++;
    }
    return word;
}

// This function finds the main word created by placed tiles
// Makes calls to find other words formed by a move
// Also scores every word that is created by a move
vector<string> Board::allWords(int row, int col, char dir, int& score, vector<Tile*>& usedTiles)
{
    vector<string> words;
    string tempWord = "";
    int multiplier = 1;
    int secondaryMultiplier = 1;
    int points = 0;
    string word2;
    int right = col;
    int left = col - 2;
    if(left == -1){
        left = 0;
    }
    int up = row - 2;
    if(up == -1){
        up = 0;
    }
    int down = row;
    int counter = 1;
    bool isValid = false;
    int wordLen = usedTiles.size();
    tempWord += usedTiles[0]->isBlank() ? usedTiles[0]->getUse() : usedTiles[0]->getLetter();
    string mult = boardVect[row - 1][col - 1]->getMultiplier();
    if(mult == "3n"){
        multiplier *= 3;
        score += (3 * usedTiles[0]->getPoints());
    } 
    else if(mult == "2n"){
        multiplier *= 2;
        score += (2 * usedTiles[0]->getPoints());
    } 
    else if(mult == "3") score += (3 * usedTiles[0]->getPoints());
    else if(mult == "2") score += (2 * usedTiles[0]->getPoints());
    else score += (usedTiles[0]->getPoints()) * multiplier;
    
    if(dir == '-'){
        points = 0;
        // Check if there are words in the vertical direction
        word2 = vertWord(usedTiles[0], row - 1, col - 1, points);
        if(word2.length() != 1){
            points *= multiplier;
            score += points;
            words.push_back(word2);
        }
        while(left >= 0 && right < _y){    
            // Add letters left adjacent to the first placed tile
            if(boardVect[row - 1][left]->occupied()){
                isValid = true;
                tempWord = boardVect[row - 1][left]->getValue() + tempWord;
                score += (boardVect[row - 1][left]->returnPoints()) * multiplier;
                if(left != 0){
                    left--;
                    continue;
                }
            }
            // Add letters right adjacent to placed tiles
            if(boardVect[row - 1][right]->occupied()){
                isValid = true;
                tempWord += boardVect[row - 1][right]->getValue();
                score += (boardVect[row - 1][right]->returnPoints()) * multiplier;
                if (right != _y - 1){
                    right++;
                    continue;
                }
            }
            // Else use placed tiles to form word
            else{
                if(counter >= wordLen) break;
                tempWord += usedTiles[counter]->isBlank() ? usedTiles[counter]->getUse() : usedTiles[counter]->getLetter();
                mult = boardVect[row - 1][right]->getMultiplier();
                if(mult == "3n"){
                    secondaryMultiplier *= 3;
                    multiplier *= 3;
                    score += (usedTiles[counter]->getPoints()) * multiplier;
                } 
                else if(mult == "2n"){
                    secondaryMultiplier *= 2;
                    multiplier *= 2;
                    score += (usedTiles[counter]->getPoints()) * multiplier;
                }
                else if(mult == "3") score += (3 * usedTiles[counter]->getPoints()) * multiplier;
                else if(mult == "2") score += (2 * usedTiles[counter]->getPoints()) * multiplier;
                else score += (usedTiles[counter]->getPoints()) * multiplier;
                points = 0;
                word2 = vertWord(usedTiles[counter], row - 1, right, points);
                if(word2.length() != 1){
                    points *= secondaryMultiplier;
                    score += points;
                    words.push_back(word2);
                }
                right++;
                counter++;
            }
        }
        // If not first move and no adjacent tiles, return empty vector
        if(!isValid && !isFirstMove){
            return words;
        }
        // Add word to be checked by dictionary
        words.push_back(tempWord);
    }
    // Same as above, replace left with up & right with down
    // Forms main word in vertical direction and connected horizontal words
    else if(dir == '|'){
        points = 0;
        word2 = horizWord(usedTiles[0], row - 1, col - 1, points);
        if(word2.length() != 1){
            points *= multiplier;
            score += points;
            words.push_back(word2);
        }
        while(up >= 0 && down < _x){    
            if(boardVect[up][col - 1]->occupied()){
                isValid = true;
                tempWord = boardVect[up][col - 1]->getValue() + tempWord;
                score += (boardVect[up][col - 1]->returnPoints()) * multiplier;
                up--;
                continue;
            }
            if(boardVect[down][col - 1]->occupied()){
                isValid = true;
                tempWord += boardVect[down][col - 1]->getValue();
                score += (boardVect[down][col - 1]->returnPoints()) * multiplier;
                down++;
                continue;
            }
            else{
                if(counter >= wordLen) break;
                tempWord += usedTiles[counter]->isBlank() ? usedTiles[counter]->getUse() : usedTiles[counter]->getLetter();
                mult = boardVect[down][col - 1]->getMultiplier();
                if(mult == "3n"){
                    secondaryMultiplier *= 3;
                    multiplier *= 3;
                    score += (usedTiles[counter]->getPoints()) * multiplier;
                } 
                else if(mult == "2n"){
                    secondaryMultiplier *= 2;
                    multiplier *= 2;
                    score += (usedTiles[counter]->getPoints()) * multiplier;
                }
                else if(mult == "3") score += (3 * usedTiles[counter]->getPoints()) * multiplier;
                else if(mult == "2") score += (2 * usedTiles[counter]->getPoints()) * multiplier;
                else score += (usedTiles[counter]->getPoints()) * multiplier;
                points = 0;
                word2 = horizWord(usedTiles[counter], down, col - 1, points);
                if(word2.length() != 1){
                    points *= secondaryMultiplier;
                    score += points;
                    words.push_back(word2);
                }
                down++;
                counter++;
            }
        }
        if(!isValid && !isFirstMove){
            return words;
        }
        words.push_back(tempWord);
    }
    return words;
}

void Board::setFirstMove(bool b)
{
    isFirstMove = b;
}

bool Board::getFirstMove()
{
    return isFirstMove;
}

/*
1. Includes and Namespace
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "../headers/Board.h"
#include "../headers/Square.h"
#include "../headers/Tile.h"
#include "../headers/Dictionary.h"

using namespace std;

Standard libraries provide file handling (fstream), string manipulation (sstream, string), and error handling (stdexcept).
Custom headers include classes for core game components (dictionary, board, tiles, players, bag, square, user interface).
using namespace std; avoids prefixing std:: throughout the file.

2. Constructor and Destructor
2.1 Constructor
Board::Board(string board_file_name)
{
    ifstream boardFile(board_file_name.c_str());
    if (!boardFile is_open())
        throw invalid_argument("Cannot open file: " + board_file_name);

    string line;
    while (getline(boardFile, line))
    {
        stringstream ss(line);
        string symbol, multiplier;
        int row, col;
        ss >> row >> col >> symbol >> multiplier;
        Square* square = new Square(row, col, symbol, multiplier);
        if (row >= (int)boardVect.size())
            boardVect.resize(row + 1);
        if (col >= (int)boardVect[row].size())
            boardVect[row].resize(col + 1);
        boardVect[row][col] = square;
    }
    boardFile.close();

    _x = boardVect.size();
    _y = boardVect[0].size();
    _startx = _x / 2;
    _starty = _y / 2;
    isFirstMove = true;
}

2.2 Destructor
Board::~Board()
{
    for (unsigned int i = 0; i < boardVect.size(); i++)
        for (unsigned int j = 0; j < boardVect[i].size(); j++)
            delete boardVect[i][j];
}

3. Public Methods
3.1 Word Validation and Scoring
vector<string> Board::allWords(int row, int col, char dir, int& score, vector<Tile*>& usedTiles)
{
    vector<string> words;
    // ...existing code...
    return words;
}

string Board::vertWord(Tile* t, int row, int col, int& points)
{
    string word = t->isBlank() ? t->getUse() : t->getLetter(); // Initialize word with tile letter
    // ...existing code...
    return word;
}

string Board::horizWord(Tile* t, int row, int col, int& points)
{
    string word = t->isBlank() ? t->getUse() : t->getLetter(); // Initialize word with tile letter
    // ...existing code...
    return word;
}

3.2 Game State Management
void Board::setFirstMove(bool b)
{
    isFirstMove = b;
}

bool Board::getFirstMove()
{
    return isFirstMove;
}

int Board::getRowSize()
{
    return _x;
}

int Board::getColSize()
{
    return _y;
}

int Board::getStartX()
{
    return _startx;
}

int Board::getStartY()
{
    return _starty;
}

4. Code Design Features
- Uses object-oriented principles, with `Board` managing tiles and words while `Square` handles individual tile placement rules.
- Uses dynamic memory allocation for flexible board sizes.
- Implements modular design, keeping word validation, scoring, and tile placement separate for clarity.

5. Advantages of This Design
- Modular Structure: The separation of concerns improves maintainability and scalability.
- Efficient Word Validation: Uses `Dictionary` for fast lookups.
- Flexible Expansion: The board supports additional rules like custom tile distributions.
- Encapsulation: Keeps board-specific logic inside the `Board` class, preventing unintended modifications from external classes.
*/