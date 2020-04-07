#pragma once
#include <windows.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>

constexpr int WIDTH = 400;
constexpr int HEIGHT = 300;

//void readFile(std::string& selectedWord, std::string& guessWord);

struct HangmanDisplay : public Fl_Widget {
    HangmanDisplay(int x, int y, int w, int h) : Fl_Widget(x, y, w, h), x(x), y(y), w(w), h(h) {}
    void draw();

    int counter = 0;
private:
    int x, y, w, h;

};

struct Interface {
    Interface();
    void run();
    void reset();
private:
    std::string selectedWord, guessWord;
    HangmanDisplay* display;
    Fl_Window* window;
    Fl_Box* box;
    Fl_Input* input;
    Fl_Return_Button* button;

    static void static_button_CB(Fl_Widget* w, void* data);
    void real_button_CB(Fl_Widget* w);
    int check(const std::string& input);
    //void win();
    //void lose();
};

struct GameOver : public Fl_Window {
    GameOver(int w, int h, const char* t, Interface* inter);
private:
    Fl_Window* wind;
    Fl_Button* ok;
    Fl_Button* reset;
    Interface* i;

    static void okbutton_CB(Fl_Widget* w, void* data);
    static void static_resetbutton_CB(Fl_Widget* w, void* data);
    void real_resetbutton_CB(Fl_Widget* w);
};