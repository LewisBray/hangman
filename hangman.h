#ifndef __HANGMAN_H__
#define __HANGMAN_H__

#include <iostream>
#include <vector>


// Class defined to handle the game logic once a word has been chosen
class hangman
{
public:
    hangman(const std::string& input);

    bool IsOver() const;
    void PrintProgress() const;
    void GetGuess(char& guess);
    void UpdateProgress(const char guess);

private:
    bool WordRevealed() const;
    bool TooManyGuesses() const;
    bool ValidGuess(char& guess) const;
    bool HasBeenGuessed(const char guess) const;
    std::string GetWordAsString() const;


    // Struct that holds info on each character in word to be guessed
    struct character
    {
        character(const char nextLetter, const bool defaultVal)
            : letter{ nextLetter }
            , guessed{ defaultVal }
        {}

        char letter;        // Letter the struct represents
        bool guessed;       // Has the player guessed this correctly
    };

    unsigned mistakes;              // Number of mistakes made (<= 6)
    std::vector<char> guesses;      // Previously guessed letters
    std::vector<character> word;    // All info regarding word to guess
};

#endif
