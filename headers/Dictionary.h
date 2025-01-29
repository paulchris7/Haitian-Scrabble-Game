#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <vector>
#include <string>

class Dictionary {
    public:
        Dictionary (std::string dictionary_file_name); // Constructor: Initializes the dictionary from a file
        bool checkValid(std::string word); // Checks if a given word is valid (exists in the dictionary)

    private:
        std::vector<std::string> _words; // Stores all words in the dictionary
};

#endif /* DICTIONARY_H_ */

/*
1. Overview
The `Dictionary` class manages a list of words and checks whether a given word exists in the dictionary. 
The words are loaded from an external file, and the class provides a method to validate if a word is present in that dictionary.

2. Code Breakdown

2.1 Header Guards
#ifndef DICTIONARY_H_
#define DICTIONARY_H_
- Prevents multiple inclusions of the header file, avoiding redefinition errors.

2.2 Includes
#include <vector>
#include <string>
- **`<vector>`**: Used for storing collections of words.
- **`<string>`**: Provides the string data type to work with word representations.

2.3 Constructor
Dictionary(std::string dictionary_file_name);
- Initializes the dictionary from a file. The file name is provided as a parameter.

2.4 Public Methods
bool checkValid(std::string word);
- Checks whether a given word exists in the dictionary.
- Returns a boolean value (`true` if the word is found, `false` otherwise).

2.5 Private Members
std::vector<std::string> _words;
- Stores the collection of words in the dictionary.

3. Code Design Features

- Simplicity: The class is designed to be simple, containing a basic data structure (`std::vector<std::string>`) for storing words and a straightforward method (`checkValid`) to check if a word exists in the dictionary.
- Flexibility: The design allows the dictionary to be initialized from a file, but the actual reading and parsing logic would be implemented in the corresponding source file.
- Extendability: The design can be extended to support additional features, such as case-insensitive word matching, loading multiple dictionary files, or storing metadata like word scores.

4. Advantages of This Design

- Simplicity: The design is straightforward, with a clear responsibility for checking the validity of words in the dictionary. It's easy to understand and use.
- File Input: The class is capable of loading words from an external file, allowing for easy updates or changes to the dictionary without modifying the code.
- Maintainability: The code is kept simple, making it easy to maintain or extend in the future (e.g., by improving the data structure or adding new features).

Potential Areas for Improvement

- Efficiency: The use of `std::vector` to store words could be replaced by a more efficient data structure like `std::unordered_set`. This would reduce the time complexity for lookups from O(n) to O(1), making the game more responsive as the dictionary grows in size.
- Error Handling: There is no error handling in the constructor for cases where the file cannot be opened or read. This should be addressed to prevent undefined behavior.
- Function Renaming: The function `checkValid` could be renamed to something more expressive like `isValidWord` for clarity.
*/