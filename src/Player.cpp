#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <cstdlib>
#include "../headers/Player.h"
#include "../headers/Tile.h"
#include "../headers/Bag.h"
#include "../headers/Dictionary.h"
#include "../headers/Board.h"
#include "../headers/Square.h"

using namespace std;

Player::Player(string name, int score, int numTiles) {
    _name = name; // Initialize player's name
    _score = score; // Initialize player's score
    _numTiles = numTiles; // Initialize number of tiles the player can hold
}

Player::~Player() {
    for (unsigned int i = 0; i < _playerTiles.size(); i++) {
        delete _playerTiles[i]; // Delete dynamically allocated tiles
    }
}

string Player::getName() {
    return _name; // Return the player's name
}

void Player::getTiles(set<Tile*> tileSet) {
    for (set<Tile*>::iterator it = tileSet.begin(); it != tileSet.end(); it++) {
        _playerTiles.push_back(*it); // Add tiles to the player's hand
    }
}

void Player::useTile(string s) {
    for (unsigned int i = 0; i < _playerTiles.size(); i++) {
        if (s == _playerTiles[i]->getLetter()) {
            _playerTiles.erase(_playerTiles.begin() + i); // Remove the tile from the player's hand
            break;
        }
    }
}

void Player::exchangeTile(string s, Bag& bag) {
    for (unsigned int i = 0; i < _playerTiles.size(); i++) {
        if (s == _playerTiles[i]->getLetter()) {
            bag.addTile(_playerTiles[i]); // Return the tile to the bag
            _playerTiles.erase(_playerTiles.begin() + i); // Remove the tile from the player's hand
            break;
        }
    }
}

bool Player::findTile(string s, int& pos) {
    for (int i = 0; i < (int)_playerTiles.size(); i++) {
        if (i == pos)
            continue;
        if (s == _playerTiles[i]->getLetter()) {
            pos = i; // Update the position of the found tile
            return true;
        }
    }
    return false; // Tile not found
}

void Player::returnTile(string s, vector<Tile*>& usedTiles) {
    for (int i = 0; i < (int)_playerTiles.size(); i++) {
        if (s == _playerTiles[i]->getLetter()) {
            usedTiles.push_back(_playerTiles[i]); // Add the tile to the used tiles collection
            return;
        }
    }
}

void Player::addScore(int score) {
    _score += score; // Add the specified score to the player's total score
}

void Player::subtractScore(int score) {
    _score -= score; // Subtract the specified score from the player's total score
}

int Player::getScore() {
    return _score; // Return the player's current score
}

int Player::getHandSize() {
    return _playerTiles.size(); // Return the number of tiles currently in the player's hand
}

int Player::getHandScore() {
    int tilesScore = 0;
    for (unsigned int i = 0; i < _playerTiles.size(); i++) {
        tilesScore += _playerTiles[i]->getPoints(); // Sum the points of all tiles in the player's hand
    }
    return tilesScore; // Return the total score of all tiles in the player's hand
}

void Player::executeExchangeMove(Bag& bag, std::string word) {
    for (int i = 0; i < (int)word.length(); i++) {
        this->exchangeTile(word.substr(i, 1), bag); // Exchange each specified tile
    }
    this->getTiles(bag.drawTiles(word.length())); // Draw new tiles from the bag
}

