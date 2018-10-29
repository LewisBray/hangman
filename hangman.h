#ifndef __HANGMAN_H__
#define __HANGMAN_H__

#include <string>
#include <vector>

// Class defined to handle the game logic once a word has been chosen
class Hangman
{
public:
    Hangman(const std::string& word);

    char askUserForGuess() const;
    bool isOver() const;
    void updateProgress(const char guess);

    friend std::ostream& operator<<(std::ostream& out, const Hangman& hangman);

private:
    enum { MaxNumberOfMistakes = 6 };

    bool tooManyMistakesMade() const;
    bool wordHasBeenRevealed() const;
    bool guessIsValid(char& guess) const;
    bool hasAlreadyBeenGuessed(const char guess) const;
    std::string getWordAsString() const;

    // Struct that holds info on each character in word to be guessed
    struct Character
    {
        Character(const char letter, const bool hasBeenGuessed)
            : letter_{ letter }
            , hasBeenGuessed_{ hasBeenGuessed }
        {}

        char letter_;
        bool hasBeenGuessed_;
    };

    unsigned numMistakesMade_;
    std::vector<char> guessedLetters_;
    std::vector<Character> word_;
};

#endif
