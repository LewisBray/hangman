#include "hangman.h"

#include <iostream>


// Initialises the game after being passed a word.
hangman::hangman(const std::string& input)
    : mistakes{0}
    , wordLength{input.size()}
    , word{input}
    , progress(input.size())
{
    // Set corresponding bool for 'spaces' to true as we
    // want /'s displayed in place of spaces throughout
    for (int i = 0; i < input.size(); ++i) {
        if (word[i] == ' ')
            progress[i] = true;
        else
            progress[i] = false;
    }
}


// Checks if game is over (e.g. no more guesses or word has been correctly guessed).
bool hangman::IsOver()
{
    if (TooManyGuesses()) {
        printf("\nUh, oh!  Too many guesses...  The word/phrase was: %s.\n\n", word);
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


// Updates the fields in the hangman class.
/*
The parameter 'guess' should be lower case before calling this, this results in
only lower case letters being stored in 'guesses' which keeps the logic simpler
*/
void hangman::UpdateProgress(const char guess)
{
    guesses.push_back(guess);

    bool present = false;

    // Check for both upper and lower case
    // letters in case they were used in text file
    for (int i = 0; i < wordLength; ++i)
        if ((guess == word[i]) || (toupper(guess) == word[i]))
        {
            progress[i] = true;
            present = true;
        }

    if (present)
        std::cout << "Good guess.";
    else {
        ++mistakes;
        std::cout << "Sorry, not there.";
    }
}


// Prints the gallows, progress and guesses.
/*
This is pretty tedious...probably a smarter way.
*/
void hangman::PrintProgress()
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
    for (int i = 0; i < wordLength; i++)
    {
        if (progress[i]) {
            if(word[i] == ' ')
                std::cout << '/';   //Replace spaces with /'s
            else
                std::cout << word[i];
        }
        else
            std::cout << '_';

        if (i == wordLength - 1)
            std::cout << "\n";
        else
            std::cout << ' ';
    }

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

    // Print out the previous guesses from the user to remind them
    if (!guesses.empty())
        for (int i = 0; i < guesses.size(); i++)
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

    std::cout << "\t-------------\n";
}


//Checks if the word has been fully revealed.
bool hangman::WordRevealed()
{
    for (int i = 0; i < wordLength; ++i)
        if (!progress[i])
            return false;

    return true;
}


// Returns true if the player has made 6 guesses.
bool hangman::TooManyGuesses()
{
    return (mistakes == 6);
}


//Handles errors from the user when inputting a guess.
/*
guess becomes lower case after this function has run.
*/
bool hangman::ValidGuess(char& guess)
{
    // Make sure input is a letter
    if (!isalpha(guess)) {
        std::cout << "That's not a letter!\n";
        return false;
    }

    if (isupper(guess))
        guess = tolower(guess); // guess is now lower case from this point on

    //Makes sure the letter hasn't already been guessed
    if (HasBeenGuessed(guess)) {
        std::cout << "You've already guessed that letter.\n";
        return false;
    }

    return true;
}


// Returns true if a letter has already been guessed.
bool hangman::HasBeenGuessed(const char& guess)
{
    if (guesses.size() == 0)
        return false;

    const int stop = guesses.size();
    for (int i = 0; i < stop; ++i)
        if (guess == guesses[i])
            return true;

    return false;
}
