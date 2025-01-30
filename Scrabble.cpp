#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include "../headers//Dictionary.h"
#include "../headers/Board.h"
#include "../headers/Tile.h"
#include "../headers/Player.h"
#include "../headers/Bag.h"
#include "../headers/Square.h"
#include "../headers/UserInterface.h"

using namespace std;

void gamePlay(Dictionary& dict, Board& board, Bag& bag, int numTiles);
bool onFirstTile(int row, int col, char dir, string word, Board& board);


void readConfigFile (string config_file_name,
					 string & dictionary_file_name,
					 string & board_file_name,
					 string & bag_file_name,
					 unsigned int & hand_size)
{
	ifstream configFile (config_file_name.c_str());
	string line;
    bool number = false, hasBoard = false, hasTiles = false, hasDict = false;

	if (!configFile.is_open())
		throw invalid_argument("Cannot open file: " + config_file_name); // Handle file open error
	while (getline (configFile, line))
	{
		stringstream ss (line);
		string parameter;
		ss >> parameter;
		if (parameter == "NUMBER:")
			{ ss >> hand_size; number = true; }
		else if (parameter == "BOARD:")
		    { ss >> board_file_name; hasBoard = true; }
		else if (parameter == "TILES:")
			{ ss >> bag_file_name; hasTiles = true; }
		else if (parameter == "DICTIONARY:")
			{ ss >> dictionary_file_name; hasDict = true; }
	}
	if (!number)
		throw invalid_argument("Hand size not specified in config file");
	if (!hasBoard)
		throw invalid_argument("Board file name not specified in config file");
	if (!hasTiles)
		throw invalid_argument("Bag file name not specified in config file");
	if (!hasDict)
		throw invalid_argument("Dictionary file name not specified in config file");
}

int main (int nargs, char **args)
{
	if (nargs < 2 || nargs > 2)
		cout << "Usage: Scrabble <config-filename>\n";
	try {
		string dictionaryFileName, boardFileName, bagFileName;
		unsigned int numTiles;

		readConfigFile (args[1],
						dictionaryFileName, boardFileName, bagFileName,
						numTiles);

		Dictionary dict (dictionaryFileName); // Initialize dictionary
		Board board (boardFileName); // Initialize board
		Bag bag (bagFileName, 794); // Initialize bag with random seed
		gamePlay(dict, board, bag, numTiles); // Start the game
		return 0;
	}
	catch (invalid_argument & e)
	{ cout << "Fatal Error! " << e.what(); } // Handle exceptions

	return 1;
}

