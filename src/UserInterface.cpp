#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <limits>
#include "../headers/Dictionary.h"
#include "../headers/Board.h"
#include "../headers/Tile.h"
#include "../headers/Player.h"
#include "../headers/Bag.h"
#include "../headers/Square.h"
#include "../headers/UserInterface.h"

using namespace std;

UserInterface::UserInterface() {
    _turn = 0; // Initialize the turn to the first player
}

UserInterface::~UserInterface() {
    for (unsigned int i = 0; i < players.size(); i++) {
        delete players[i]; // Delete dynamically allocated player objects
    }
}

void UserInterface::createNewPlayers(Bag& bag, int numTiles) {
    string dummy;
    cout << "Please enter the number of players (1-8): ";
    cin >> _numPlayers;
    while (1) {
        if (cin.fail() || _numPlayers < 1 || _numPlayers > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid number of players." << endl;
            cout << "Please enter the number of players (1-8): ";
            cin >> _numPlayers;
        } else {
            break;
        }
    }
    players.resize(_numPlayers); // Resize the players vector to the number of players
    for (int i = 0; i < _numPlayers; i++) {
        cout << "Enter the name of player " << i + 1 << ": ";
        cin >> _playerName;
        getline(cin, dummy); // Clear the input buffer
        players[i] = new Player(_playerName, 0, numTiles); // Create a new player
        players[i]->getTiles(bag.drawTiles(numTiles)); // Assign tiles to the player
    }
}

void UserInterface::switchTurns() {
    cout << "\n";
    if (_turn == _numPlayers - 1)
        _turn = 0; // Loop back to the first player
    else
        _turn++; // Move to the next player
}

void UserInterface::printBoard(Board& board) {
    cout << "   ";
    for (int i = 1; i <= board.getRowSize(); i++) {
        if (i >= 10) {
            cout << i << "  ";
        } else {
            cout << i << "   ";
        }
    }
    cout << endl;
    for (int i = 0; i < board.getRowSize(); i++) {
        if (i >= 9) {
            cout << i + 1 << " ";
        } else {
            cout << i + 1 << "  ";
        }
        for (int j = 0; j < board.getColSize(); j++) {
            cout << board.boardVect[i][j]->valueForBoard() << " ";
        }
        cout << endl;
    }
    cout << "\n";
}

void UserInterface::printTiles() {
    cout << players[_turn]->getName() << "'s tiles: ";
    for (unsigned int i = 0; i < players[_turn]->_playerTiles.size(); i++) {
        cout << "[" << players[_turn]->_playerTiles[i]->getLetter() << ", "
             << players[_turn]->_playerTiles[i]->getPoints() << "]" << " ";
    }
    cout << endl;
}

string UserInterface::getMove() {
    cout << "To pass your turn, type PASS." << endl;
    cout << "To discard tiles, type EXCHANGE, followed by a string of those tiles." << endl;
    cout << "To place a word, type PLACE, followed by the following: " << endl;
    cout << "  first, either a | or - for vertical/horizontal placement;" << endl;
    cout << "  second, the row (from the top), the column (from the left)," << endl;
    cout << "  third, a sequence of letters to place;" << endl;
    cout << "  to use a blank tile, type ? followed by the letter you want to use it for." << endl;

    getline(cin, line); // Get the entire line of input
    return line;
}

void UserInterface::printScore() {
    cout << "CURRENT SCORE:" << endl;
    for (int i = 0; i < _numPlayers; i++) {
        cout << players[i]->getName() << ": " << players[i]->getScore() << endl;
    }
}

void UserInterface::printTurn() {
    cout << players[_turn]->getName() << ", it is your turn!" << endl;
}

int UserInterface::getTurn() {
    return _turn; // Return the index of the current player
}

void UserInterface::endGame() {
    int totScore = 0;
    int pos = 0;
    int max = 0;
    if (players[_turn]->getHandSize() == 0) {
        for (unsigned int i = 0; i < players.size(); i++) {
            players[i]->subtractScore(players[i]->getHandScore()); // Subtract the score of remaining tiles
            totScore += players[i]->getHandScore(); // Add to total score
        }
        players[_turn]->addScore(totScore); // Add total score to the current player
    }
    cout << "FINAL SCORE:" << endl;
    for (int i = 0; i < _numPlayers; i++) {
        if (players[i]->getScore() >= max) {
            max = players[i]->getScore();
            pos = i;
        }
        cout << players[i]->getName() << ": " << players[i]->getScore() << endl;
    }
    cout << "THE WINNER IS: " << players[pos]->getName();
    for (int i = 0; i < _numPlayers; i++) {
        if (i == pos)
            continue;
        else if (players[i]->getScore() == max) {
            cout << ", " << players[i]->getName();
        }
    }
    cout << endl;
}

