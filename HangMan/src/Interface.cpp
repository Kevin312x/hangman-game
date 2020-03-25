#include <iostream>
#include <string>
#include "Interface.h"

using std::cout;
using std::cin;
using std::endl;

Interface::Interface() : gameOver(false), counter(0) {
    //These three lines are where the body appears
    hangman[0] = "|                     |   |";
    hangman[1] = "|                     |   |";
    hangman[2] = "|                     |   |";
}

Interface::~Interface() {}

void Interface::displayInterface() {
    //To display the interface
    cout << "+-------------------------+" << endl;
    cout << "|        Hang Man         |" << endl;
    cout << "+-------------------------+" << endl;
    cout << "|            +--------+   |" << endl;
    cout << "|            |        |   |" << endl;
    cout << "|            |        |   |" << endl;
    for (int i = 0; i < 3; i++) {
        cout << hangman[i] << endl;
    }
    cout << "|                     |   |" << endl;
    cout << "|                     |   |" << endl;
    cout << "|---------------------+---|" << endl;
    cout << "|                         |" << endl;
    cout << "+-------------------------+" << endl;
    cout << "|";

    //Prints out the letters guessed and fills the line with whitespaces
    for (char c : guessWord) cout << c;
    for (int i = 0; i < hangman[0].length() - guessWord.length() - 2; i++) cout << " ";
    cout << "|" << endl;
}

void Interface::updateInterface() {
    //Swaps the array with body parts to display on interface
    switch (counter) {
    case 1:
        hangman[0][13] = 'O';
        break;
    case 2:
        hangman[1][13] = '|';
        break;
    case 3:
        hangman[1][12] = '/';
        break;
    case 4:
        hangman[1][14] = '\\';
        break;
    case 5:
        hangman[2][12] = '/';
        break;
    case 6:
        hangman[2][14] = '\\';
        lose();
        break;
    }
}

void Interface::lose() {
    //To be printed if player loses
    cout << "The answer was: " << selectedWord << endl;
    cout << "You Lose!" << endl;
    gameOver = true;
}

void Interface::win() {
    //To be printed if player wins
    cout << "You Win!" << endl;
    gameOver = true;
}

/*
Checks if user input, if it is a character, matches any
of the characters of the selected word.
If it isn't a character, the it matches the selected word itself.
*/
void Interface::check(const std::string& input) {
    bool containsLetter = false;
    bool equal = true;
    if (input.size() == 0) {
        return;
    } else if (input.size() < 2) {
        if (std::find(guessed_letters.begin(), guessed_letters.end(), input[0]) != guessed_letters.end()) {
            return;
        }
        guessed_letters.push_back(input[0]);
        for (int i = 0; i < selectedWord.length(); i++) {
            
            if (selectedWord[i] == input[0]) {
                guessWord[i] = input[0];
                containsLetter = true;
            }
        }
        if (containsLetter) {
            if (guessWord.find('_') == std::string::npos) {
                win();
            }
        } else {
            incrementCounter();
            updateInterface();
        }
    } else {
        if (input == selectedWord) {
            win();
        } else {
            incrementCounter();
            updateInterface();
        }
    }
}

int Interface::getCounter() {
    return counter;
}

void Interface::incrementCounter() {
    counter += 1;
}