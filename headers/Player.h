#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <vector>
#include <set>
#include "../headers/Tile.h"
#include "../headers/Bag.h"
#include "../headers/Dictionary.h"
#include "../headers/Board.h"
#include "../headers/Square.h"

class Player {
    public:
        Player(std::string name, int score, int numTiles); // Constructor: Initializes a player with a name, score, and number of tiles
        ~Player(); // Destructor: Cleans up resources if necessary

        std::string getName(); // Returns the player's name
        void getTiles(std::set<Tile*> tiles); // Sets the player's tiles
        void useTile(char c); // Removes a tile from the player's hand by its character identifier
        void exchangeTile(char c, Bag& bag); // Allows the player to exchange a tile with one from the bag
        void addScore(int score); // Adds the specified score to the player's total score
        void subtractScore(int score); // Subtracts the specified score from the player's total score
        bool findTile(char c, int& pos); // Searches for a tile in the player's hand and returns its position
        void returnTile(char c, std::vector<Tile*>& usedTiles); // Returns a tile to a collection of used tiles
        bool executePlaceMove(Bag& bag, Dictionary& dict, Board& board, char dir, int row, int col, std::string word); // Executes a move where the player places a word on the board
        void executeExchangeMove(Bag& bag, std::string word); // Executes an exchange move where the player exchanges one or more tiles for new ones from the bag
        int getScore(); // Returns the player's current score
        int getHandSize(); // Returns the number of tiles currently in the player's hand
        int getHandScore(); // Returns the total score of all tiles in the player's hand

        std::vector<Tile*> _playerTiles; // Stores the player's tiles

    private:
        int _score; // Player's score
        int _numTiles; // Number of tiles the player has
        std::string _name; // Player's name
};

#endif /* PLAYER_H_ */

/*
1. File Overview
This header file defines the `Player` class, which manages all the necessary functionality for a player in the game. 
It includes methods for interacting with tiles, managing scores, and making moves, as well as storing player-related data such as their name, score, and tiles.

2. Code Breakdown
2.1 Header Guards
#ifndef PLAYER_H_
#define PLAYER_H_
- Prevents multiple inclusions of the same header file, ensuring that the compiler processes it only once during the compilation of each translation unit.

2.2 Includes
#include <string>
#include <vector>
#include <set>
#include "Tile.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Board.h"
#include "Square.h"
- **`<string>`**: Used for managing player names.
- **`<vector>`**: Used for storing the player's tiles.
- **`<set>`**: Used for managing sets of tiles.
- **`Tile.h`**: Includes the Tile class definition.
- **`Bag.h`**: Includes the Bag class definition.
- **`Dictionary.h`**: Includes the Dictionary class definition.
- **`Board.h`**: Includes the Board class definition.
- **`Square.h`**: Includes the Square class definition.

2.3 Constructor and Destructor
Player(std::string name, int score, int numTiles);
- Initializes a player with a name, score, and number of tiles.

~Player();
- Cleans up resources if necessary.

2.4 Public Methods
std::string getName();
- Returns the player's name.

void getTiles(std::set<Tile*> tiles);
- Sets the player's tiles.

void useTile(char c);
- Removes a tile from the player's hand by its character identifier.

void exchangeTile(char c, Bag& bag);
- Allows the player to exchange a tile with one from the bag.

void addScore(int score);
- Adds the specified score to the player's total score.

void subtractScore(int score);
- Subtracts the specified score from the player's total score.

bool findTile(char c, int& pos);
- Searches for a tile in the player's hand and returns its position.

void returnTile(char c, std::vector<Tile*>& usedTiles);
- Returns a tile to a collection of used tiles.

bool executePlaceMove(Bag& bag, Dictionary& dict, Board& board, char dir, int row, int col, std::string word);
- Executes a move where the player places a word on the board.

void executeExchangeMove(Bag& bag, std::string word);
- Executes an exchange move where the player exchanges one or more tiles for new ones from the bag.

int getScore();
- Returns the player's current score.

int getHandSize();
- Returns the number of tiles currently in the player's hand.

int getHandScore();
- Returns the total score of all tiles in the player's hand.

2.5 Private Members
int _score;
- Player's score.

int _numTiles;
- Number of tiles the player has.

std::string _name;
- Player's name.

std::vector<Tile*> _playerTiles;
- Stores the player's tiles.

3. Code Design Features
- Data Encapsulation: The `Player` class encapsulates all player-related data, such as the name, score, and tiles. This abstraction allows for better organization and separation of concerns.
- Tile Management: The player has a collection of tiles (`_playerTiles`) and is able to interact with these tiles, either by playing or exchanging them, through various methods.
- Interaction with Other Classes: The `Player` interacts with other game components such as the `Bag`, `Dictionary`, and `Board`. This shows how the `Player` class is central to the gameplay, requiring communication with other objects to execute actions like placing words and managing tiles.

4. Advantages of This Design
- Modularity: The `Player` class is modular, managing player-specific actions while delegating tasks such as dictionary validation or board manipulation to other classes like `Dictionary` and `Board`. This improves code readability and maintainability.
- Easy Expansion: The class could easily be expanded to include additional functionality, such as handling multiple players, implementing AI logic, or adding more complex rules for scoring and tile usage.
- Separation of Concerns: Each method has a specific responsibility, which follows the principle of separation of concerns. This ensures that the `Player` class focuses only on actions related to the player, such as managing tiles and scores, without taking on responsibilities that belong to other classes.
*/