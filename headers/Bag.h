#ifndef BAG_H_
#define BAG_H_

#include <vector>
#include <string>
#include <set>
#include "../headers/Tile.h"

class Bag {
    public:
        Bag (const std::string bag_file_name, int random_seed); // Constructor: Initializes the bag with tiles from a file
        ~Bag (); // Destructor: Cleans up dynamically allocated memory

        void addTile (Tile *tile); // Adds a single tile to the bag
        void addTiles (std::vector<Tile*> tiles); // Adds multiple tiles to the bag
        std::set<Tile*> drawTiles (int number); // Draws a specified number of tiles from the bag
        int tilesRemaining () const; // Returns the number of tiles remaining in the bag

    private:
        std::vector<Tile*> _tiles; // Stores all tiles in the bag
};

#endif /* BAG_H_ */

/* 
1. Overview
The `Bag` class manages the game's tiles, providing functionalities for initializing the bag, adding tiles, drawing tiles, and tracking the number of remaining tiles.

2. Code Breakdown
2.1 Header Guards
#ifndef BAG_H_
#define BAG_H_
- Prevents multiple inclusions of the header file, avoiding redefinition errors.

2.2 Includes
#include <vector>
#include <string>
#include <set>
#include "Tile.h"
- **`<vector>`**: Used to store all tiles in the bag.
- **`<string>`**: Handles file input (tile distribution file name).
- **`<set>`**: Ensures unique tile selection when drawing tiles.
- **`Tile.h`**: Includes the Tile class definition to use Tile* pointers.

2.3 Public Methods
2.3.1 Constructor
Bag(const std::string bag_file_name, int random_seed);
- Initializes the bag with tiles specified in the bag_file_name.
- The random_seed ensures randomness for drawing tiles.

2.3.2 Destructor
~Bag();
- Cleans up memory associated with tiles, preventing memory leaks.

2.3.3 Add a Single Tile
void addTile(Tile* tile);
- Adds one tile to the bag.

2.3.4 Add Multiple Tiles
void addTiles(std::vector<Tile*> tiles);
- Adds multiple tiles to the bag at once.

2.3.5 Draw Tiles
std::set<Tile*> drawTiles(int number);
- Randomly selects a specified number of tiles from the bag and removes them.
- Returns a std::set<Tile*>, ensuring no duplicate tiles are drawn.

2.3.6 Tiles Remaining
int tilesRemaining() const;
- Returns the number of tiles left in the bag.
- Declared const because it does not modify the object's state.

3. Private Members
3.1 Tile Storage
std::vector<Tile*> _tiles;
- Stores all tiles currently in the bag.

4. Destructor Logic
The destructor (~Bag) ensures proper memory management:
- Deletes any dynamically allocated Tile* objects stored in _tiles.

5. Code Design Features
5.1 Encapsulation
- All tile-related logic is encapsulated within the Bag class.

5.2 Randomness
- The random_seed parameter ensures fair and unpredictable gameplay while supporting deterministic testing.

5.3 Flexibility
- The bag can be dynamically updated with new tiles using addTile and addTiles.

5.4 Error Prevention
- Use of std::set in drawTiles ensures no duplicate tiles are drawn.
- Header guards prevent multiple inclusions of the file.

6. Advantages of This Design
6.1 Separation of Concerns
- The Bag class focuses solely on managing tiles, ensuring clean and modular code.

6.2 Reusability
- The Bag class can be reused or extended for other word games or languages.

6.3 Testability
- The inclusion of random_seed allows controlled tests for debugging purposes.

6.4 Memory Management
- By leveraging a destructor, the class ensures no memory leaks, even when tiles are dynamically allocated.
*/