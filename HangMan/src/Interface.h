#include <iostream>
#include <string>
#include <vector>

#ifndef INTERFACE_H
#define INTERFACE_H

class Interface {
public:
    Interface();
    bool gameOver;
    std::string selectedWord;
    std::string guessWord;
    std::string* hangman = new std::string[3];
    ~Interface();
    void displayInterface();
    void updateInterface();
    void lose();
    void win();
    void check(const std::string& input);
    int getCounter();
    void incrementCounter();
private:
    int counter;
    std::vector<char> guessed_letters;
};

#endif