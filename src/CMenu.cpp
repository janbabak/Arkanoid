/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 19.05.20
*/

#include "CMenu.h"

EReturnVal CMenu::KeyboardReactionInMenu() {
    char userInput;
    std::cin >> std::noskipws >> userInput;
    switch ( userInput ) {
        case '8':
        case 'w':
            return EReturnVal::UP;
        case '2':
        case 's':
            return EReturnVal::DOWN;
        case '\n':
        case '5' :
            return EReturnVal::ENTER;
        default:
            return EReturnVal::NOT_INTERESTED;
    }
}

EReturnVal CMenu::MainMenu( CBufferSwitch & buffer, bool showWarning, const char * warning ) {
    int position = 0;
    buffer.TurnOff();
    while ( true ) {
        if ( position > 2 )
            position = 0;
        if ( position < 0 )
            position = 2;
        std::system( "clear" );  //clear the screen
        PrintMainMenu( position );
        if ( showWarning )  //show warning
            std::cout << warning << std::endl;
        if ( TKeyboardDetector::KeyboardPressed() ) {
            EReturnVal tmp = KeyboardReactionInMenu();
            if ( tmp == EReturnVal::DOWN )
                position++;
            else if ( tmp == EReturnVal::UP )
                position--;
            else if ( tmp == EReturnVal::ENTER ) { // enter
                if ( position == 0 ) {
                    return EReturnVal::QUIT;
                } else if ( position == 1 ) {
                    return EReturnVal::MAP_FROM_FILE;
                } else {
                    return EReturnVal::RANDOM_MAP;
                }
            }
        }
        std::this_thread::sleep_for( 100ms );  //sleep
    }
}

std::ostream & CMenu::PrintMainMenu( int position, std::ostream & os ) {
    //first line of boarder
    for ( std::size_t i = 0; i < 33; ++i )
        os << '#';
    os << std::endl;

    //name of game
    os << "#" << BRIGHT_YELLOW << "  <<<<< A R K A N O I D >>>>>  " << DEFAULT_COLOR << "#" << std::endl;

    //empty line
    os << '#';
    for ( size_t j = 0; j < 31; ++j )
        os << ' ';
    os << '#' << std::endl;

    //quit option
    if ( position == 0 )
        os << "#            " << BRIGHT_RED << ">" << BRIGHT_BLUE << "Quit" << BRIGHT_RED << "<" << DEFAULT_COLOR << "             #"
           << std::endl;  //selected row in magenta
    else
        os << "#             Quit              #" << std::endl;

    //empty line
    os << '#';
    for ( size_t i = 0; i < 31; ++i )
        os << ' ';
    os << '#' << std::endl;

    //map from file option
    if ( position == 1 )
        os << "#        " << BRIGHT_RED << ">" << BRIGHT_BLUE << "Map from file" << BRIGHT_RED << "<" << DEFAULT_COLOR << "        #"
           << std::endl;  //selected row in magenta
    else
        os << "#         Map from file         #" << std::endl;

    //empty line
    os << '#';
    for ( size_t i = 0; i < 31; ++i )
        os << ' ';
    os << '#' << std::endl;

    //random map option
    if ( position == 2 )
        os << "#         " << BRIGHT_RED << ">" << BRIGHT_BLUE << "Random map" << BRIGHT_RED << "<" << DEFAULT_COLOR << "          #"
           << std::endl;  //selected row in magenta
    else
        os << "#          Random map           #" << std::endl;

    //2 empty lines
    for ( std::size_t i = 0; i < 2; ++i ) {
        os << '#';
        for ( size_t j = 0; j < 31; ++j )
            os << ' ';
        os << '#' << std::endl;
    }

    os << "#    \"2\" or \"s\" to move down    #" << std::endl;
    os << "#     \"8\" or \"w\" to move up     #" << std::endl;
    os << "#    \"enter\" or \"5\" to select   #" << std::endl;

    //last line of boarder
    for ( std::size_t i = 0; i < 33; ++i )
        os << '#';
    os << std::endl;
    return os;
}

EReturnVal CMenu::MapMenu() {
    int position = 0;
    while ( true ) {
        if ( position > 3 )
            position = 0;
        if ( position < 0 )
            position = 3;
        std::system( "clear" );  //clear the screen
        PrintMapMenu( position );
        if ( TKeyboardDetector::KeyboardPressed() ) {
            EReturnVal tmp = KeyboardReactionInMenu();
            if ( tmp == EReturnVal::DOWN )
                position++;
            else if ( tmp == EReturnVal::UP )
                position--;
            else if ( tmp == EReturnVal::ENTER ) { // enter
                if ( position == 0 ) {
                    return EReturnVal::MAP1;
                } else if ( position == 1 ) {
                    return EReturnVal::MAP2;
                } else if ( position == 2 ) {
                    return EReturnVal::MAP3;
                } else {
                    return EReturnVal::BACK;
                }
            }
        }
        std::this_thread::sleep_for( 100ms );  //sleep
    }
}

