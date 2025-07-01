#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cctype>
using namespace std;
// Base class 
class Game {
protected:
    string wordToGuess;
    string guessedWord;
    int maxAttempts;
    int attempts;

public:
    Game(const string &word, int max_attempts = 6)
        : wordToGuess(word), maxAttempts(max_attempts), attempts(0) {
        guessedWord = string(wordToGuess.size(), '_');  // Initialize with underscores
    }

    virtual void startGame() = 0;
    virtual void playTurn(char guess) = 0;
    virtual bool isGameOver() const = 0;
    virtual void displayStatus() const = 0;

    int getMaxAttempts() const { return maxAttempts; }
    int getAttempts() const { return attempts; }
};

// Derived class for Hangman game
class HangmanGame : public Game {
private:
    vector<char> guessedLetters;

    // Draws the hangman figure based on the number of wrong attempts
    void drawHangman() const {
        vector<string> hangmanStages = {
            "   +---+\n"
            "   |   |\n"
            "       |\n"
            "       |\n"
            "       |\n"
            "       |\n"
            "=========\n",
            
            "   +---+\n"
            "   |   |\n"
            "   O   |\n"
            "       |\n"
            "       |\n"
            "       |\n"
            "=========\n",

            "   +---+\n"
            "   |   |\n"
            "   O   |\n"
            "   |   |\n"
            "       |\n"
            "       |\n"
            "=========\n",

            "   +---+\n"
            "   |   |\n"
            "   O   |\n"
            "  /|   |\n"
            "       |\n"
            "       |\n"
            "=========\n",

            "   +---+\n"
            "   |   |\n"
            "   O   |\n"
            "  /|\\  |\n"
            "       |\n"
            "       |\n"
            "=========\n",

            "   +---+\n"
            "   |   |\n"
            "   O   |\n"
            "  /|\\  |\n"
            "  /    |\n"
            "       |\n"
            "=========\n",

            "   +---+\n"
            "   |   |\n"
            "   O   |\n"
            "  /|\\  |\n"
            "  / \\  |\n"
            "       |\n"
            "=========\n"
        };

        cout << hangmanStages[attempts] << endl;
    }

public:
    HangmanGame(const string &word) : Game(word) {}

    // Start the game
    void startGame() override {
        cout << "Welcome to Hangman!" << endl;
        cout << "You have " << maxAttempts << " attempts to guess the word." << endl;
        cout << "The word has " << wordToGuess.size() << " letters." << endl;  // Show word length
        displayStatus();
    }

    // Play a turn in the hangman game
    void playTurn(char guess) override {
        guess = tolower(guess);

        // Validate the guess
        if (!isalpha(guess)) {
           cout << "Invalid input! Please enter an alphabet letter." << endl;
            return;
        }

        // Check if letter was already guessed
        if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            cout << "You've already guessed the letter '" << guess << "'." << endl;
            return;
        }

        // Add the letter to guessed letters
        guessedLetters.push_back(guess);
        bool correctGuess = false;

        // Check if the guess is correct
        for (size_t i = 0; i < wordToGuess.size(); ++i) {
            if (wordToGuess[i] == guess) {
                guessedWord[i] = guess;
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            attempts++;
            cout << "Incorrect guess. You have " << (maxAttempts - attempts) << " attempts remaining." << endl;
        } else {
            cout << "Good guess!" << endl;
        }

        drawHangman();  // Draw the current hangman state after each guess
        displayStatus();
    }

    // Check if the game is over
    bool isGameOver() const override {
        if (guessedWord == wordToGuess) {
            cout << "Congratulations! You've guessed the word: " << wordToGuess << endl;
            return true;
        } else if (attempts >= maxAttempts) {
            cout << "Game Over! You've run out of attempts. The word was: " << wordToGuess << endl;
            return true;
        }
        return false;
    }

    // Display the current game status
    void displayStatus() const override {
        cout << "Word to guess: " << guessedWord << endl;
        cout << "Guessed letters: ";
        for (char letter : guessedLetters) {
            cout << letter << ' ';
        }
        cout << endl;
    }
};

// Main function to drive the Hangman game
int main() {
    // Initialize random seed for word selection
    srand(static_cast<unsigned>(time(0)));
    vector<string> wordList = {"encapsulation", "inheritance", "polymorphism", "abstraction", "stand", "run", "walk", "computer"};
    string selectedWord = wordList[rand() % wordList.size()];

    // Initialize the game
    HangmanGame game(selectedWord);
    game.startGame();

    // Game loop
    while (!game.isGameOver()) {
        char guess;
        cout << "Enter a letter to guess: ";
        cin >> guess;

        game.playTurn(guess);
    }

    return 0;
}
