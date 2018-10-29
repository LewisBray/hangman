#include "hangman.h"

#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <string>

static bool askUserToPlayAgain()
{
    while (true)
    {
        std::cout << "Play again? -> (Y/N): ";

        char choice;
        std::cin >> choice;

        if (choice == 'N' || choice == 'n')
            return false;
        else if ((choice == 'Y') || (choice == 'y'))
            return true;
        else
            std::cout << "Invalid choice.  ";
    }
}

// File format described in readme file in repository
static std::vector<std::string> loadWordsFromFile(const std::string& file)
{
    std::ifstream ifile(file);

    if (!ifile.is_open()) {
        std::cout << "Could not open file -> Exiting..." << std::endl;
        return std::vector<std::string>{};
    }

    std::vector<std::string> words;

    std::string current;
    while (std::getline(ifile, current))
        words.push_back(current);

    if (words.size() == 0) {
        std::cout << "Unable to read anything -> Exiting..." << std::endl;
        return std::vector<std::string>{};
    }

    if (!ifile.eof()) {
        std::cout << "Bad read -> Exiting..." << std::endl;
        return std::vector<std::string>{};
    }

    return words;
}

int main()
{
    const std::vector<std::string> words = loadWordsFromFile("words.txt");
    if (words.empty())
        return -1;

    const int lastWordIndex = words.size() - 1;
    std::uniform_int_distribution<int> uniformDist{ 0, lastWordIndex };
    std::minstd_rand rng;

    std::cout << "Welcome to hangman!\n" << std::endl;

    bool quit = false;
    do
    {
        const auto currentTime = std::chrono::system_clock::now();
        const unsigned rngSeed =
            static_cast<unsigned>(currentTime.time_since_epoch().count());
        rng.seed(rngSeed);

        Hangman game{ words[uniformDist(rng)] };

        std::cout << game << std::endl;

        while (!game.isOver())
        {
            const char guess = game.askUserForGuess();
            game.updateProgress(guess);

            std::cout << "\n\n" << game << std::flush;
        }
    } while (askUserToPlayAgain());

    std::cout << "\nThanks for playing!!!\n" << std::endl;

    return 0;
}