std::ostream & CMenu::PrintMapMenu( int position, std::ostream & os ) {
    //first line of boarder
    for ( std::size_t i = 0; i < 33; ++i )
        os << '#';
    os << std::endl;

    //empty line
    os << '#';
    for ( size_t i = 0; i < 31; ++i )
        os << ' ';
    os << '#' << std::endl;

    //map 1 option
    if ( position == 0 )
        os << "#            " << BRIGHT_RED << ">" << BRIGHT_BLUE << "Map 1" << BRIGHT_RED << "<" << DEFAULT_COLOR << "            #"
           << std::endl;  //selected row in magenta
    else
        os << "#             Map 1             #" << std::endl;

    //empty line
    os << '#';
    for ( size_t i = 0; i < 31; ++i )
        os << ' ';
    os << '#' << std::endl;

    //map 2 option
    if ( position == 1 )
        os << "#            " << BRIGHT_RED << ">" << BRIGHT_BLUE << "Map 2" << BRIGHT_RED << "<" << DEFAULT_COLOR << "            #"
           << std::endl;  //selected row in magenta
    else
        os << "#             Map 2             #" << std::endl;

    //empty line
    os << '#';
    for ( size_t i = 0; i < 31; ++i )
        os << ' ';
    os << '#' << std::endl;

    //map 3 option
    if ( position == 2 )
        os << "#            " << BRIGHT_RED << ">" << BRIGHT_BLUE << "Map 3" << BRIGHT_RED << "<" << DEFAULT_COLOR << "            #"
           << std::endl;  //selected row in magenta
    else
        os << "#             Map 3             #" << std::endl;

    //empty line
    os << '#';
    for ( size_t i = 0; i < 31; ++i )
        os << ' ';
    os << '#' << std::endl;

    //back option
    if ( position == 3 )
        os << "#            " << BRIGHT_RED << ">" << BRIGHT_BLUE << "Back" << BRIGHT_RED << "<" << DEFAULT_COLOR << "             #"
           << std::endl;  //selected row in magenta
    else
        os << "#             Back              #" << std::endl;

    //empty line
    os << '#';
    for ( size_t i = 0; i < 31; ++i )
        os << ' ';
    os << '#' << std::endl;

    os << "#    \"2\" or \"s\" to move down    #" << std::endl;
    os << "#     \"8\" or \"w\" to move up     #" << std::endl;
    os << "#    \"enter\" or \"5\" to select   #" << std::endl;

    //last line of boarder
    for ( std::size_t i = 0; i < 33; ++i )
        os << '#';
    os << std::endl;
    return os;
}

EReturnVal CMenu::finalScreenMenu( bool won, long long int score, long long int bestScore ) {
    int position = 0;
    while ( true ) {
        if ( position > 1 )
            position = 0;
        if ( position < 0 )
            position = 1;
        std::system( "clear" );  //clear the screen
        PrintFinalScreenMenu( won, position, score, bestScore );
        if ( TKeyboardDetector::KeyboardPressed() ) {
            EReturnVal tmp = KeyboardReactionInMenu();
            if ( tmp == EReturnVal::DOWN ) {
                position++;
            } else if ( tmp == EReturnVal::UP ) {
                position--;
            } else if ( tmp == EReturnVal::ENTER ) { // enter
                if ( position == 0 ) {
                    return EReturnVal::PLAY_AGAIN;
                } else {
                    return EReturnVal::MENU;
                }
            }
        }
        std::this_thread::sleep_for( 100ms );  //sleep
    }
}

