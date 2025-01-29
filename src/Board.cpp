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

Board::Board (string board_file_name) {
    isFirstMove = true; // Initialize the first move flag
    ifstream boardFile (board_file_name.c_str()); // Open the board configuration file
    string row;

    _x = _y = _startx = _starty = 0; // Initialize dimensions and start position
    if (!boardFile.is_open())
        throw invalid_argument("Cannot open file: " + board_file_name); // Handle file open error

    getline (boardFile, row);
    stringstream s1 (row);
    s1 >> _x >> _y; // Read board dimensions
    getline (boardFile, row);
    stringstream s2 (row);
    s2 >> _startx >> _starty; // Read starting position
    _startx--; _starty--; // Convert to zero-based indexing

    boardVect.resize(_y); // Resize the board vector
    for (int i = 0; i < _y; ++i) {
        getline (boardFile, row);
        boardVect[i].resize(_x);
        for (int j = 0; j < _x; ++j) {
            if (i == _starty && j == _startx) { 
                Square *s = new Square(i, j, "***", "2n"); // Initialize starting square
                boardVect[i][j] = s; 
            } else {
                switch (row[j]) {
                    case '.':
                        boardVect[i][j] = new Square(i, j, "[.]", "1"); // Regular square
                        break;
                    case '2':
                        boardVect[i][j] = new Square(i, j, "2L ", "2"); // Double letter score
                        break;
                    case '3':
                        boardVect[i][j] = new Square(i, j, "3L ", "3"); // Triple letter score
                        break;
                    case 'd':
                        boardVect[i][j] = new Square(i, j, "2W ", "2n"); // Double word score
                        break;
                    case 't':
                        boardVect[i][j] = new Square(i, j, "3W ", "3n"); // Triple word score
                        break;
                    default:
                        throw invalid_argument("Improper character in Board file: " + row[j]); // Handle invalid character
                }
            }
        }
    }
    boardFile.close(); // Close the file
}

Board::~Board() {
    for (int i = 0; i < _y; ++i) {
        for (int j = 0; j < _x; ++j) {
            delete boardVect[i][j]; // Delete dynamically allocated squares
        }
    }
}

int Board::getRowSize() {
    return _x; // Return the number of rows
}

int Board::getColSize() {
    return _y; // Return the number of columns
}

int Board::getStartX() {
    return _startx; // Return the starting X coordinate
}

int Board::getStartY() {
    return _starty; // Return the starting Y coordinate
}

string Board::vertWord(Tile* t, int row, int col, int& points) {
    string word = t->isBlank() ? t->getUse() : t->getLetter(); // Initialize word with tile letter
    points += t->getPoints(); // Add tile points
    int up = row - 1;
    int down = row + 1;
    while (up >= 0 && boardVect[up][col]->occupied()) {
        word = boardVect[up][col]->getValue() + word; // Prepend letters above
        points += boardVect[up][col]->returnPoints(); // Add points
        up--;
    }
    while (down <= _x - 1 && boardVect[down][col]->occupied()) {
        word += boardVect[down][col]->getValue(); // Append letters below
        points += boardVect[down][col]->returnPoints(); // Add points
        down++;
    }
    return word; // Return the formed word
}

string Board::horizWord(Tile* t, int row, int col, int& points) {
    string word = t->isBlank() ? t->getUse() : t->getLetter(); // Initialize word with tile letter
    points += t->getPoints(); // Add tile points
    int right = col + 1;
    int left = col - 1;
    while (left >= 0 && boardVect[row][left]->occupied()) {
        word = boardVect[row][left]->getValue() + word; // Prepend letters to the left
        points += boardVect[row][left]->returnPoints(); // Add points
        left--;
    }
    while (right <= _y - 1 && boardVect[row][right]->occupied()) {
        word += boardVect[row][right]->getValue(); // Append letters to the right
        points += boardVect[row][right]->returnPoints(); // Add points
        right++;
    }
    return word; // Return the formed word
}

