#ifndef __HANGMAN_H__
#define __HANGMAN_H__

#include <vector>
#include <string>


// Class defined to handle the game logic once a word has been chosen
class hangman
{
    public:
        hangman(const std::string& input);

        bool IsOver();
        void GetGuess(char& guess);
        void UpdateProgress(const char guess);
        void PrintProgress();

    private:
        bool WordRevealed();
        bool TooManyGuesses();
        bool ValidGuess(char& guess);
        bool HasBeenGuessed(const char& guess);

        int mistakes;               // Number of mistakes made by player (<= 6)
        int wordLength;             // Length of word to be guessed
        std::string word;           // Word to be guessed
        std::vector<char> guesses;  // Stores guessed letters from the player
        std::vector<bool> progress; // Stores which letters have been guessed or not
};


#endif
