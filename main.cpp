#include "hangman.h"

#include <iostream>
#include <fstream>
#include <ctime>

bool get_words(vector<string>& words);//Gets words/phrases from text file, returns true if completed successfully
bool play_again();//Prompts the user if they would like to play again, returns true if users specifies yes

int main()
{
    cout << "Welcome to hangman!" << endl << endl;

    vector<string> words;//Vector to store words from text file

    if(!get_words(words)){return 0;}//If reading words was not possible it exits the program early

    srand(time(NULL));

    bool quit = false;//Variable to determine if game loops or not

    while(!quit)//Main game loop
    {
        int selection = rand()%words.size();

        hangman game(words[selection]);//Initialises game with random word

        game.PrintProgress();

        while(1)//Loop to receive and check guesses after game is initialised
        {
            char guess;

            game.GetGuess(guess);

            game.UpdateProgress(guess);

            cout << endl << endl;

            game.PrintProgress();

            if(game.IsOver())
            {
                if(!play_again()){quit = true;}//If user does not want to play again, main loop is exited
                break;
            }
        }
    }

    cout << endl << "Thanks for playing!!!" << endl << endl;

    return 0;
}

bool get_words(vector<string>& words)
{
    ifstream ifile("words.txt");

    if(!ifile.is_open())
    {
        cout << "Could not open file -> Exiting..." << endl;
        return false;
    }

    string current;

    while(getline(ifile, current)){words.push_back(current);}//Uses getline so that phrases can be used in the game

    if(words.size() == 0)//If there are no string in words at this point then something went wrong
    {
        cout << "Unable to read anything -> Exiting..." << endl;
        return false;
    }

    if(!ifile.eof())//If not at the end of the file there was an error
    {
        cout << "Bad read -> Exiting..." << endl;
        return false;
    }

    return true;
}

bool play_again()
{
    char choice;

    while(1)
    {
        cout << "Play again? -> (Y/N): ";
        cin >> choice;

        if(choice == 'N' || choice == 'n'){return false;}
        else if(choice == 'Y' || choice == 'y'){return true;}
        else{cout << "Invalid choice  .";}
    }
}