void gamePlay(Dictionary& dict, Board& board, Bag& bag, int numTiles)
{
	stringstream ss;
	string move, word;
	char dir;
	int r = 0; 
	int c = 0;
	int pos = -1;
	unsigned int counter = 0;
	bool hasTile = true;
	bool firstMove = true;
	bool isValid = true;
	UserInterface UI;
	UI.createNewPlayers(bag, numTiles); // Create players and distribute tiles
	
	while((bag.tilesRemaining() > 0 || UI.players[UI.getTurn()]->getHandSize() != 0)
		&& (counter != UI.players.size())){
		ss.clear();
		ss.str("");
		UI.printTurn(); // Print current player's turn
		UI.printScore(); // Print scores
		UI.printBoard(board); // Print the board
		UI.printTiles(); // Print player's tiles
		string line = UI.getMove(); // Get player's move
		ss << line;
		ss >> move;
		if(move == "PASS"){
			counter++;
			UI.switchTurns(); // Switch turns
		}
		else if(move == "EXCHANGE"){
			counter = 0;
			ss >> word;
			if(ss.fail()){
				cout << "Please enter the right number of parameters.";
				cout << "\n\n";
				continue;
			}
			else{
				for(unsigned int i = 0; i < word.length(); i++){
					word[i] = toupper(word[i]); // Convert to uppercase
				}
			}
			for(unsigned int i = 0; i < word.length(); i++){
				if(!UI.players[UI.getTurn()]->findTile(string(1, word[i]),pos)){ // Convert char to string
					cout << "You do not have this tile. Please try again!";
					cout << "\n\n";
					hasTile = false;
					break;
				}
			}
			pos = -1;
			if(!hasTile){
				hasTile = true;
				continue;
			}
			UI.players[UI.getTurn()]->executeExchangeMove(bag, word); // Execute exchange move
			UI.switchTurns(); // Switch turns
		}
		else if (move == "PLACE"){
			counter = 0;
			int numBlanks = 0;
			ss >> dir >> r >> c >> word;
			if(ss.fail()){
				cout << "Command was malformed. Please try another move.";
				cout << "\n\n";
				continue;
			}
			else{
				for(unsigned int i = 0; i < word.length(); i++){
					if(word[i] == '?')
						numBlanks++;
					else
						word[i] = toupper(word[i]); // Convert to uppercase
				}
			}
			if((dir == '-' && (c-1 - numBlanks + (int)word.length() > board.getColSize())) ||
			(dir == '|' && (r-1 - numBlanks + (int)word.length() > board.getRowSize()))) {
				cout << "One or more of your tiles would end up out of bounds. ";
				cout << "Please try another move." << "\n\n";
				continue;
			}
			if(firstMove && !onFirstTile(r-1,c-1,dir,word,board)){
				cout << "First move must start on the starting square. ";
				cout << "Please try another move." << "\n\n";
				continue;
			}
			if(board.boardVect[r-1][c-1]->occupied()){
				cout << "A tile already exists here! Please enter a different position.";
				cout << "\n\n";
				continue;
			}
			for(unsigned int i = 0; i < word.length(); i++){
				if(i != 0 && word[i-1] == '?'){
					continue;
				}
				if(!UI.players[UI.getTurn()]->findTile(string(1, word[i]), pos)){ // Convert char to string
					cout << "You do not have this tile. Please try again!";
					cout << "\n\n";
					hasTile = false;
					break;
				}
			}
			pos = -1;
			if(!hasTile){
				hasTile = true;
				continue;
			}
			isValid = UI.players[UI.getTurn()]->executePlaceMove(bag,dict,board,dir,r,c,word); // Execute place move
			if(!isValid) continue;
			firstMove = false;
			UI.switchTurns(); // Switch turns
		}
		else{
			cout << "Did not recognize your command. Please try another move!";
			cout << "\n\n";
		}
	}
	UI.endGame(); // End the game
}

bool onFirstTile(int row, int col, char dir, string word, Board& board)
{
	for(int i = 0; i < (int)word.length(); i++){
		if(dir == '|'){
			if(row + i == board.getStartY() && col == board.getStartX())
				return true;
		}
		else if (dir == '-'){
			if(col + i == board.getStartX() && row == board.getStartY())
				return true;
		}
	}
	return false;
}

