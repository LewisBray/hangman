#include <iostream>
#include <cstring>
#include <vector>

#include "hangman.h"

hangman::hangman(const string& input) : mistakes(0), word_length(input.size()), word(input), progress(input.size())
//Constructor which sets up the game after being given a word (called 'input' in declaration)
{
    for(int i = 0; i < input.size(); i++)//Sets all progress elements to false since no letters have been guessed
    {
        if(word[i] == ' '){progress[i] = true;}//Sets spaces to true since we want /'s to be displayed in place of spaces
        else{progress[i] = false;}
    }
}

bool hangman::check_if_over()
//Checks if the game is finished, e.g. no more guesses or word has been correctly guessed
{
    if(check_if_failed())
    {
        cout << endl << "Uh, oh!  Too many guesses...  The word/phrase was: " << word << "." << endl << endl;

        return true;
    }

    if(check_if_complete())
    {
        cout << endl << "Well done, you got it!" << endl << endl;

        return true;
    }

    return false;
}

void hangman::get_input(char& guess)
//Prompts the user to guess a letter and makes sure it is valid before moving on
{
    while(1)
    {
        cout << endl << "Guess: ";
        cin >> guess;

        if(check_if_valid(guess)){break;}
    }
}

void hangman::update_game(const char& guess)
//Updates the fields in the hangman class, in game 'guess' is lower-case by this point
{
    guesses.push_back(guess);//Only put lower-case letters into 'guesses' to keep logic simpler

    bool present = false;
    char other = toupper(guess);

    for(int i = 0; i < word_length; i++)
    {
        if(guess == word[i] || other == word[i])//check for both upper and lower case letters in case they were used in text file
        {
            progress[i] = true;

            present = true;
        }
    }

    if(present){cout << "Good guess.";}
    else
    {
        mistakes++;

        cout << "Sorry, not there.";
    }
}

void hangman::print_progress()
//Prints the gallows, progress and guesses
{
    cout << "\t     .-----. " << endl;
    cout << "\t     |     | " << endl;

    if(mistakes >= 1)//The output could be handled differently but it made the code difficult to read and there probably
    {                //wasn't a noticeable time difference in this application
        cout << "\t     _     | " << endl;
        cout << "\t    | |    | " << endl;
        cout << "\t     T     | ";
    }
    else
    {
        cout << "\t           | " << endl;
        cout << "\t           | " << endl;
        cout << "\t           | ";
    }

    cout << "\t\t";

    for(int i = 0; i < word_length; i++)//Prints the current progress towards guessing 'word'
    {
        if(progress[i])
        {
            if(word[i] == ' '){cout << '/';}//Replace spaces with /'s
            else{cout << word[i];}
        }
        else{cout << '_';}

        if(i == word_length - 1){cout << endl;}
        else{cout << ' ';}
    }

    if(mistakes == 2){cout << "\t     +     | ";}
    else if(mistakes == 3){cout << "\t   --+     | ";}
    else if(mistakes >= 4){cout << "\t   --+--   | ";}
    else{cout << "\t           | ";}

    cout << endl;

    if(mistakes >= 2)
    {
        cout << "\t     |     | " << endl;
        cout << "\t     |     | " << endl;
        cout << "\t     |     | ";
    }
    else
    {
        cout << "\t           | " << endl;
        cout << "\t           | " << endl;
        cout << "\t           | ";
    }

    cout << "\t   ";

    cout << "Guesses: ";

    if(guesses.size() != 0)//Prints out the previous guesses from the user to remind them
    {
        for(int i = 0; i < guesses.size(); i++)
        {
            if(i == 0){cout << guesses[i];}
            else{cout << ", " << guesses[i];}
        }
    }

    cout << endl;

    if(mistakes == 5)
    {
        cout << "\t    /      | " << endl;
        cout << "\t   /       | " << endl;
        cout << "\t           | " << endl;
    }
    else if(mistakes >= 5)
    {
        cout << "\t    / \\    | " << endl;
        cout << "\t   /   \\   | " << endl;
        cout << "\t           | " << endl;
    }
    else
    {
        cout << "\t           | " << endl;
        cout << "\t           | " << endl;
        cout << "\t           | " << endl;
    }

    cout << "\t-------------" << endl;
}

bool hangman::check_if_complete()
//Checks to see if 'word' has been fully revealed <=> all elements of 'progress' vector are true
{
    bool a = true;

    for(int i = 0; i < word_length; i++){if(!progress[i]){a = false;}}

    return a;
}

bool hangman::check_if_failed()
//If the player has made 6 mistakes this returns true to end the game
{
    if(mistakes == 6){return true;}
    else{return false;}
}

bool hangman::check_if_valid(char& guess)
//Handles errors from the user when inputting a guess, 'guess' becomes lower case after this function has run
{
    if(!isalpha(guess))//Handles if user enters something that isn't a letter (upper or lower case)
    {
        cout << "That's not a letter!" << endl;

        return false;
    }

    if(isupper(guess)){guess = tolower(guess);}//'guess' is now definitely lower case from this point on

    if(has_been_guessed(guess))//Makes sure the letter hasn't already been guessed
    {
        cout << "You've already guessed that letter." << endl;

        return false;
    }

    return true;
}

bool hangman::has_been_guessed(const char& guess)
//Goes through 'guesses' and makes sure that 'guess' is not present
{
    if(guesses.size() == 0){return false;}

    int last = guesses.size();
    bool present = false;

    for(int i = 0; i < last; i++)
    {
        if(guess == guesses[i])
        {
            present = true;

            break;
        }
    }

    return present;
}
