#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include <vector>
#include <string>
#include "../headers/Player.h"
#include "../headers/Bag.h"
#include "../headers/Board.h"
#include "../headers/Dictionary.h"

class UserInterface {
public:
    UserInterface(); // Constructor: Initializes the UserInterface object
    ~UserInterface(); // Destructor: Cleans up resources if necessary

    void createNewPlayers(Bag& bag, int numTiles); // Initializes player objects and assigns them tiles from the bag
    void switchTurns(); // Switches the active player to the next in sequence
    void printBoard(Board& board); // Displays the current state of the game board
    void printTiles(); // Shows the tiles that the current player has
    int getTurn(); // Returns the index of the current player
    std::string getMove(); // Collects a move input from the player and returns it as a string
    void printScore(); // Displays the scores of all players
    void printTurn(); // Prints whose turn it is
    void endGame(); // Handles end-of-game procedures such as declaring the winner and finalizing the game

    std::vector<Player*> players; // Stores pointers to all player objects in the game

private:
    int _numPlayers; // Stores the number of players in the game
    int _turn; // Keeps track of the current player's turn (index in players vector)
    std::string _playerName; // Stores the name of the current player
    std::string line; // A general-purpose string variable, likely used for handling user input
};

#endif /* USERINTERFACE_H_ */

/*
Code Overview
The UserInterface.h file defines the UserInterface class, which serves as the main interface for interacting with the Scrabble game. This class manages player turns, displays game-related information, and facilitates user interactions. It also stores a list of Player objects and tracks game progression.

Key Responsibilities
- Player Management: Handles player creation and turn switching.
- Game Display: Prints the game board, tiles, scores, and turns.
- User Input Handling: Collects and processes user moves.
- Game Flow Control: Manages the game's progression and termination.

Detailed Code Breakdown
1. Header Guards
#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_
- Prevents multiple inclusions of this header file, ensuring only one definition of UserInterface exists in the compilation.

2. Included Libraries
#include <vector>
#include <string>
#include "Player.h"
#include "Bag.h"
#include "Board.h"
#include "Dictionary.h"
- **`<vector>`** and **`<string>`**: Used for storing player objects and handling input/output.
- **`Player.h`**: Manages individual player data, including hand tiles and scores.
- **`Bag.h`**: Manages the bag of tiles.
- **`Board.h`**: Represents the game board where words are placed.
- **`Dictionary.h`**: Handles word validation.

3. Class Definition
class UserInterface {
- Declares the UserInterface class, which provides methods for user interaction in the game.

4. Public Methods
UserInterface();
- Constructor: Initializes a UserInterface object.

~UserInterface();
- Destructor: Cleans up allocated resources.

void createNewPlayers(Bag& bag, int numTiles);
- Purpose: Initializes player objects, assigns them tiles from the bag, and prepares them for gameplay.
- Parameters:
  - Bag& bag: The tile bag from which players draw tiles.
  - int numTiles: The number of tiles each player receives.

void switchTurns();
- Purpose: Switches the active player to the next in sequence.

void printBoard(Board& board);
- Purpose: Displays the current state of the game board.

void printTiles();
- Purpose: Shows the tiles that the current player has.

int getTurn();
- Purpose: Returns the index of the current player.

std::string getMove();
- Purpose: Collects a move input from the player and returns it as a string.

void printScore();
- Purpose: Displays the scores of all players.

void printTurn();
- Purpose: Prints whose turn it is.

void endGame();
- Purpose: Handles end-of-game procedures such as declaring the winner and finalizing the game.

std::vector<Player*> players;
- Purpose: Stores pointers to all player objects in the game.
- Type: std::vector<Player*> (a dynamic array of player pointers).

5. Private Attributes
int _numPlayers;
- Purpose: Stores the number of players in the game.

int _turn;
- Purpose: Keeps track of the current player's turn (index in players vector).

std::string _playerName;
- Purpose: Stores the name of the current player.

std::string line;
- Purpose: A general-purpose string variable, likely used for handling user input.
6. End of Header Guard
#endif /* USERINTERFACE_H_ *
- Closes the #ifndef directive to prevent multiple inclusions of the file.

Conclusion
The UserInterface class plays a critical role in managing player interactions, displaying game state information, and handling game flow. It provides essential methods for printing the board, managing turns, retrieving user input, and ending the game. The class keeps track of players, their turns, and user inputs, making it a core component of the Scrabble game implementation.
*/