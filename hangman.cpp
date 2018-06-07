#include "hangman.h"


// Initialises the game after being passed a word.
hangman::hangman(const std::string& input)
    : mistakes{0}
{
    // Set corresponding bool for 'spaces' to true as we
    // want /'s displayed in place of spaces throughout
    const unsigned wordLength = input.size();
    for (unsigned i = 0; i < wordLength; ++i)
        word.emplace_back(input[i], (input[i] == ' '));
}


// Checks if game is over (e.g. no more guesses or word has been correctly guessed).
bool hangman::IsOver() const
{
    if (TooManyGuesses())
    {
        std::string wordAsStr{GetWordAsString()};
        std::cout << "\nUh, oh!  Too many guesses...  ";
        printf("The word/phrase was: %s.\n\n", wordAsStr.c_str());
        return true;
    }

    if (WordRevealed()) {
        std::cout << "\nWell done, you got it!\n\n";
        return true;
    }

    return false;
}


// Prompts the user to guess a letter and makes sure it is valid before moving on.
void hangman::GetGuess(char& guess)
{
    while (true)
    {
        printf("\nGuess: ");
        std::cin >> guess;

        if (ValidGuess(guess))
            break;
    }
}


// Prints the gallows, progress and guesses.
/*
This is pretty tedious... there's probably a smarter way.
*/
void hangman::PrintProgress() const
{
    std::cout << "\t     .-----. \n";
    std::cout << "\t     |     | \n";

    if (mistakes >= 1) {
        std::cout << "\t     _     | \n";
        std::cout << "\t    | |    | \n";
        std::cout << "\t     T     | ";
    }
    else {
        std::cout << "\t           | \n";
        std::cout << "\t           | \n";
        std::cout << "\t           | ";
    }

    std::cout << "\t\t";

    // Prints the current progress towards guessing the word
    for (const character& ch : word)
    {
        if (ch.guessed) {
            if (ch.letter == ' ')
                std::cout << '/';
            else
                std::cout << ch.letter;
        }
        else
            std::cout << '_';

        std::cout << ' ';
            
    }

    std::cout << "\n";

    if (mistakes == 2)
        std::cout << "\t     +     | ";
    else if (mistakes == 3)
        std::cout << "\t   --+     | ";
    else if (mistakes >= 4)
        std::cout << "\t   --+--   | ";
    else
        std::cout << "\t           | ";

    std::cout << "\n";

    if (mistakes >= 2) {
        std::cout << "\t     |     | \n";
        std::cout << "\t     |     | \n";
        std::cout << "\t     |     | ";
    }
    else {
        std::cout << "\t           | \n";
        std::cout << "\t           | \n";
        std::cout << "\t           | ";
    }

    std::cout << "\t   Guesses: ";
    for (unsigned i = 0, numGuesses = guesses.size(); i < numGuesses; ++i)
        if (i == 0)
            std::cout << guesses[i];
        else
            printf(", %c", guesses[i]);
    std::cout << "\n";

    if (mistakes == 5) {
        std::cout << "\t    /      | \n";
        std::cout << "\t   /       | \n";
        std::cout << "\t           | ";
    }
    else if (mistakes >= 5) {
        std::cout << "\t    / \\    | \n";
        std::cout << "\t   /   \\   | \n";
        std::cout << "\t           | ";
    }
    else {
        std::cout << "\t           | \n";
        std::cout << "\t           | \n";
        std::cout << "\t           | ";
    }

    std::cout << "\n\t -------------\n";
}


// Updates the fields in the hangman class.
/*
The parameter 'guess' should be lower case before calling this, this results in
only lower case letters being stored in 'guesses' which keeps the logic simpler.
*/
void hangman::UpdateProgress(const char guess)
{
    guesses.push_back(guess);

    bool present = false;

    // Check for both upper and lower case
    // letters in case they were used in text file
    for (character& ch : word)
        if ((guess == ch.letter) || (toupper(guess) == ch.letter))
        {
            ch.guessed = true;
            present = true;
        }

    if (present)
        std::cout << "Good guess.";
    else {
        ++mistakes;
        std::cout << "Sorry, not there.";
    }
}


// Checks if the word has been fully revealed.
bool hangman::WordRevealed() const
{
    for (const character& ch : word)
        if (!ch.guessed)
            return false;

    return true;
}


// Returns true if the player has made 6 guesses.
bool hangman::TooManyGuesses() const
{
    return (mistakes == 6);
}


// Checks if the current guess is actually a letter and hasn't already been guessed.
/*
guess becomes lower case after this function has run.
*/
bool hangman::ValidGuess(char& guess) const
{
    if (!isalpha(guess)) {
        std::cout << "That's not a letter!\n";
        return false;
    }

    if (isupper(guess))
        guess = tolower(guess);

    if (HasBeenGuessed(guess)) {
        std::cout << "You've already guessed that letter.\n";
        return false;
    }

    return true;
}


// Returns true if the letter has already been guessed.
bool hangman::HasBeenGuessed(const char guess) const
{
    if (guesses.empty())
        return false;

    for (const char prevGuess : guesses)
        if (guess == prevGuess)
            return true;

    return false;
}


// Constructs and returns the word the player is guessing as a string.
std::string hangman::GetWordAsString() const
{
    std::string ret{""};
    for (const character& ch : word)
        ret += ch.letter;

    return ret;
}