/*
Code Overview
The UserInterface.cpp file implements the UserInterface class, which is responsible for managing user interactions in the Scrabble game. It facilitates:

Player management: Creating players, switching turns, and tracking the current player.
Game display: Printing the board, tiles, and scores.
User input handling: Getting player moves and processing them.
Game control: Managing turn-based gameplay and handling game-ending logic.
This implementation ensures a smooth interface between the player and the game's logic.

Detailed Code Breakdown
Includes and Namespace
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <limits>
#include "../headers/Dictionary.h"
#include "../headers/Board.h"
#include "../headers/Tile.h"
#include "../headers/Player.h"
#include "../headers/Bag.h"
#include "../headers/Square.h"
#include "../headers/UserInterface.h"

using namespace std;
- Includes necessary libraries for input/output, string manipulation, error handling, and game logic components.
- Uses std namespace to simplify syntax.

Constructor
UserInterface::UserInterface()
{
    _turn = 0;
}
- Initializes _turn to 0, ensuring that the first player starts the game.

Destructor
UserInterface::~UserInterface()
{
    for(unsigned int i = 0; i < players.size(); i++){
        delete players[i];
    }
}
- Frees memory allocated for players, preventing memory leaks.

Player Creation
void UserInterface::createNewPlayers(Bag& bag, int numTiles){
    string dummy;
    cout << "Please enter the number of players (1-8): ";
    cin >> _numPlayers;
    while(1){
        if(cin.fail() || _numPlayers < 1 || _numPlayers > 8){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid number of players." << endl;
            cout << "Please enter the number of players (1-8): ";
            cin >> _numPlayers;
        }
        else{
            break;
        }
    }
    players.resize(_numPlayers);
    for(int i = 0; i < _numPlayers; i++){
        cout << "Enter the name of player " << i+1 << ": ";
        cin >> _playerName;
        getline(cin, dummy); // Ensures input buffer is cleared
        players[i] = new Player(_playerName, 0, numTiles);
        players[i]->getTiles(bag.drawTiles(numTiles));
    }
}
- Gets player count, ensuring it is between 1 and 8.
- Validates input, preventing invalid entries.
- Creates players, assigns names, and gives them an initial set of tiles.

Turn Management
void UserInterface::switchTurns()
{
    cout << "\n";
    if(_turn == _numPlayers-1)
        _turn = 0;
    else
        _turn++;
}
- Cycles through players, ensuring the turn loops back to the first player after the last player.

Printing the Board
void UserInterface::printBoard(Board& board)
{
    cout << "   ";
    for(int i = 1; i <= board.getRowSize(); i++){
        if(i >= 10){
            cout << i << "  ";
        }
        else{
            cout << i << "   ";
        }
    }
    cout << endl;
    for (int i = 0; i < board.getRowSize(); i++){
        if(i >= 9){
            cout << i+1 << " ";
        }
        else{
            cout << i+1 << "  ";
        }
        for(int j = 0; j < board.getColSize(); j++){
            cout << board.boardVect[i][j]->valueForBoard() << " ";
        }
        cout << endl;
    }
    cout << "\n";
}
- Displays the game board with row and column numbers for easy reference.
- Ensures proper spacing to align the board correctly.

Displaying Player Tiles
void UserInterface::printTiles()
{
    cout << players[_turn]->getName() << "'s tiles: ";
    for(unsigned int i = 0; i < players[_turn]->_playerTiles.size(); i++){
        cout << "["<< players[_turn]->_playerTiles[i]->getLetter() << ", "
        << players[_turn]->_playerTiles[i]->getPoints() << "]" << " ";
    }
    cout << endl;
}
- Prints the current player’s tiles, showing both the letter and its point value.

Getting Player Input
string UserInterface::getMove()
{
    cout << "To pass your turn, type PASS." << endl;
    cout << "To discard tiles, type EXCHANGE, followed by a string of those tiles." << endl;
    cout << "To place a word, type PLACE, followed by the following: " << endl;
    cout << "  first, either a | or - for vertical/horizontal placement;" << endl;
    cout << "  second, the row (from the top), the column (from the left)," << endl;
    cout << "  third, a sequence of letters to place;" << endl;
    cout << "  to use a blank tile, type ? followed by the letter you want to use it for." << endl;
    
    getline(cin, line);
    return line;
}
- Provides clear instructions on how to input different moves.
- Reads user input into line and returns it.

Displaying Scores
void UserInterface::printScore()
{
    cout << "CURRENT SCORE:" << endl;
    for(int i = 0; i < _numPlayers; i++){
        cout << players[i]->getName() << ": " << players[i]->getScore() << endl;
    }
}
- Prints the score of all players, keeping players updated on the game state.

Indicating Player Turn
void UserInterface::printTurn()
{
    cout << players[_turn]->getName() << ", it is your turn!" << endl;
}
- Notifies the current player that it's their turn.

Getting the Current Turn
int UserInterface::getTurn()
{
    return _turn;
}
- Returns the index of the current player.

Handling Game End
void UserInterface::endGame()
{
    int totScore = 0;
    int pos = 0;
    int max = 0;
    if(players[_turn]->getHandSize() == 0){
        for(unsigned int i = 0; i < players.size(); i++){
            players[i]->subtractScore(players[i]->getHandScore());
            totScore += players[i]->getHandScore();
        }
        players[_turn]->addScore(totScore);
    }
    cout << "FINAL SCORE:" << endl;
    for(int i = 0; i < _numPlayers; i++){
        if(players[i]->getScore() >= max){
            max = players[i]->getScore();
            pos = i;
        }
        cout << players[i]->getName() << ": " << players[i]->getScore() << endl;
    }
    cout << "THE WINNER IS: " << players[pos]->getName();
    for(int i = 0; i < _numPlayers; i++){
        if(i == pos)
            continue;
        else if(players[i]->getScore() == max){
            cout << ", " << players[i]->getName();
        }
    }
    cout << endl;
}
- Finalizes scores, deducting leftover tile points.
- Determines the winner, considering ties.
- Prints final scores and announces the winner.

Conclusion
The UserInterface.cpp file provides essential functions for interacting with players, managing turns, displaying game information, and handling game flow. It ensures:

Smooth player interaction with the game.
Clear game state presentation, including the board, scores, and tiles.
Proper input handling, reducing errors in player commands.
Correct game termination, including fair scoring and winner declaration.
This file is a crucial component of the Scrabble game, ensuring an engaging and well-managed gameplay experience.
*/