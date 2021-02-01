/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 19.05.20
*/

#pragma once

#include "CPlayingBoard.h"
#include "CBufferSwitch.h"
#include "TKeyboardDetector.h"
#include "EReturnVal.h"
#include "Colors.h"

#include <asm/ioctls.h>
#include <sys/ioctl.h>
#include <fstream>
#include <thread>

using namespace std::chrono_literals;  //because of using time unit suffix ( ms )

/**
 * represent all menus from game (main menu, map menu, final menu)
 */
class CMenu {
public:
    CMenu() = default;

    ~CMenu() = default;

    /**
     * load playing board form file or randomly
     * @param board playing board, which will be loaded
     * @param bufferSwitch is used for turning buffering on and off
     * @return QUIT or NOT_INTERESTED
     */
    static EReturnVal LoadPlayingBoard( CPlayingBoard & board, CBufferSwitch & bufferSwitch ) ;

    /**
     * display main menu - options are: Quit, Map from file, Random Map
     * @param buffer for turning buffering on and off
     * @param showWarning if showWarning==true display warning
     * @param warning warning which is shown, when the file is corrupted, default value is "FILE WAS CORRUPTED"
     * @return what user selected (QUIT, MAP_FROM_FILE, RANDOM_MAP)
     */
    static EReturnVal MainMenu( CBufferSwitch & buffer, bool showWarning = false,
                         const char *warning = "       \u001b[31mFILE WAS CORRUPTED!\u001b[0m" ) ;

    /**
     * print menu to the output stream
     * @param position is position of label which should be selected ( highlighted ), labels are indexed from 0
     * @param os output stream - default is std::cout
     * @return output stream
     */
    static std::ostream & PrintMainMenu( int position, std::ostream & os = std::cout );

    /**
     * react when keyboard is pressed
     * @return which of these keys user pressed: UP, DOWN, ENTER, NOT_INTERESTED - pressed something else
     */
    static EReturnVal KeyboardReactionInMenu();

    /**
     * show menu of maps
     * @return which of these options user chose: MAP1, MAP2, MAP3, BACK
     */
    static EReturnVal MapMenu() ;

    /**
     * print menu of maps to the output stream
     * @param position is position of label which should be selected ( highlighted ), labels are indexed from 0
     * @param os output stream - default is std::cout
     * @return output stream
     */
    static std::ostream & PrintMapMenu( int position, std::ostream & os = std::cout ) ;

    /**
     * show final screen menu
     * @param won if won==true -> show label VICTORY, else show label GAME OVER
     * @param score score of this game
     * @param bestScore best score from save file
     * @return which option user chose: PLAY_AGAIN or MENU
     */
    static EReturnVal finalScreenMenu( bool won, long long score, long long bestScore ) ;

    /**
     * print final menu to the ostram
     * @param won if won==true show VICTORY, if won==false show GAME OVER
     * @param position is position of label which should be selected ( highlighted ), labels are indexed from 0
     * @param score score of this game
     * @param bestScore best score from save file
     * @param os output stream - default is std::cout
     * @return output stream
     */
    static std::ostream & PrintFinalScreenMenu( bool won, int position, long long score, long long bestScore,
                                         std::ostream & os = std::cout ) ;

private:
    TKeyboardDetector m_KeyboardDetector;
};