/*
Code Overview
The Scrabble.cpp file is the main entry point for the Scrabble game. It is responsible for:

Reading configuration files to initialize game components.
Managing the game loop, handling user input, and executing game logic.
Interacting with the board, dictionary, tile bag, and players to ensure proper gameplay.
Providing a user interface for player interaction.

Key Functionalities
Configuration File Parsing (readConfigFile)
- Reads file paths and game settings from a configuration file.
- Ensures all necessary parameters are present.

Game Initialization (main)
- Parses command-line arguments.
- Loads game components using the configuration file.
- Starts the game loop.

Game Loop (gamePlay)
- Manages player turns, move validation, and game flow.
- Handles different player actions: PASS, EXCHANGE, and PLACE.
- Switches turns and determines game end conditions.

Move Validation (onFirstTile)
- Ensures the first move is placed on the required starting square.

Detailed Code Breakdown
1. Includes and Namespace
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include "lib/Dictionary.h"
#include "lib/Board.h"
#include "lib/Tile.h"
#include "lib/Player.h"
#include "lib/Bag.h"
#include "lib/Square.h"
#include "lib/UserInterface.h"

using namespace std;

Standard libraries provide file handling (fstream), string manipulation (sstream, string), and error handling (stdexcept).
Custom headers include classes for core game components (dictionary, board, tiles, players, bag, square, user interface).
using namespace std; avoids prefixing std:: throughout the file.

2. Configuration File Parsing
void readConfigFile (string config_file_name,
                     string & dictionary_file_name,
                     string & board_file_name,
                     string & bag_file_name,
                     unsigned int & hand_size)
{
    ifstream configFile (config_file_name.c_str());
    string line;
    bool number = false, hasBoard = false, hasTiles = false, hasDict = false;

    if (!configFile.is_open())
        throw invalid_argument("Cannot open file: " + config_file_name);
    while (getline (configFile, line))
    {
        stringstream ss (line);
        string parameter;
        ss >> parameter;
        if (parameter == "NUMBER:")
            { ss >> hand_size; number = true; }
        else if (parameter == "BOARD:")
            { ss >> board_file_name; hasBoard = true; }
        else if (parameter == "TILES:")
            { ss >> bag_file_name; hasTiles = true; }
        else if (parameter == "DICTIONARY:")
            { ss >> dictionary_file_name; hasDict = true; }
    }
    if (!number)
        throw invalid_argument("Hand size not specified in config file");
    if (!hasBoard)
        throw invalid_argument("Board file name not specified in config file");
    if (!hasTiles)
        throw invalid_argument("Bag file name not specified in config file");
    if (!hasDict)
        throw invalid_argument("Dictionary file name not specified in config file");
}

3. Game Initialization (main)
int main (int nargs, char **args)
{
    if (nargs < 2 || nargs > 2)
        cout << "Usage: Scrabble <config-filename>\n";
    try {
        string dictionaryFileName, boardFileName, bagFileName;
        unsigned int numTiles;

        readConfigFile (args[1], dictionaryFileName, boardFileName, bagFileName, numTiles);

        Dictionary dict (dictionaryFileName);
        Board board (boardFileName);
        Bag bag (bagFileName, 794); // second argument is random seed
        gamePlay(dict, board, bag, numTiles);

        return 0;
    }
    catch (invalid_argument & e)
    { cout << "Fatal Error! " << e.what(); }

    return 1;
}

Functionality
- Ensures a valid number of command-line arguments (Scrabble <config-filename>).
- Reads configuration data and initializes:
  - Dictionary (word list).
  - Board (Scrabble board layout).
  - Bag (tile bag with a random seed of 794).
- Calls gamePlay() to start the main game loop.
- Catches and reports errors if file loading fails.

4. Game Loop (gamePlay)
void gamePlay(Dictionary& dict, Board& board, Bag& bag, int numTiles)
{
    stringstream ss;
    string move, word;
    char dir;
    int r = 0, c = 0, pos = -1;
    unsigned int counter = 0;
    bool hasTile = true, firstMove = true, isValid = true;
    UserInterface UI;
    UI.createNewPlayers(bag, numTiles);

Functionality
- Initializes game variables.
- Creates players with their starting tiles.
- The loop continues as long as:
  - Tiles remain in the bag OR a player has tiles left AND all players haven't passed consecutively.

Handling Different Moves
if(move == "PASS"){
    counter++;
    UI.switchTurns();
}
- Passes the turn, increasing counter. If all players pass consecutively, the game ends.

else if(move == "EXCHANGE"){
    counter = 0;
    ss >> word;
    if(ss.fail()){
        cout << "Please enter the right number of parameters.\n\n";
        continue;
    }
Reads tile exchange input and ensures the player has the required tiles.
If valid, executes exchange and switches turns.

else if (move == "PLACE"){
    counter = 0;
    int numBlanks = 0;
    ss >> dir >> r >> c >> word;
Reads PLACE command (direction, row, column, word).
Converts to uppercase for consistency.
Checks for:
- Out-of-bounds placement.
- First move on center square.
- Tile availability.

if(board.boardVect[r-1][c-1]->occupied()){
    cout << "A tile already exists here! Please enter a different position.\n\n";
    continue;
}
Ensures no tile already occupies the specified position.

isValid = UI.players[UI.getTurn()]->executePlaceMove(bag,dict,board,dir,r,c,word);
if(!isValid) continue;
firstMove = false;
UI.switchTurns();
Executes the move if valid and switches turns.

else{
    cout << "Did not recognize your command. Please try another move!\n\n";
}
Handles invalid inputs.

5. First Move Validation (onFirstTile)
bool onFirstTile(int row, int col, char dir, string word, Board& board)
{
    for(int i = 0; i < (int)word.length(); i++){
        if(dir == '|'){
            if(row + i == board.getStartY() && col == board.getStartX())
                return true;
        }
        else if (dir == '-'){
            if(col + i == board.getStartX() && row == board.getStartY())
                return true;
        }
    }
    return false;
}

Functionality
- Ensures the first move is placed on the required starting square.
- Checks both vertical ('|') and horizontal ('-') placements.

Final Thoughts
This file serves as the core game engine:

Configuration Handling: Reads and validates config files.
Game Initialization: Sets up the game board, dictionary, tile bag, and players.
Gameplay Management: Runs the game loop, validating and executing moves.
Turn Switching & End Conditions: Controls turn progression and game termination.
*/