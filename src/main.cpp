#include "CApplication.h"
#include <iostream>
#include <csignal>

CApplication app;  //global variable because of signal catching

/**
 * call destructors when user press ctrl+c
 * @source http://vyuka.bernhauer.cz/pa2-clanky/semestralni-prace */
void signalHandler ( int ) {
    exit( 0 );  //call destructor on all "live" objects
}

int main() {
    signal( SIGTERM, signalHandler );
    signal( SIGINT, signalHandler );
    return app.Run();
}
