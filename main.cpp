#include "hangman.h"

#include <fstream>
#include <string>
#include <ctime>

bool PlayAgain();
bool LoadWords(std::vector<std::string>& words);


int main()
{
    std::vector<std::string> words;
    if (!LoadWords(words))
        return -1;

    srand((unsigned)time(nullptr));

    std::cout << "Welcome to hangman!\n\n";

    bool quit = false;
    while (!quit)
    {
        const int selection = rand() % words.size();
        hangman game{words[selection]};

        game.PrintProgress();

        while (true)    // Main game loop
        {
            char guess;
            game.GetGuess(guess);
            game.UpdateProgress(guess);

            std::cout << "\n\n";
            game.PrintProgress();

            if (game.IsOver()) {
                if (!PlayAgain())
                    quit = true;
                break;
            }
        }
    }

    std::cout << "\nThanks for playing!!!\n\n";

    return 0;
}


// Checks if the user wants to play again.
bool PlayAgain()
{
    char choice;
    while (true)
    {
        std::cout << "Play again? -> (Y/N): ";
        std::cin >> choice;

        if ((choice == 'N') || (choice == 'n'))
            return false;
        else if ((choice == 'Y') || (choice == 'y'))
            return true;
        else
            std::cout << "Invalid choice.  ";
    }
}


// Loads all words/phrases from associated "words.txt" file.
/*
The file format for "words.txt" is simply one line per word/phrase.
*/
bool LoadWords(std::vector<std::string>& words)
{
    std::ifstream ifile("words.txt");

    if (!ifile.is_open()) {
        std::cout << "Could not open file -> Exiting...\n";
        return false;
    }

    std::string current;

    while (getline(ifile, current)) // Each line holds different word/phrase
        words.push_back(current);

    if (words.size() == 0) {
        std::cout << "Unable to read anything -> Exiting...\n";
        return false;
    }

    if (!ifile.eof()) {
        std::cout << "Bad read -> Exiting...\n";
        return false;
    }

    return true;
}
