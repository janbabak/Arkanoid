/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 02.06.20
*/

#pragma once

//constants of colors of ansi sequences for coloring terminal text
static const char * BRIGHT_RED = "\u001b[31;1m";
static const char * BRIGHT_GREEN = "\u001b[32;1m";
static const char * BRIGHT_YELLOW = "\u001b[33;1m";
static const char * BRIGHT_BLUE = "\u001b[34;1m";
static const char * BRIGHT_MAGENTA = "\u001b[35;1m";
static const char * BRIGHT_CYAN = "\u001b[36;1m";
static const char * DEFAULT_COLOR = "\u001b[0m";

//constant are unused in this file - need to ged rid of unused constant warnings
struct bar {
    void foo () {
        if ( bool a = false ) {
            std::cout << BRIGHT_RED;
            std::cout << BRIGHT_GREEN;
            std::cout << BRIGHT_YELLOW;
            std::cout << BRIGHT_BLUE;
            std::cout << BRIGHT_MAGENTA;
            std::cout << BRIGHT_CYAN;
            std::cout << DEFAULT_COLOR;
            a = true;
        }
    }
};
