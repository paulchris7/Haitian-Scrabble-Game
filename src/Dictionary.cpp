#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "../headers/Dictionary.h"


using namespace std;

Dictionary::Dictionary (string dictionary_file_name) {
    ifstream dictFile (dictionary_file_name.c_str()); // Open the dictionary file
    string word;

    if (dictFile.is_open()) {
        while (getline (dictFile, word)) {
            word.erase(word.find_last_not_of("\r\n") + 1); // Remove end-of-line characters
            _words.push_back(word); // Add word to the list
        }
        sort(_words.begin(), _words.end()); // Sort the list of words
        dictFile.close (); // Close the file
    } else {
        throw invalid_argument("Cannot open file: " + dictionary_file_name); // Handle file open error
    }
}

//binary search on vector to check if word(s) exist
bool Dictionary::checkValid(string word) {
    int min = 0;
    int max = _words.size() - 1;
    int index = (max + min) / 2;

    while (min <= max) {
        if (word.compare(_words[index]) == 0) {
            return true; // Word found
        } else if (word.compare(_words[index]) > 0) {
            min = index + 1; // Search in the upper half
        } else {
            max = index - 1; // Search in the lower half
        }
        index = (max + min) / 2;
    }
    return false; // Word not found
}

/*
Overview of Dictionary.cpp
The Dictionary.cpp file is responsible for managing the dictionary of valid words in the Scrabble game. 
It loads words from a file, stores them in a sorted vector, and provides a binary search function to check if a word is valid.

Breakdown of Dictionary.cpp
1. Headers and Namespace
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "../lib/Dictionary.h"

using namespace std;
Includes necessary libraries:
<string>: Handles string operations.
<fstream>: Reads the dictionary file.
<iostream>: Used for debugging (though not actively used here).
<stdexcept>: Handles exceptions.
<vector>: Stores words in a dynamic array.
<algorithm>: Provides sorting functions.
Includes the corresponding header file (Dictionary.h).
Uses std namespace to avoid std:: prefixing.

2. Dictionary Constructor
Dictionary::Dictionary(string dictionary_file_name)
{
    ifstream dictFile(dictionary_file_name.c_str());
    string word;

    if (dictFile.is_open())
    {
        while (getline(dictFile, word))
        {
            word.erase(word.find_last_not_of("\r\n") + 1); // remove end-of-line characters
            _words.push_back(word);
        }
        sort(_words.begin(), _words.end()); // Sort unordered list
        dictFile.close();
    }
    else throw invalid_argument("Cannot open file: " + dictionary_file_name);
}
Functionality:
Opens the dictionary file using ifstream.
Reads words line by line using getline(dictFile, word).
Removes end-of-line characters using word.erase(word.find_last_not_of("\r\n") + 1).
Adds each word to _words, a vector<string>.
Sorts the list to allow efficient binary search.
Throws an exception if the file cannot be opened.
Bug in word.erase(word.length());
word.erase(word.length()); does nothing since erase() starts at index word.length() and removes nothing.
Correct approach: word.erase(word.find_last_not_of("\r\n") + 1); (removes any newline characters at the end).

3. checkValid(string word): Binary Search
bool Dictionary::checkValid(string word)
{
    int min = 0;
    int max = _words.size() - 1;
    int index = (max + min) / 2;

    while (min <= max)
    {
        if (word.compare(_words[index]) == 0) return true;
        else if (word.compare(_words[index]) > 0)
        {
            min = index + 1;
        }
        else // (word.compare(_words[index]) < 0)
        {
            max = index - 1;
        }
        index = (max + min) / 2;
    }
    return false;
}
Functionality:
Performs a binary search on _words to determine if word exists.
Uses integer indices (min, max, index) to navigate the sorted vector.
Compares word with _words[index]:
Match: Returns true.
Greater: Move min up (min = index + 1).
Smaller: Move max down (max = index - 1).
Returns false if the word is not found.

Possible Optimization
Instead of manually computing index, use std::binary_search() from <algorithm>:
return binary_search(_words.begin(), _words.end(), word);
This simplifies the function while maintaining efficiency.
*/