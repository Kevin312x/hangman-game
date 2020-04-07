#include "Interface.h"

void HangmanDisplay::draw() {
    fl_line_style(0, 3);
    fl_line(x + (WIDTH * 1 / 4), y + (HEIGHT * 2 / 3), x + (WIDTH * 1 / 4) + 200, y + (HEIGHT * 2 / 3));
    fl_line(x + (WIDTH * 1 / 4) + 150, y + (HEIGHT * 2 / 3), x + (WIDTH * 1 / 4) + 150, y + (HEIGHT * 2 / 3) - 150);
    fl_line(x + (WIDTH * 1 / 4) + 150, y + (HEIGHT * 2 / 3) - 150, x + (WIDTH * 1 / 4) + 100, y + (HEIGHT * 2 / 3) - 150);
    fl_line(x + (WIDTH * 1 / 4) + 100, y + (HEIGHT * 2 / 3) - 150, x + (WIDTH * 1 / 4) + 100, y + (HEIGHT * 2 / 3) - 120);

    if (counter >= 1) {
        // Head
        fl_circle(x + (WIDTH * 1 / 4) + 100, y + (HEIGHT * 2 / 3) - 115, 5);
    }

    if (counter >= 2) {
        // Body
        fl_line(x + (WIDTH * 1 / 4) + 100, y + (HEIGHT * 2 / 3) - 110, x + (WIDTH * 1 / 4) + 100, y + (HEIGHT * 2 / 3) - 90);
    }

    if (counter >= 3) {
        // Left arm
        fl_line(x + (WIDTH * 1 / 4) + 100, y + (HEIGHT * 2 / 3) - 110, x + (WIDTH * 1 / 4) + 90, y + (HEIGHT * 2 / 3) - 100);
    }

    if (counter >= 4) {
        // Right arm
        fl_line(x + (WIDTH * 1 / 4) + 100, y + (HEIGHT * 2 / 3) - 110, x + (WIDTH * 1 / 4) + 110, y + (HEIGHT * 2 / 3) - 100);
    }

    if (counter >= 5) {
        // Left leg
        fl_line(x + (WIDTH * 1 / 4) + 100, y + (HEIGHT * 2 / 3) - 90, x + (WIDTH * 1 / 4) + 90, y + (HEIGHT * 2 / 3) - 80);
    }

    if (counter >= 6) {
        // Right leg
        fl_line(x + (WIDTH * 1 / 4) + 100, y + (HEIGHT * 2 / 3) - 90, x + (WIDTH * 1 / 4) + 110, y + (HEIGHT * 2 / 3) - 80);
    }

}
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
                for (int i = 0; i < selectedWord.length(); i++) {
                    guessWord += '_';
                }
                std::cout << selectedWord << '\n' << guessWord << '\n';
                file.close();
            }
        }
    }
}

Interface::Interface() {
    readFile(selectedWord, guessWord);
    display = new HangmanDisplay(0, 0, WIDTH, HEIGHT);
    window = new Fl_Window(WIDTH, HEIGHT, "HangMan");
    box = new Fl_Box(0, 0, WIDTH, 35, guessWord.c_str());
    box->box(FL_UP_BOX);
    input = new Fl_Input(100, 250, 200, 30);
    button = new Fl_Button(310, 250, 50, 30, "Enter");
    button->callback(static_button_CB, this);
    window->add(display);
}

void Interface::run() {
    window->show();
    Fl::run();
}

void Interface::reset() {
    display->counter = 0;
    readFile(selectedWord, guessWord);
    display->redraw();
}

// Returns -1 if there is no input or input was guessed previously
// Returns 0 if selected word does not contain input
// Returns 1 if selected word contains input
// Returns 2 if selected word is input
int Interface::check(const std::string& input) {
    int ret_val = 0;

    if (input.size() == 0)
        ret_val = -1;
    else if (input.size() > 1) {
        if (selectedWord == input) {
            guessWord = selectedWord;
            ret_val = 2;
        }
    }
    else {
        for (int i = 0; i < selectedWord.length(); ++i) {
            if (selectedWord[i] == input[0]) {
                guessWord[i] = input[0];
                ret_val = 1;
            }
        }
    }

    return ret_val;
}

void Interface::static_button_CB(Fl_Widget* w, void* data) {
    ((Interface*)data)->real_button_CB(w);
}

void Interface::real_button_CB(Fl_Widget* w) {
    std::string guess = input->value();
    int val = check(guess);
    input->value("");

    if (val == -1) {
        return;
    }
    if (val == 0) {
        display->counter += 1;
        display->redraw();
    }
    if (val >= 1) {
        box->label(guessWord.c_str());
    }

    if (selectedWord == guessWord) {
        //win
        GameOver win(200, 200, "win", this);
    }
    else if (display->counter >= 6) {
        //lose
        GameOver lose(200, 200, "lose", this);
    }
}

GameOver::GameOver(int w, int h, const char* t, Interface* inter) : Fl_Window(w, h, t) {
    i = inter;
    wind = new Fl_Window(w, h, t);
    ok = new Fl_Button(40, 150, 50, 25, "OK");
    ok->callback(okbutton_CB);
    //reset = new Fl_Button(100, 150, 50, 25, "Reset");
    //reset->callback(static_resetbutton_CB, this);
    wind->show();
}

void GameOver::okbutton_CB(Fl_Widget* w, void* data) {
    exit(0);
}

void GameOver::static_resetbutton_CB(Fl_Widget* w, void* data) {
    ((GameOver*)data)->real_resetbutton_CB(w);
}

void GameOver::real_resetbutton_CB(Fl_Widget* w) {
    i->reset();
    wind->end();
}