std::ostream & CMenu::PrintFinalScreenMenu( bool won, int position, long long int score, long long int bestScore,
                                            std::ostream & os ) {
    std::size_t WIDTH = 33;

    //first line of border
    for ( std::size_t i = 0; i < 33; ++i )
        os << '#';
    os << std::endl;

    //empty line
    os << '#';
    for ( size_t i = 0; i < 31; ++i )
        os << ' ';
    os << '#' << std::endl;

    //VICTORY or GAME OVER label
    if ( won )
        os << "#            " << BRIGHT_GREEN << "VICTORY" << DEFAULT_COLOR << "            #" << std::endl;
    else
        os << "#           " << BRIGHT_RED << "GAME OVER" << DEFAULT_COLOR << "           #" << std::endl;

    //score
    os << '#';
    std::size_t i = 0;
    for ( ; i <
            ( WIDTH - std::to_string( score ).length() - 7 - 2 ) / 2; ++i )  //7 is length of "score: ", 2 for two '#'
        os << ' ';
    os << "score: " << score;
    for ( std::size_t j = 0; j < WIDTH - i - 7 - 2 - std::to_string( score ).length(); ++j )
        os << ' ';
    os << '#' << std::endl;

    //best score
    if ( score > bestScore )
        os << "#          " << BRIGHT_YELLOW << "(new best)" << DEFAULT_COLOR << "           #" << std::endl;
    else {
        os << '#';
        i = 0;
        for ( ; i < ( WIDTH - std::to_string( bestScore ).length() - 12 - 2 ) /
                    2; ++i )  //13 is length of "best score: ", 2 for two '#'
            os << ' ';
        os << "best score: " << bestScore;
        for ( std::size_t j = 0; j < WIDTH - i - 12 - 2 - std::to_string( bestScore ).length(); ++j )
            os << ' ';
        os << '#' << std::endl;
    }


    //empty line
    os << '#';
    for ( size_t i = 0; i < 31; ++i )
        os << ' ';
    os << '#' << std::endl;

    //play again
    if ( position == 0 )
        os << "#         " << BRIGHT_RED << ">" << BRIGHT_BLUE << "Play again" << BRIGHT_RED << "<" << DEFAULT_COLOR << "          #" << std::endl;
    else
        os << "#          Play again           #" << std::endl;

    //empty line
    os << '#';
    for ( size_t i = 0; i < 31; ++i )
        os << ' ';
    os << '#' << std::endl;

    //menu
    if ( position == 1 )
        os << "#            " << BRIGHT_RED << ">" << BRIGHT_BLUE << "Menu" << BRIGHT_RED << "<" << DEFAULT_COLOR << "             #" << std::endl;
    else
        os << "#             Menu              #" << std::endl;

    //empty line
    os << '#';
    for ( size_t i = 0; i < 31; ++i )
        os << ' ';
    os << '#' << std::endl;


    os << "#    \"2\" or \"s\" to move down    #" << std::endl;
    os << "#     \"8\" or \"w\" to move up     #" << std::endl;
    os << "#    \"enter\" or \"5\" to select   #" << std::endl;

    //last line of boarder
    for ( std::size_t i = 0; i < 33; ++i )
        os << '#';
    os << std::endl;

    return os;
}

EReturnVal CMenu::LoadPlayingBoard( CPlayingBoard & board, CBufferSwitch & bufferSwitch ) {
    //main menu
    EReturnVal menuChoice = EReturnVal::BACK;
    bool showWarning = false;
    //while user doesn't choose quit or random map or map from map menu
    while ( menuChoice == EReturnVal::BACK ) {
        menuChoice = MainMenu( bufferSwitch, showWarning );
        //map from file
        if ( menuChoice == EReturnVal::MAP_FROM_FILE ) {
            board.m_Mode = EReturnVal::MAP_FROM_FILE;
            //map from file options
            menuChoice = MapMenu();
            if ( menuChoice == EReturnVal::MAP1 ) {
                board.m_Map = "saveFiles/map1.txt";
                bufferSwitch.TurnOn();
                if ( !board.LoadFromFile( "saveFiles/map1.txt" ) ) {
                    std::cout << "FILE 1 CORRUPTED" << std::endl;
                    menuChoice = EReturnVal::BACK;
                    showWarning = true;
                } else {
                    showWarning = false;
                }
                bufferSwitch.TurnOff();
            } else if ( menuChoice == EReturnVal::MAP2 ) {
                board.m_Map = "saveFiles/map2.txt";
                bufferSwitch.TurnOn();
                if ( !board.LoadFromFile( "saveFiles/map2.txt" ) ) {
                    std::cout << "FILE 2 CORRUPTED" << std::endl;
                    menuChoice = EReturnVal::BACK;
                    showWarning = true;
                } else {
                    showWarning = false;
                }
                bufferSwitch.TurnOff();
            } else if ( menuChoice == EReturnVal::MAP3 ) {
                board.m_Map = "saveFiles/map3.txt";
                bufferSwitch.TurnOn();
                if ( !board.LoadFromFile( "saveFiles/map3.txt" ) ) {
                    std::cout << "FILE 3 CORRUPTED" << std::endl;
                    menuChoice = EReturnVal::BACK;
                    showWarning = true;
                } else {
                    showWarning = false;
                }
                bufferSwitch.TurnOff();
                board.m_Mode = EReturnVal::MAP_FROM_FILE;
            }
            //random map
        } else if ( menuChoice == EReturnVal::RANDOM_MAP ) {
            board.LoadRandom();
            board.m_Mode = EReturnVal::RANDOM_MAP;
        }
            //quit
        else if ( menuChoice == EReturnVal::QUIT )
            return EReturnVal::QUIT;
    }

    return EReturnVal::NOT_INTERESTED;
}