vector<string> Board::allWords(int row, int col, char dir, int& score, vector<Tile*>& usedTiles) {
    vector<string> words;
    string tempWord = "";
    int multiplier = 1;
    int secondaryMultiplier = 1;
    int points = 0;
    string word2;
    int right = col;
    int left = col - 2;
    if (left == -1) {
        left = 0;
    }
    int up = row - 2;
    if (up == -1) {
        up = 0;
    }
    int down = row;
    int counter = 1;
    bool isValid = false;
    int wordLen = usedTiles.size();
    if (usedTiles[0]->isBlank()) {
        tempWord += usedTiles[0]->getUse();
    } else {
        tempWord += usedTiles[0]->getLetter();
    }
    string mult = boardVect[row - 1][col - 1]->getMultiplier();
    if (mult == "3n") {
        multiplier *= 3;
        score += (3 * usedTiles[0]->getPoints());
    } else if (mult == "2n") {
        multiplier *= 2;
        score += (2 * usedTiles[0]->getPoints());
    } else if (mult == "3") {
        score += (3 * usedTiles[0]->getPoints());
    } else if (mult == "2") {
        score += (2 * usedTiles[0]->getPoints());
    } else {
        score += (usedTiles[0]->getPoints()) * multiplier;
    }

    if (dir == '-') {
        points = 0;
        word2 = vertWord(usedTiles[0], row - 1, col - 1, points);
        if (word2.length() != 1) {
            points *= multiplier;
            score += points;
            words.push_back(word2);
        }
        while (left >= 0 && right < _y) {
            if (boardVect[row - 1][left]->occupied()) {
                isValid = true;
                tempWord = boardVect[row - 1][left]->getValue() + tempWord;
                score += (boardVect[row - 1][left]->returnPoints()) * multiplier;
                if (left != 0) {
                    left--;
                    continue;
                }
            }
            if (boardVect[row - 1][right]->occupied()) {
                isValid = true;
                tempWord += boardVect[row - 1][right]->getValue();
                score += (boardVect[row - 1][right]->returnPoints()) * multiplier;
                if (right != _y - 1) {
                    right++;
                    continue;
                }
            } else {
                if (counter >= wordLen) break;
                if (usedTiles[counter]->isBlank()) {
                    tempWord += usedTiles[counter]->getUse();
                } else {
                    tempWord += usedTiles[counter]->getLetter();
                }
                mult = boardVect[row - 1][right]->getMultiplier();
                if (mult == "3n") {
                    secondaryMultiplier *= 3;
                    multiplier *= 3;
                    score += (usedTiles[counter]->getPoints()) * multiplier;
                } else if (mult == "2n") {
                    secondaryMultiplier *= 2;
                    multiplier *= 2;
                    score += (usedTiles[counter]->getPoints()) * multiplier;
                } else if (mult == "3") {
                    score += (3 * usedTiles[counter]->getPoints()) * multiplier;
                } else if (mult == "2") {
                    score += (2 * usedTiles[counter]->getPoints()) * multiplier;
                } else {
                    score += (usedTiles[counter]->getPoints()) * multiplier;
                }
                points = 0;
                word2 = vertWord(usedTiles[counter], row - 1, right, points);
                if (word2.length() != 1) {
                    points *= secondaryMultiplier;
                    score += points;
                    words.push_back(word2);
                }
                right++;
                counter++;
            }
        }
        if (!isValid && !isFirstMove) {
            return words;
        }
        words.push_back(tempWord);
    } else if (dir == '|') {
        points = 0;
        word2 = horizWord(usedTiles[0], row - 1, col - 1, points);
        if (word2.length() != 1) {
            points *= multiplier;
            score += points;
            words.push_back(word2);
        }
        while (up >= 0 && down < _x) {
            if (boardVect[up][col - 1]->occupied()) {
                isValid = true;
                tempWord = boardVect[up][col - 1]->getValue() + tempWord;
                score += (boardVect[up][col - 1]->returnPoints()) * multiplier;
                up--;
                continue;
            }
            if (boardVect[down][col - 1]->occupied()) {
                isValid = true;
                tempWord += boardVect[down][col - 1]->getValue();
                score += (boardVect[down][col - 1]->returnPoints()) * multiplier;
                down++;
                continue;
            } else {
                if (counter >= wordLen) break;
                if (usedTiles[counter]->isBlank()) {
                    tempWord += usedTiles[counter]->getUse();
                } else {
                    tempWord += usedTiles[counter]->getLetter();
                }
                mult = boardVect[down][col - 1]->getMultiplier();
                if (mult == "3n") {
                    secondaryMultiplier *= 3;
                    multiplier *= 3;
                    score += (usedTiles[counter]->getPoints()) * multiplier;
                } else if (mult == "2n") {
                    secondaryMultiplier *= 2;
                    multiplier *= 2;
                    score += (usedTiles[counter]->getPoints()) * multiplier;
                } else if (mult == "3") {
                    score += (3 * usedTiles[counter]->getPoints()) * multiplier;
                } else if (mult == "2") {
                    score += (2 * usedTiles[counter]->getPoints()) * multiplier;
                } else {
                    score += (usedTiles[counter]->getPoints()) * multiplier;
                }
                points = 0;
                word2 = horizWord(usedTiles[counter], down, col - 1, points);
                if (word2.length() != 1) {
                    points *= secondaryMultiplier;
                    score += points;
                    words.push_back(word2);
                }
                down++;
                counter++;
            }
        }
        if (!isValid && !isFirstMove) {
            return words;
        }
        words.push_back(tempWord);
    }
    return words;
}

void Board::setFirstMove(bool b) {
    isFirstMove = b; // Set the first move flag
}

bool Board::getFirstMove() {
    return isFirstMove; // Return the first move flag
}

