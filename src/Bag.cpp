#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "../headers/Bag.h"
#include "../headers/Tile.h"

using namespace std;

Bag::Bag (const string bag_file_name, int random_seed) {
    srand (random_seed); // Seed the random number generator
    ifstream bagFile (bag_file_name.c_str()); // Open the tile bag file

    if (bagFile.is_open()) { // Fix the syntax error here
        string line;
        while (getline (bagFile, line)) {
            stringstream ss (line);
            string letter;
            int points;
            int count;
            ss >> letter >> points >> count; // Parse tile properties
            for (int i = 0; i < count; ++i) {
                Tile *t = new Tile (letter, points); // Create a new tile
                addTile (t); // Add the tile to the bag
            }
        }
        bagFile.close (); // Close the file
    } else {
        throw invalid_argument ("Cannot open file: " + bag_file_name); // Handle file open error
    }
}

Bag::~Bag () {
    for (unsigned int i = 0; i < _tiles.size(); ++i) {
        delete _tiles[i]; // Delete dynamically allocated tiles
    }
}

void Bag::addTile (Tile *tile) {
    _tiles.push_back (tile); // Add the tile to the vector
    int j = rand() % _tiles.size(); // Generate a random index
    _tiles[_tiles.size()-1] = _tiles[j]; // Swap the new tile with a random tile
    _tiles[j] = tile; // Place the new tile at the random index
}

void Bag::addTiles (vector<Tile*> tiles) {
    for (Tile* tile : tiles) {
        addTile(tile); // Add each tile to the bag
    }
}

std::set<Tile*> Bag::drawTiles (int number) {
    set<Tile*> tileSet;
    for (int i = 0; i < number && tilesRemaining() > 0; ++i) {
        tileSet.insert (_tiles.back()); // Add the last tile to the set
        _tiles.pop_back(); // Remove the last tile from the vector
    }
    return tileSet; // Return the set of drawn tiles
}

int Bag::tilesRemaining () const { 
    return _tiles.size(); // Return the number of tiles remaining in the bag
}