bool Player::executePlaceMove(Bag& bag, Dictionary& dict, Board& board, char dir, int row, int col, std::string word) {
    vector<string> words;
    vector<Tile*> usedTiles;
    int score = 0;
    for (unsigned int i = 0; i < word.length(); i++) {
        returnTile(word.substr(i, 1), usedTiles); // Return the tile to the used tiles collection
        if (usedTiles[usedTiles.size() - 1]->isBlank() && i + 1 < word.length()) {
            usedTiles[usedTiles.size() - 1]->useAs(word.substr(i + 1, 1)); // Assign a letter to the blank tile
            i++;
        }
    }

    bool isValid = true;
    words = board.allWords(row, col, dir, score, usedTiles); // Find all words formed by the move

    for (unsigned int i = 0; i < words.size(); i++) {
        for (unsigned int j = 0; j < words[i].length(); j++) {
            words[i][j] = tolower(words[i][j]); // Convert words to lowercase
        }
    }

    if (words.empty()) {
        cout << "At least one tile must be adjacent to other tiles on the board." << endl;
        return false;
    }

    for (unsigned int i = 0; i < words.size(); i++) {
        isValid = dict.checkValid(words[i]); // Check if the word is valid
        if (!isValid) {
            cout << words[i] << " is invalid. Please try again." << endl;
            return false;
        }
    }

    if ((int)usedTiles.size() == _numTiles) {
        score += 50; // Bonus for using all tiles
    }
    this->addScore(score); // Add the score to the player's total
    cout << "Score for this round: " << score << endl;

    unsigned int i = 0;
    bool isOccupied = false;
    while (i < usedTiles.size()) {
        isOccupied = board.boardVect[row - 1][col - 1]->occupied();
        if (dir == '-') {
            if (!isOccupied) {
                board.boardVect[row - 1][col - 1]->setValue(usedTiles[i]); // Place the tile on the board
                this->useTile(usedTiles[i]->getLetter()); // Remove the tile from the player's hand
                i++;
            }
            col++;
        } else if (dir == '|') {
            if (!isOccupied) {
                board.boardVect[row - 1][col - 1]->setValue(usedTiles[i]); // Place the tile on the board
                this->useTile(usedTiles[i]->getLetter()); // Remove the tile from the player's hand
                i++;
            }
            row++;
        }
    }

    if ((int)usedTiles.size() > bag.tilesRemaining()) {
        this->getTiles(bag.drawTiles(bag.tilesRemaining())); // Draw remaining tiles from the bag
    } else {
        this->getTiles(bag.drawTiles(usedTiles.size())); // Draw new tiles from the bag
    }
    board.setFirstMove(false); // Update the first move flag
    return true;
}

