#ifndef BAG_H_
#define BAG_H_

#include <vector>
#include <string>
#include <set>
#include "../headers/Tile.h"

class Bag {

public:
	Bag (const std::string bag_file_name, int random_seed); // Constructor
	~Bag (); // Destructor

	void addTile (Tile *tile); // Add a single tile
	void addTiles (std::vector<Tile*> tiles); // add a list of tiles
	std::set<Tile*> drawTiles (int number); // Draw a tiles
	int tilesRemaining () const; // Get the number of tiles remaining

private:
	std::vector<Tile*> _tiles; // Store all tiles
};

#endif 
/* BAG_H_ */

/* 
1. File Overview
The Bag.h file defines the Bag class, a critical component of the Scrabble game, which manages the game's tiles. 
It provides functionalities for initializing the bag, adding tiles, drawing tiles, and tracking the number of remaining tiles. 
This class ensures tiles are managed efficiently and supports randomness for game fairness.

2. Code Breakdown
2.1 Header Guards
#ifndef BAG_H_
#define BAG_H_
These ensure the file is only included once during compilation, preventing redefinition errors.

2.2 Includes
#include <vector>
#include <string>
#include <set>
#include "Tile.h"

<vector>: Used to store all tiles in the bag.
<string>: Handles file input (tile distribution file name).
<set>: Ensures unique tile selection when drawing tiles.
Tile.h: Includes the Tile class definition to use Tile* pointers.

2.3 Public Methods
2.3.1 Constructor
Bag(const std::string bag_file_name, int random_seed);
Initializes the bag with tiles specified in the bag_file_name.
The random_seed is used to ensure randomness for drawing tiles.

2.3.2 Destructor
~Bag();
Cleans up memory associated with tiles. This is crucial since tiles are stored as pointers (Tile*).

2.3.3 Add a Single Tile
void addTile(Tile* tile);
Adds one tile to the bag.
Use: When replacing tiles or loading a custom tile set.

2.3.4 Add Multiple Tiles
void addTiles(std::vector<Tile*> tiles);
Adds multiple tiles to the bag at once.
Use: Initializing the bag with a pre-loaded set of tiles.

2.3.5 Draw Tiles
std::set<Tile*> drawTiles(int number);
Randomly selects a specified number of tiles from the bag and removes them.
Returns a std::set<Tile*>, ensuring no duplicate tiles are drawn.
Use: When a player needs to refill their rack after their turn.

2.3.6 Tiles Remaining
int tilesRemaining() const;
Returns the number of tiles left in the bag.
Declared const because it does not modify the object's state.
Use: To check if the bag is empty or near empty during gameplay.

3. Private Members
3.1 Tile Storage
std::vector<Tile*> _tiles;
Stores all tiles currently in the bag.
Tiles are managed as pointers to reduce memory usage and allow flexibility.

4. Destructor Logic
The destructor (~Bag) ensures proper memory management:
It deletes any dynamically allocated Tile* objects stored in _tiles.
Without this, memory leaks could occur, especially in a game with multiple runs.

5. Code Design Features
5.1 Encapsulation
All tile-related logic is encapsulated within the Bag class.
Other components (e.g., Player, Game) interact with the bag only through public methods.

5.2 Randomness
The random_seed parameter ensures fair and unpredictable gameplay while supporting deterministic testing.

5.3 Flexibility
The bag can be dynamically updated with new tiles using addTile and addTiles.
The game logic can adapt to different languages (e.g., Haitian Creole) by loading custom tiles via the constructor.

5.4 Error Prevention
Use of std::set in drawTiles ensures no duplicate tiles are drawn.
Header guards prevent multiple inclusions of the file.

6. Advantages of This Design
6.1 Separation of Concerns
The Bag class focuses solely on managing tiles, ensuring clean and modular code.
6.2 Reusability
The Bag class can be reused or extended for other word games or languages.
6.3 Testability
The inclusion of random_seed allows controlled tests for debugging purposes.
6.4 Memory Management
By leveraging a destructor, the class ensures no memory leaks, even when tiles are dynamically allocated.
*/