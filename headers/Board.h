#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <string>
#include "../headers/Square.h"
#include "../headers/Dictionary.h"
#include "../headers/Tile.h"

class Board {
    public:
        Board (std::string board_file_name); // Constructor: Initializes the board from a file
        ~Board(); // Destructor: Cleans up dynamically allocated memory
        
        std::vector<std::string> allWords(int row, int col, char dir, int& score, std::vector<Tile*>& usedTiles); // Generates all possible words formed by placing a tile at the given position
        std::string vertWord(Tile* t, int row, int col, int& points); // Extracts and scores the vertical word formed by placing a tile
        std::string horizWord(Tile* t, int row, int col, int& points); // Extracts and scores the horizontal word formed by placing a tile
        
        void setFirstMove(bool b); // Sets the flag indicating whether the first move has been made
        bool getFirstMove(); // Gets the flag indicating whether the first move has been made
        
        int getRowSize(); // Returns the number of rows on the board
        int getColSize(); // Returns the number of columns on the board
        int getStartX(); // Returns the starting X coordinate for the first move
        int getStartY(); // Returns the starting Y coordinate for the first move
        
        std::vector<std::vector <Square*> > boardVect; // 2D vector representing the board grid

    private:
        bool isFirstMove; // Flag indicating whether the first move has been made
        int _x; // Board width
        int _y; // Board height
        int _startx; // Starting X coordinate for the first move
        int _starty; // Starting Y coordinate for the first move
};

#endif /* BOARD_H_ */

/*
1. Overview
The `Board` class is responsible for managing the Scrabble game board, which is represented as a grid of squares. 
This class includes functionality for:
1. Loading the board's configuration from a file.
2. Tracking the first move on the board.
3. Managing word formation and scoring.
4. Providing access to the dimensions of the board and its starting position.

2. Code Breakdown
2.1 Header Guards
#ifndef BOARD_H_
#define BOARD_H_
- Prevents multiple inclusions of the header file.  
- Ensures the compiler processes this file only once, avoiding redefinition errors.  

2.2 Includes 
#include <vector>
#include <string>
#include "Square.h"
#include "Dictionary.h"
#include "Tile.h"

- **`<vector>`**: Used for storing board rows and columns.  
- **`<string>`**: Required for handling word validation and file operations.  
- **`Square.h`**: Defines board squares, including special bonus tiles.  
- **`Dictionary.h`**: Enables word validation by checking against a list of allowed words.  
- **`Tile.h`**: Represents Scrabble tiles (letters and point values).  

2.3 Constructor and Destructor
2.3.1 Constructor
Board (std::string board_file_name);
- Loads the board configuration from a file.  
- Initializes the 2D vector representing the board grid.  
- Sets the starting position (`_startx`, `_starty`) for the first move.  
2.3.2 Destructor
~Board();
- Ensures proper memory cleanup.  
- Deallocates dynamically allocated `Square` objects stored in `boardVect`.  

2.4 Public Methods  
2.4.1 Word Validation and Scoring
std::vector<std::string> allWords(int row, int col, char dir, int& score, std::vector<Tile*>& usedTiles);
- Generates all possible words formed by placing a tile at the given position.  
- Computes the score based on Scrabble rules.  
- Uses `Dictionary` to validate words.  

std::string vertWord(Tile* t, int row, int col, int& points);
std::string horizWord(Tile* t, int row, int col, int& points);
- Extracts words formed in the vertical (`vertWord`) or horizontal (`horizWord`) directions.  
- Calculates word scores using tile multipliers from `Square`.  

2.4.2 Game State Management
void setFirstMove(bool b);
bool getFirstMove();
- Tracks whether the first move has been made.  
- Important because the first word must cover the center tile.  

int getRowSize();
int getColSize();

- Returns the board dimensions (rows and columns).  

int getStartX();
int getStartY();

- Returns the starting tile’s coordinates (center of the board).  

2.5 Private Members 
2.5.1 Board Grid
std::vector<std::vector<Square*>> boardVect;
- Represents the Scrabble board as a 2D vector of `Square` pointers.  
- Each `Square` holds information about bonus tiles and tile placement.  

2.5.2 Game State Tracking 
bool isFirstMove;
- Tracks whether the first move has been made.  

int _x, _y, _startx, _starty;
- Stores the board’s dimensions (`_x`, `_y`).  
- Stores the start position of the game (`_startx`, `_starty`).  

3. Code Design Features
- Uses object-oriented principles, with `Board` managing tiles and words while `Square` handles individual tile placement rules.  
- Uses dynamic memory allocation for flexible board sizes.  
- Implements modular design, keeping word validation, scoring, and tile placement separate for clarity.  

4. Advantages of This Design
Modular Structure – The separation of concerns improves maintainability and scalability.  
Efficient Word Validation – Uses `Dictionary` for fast lookups.  
Flexible Expansion – The board supports additional rules like custom tile distributions.  
Encapsulation – Keeps board-specific logic inside the `Board` class, preventing unintended modifications from external classes.  
*/