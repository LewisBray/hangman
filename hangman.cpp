#include "hangman.h"

#include <iostream>

Hangman::Hangman(const std::string& word)
    : numMistakesMade_{ 0 }
{
    // Set corresponding bool for 'spaces' to true as we want them displayed
    const size_t wordLength = word.size();
    word_.reserve(wordLength);
    for (size_t i = 0; i < wordLength; ++i)
        word_.emplace_back(word[i], (word[i] == ' '));
}

bool Hangman::isOver() const
{
    if (tooManyMistakesMade())
    {
        const std::string wordAsString{ getWordAsString() };
        std::cout << std::endl << "Uh, oh!  Too many mistakes...  "
            << "The word/phrase was: " << wordAsString << ".\n" << std::endl;
        return true;
    }

    if (wordHasBeenRevealed()) {
        std::cout << std::endl << "Well done, you got it!\n" << std::endl;
        return true;
    }

    return false;
}

char Hangman::askUserForGuess() const
{
    while (true)
    {
        std::cout << "\nGuess: ";

        char guess;
        std::cin >> guess;

        if (guessIsValid(guess))
            return guess;
    }
}

// 'guess' should be lower case before calling this, this results in only lower
// case letters being stored in 'guesses' which keeps the logic simpler.
void Hangman::updateProgress(const char guess)
{
    guessedLetters_.push_back(guess);

    bool present = false;
    for (Character& character : word_)
        if (guess == character.letter_ || toupper(guess) == character.letter_)
        {
            character.hasBeenGuessed_ = true;
            present = true;
        }

    if (present)
        std::cout << "Good guess.";
    else {
        ++numMistakesMade_;
        std::cout << "Sorry, not there.";
    }
}

bool Hangman::wordHasBeenRevealed() const
{
    for (const Character& character : word_)
        if (!character.hasBeenGuessed_)
            return false;

    return true;
}

bool Hangman::tooManyMistakesMade() const
{
    return (numMistakesMade_ == MaxNumberOfMistakes);
}

// 'guess' becomes lower case after this function has run.
bool Hangman::guessIsValid(char& guess) const
{
    if (!isalpha(guess)) {
        std::cout << "That's not a letter!" << std::endl;
        return false;
    }

    if (isupper(guess))
        guess = tolower(guess);

    if (hasAlreadyBeenGuessed(guess)) {
        std::cout << "You've already guessed that letter." << std::endl;
        return false;
    }

    return true;
}

bool Hangman::hasAlreadyBeenGuessed(const char guess) const
{
    if (guessedLetters_.empty())
        return false;

    for (const char guessedLetter : guessedLetters_)
        if (guess == guessedLetter)
            return true;

    return false;
}

std::string Hangman::getWordAsString() const
{
    std::string wordAsString{ "" };
    for (const Character& character : word_)
        wordAsString += character.letter_;

    return wordAsString;
}

std::ostream& operator<<(std::ostream& out, const Hangman& hangman)
{
    out << "\t     .-----. \n";
    out << "\t     |     | \n";

    if (hangman.numMistakesMade_ >= 1) {
        out << "\t     _     | \n";
        out << "\t    | |    | \n";
        out << "\t     T     | ";
    }
    else {
        out << "\t           | \n";
        out << "\t           | \n";
        out << "\t           | ";
    }
    out << "\t\t";

    // Prints the current progress towards guessing the word
    for (const Hangman::Character& character : hangman.word_)
    {
        if (character.hasBeenGuessed_)
            out << character.letter_;
        else
            out << '_';

        out << ' ';
    }
    out << '\n';

    if (hangman.numMistakesMade_ == 2)
        out << "\t     +     | ";
    else if (hangman.numMistakesMade_ == 3)
        out << "\t   --+     | ";
    else if (hangman.numMistakesMade_ >= 4)
        out << "\t   --+--   | ";
    else
        out << "\t           | ";
    out << '\n';

    if (hangman.numMistakesMade_ >= 2) {
        out << "\t     |     | \n";
        out << "\t     |     | \n";
        out << "\t     |     | ";
    }
    else {
        out << "\t           | \n";
        out << "\t           | \n";
        out << "\t           | ";
    }

    out << "\t   Guesses: ";
    for (const char letter : hangman.guessedLetters_) {
        out << letter;
        if (letter != hangman.guessedLetters_.back())
            out << ", ";
    }
    out << '\n';

    if (hangman.numMistakesMade_ == 5) {
        out << "\t    /      | \n";
        out << "\t   /       | \n";
        out << "\t           | ";
    }
    else if (hangman.numMistakesMade_ >= 5) {
        out << "\t    / \\    | \n";
        out << "\t   /   \\   | \n";
        out << "\t           | ";
    }
    else {
        out << "\t           | \n";
        out << "\t           | \n";
        out << "\t           | ";
    }
    out << "\n\t -------------";

    return out;
}