/*
1. File Overview
Loads Scrabble tiles from a file and stores them in a bag.
Provides functionality to add, shuffle, and draw tiles.
Manages tile memory by allocating and deallocating dynamically created Tile objects.

2. Code Breakdown
2.1 Includes and Namespace
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "../headers/Bag.h"
#include "../headers/Tile.h"

using namespace std;

Headers Included:
- **`<vector>`**: Stores tile objects.
- **`<set>`**: Used to return drawn tiles as a unique set.
- **`<string>`, `<fstream>`, `<sstream>`: Used to read tile data from a file.
- **`<iostream>`**: Handles errors via standard output.
- **`<cstdlib>`**: Provides rand() and srand().
- **`<stdexcept>`**: Throws exceptions for file errors.

Using Namespace std:
- Avoids explicit std:: prefixes, making the code cleaner.
- Could be removed to prevent namespace pollution.

2.2 Constructor: Bag::Bag()
Bag::Bag (const string bag_file_name, int random_seed)
{
    srand (random_seed);
    ifstream bagFile (bag_file_name.c_str());

    if (bagFile is open())
    {
        string line;
        while (getline (bagFile, line))
        {
            stringstream ss (line);
            string letter;
            int points;
            int count;
            ss >> letter >> points >> count;
            for (int i = 0; i < count; ++ i)
            {
                Tile *t = new Tile (letter, points);
                addTile (t);
            }
        }
        bagFile close ();
    }
    else throw invalid_argument ("Cannot open file: " + bag_file_name);
}

Purpose:
- Initializes the bag by loading tiles from a file.
- Seeds the random number generator for shuffling.

Steps:
- Set Random Seed:
  srand (random_seed);
  Ensures consistent random behavior for debugging.

- Open the File:
  ifstream bagFile (bag_file_name.c_str());
  Opens the tile bag file for reading.
  .c_str() is unnecessary in C++11+ since ifstream accepts std::string.

- Read File Line by Line:
  while (getline (bagFile, line))
  Reads each line containing a tile's letter, point value, and count.

- Parse Tile Data:
  stringstream ss (line);
  string letter;
  int points;
  int count;
  ss >> letter >> points >> count;
  Extracts tile properties from the line.

- Create and Add Tiles:
  for (int i = 0; i < count; ++ i)
  {
      Tile *t = new Tile (letter, points);
      addTile (t);
  }
  Converts letter to uppercase (toupper(c)).
  Dynamically allocates tiles and adds them to _tiles.

- Handle File Errors:
  else throw invalid_argument ("Cannot open file: " + bag_file_name);
  If the file cannot be opened, an exception is thrown.

Potential Improvements:
- Use std::unique_ptr or std::vector<Tile> instead of raw pointers for memory safety.
- Check File Format before parsing to avoid unexpected errors.

2.3 Destructor: Bag::~Bag()
Bag::~Bag ()
{
    for (unsigned int i = 0; i < _tiles.size(); ++i)
        delete _tiles [i];
}
- Deletes dynamically allocated tiles to prevent memory leaks.
- Potential Improvement: Use std::vector<std::unique_ptr<Tile>> instead of raw pointers.

2.4 Adding Tiles: Bag::addTile()
void Bag::addTile (Tile *tile)
{
    _tiles.push_back (tile);
    int j = rand() % _tiles.size();
    _tiles[_tiles.size()-1] = _tiles[j];
    _tiles[j] = tile;
}

Purpose:
- Adds a tile to the bag while ensuring random placement.

Steps:
- Push Tile into _tiles Vector:
  _tiles.push_back (tile);

- Randomly Swap the New Tile with an Existing Tile:
  int j = rand() % _tiles.size();
  _tiles[_tiles.size()-1] = _tiles[j];
  _tiles[j] = tile;
  Ensures tiles remain randomized in the bag.

Potential Improvements:
- Use std::shuffle() from <algorithm> for better shuffling:
  std::shuffle(_tiles.begin(), _tiles.end(), std::default_random_engine(random_seed));

2.5 Bulk Add Tiles: Bag::addTiles()
void Bag::addTiles (vector<Tile*> tiles)
{
    for (Tile* tile : tiles)
        addTile(tile);
}

Purpose:
- Adds multiple tiles to the bag using addTile().
- Uses range-based for loop for readability.

2.6 Drawing Tiles: Bag::drawTiles()
std::set<Tile*> Bag::drawTiles (int number)
{
    set<Tile*> tileSet;
    for (int i = 0; i < number && tilesRemaining() > 0; ++i)
    {
        tileSet.insert (_tiles.back());
        _tiles.pop_back();
    }

    return tileSet;
}

Purpose:
- Draws a given number of tiles from the bag.

Steps:
- Create a Set to Store Drawn Tiles:
  set<Tile*> tileSet;

- Extract Tiles Until Limit is Reached:
  for (int i = 0; i < number && tilesRemaining() > 0; ++i)
  {
      tileSet insert (_tiles.back());
      _tiles.pop_back();
  }
  Uses pop_back() to remove tiles from the bag in LIFO order.

Potential Issues:
- Tiles are removed but not deleted, meaning ownership is transferred.
- Better approach: Use std::vector<std::unique_ptr<Tile>> to manage ownership automatically.

2.7 Checking Remaining Tiles: Bag::tilesRemaining()
int Bag::tilesRemaining () const
{ return _tiles.size(); }
- Returns the number of tiles left in the bag.
- Declared const to ensure it does not modify the object.

3. Code Design Features
- Encapsulation: _tiles is private, with controlled access.
- Memory Management: Destructor deletes allocated tiles.
- Randomization: Tiles are shuffled for fairness.
- Efficiency: Uses vector<Tile*> for dynamic resizing.
*/