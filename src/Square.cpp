#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "../headers/Square.h"
#include "../headers/Tile.h"

using namespace std;

Square::Square (int row, int col, string symbol, string multiplier) {
    _row = row;
    _col = col;
    _symbol = symbol;
    _multiplier = multiplier;
    _hasTile = false; // Initialize the square as unoccupied
}

Square::~Square() {
    if (_hasTile) {
        delete _tile; // Delete the tile if the square is occupied
    }
}

string Square::getValue() {
    string temp = "";
    if (_hasTile) {
        if (_tile->isBlank()) {
            temp += _tile->getUse(); // Get the letter the blank tile is used as
            cout << temp << endl; // Debugging output
            return temp;
        } else {
            temp += _tile->getLetter(); // Get the tile's letter
            return temp;
        }
    }
    return _symbol; // Return the square's symbol if no tile is present
}

string Square::valueForBoard() {
    if (_hasTile) {
        string temp = "";
        if (_tile->isBlank()) {
            temp += _tile->getUse();
            temp += "0 ";
            return temp;
        }
        stringstream ss;
        ss << _tile->getPoints();
        ss >> temp;
        temp = _tile->getLetter() + temp;
        if (temp == "Z10") {
            return temp;
        } else {
            return temp + " ";
        }
    }
    return _symbol; // Return the square's symbol if no tile is present
}

void Square::setValue(Tile *t) {
    _tile = t;
    _hasTile = true; // Mark the square as occupied
}

int Square::returnPoints() {
    return _tile->getPoints(); // Return the points of the tile on the square
}

string Square::getMultiplier() {
    return _multiplier; // Return the multiplier of the square
}

bool Square::occupied() {
    return _hasTile; // Return whether the square is occupied
}

/*
1. Includes and Namespace
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "../headers/Square.h"
#include "../headers/Tile.h"

using namespace std;

Explanation:
- **`#include <string>`**: Handles string operations.
- **`#include <iostream>`**: Enables standard input/output operations.
- **`#include <stdexcept>`**: Provides exception handling.
- **`#include <sstream>`**: Allows string stream manipulations (e.g., converting numbers to strings).
- **`#include "../headers/Square.h"`** & **`#include "../headers/Tile.h"`**: Includes necessary headers for the Square and Tile classes.
- **`using namespace std;`**: Avoids the need for `std::` before standard library functions.

2. Constructor
Square::Square (int row, int col, string symbol, string multiplier)
{
    _row = row;
    _col = col;
    _symbol = symbol;
    _multiplier = multiplier;
    _hasTile = false;
}

Explanation:
- Initializes a Square object.
- `_row = row` & `_col = col`: Stores row and column positions.
- `_symbol = symbol`: Stores the square’s display symbol (e.g., "DL" for Double Letter).
- `_multiplier = multiplier`: Stores the multiplier type.
- `_hasTile = false`: Initially, the square does not have a tile.

3. Destructor
Square::~Square()
{
    if (_hasTile) {
        delete _tile;
    }
}

Explanation:
- Ensures memory cleanup by deleting the tile if the square contains one.
- Prevents memory leaks.

4. getValue() Method
string Square::getValue()
{
    string temp = "";
    if (_hasTile) {
        if (_tile isBlank()) {
            temp += _tile->getUse();
            cout << temp << endl;
            return temp;
        } else {
            temp += _tile->getLetter();
            return temp;
        }
    }
    return _symbol;
}

Explanation:
- If the square has a tile:
  - If the tile is blank, it returns the letter it's used as (e.g., a blank tile might represent an 'E').
  - Otherwise, it returns the tile’s actual letter.
- If the square does not have a tile, it returns the square’s symbol (e.g., "DL", "TL").
- `cout << temp << endl;`: Debugging output (prints tile usage). Consider removing it in production.

5. valueForBoard() Method
string Square::valueForBoard()
{
    if (_hasTile) {
        string temp = "";
        if (_tile isBlank()) {
            temp += _tile->getUse();
            temp += "0 ";
            return temp;
        }
        stringstream ss;
        ss << _tile->getPoints();
        ss >> temp;
        temp = _tile->getLetter() + temp;
        if (temp == "Z10") {
            return temp;
        } else {
            return temp + " ";
        }
    }
    return _symbol;
}

Explanation:
- If the square has a tile:
  - If the tile is blank, it returns its used letter + "0 ".
  - Otherwise, it formats the tile's letter and point value (e.g., "A1", "Z10").
  - Ensures "Z10" is correctly formatted.
- If the square has no tile, it returns the square’s symbol.

6. setValue() Method
void Square::setValue(Tile *t)
{
    _tile = t;
    _hasTile = true;
}

Explanation:
- Assigns a tile to the square.
- Marks `_hasTile` as true.

7. returnPoints() Method
int Square::returnPoints()
{
    return _tile->getPoints();
}

Explanation:
- Returns the tile’s point value.

8. getMultiplier() Method
string Square::getMultiplier()
{
    return _multiplier;
}

Explanation:
- Returns the multiplier type (e.g., "DL" for Double Letter, "TW" for Triple Word).

9. occupied() Method
bool Square::occupied()
{
    return _hasTile;
}

Explanation:
- Checks if the square is occupied by a tile.
*/