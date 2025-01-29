#ifndef TILE_H_
#define TILE_H_

#include <string>

class Tile {
    public:
        Tile (std::string letter, int points)
        { 
            _letter = letter; 
            _points = points; 
            _use = letter; 
        } // Constructor: Initializes a tile with a letter and point value

        std::string getLetter () const { return _letter; } // Returns the string on the tile

        int getPoints () const { return _points; } // Returns the point value of the tile

        bool isBlank () const { return (_letter == "?"); } // Checks if the tile is a blank tile

        std::string getUse () const { return _use; } // Returns the letter assigned to a blank tile
        void useAs (std::string use) { _use = use; } // Sets the letter a blank tile is being used as

    private:
        std::string _letter; // The letter printed on the tile
        std::string _use; // The letter that a blank tile is used as (for blank tiles only)
        int _points; // The number of points associated with the tile
};

#endif /* TILE_H_ */

/*
1. File Overview
Defines the `Tile` class, which represents a single letter tile in the game.
Each tile has a letter, a score, and an optional assigned letter if it's a blank tile.
The file includes methods for retrieving tile properties and modifying blank tile usage.

2. Code Breakdown
2.1 Header Guards
#ifndef TILE_H_
#define TILE_H_
- Prevents multiple inclusions of the same header file, avoiding redefinition errors.
- Ensures the compiler includes this file only once per compilation unit.

2.2 Class Definition
class Tile {
- Encapsulates the properties and behaviors of a Scrabble tile.
- Designed to represent both standard letter tiles and blank tiles.

2.3 Constructor
Tile (std::string letter, int points)
{ _letter = letter; _points = points; _use = letter; }
- Initializes a tile with a letter and point value.
- Sets _letter and _points to the provided values.
- Sets _use to _letter, meaning blank tiles default to '?', while normal tiles retain their original letter.
- Potential Improvement: Use an initialization list for better performance:
  Tile(std::string letter, int points) : _letter(letter), _points(points), _use(letter) {}

2.4 Public Methods
std::string getLetter () const;
- Returns the string on the tile.
- Declared const to ensure it does not modify the tile.

int getPoints () const;
- Returns the point value of the tile.
- Declared const to ensure it does not modify the tile.

bool isBlank () const;
- Returns true if the tile is a blank tile ('?'), otherwise false.
- Allows special handling for blank tiles.
- Potential Improvement: Define '?' as a named constant for readability:
  static constexpr char BLANK_TILE = '?';
  bool isBlank() const { return _letter == BLANK_TILE; }

std::string getUse () const;
- Returns the letter assigned to a blank tile.
- For normal tiles, returns the original letter.

void useAs (std::string use);
- Sets the letter a blank tile is being used as.
- Enables blank tiles to substitute for any letter during gameplay.

2.5 Private Members
std::string _letter;
- The letter printed on the tile.
- Possible values: A–Z or '?' (blank tile).
- Potential Improvement: Mark as const to prevent unintended modifications:
  const std::string _letter;

std::string _use;
- The letter that a blank tile is used as.
- Default: If not a blank tile, _use is the same as _letter.

int _points;
- The number of points associated with the tile.
- Potential Improvement: Mark as const since tile scores should not change:
  const int _points;

3. Code Design Features
- Encapsulation: Keeps tile attributes private, with public accessors.
- Const-correctness: Methods that don't modify the object are marked const.
- Flexibility: Supports blank tile substitution via _use.
- Efficiency: Minimal memory usage, storing only essential tile attributes.

4. Advantages of This Design
- Lightweight and Efficient: The class is simple and only stores necessary data.
- Extensible: Can be expanded with additional features, such as multipliers.
- Encapsulated Behavior: All tile-related logic is inside the class.
- Prevents Errors: Use of const and private members ensures controlled data access.
*/