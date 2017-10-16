using namespace std;

class hangman//Class defined to handle the game logic once a word has been chosen
{
    public:
        hangman(const string& input);

        bool check_if_over();
        void get_input(char& guess);
        void update_game(const char& guess);
        void print_progress();

    private:
        int mistakes;//Number of mistakes the player has made, you can have 6 mistakes in this game
        int word_length;//Length of word to be guessed, defined for small optimisation
        string word;//Stores the word to be guessed
        vector<char> guesses;//Vector that stores all guesses from the player to make sure they don't pick the same letter twice
        vector<bool> progress;//Array of bool values set to the length of 'word', when a letter is correctly guessed, say word[3],
                              //then bool[3] is set to true
        bool check_if_complete();
        bool check_if_failed();
        bool check_if_valid(char& guess);
        bool has_been_guessed(const char& guess);
};
