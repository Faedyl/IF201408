#ifndef MENULOKAL_H
#define MENULOKAL_H

#include <iostream>
#include <vector>
#include <string>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

class Menu {
private:
    std::vector<std::string> options;
    int selected_option;

    #ifndef _WIN32
    static struct termios old_tio, new_tio;
    static void init_termios() {
        tcgetattr(STDIN_FILENO, &old_tio);
        new_tio = old_tio;
        new_tio.c_lflag &= (~ICANON & ~ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    }
    static void reset_termios() {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    }
    static char getch() {
        char ch;
        read(STDIN_FILENO, &ch, 1);
        return ch;
    }
    #endif

public:
    Menu(const std::vector<std::string>& opts) : options(opts), selected_option(0) {
        #ifndef _WIN32
        init_termios();
        #endif
    }

    ~Menu() {
        #ifndef _WIN32
        reset_termios();
        #endif
    }

    void display() {
        system(
        #ifdef _WIN32
            "cls"
        #else
            "clear"
        #endif
        );
        std::cout << std::string(40,'=') << "\nSORTING SELECTION | KELOMPOK 3 |\n" << std::string(40,'=') << "\n";
        for (size_t i = 0; i < options.size(); ++i) {
            if (i == static_cast<size_t>(selected_option)) {
                std::cout << "> ";
            } else {
                std::cout << "  ";
            }
            std::cout << i+1 << ". " << options[i] << std::endl;
        }
        std::cout << std::string(40,'=') << "\nUse Arrow Key to Select!\n";
    }

    int run() {
        while (true) {
            display();
            #ifdef _WIN32
            int ch = _getch();
            if (ch == 224) { // Arrow key pressed
                ch = _getch();
                switch (ch) {
                    case 72: // Up arrow
                        selected_option = (selected_option - 1 + options.size()) % options.size();
                        break;
                    case 80: // Down arrow
                        selected_option = (selected_option + 1) % options.size();
                        break;
                }
            } else if (ch == 13) { // Enter key
                return selected_option;
            }
            #else
            char ch = getch();
            if (ch == 27 && getch() == 91) { // Arrow key pressed
                switch (getch()) {
                    case 65: // Up arrow
                        selected_option = (selected_option - 1 + options.size()) % options.size();
                        break;
                    case 66: // Down arrow
                        selected_option = (selected_option + 1) % options.size();
                        break;
                }
            } else if (ch == 10) { // Enter key
                return selected_option;
            }
            #endif
        }
    }

    // New method to reset terminal for normal input
    void reset_for_input() {
        #ifndef _WIN32
        reset_termios();
        #endif
    }

    // New method to reinitialize terminal for menu navigation
    void init_for_menu() {
        #ifndef _WIN32
        init_termios();
        #endif
    }
};

#ifndef _WIN32
struct termios Menu::old_tio, Menu::new_tio;
#endif

#endif // MENULOKAL_H