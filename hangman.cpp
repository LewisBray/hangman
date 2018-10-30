#include "hangman.h"

#include <iostream>
#include <sstream>

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

std::string Hangman::formatUserGuesses() const
{
    std::stringstream userGuesses;
    for (const char letter : guessedLetters_) {
        userGuesses << letter;
        if (letter != guessedLetters_.back())
            userGuesses << ", ";
    }

    return userGuesses.str();
}

std::string Hangman::formatWordProgress() const
{
    std::stringstream wordProgress;
    for (const Hangman::Character& character : word_)
    {
        if (character.hasBeenGuessed_)
            wordProgress << character.letter_;
        else
            wordProgress << '_';

        wordProgress << ' ';
    }

    return wordProgress.str();
}

// Some constants for drawing the gallows
static const char topOfGallows[] =
    "\t     .-----. \n"
    "\t     |     | \n";

static const char head[] =
    "\t     _     | \n"
    "\t    | |    | \n"
    "\t     T     | ";

static const char noHead[] =
    "\t           | \n"
    "\t           | \n"
    "\t           | ";

static const char noChest[] =
    "\t           | ";

static const char chest[] =
    "\t     +     | ";

static const char chestWithArm[] =
    "\t   --+     | ";

static const char chestWithBothArms[] =
    "\t   --+--   | ";

static const char noTorso[] =
    "\t           | \n"
    "\t           | \n"
    "\t           | ";

static const char torso[] =
    "\t     |     | \n"
    "\t     |     | \n"
    "\t     |     | ";

static const char noLegs[] =
    "\t           | \n"
    "\t           | \n"
    "\t           | ";

static const char oneLeg[] =
    "\t    /      | \n"
    "\t   /       | \n"
    "\t           | ";

static const char bothLegs[] =
    "\t    / \\    | \n"
    "\t   /   \\   | \n"
    "\t           | ";

static const char baseOfGallows[] =
    "\t -------------";

std::ostream& operator<<(std::ostream& out, const Hangman& hangman)
{
    out << topOfGallows;

    if (hangman.numMistakesMade_ >= 1)
        out << head;
    else
        out << noHead;

    const std::string wordProgress = hangman.formatWordProgress();
    out << "\t\t" << wordProgress << '\n';

    if (hangman.numMistakesMade_ == 2)
        out << chest;
    else if (hangman.numMistakesMade_ == 3)
        out << chestWithArm;
    else if (hangman.numMistakesMade_ >= 4)
        out << chestWithBothArms;
    else
        out << noChest;
    out << '\n';

    if (hangman.numMistakesMade_ >= 2)
        out << torso;
    else
        out << noTorso;

    const std::string userGuesses = hangman.formatUserGuesses();
    out << "\t   Guesses: " << userGuesses << '\n';

    if (hangman.numMistakesMade_ == 5)
        out << oneLeg;
    else if (hangman.numMistakesMade_ >= 5)
        out << bothLegs;
    else
        out << noLegs;

    out << '\n' << baseOfGallows;

    return out;
}
