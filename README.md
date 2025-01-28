# Haitian Scrabble Game

## Description

The **Haitian Scrabble game** is a C++ implementation of the popular word game Scrabble, designed specifically for the Haitian Creole language. This project is aimed at promoting linguistic diversity and preserving Haitian culture through an engaging word game experience.

The game will first be implemented as a console-based version and is designed to be easily extendable to a graphical user interface (GUI) in the future. The game will feature key components such as:

- **Bag**: A collection of tiles with letter distributions specific to Haitian Creole.
- **Board**: A 15x15 grid that will hold the tiles placed by players during their turn.
- **Player**: Users will take turns to place tiles on the board and form valid words in Haitian Creole.
- **Dictionary**: A list of valid words in Haitian Creole that players can use to form words.
- **User Interface**: Console-based prompts and outputs to manage player turns, score, and tile management.

## Features

- **Multiplayer Mode**: Supports two players or more taking turns to place tiles and form words.
- **Tile Exchange**: Allows players to exchange tiles with the bag during their turn.
- **Scoring System**: Implements a scoring system based on the standard Scrabble rules, with modifications for the Haitian Creole language.
- **Tile Distribution**: The game uses a customized distribution of letters, tailored for the Haitian Creole alphabet and its frequency of usage in words.
- **Word Validation**: A dictionary-based check ensures that only valid Haitian Creole words can be played.

## How to Run

### Prerequisites

- **C++ Compiler** (e.g., g++, mingw-w64)
- **Make** (for building the game)

### Steps for Command-Line Version

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/Haitian-Scrabble-Game.git
    cd Haitian-Scrabble-Game
    ```

2. Install dependencies (if applicable) and build the game:
    - On Linux/macOS:
      ```bash
      make
      ```

    - On Windows (using MinGW):
      ```bash
      mingw32-make
      ```

3. Run the game:
    ```bash
    ./bin/Scrabble config/config.txt
    ```

### Additional Notes:
- **`make clean`**: This command will clean up the `/bin/` directory.
- The program compiles without warnings and has been tested to avoid memory leaks.

## Contact

Feel free to reach out to me for any questions or suggestions. You can reach me at:
- Email: [paulchristaimeslg3@gmail.com ](mailto:paulchristaimeslg3@gmail.com)
- GitHub: [paulchris7](https://github.com/paulchris7)
- LinkedIn: [Paul Christopher Aimé ](https://www.linkedin.com/in/paulchristopheraime)