/*
1. Includes and Namespace
#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <cstdlib>
#include "../headers/Player.h"
#include "../headers/Tile.h"
#include "../headers/Bag.h"
#include "../headers/Dictionary.h"
#include "../headers/Board.h"
#include "../headers/Square.h"

using namespace std;

The necessary C++ standard libraries (vector, set, string, iostream, cstdlib) are included.
The using namespace std; statement is used to simplify code by avoiding prefixing standard library objects with std::.
The #include statements bring in relevant class definitions (Player, Tile, Bag, Dictionary, Board, and Square), allowing the Player class to interact with them.

2. Constructor and Destructor
Constructor
Player::Player(string name, int score, int numTiles)
{
    _name = name;
    _score = score;
    _numTiles = numTiles;
}
Initializes a Player object with:
_name: Player's name.
_score: Initial score.
_numTiles: Maximum number of tiles the player can hold.

Destructor
Player::~Player()
{
    for(unsigned int i = 0; i < _playerTiles.size(); i++){
        delete _playerTiles[i];
    }
}
Frees memory by deleting all Tile objects in _playerTiles to prevent memory leaks.

3. Player Information Methods
Get Name
string Player::getName()
{
    return _name;
}
Returns the player's name.

Get Score
int Player::getScore()
{
    return _score;
}
Returns the player's current score.

Get Hand Size
int Player::getHandSize()
{
    return _playerTiles.size();
}
Returns the number of tiles the player currently holds.

Get Hand Score
int Player::getHandScore()
{
    int tilesScore = 0;
    for(unsigned int i = 0; i < _playerTiles.size(); i++){
        tilesScore += _playerTiles[i]->getPoints();
    }
    return tilesScore;
}
Calculates and returns the sum of all tile values in the player’s hand.

4. Tile Management
Receive Tiles
void Player::getTiles(set<Tile*> tileSet)
{
    for (set<Tile*>::iterator it = tileSet.begin(); it != tileSet.end(); it++){
        _playerTiles.push_back(*it);
    }
}
Adds a set of tiles to the player's hand.

Use a Tile
void Player::useTile(string s)
{
    for(unsigned int i = 0; i < _playerTiles.size(); i++){
        if(s == _playerTiles[i]->getLetter()){
            _playerTiles.erase(_playerTiles.begin() + i);
            break;
        }
    }
}
Removes a tile from _playerTiles when used.

Exchange a Tile
void Player::exchangeTile(string s, Bag& bag)
{
    for(unsigned int i = 0; i < _playerTiles.size(); i++){
        if(s == _playerTiles[i]->getLetter()){
            bag.addTile(_playerTiles[i]);
            _playerTiles.erase(_playerTiles.begin() + i);
            break;
        }
    }
}
Removes a tile from _playerTiles and returns it to the Bag.

Find a Tile
bool Player::findTile(string s, int& pos)
{
    for(int i = 0; i < (int)_playerTiles.size(); i++){
        if(i == pos)
            continue;
        if(s == _playerTiles[i]->getLetter()){
            pos = i;
            return true;
        }
    }
    return false;
}
Searches for a tile in the player's hand. If found, updates pos and returns true.

Return a Tile to the Player's Hand
void Player::returnTile(string s, vector<Tile*>& usedTiles)
{
    for(int i = 0; i < (int)_playerTiles.size(); i++){
        if (s == _playerTiles[i]->getLetter()){
            usedTiles.push_back(_playerTiles[i]);
            return;
        }
    }
}
Moves a used tile to the usedTiles vector.

5. Score Management
Add Score
void Player::addScore(int score)
{
    _score += score;
}
Increases the player's score.

Subtract Score
void Player::subtractScore(int score)
{
    _score -= score;
}
Decreases the player's score.

6. Game Actions
Exchange Move
void Player::executeExchangeMove(Bag& bag, std::string word)
{
    for(int i = 0; i < (int)word.length(); i++){
        this->exchangeTile(word.substr(i, 1), bag);
    }
    this->getTiles(bag.drawTiles(word.length()));
}
Exchanges all specified tiles by removing them from the player's hand and drawing new ones.

Place Move
bool Player::executePlaceMove(Bag& bag, Dictionary& dict, Board& board, char dir, int row, int col, std::string word)
{
    vector<string> words;
    vector<Tile*> usedTiles;
    int score = 0;
    for(unsigned int i = 0; i < word.length(); i++){
        returnTile(word.substr(i, 1), usedTiles);
        if (usedTiles[usedTiles.size()-1]->isBlank() && i+1 < word.length()){
            usedTiles[usedTiles.size()-1]->useAs(word.substr(i+1, 1));
            i++;
        }
    }

    bool isValid = true;
    
    words = board.allWords(row,col,dir,score,usedTiles);

    for(unsigned int i = 0; i < words.size(); i++){
        for(unsigned int j = 0; j < words[i].length(); j++){
            (words[i])[j] = tolower((words[i])[j]);
        }
    }
    
    if(words.empty()){
        cout << "At least one tile must be adjacent to other tiles on the board." << endl;
        return false;
    }

    for(unsigned int i = 0; i < words.size(); i++){
        isValid = dict.checkValid(words[i]);
        if(!isValid){
            cout << words[i] << " is invalid. Please try again." << endl;
            return false;
        }
    }
    if((int)usedTiles.size() == _numTiles){
        score += 50;
    }
    this->addScore(score);
    cout << "Score for this round: " << score << endl;
    unsigned int i = 0;
    bool isOccupied = false;
    while(i < usedTiles.size()){
        isOccupied = board.boardVect[row-1][col-1]->occupied();
        if(dir == '-'){
            if(!isOccupied){
                board.boardVect[row-1][col-1]->setValue(usedTiles[i]);
                this->useTile(usedTiles[i]->getLetter());
                i++;
            }
            col++;
        }
        else if(dir == '|'){
            if(!isOccupied){
                board.boardVect[row-1][col-1]->setValue(usedTiles[i]);
                this->useTile(usedTiles[i]->getLetter());
                i++;
            }
            row++;
        }
    }
    if((int)usedTiles.size() > bag.tilesRemaining()){
        this->getTiles(bag.drawTiles(bag.tilesRemaining()));
    }
    else{
        this->getTiles(bag.drawTiles(usedTiles.size()));
    }
    board.setFirstMove(false);
    return true;
}
*/