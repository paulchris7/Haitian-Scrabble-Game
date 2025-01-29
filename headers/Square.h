#ifndef SQUARE_H_
#define SQUARE_H_

#include <string>
#include "../headers/Tile.h"

class Square {
    public:
        Square (int row, int col, std::string symbol, std::string multiplier); // Constructor: Initializes the square with position, symbol, and multiplier
        ~Square(); // Destructor: Cleans up resources if necessary

        std::string getValue(); // Returns a string representation of the square's value
        std::string valueForBoard(); // Returns a string representation of the square for display on the board
        void setValue(Tile *t); // Sets a tile on the square
        int returnPoints(); // Returns the points for the square, considering the multiplier
        std::string getMultiplier(); // Returns the multiplier associated with the square
        bool occupied(); // Checks whether the square is occupied by a tile

    private:
        int _row; // Row position of the square
        int _col; // Column position of the square
        Tile* _tile; // Pointer to the tile placed on the square
        bool _hasTile; // Indicates whether the square is occupied by a tile
        std::string _symbol; // Symbol for the square (e.g., a letter or empty space)
        std::string _multiplier; // Multiplier for the square (e.g., word or letter multiplier)
};

#endif /* SQUARE_H_ */

/*
1. File Overview
This header file defines the `Square` class, which models the squares on the Scrabble board. Each square has a position, a tile, and may have a multiplier for scoring. 
The `Square` class provides methods for manipulating and querying the state of the square, such as checking whether it is occupied or getting the multiplier.

2. Code Breakdown
2.1 Header Guards
#ifndef SQUARE_H_
#define SQUARE_H_
- Prevents multiple inclusions of the same header file, ensuring that the compiler processes it only once during the compilation of each translation unit.

2.2 Includes
#include <string>
#include "Tile.h"
- **`<string>`**: Used for handling string data types for the square's symbol and multiplier.
- **`Tile.h`**: Includes the Tile class definition to use Tile* pointers.

2.3 Constructor and Destructor
Square(int row, int col, std::string symbol, std::string multiplier);
- Initializes the square with a position (row, col), a symbol (e.g., a letter or empty space), and a multiplier (e.g., a 2x multiplier for letter or word score).

~Square();
- Ensures proper cleanup. It should handle memory management for any dynamically allocated resources, but since the square only manages a pointer to a Tile (which could be managed elsewhere), it may not need additional cleanup.

2.4 Public Methods
std::string getValue();
- Returns a string representation of the square's value, which could be either its symbol or its multiplier.

std::string valueForBoard();
- Returns a string representation of the square, likely for display purposes on the board.

void setValue(Tile *t);
- Sets a tile on the square. The method name could be changed to placeTile for clarity. It may also benefit from validation to ensure that a tile is only placed on an empty square.

int returnPoints();
- Returns the points for the square, considering the multiplier. This method would calculate the value based on whether the square has a multiplier or not.

std::string getMultiplier();
- Returns the multiplier (if any) associated with the square (e.g., "2x" or "3x").

bool occupied();
- Checks whether the square is occupied by a tile. This method uses the _hasTile boolean to track the square’s state, but encapsulating this check in a method can provide better readability and control.

2.5 Private Members
int _row;
- Row position of the square.

int _col;
- Column position of the square.

Tile* _tile;
- Pointer to the tile placed on the square.

bool _hasTile;
- Indicates whether the square is occupied by a tile.

std::string _symbol;
- Symbol for the square (e.g., a letter or empty space).

std::string _multiplier;
- Multiplier for the square (e.g., word or letter multiplier).

3. Code Design Features
- Encapsulation: The class encapsulates all data related to a single square, such as its position, symbol, multiplier, and whether it is occupied. This allows for easy access and manipulation of square data within the game.
- Tile Placement: The class supports the placement of tiles on the square and checks whether the square is occupied, ensuring that the game logic can be applied correctly.

4. Advantages of This Design
- Separation of Concerns: The `Square` class focuses on managing individual squares, while the `Board` class (presumably) handles the overall layout. This separation makes it easier to manage and test the square’s behavior independently.
- Flexibility in Scoring: The `returnPoints` and `getMultiplier` methods allow for flexible handling of square multipliers, which can change the game's scoring dynamics.
- Simple Interaction with Tiles: The square is designed to hold a reference to a tile, enabling easy interaction between tiles and squares during gameplay.
*/