/*
Overview of Board.cpp
The Board.cpp file is responsible for managing the Scrabble board, including loading its configuration, handling tile placement, and determining words formed. It interacts with other core classes like Square, Tile, and Dictionary.

Key Responsibilities:
- Loading the Board: Reads the board layout from a file, initializing special scoring tiles (double/triple letter/word scores).
- Tracking Tile Placement: Stores tiles in a 2D vector (boardVect) and manages occupied squares.
- Word Formation: Determines words formed when a tile is placed, both horizontally and vertically.
- Scoring Mechanism: Calculates scores based on tile values and board multipliers.
- Memory Management: Ensures Square objects are properly allocated and deallocated.

1. Header Files and Namespaces
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

Purpose:
- Includes necessary standard library headers for file operations, string manipulation, input/output, and exception handling.
- Includes custom header files for Board, Square, Dictionary, and Tile, which likely define key components of the Scrabble game.
- Uses the std namespace to avoid prefixing standard library functions with std::.

2. Board Constructor
Board::Board (string board_file_name)
{
    isFirstMove = true;
    ifstream boardFile (board_file_name.c_str());
    string row;

    _x = _y = _startx = _starty = 0; // to appease compiler
    if (!boardFile is open())
        throw invalid_argument("Cannot open file: " + board_file_name);

Purpose:
- Initializes isFirstMove to true (important for game rules).
- Opens the board configuration file (board_file_name).
- Initializes _x, _y, _startx, and _starty to 0 to prevent uninitialized usage.
- Throws an exception if the file cannot be opened.

2.1 Reading Board Dimensions and Start Position
    getline (boardFile, row);
    stringstream s1 (row);
    s1 >> _x >> _y;
    getline (boardFile, row);
    stringstream s2 (row);
    s2 >> _startx >> _starty;
    _startx --; _starty --;  // coordinates from 0 in array

- Reads the board's width (_x) and height (_y).
- Reads the starting tile position (_startx, _starty) and converts them to zero-based indexing.

2.2 Initializing Board with Squares
    boardVect.resize(_y);
    for (int i = 0 ; i < _y; ++ i)
    {
        getline (boardFile, row);
        boardVect[i].resize(_x);
        for (int j = 0; j < _x; ++ j)
        {
            if (i == _starty && j == _startx) 
            { 
                Square *s = new Square(i, j, "***", "2n");
                boardVect[i][j] = s; 
            }

- Resizes boardVect (a 2D vector) to _y rows.
- Reads board rows from the file and initializes each Square object.
- If the tile is the starting tile, it is marked with "***" and a double word score "2n".

2.3 Assigning Special Board Squares
            else switch (row[j]) {
            case '.' :
                boardVect[i][j] = new Square(i, j, "...", "1");
                break;
            case '2' : 
                boardVect[i][j] = new Square(i, j, "2L ", "2");
                break;
            case '3' : 
                boardVect[i][j] = new Square(i, j, "3L ", "3");
                break;
            case 'd' : 
                boardVect[i][j] = new Square(i, j, "2W ", "2n");
                break;
            case 't' : 
                boardVect[i][j] = new Square(i, j, "3W ", "3n");
                break;
            default:
                throw invalid_argument("Improper character in Board file: " + row[j]);
            }
        }
    }
    boardFile close ();
}

- Reads each character from the board file and maps them to different tile types:
  - '.' → Regular tile ("...")
  - '2' → Double Letter Score ("2L ")
  - '3' → Triple Letter Score ("3L ")
  - 'd' → Double Word Score ("2W ")
  - 't' → Triple Word Score ("3W ")
- Throws an exception if an unknown character is encountered.

3. Board Destructor
Board::~Board()
{
    for (int i = 0; i < _y; ++i){
        for(int j = 0; j < _x; ++j){
            delete boardVect[i][j];
        }
    }
}

- Frees memory by deleting each Square object stored in boardVect.

4. Getter Methods
int Board::getRowSize() { return _x; }
int Board::getColSize() { return _y; }
int Board::getStartX() { return _startx; }
int Board::getStartY() { return _starty; }

- Simple accessors to retrieve board dimensions and starting position.

5. Finding Vertical Words
string Board::vertWord(Tile* t, int row, int col, int& points)
{
    string word = t->isBlank() ? t->getUse() : t->getLetter();
    points += t->getPoints();

- Builds a vertical word using a placed tile.
- If the tile is blank, uses its wildcard letter (getUse()), otherwise uses its actual letter (getLetter()).
- Adds tile points to points.

5.1 Checking Above and Below
    int up = row-1, down = row+1;
    while(up >= 0 && boardVect[up][col]->occupied()){
        word = boardVect[up][col]->getValue() + word;
        points += boardVect[up][col]->returnPoints();
        up--;
    }    
    while(down <= _x-1 && boardVect[down][col]->occupied()){
        word += boardVect[down][col]->getValue();
        points += boardVect[down][col]->returnPoints();
        down++;
    }
    return word;
}

- Traverses up to find occupied tiles and prepends them.
- Traverses