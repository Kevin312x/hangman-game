#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "Interface.h"

using std::cout;
using std::cin;
using std::endl;
/*
+-------------------------+
|        Hang Man         |
+-------------------------+
|            +――――――――+   |
|            |        |   |
|            |        |   |
|            O        |   |
|           /|\       |   |
|           / \       |   |
|                     |   |
|                     |   |
|―――――――――――――――――――――+―――|
|                         |
+-------------------------+
*/

void readFile(std::string& selectedWord, std::string& guessWord);
void playGame(Interface interface);
void init();
std::string getInput();

int main() {
    init();
    return 0;
}

void init() {
    Interface interface;
    readFile(interface.selectedWord, interface.guessWord);
    playGame(interface);
}

// Reads from a file containing a list of words and picks one at random
void readFile(std::string& selectedWord, std::string& guessWord) {
    std::ifstream file;
    std::string line;
    int random = 0;
    int lineNum = 0;
    file.open("wordlist.txt");

    srand(time(0));
    random = (rand() % 212) + 1;

    if (file.is_open()) {
        while (getline(file, line)) {
            lineNum++;
            if (lineNum == random) {
                selectedWord = line;
                selectedWord.pop_back();
                for (int i = 0; i < selectedWord.length(); i++) {
                    guessWord += '_';
                }

                file.close();
            }
        }
    }
}

// If not game over, will repeatedly clear screen, display interface, and prompt and check user input
void playGame(Interface interface) {
    while (!(interface.gameOver)) {
        cout << std::string(20, '\n');
        interface.displayInterface();
        interface.check(getInput());
    }
}

// Retrieves user input
std::string getInput() {
    std::string userInput;
    std::cout << "Please input a letter: ";
    getline(cin, userInput);
    return userInput;
}