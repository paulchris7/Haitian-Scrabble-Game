# Source Folder

This folder contains the C++ source files that implement the functionality of the Haitian Scrabble game. These files define the core components of the game, such as the board, tiles, players, and game rules.

## Files:

- **`bag.cpp`**: Implements the Bag class, which handles the collection of tiles. It provides methods to draw tiles, return tiles, and shuffle the bag.
- **`board.cpp`**: Implements the Board class, which represents the 15x15 grid where players place tiles. It includes methods for placing tiles, checking the state of the board, and managing the layout.
- **`dictionary.cpp`**: Implements the Dictionary class, which contains the list of valid Haitian Creole words. It ensures that only valid words are accepted during gameplay.
- **`player.cpp`**: Implements the Player class, which manages the player's information such as their name, score, and tiles. It also includes methods for players to take turns and manage their tiles.
- **`square.cpp`**: Implements the Square class, representing a single square on the board (e.g., premium squares like double letter score, triple word score).