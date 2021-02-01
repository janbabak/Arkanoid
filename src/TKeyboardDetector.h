/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 30.05.20
*/
#include <iostream>
#include <asm/ioctls.h>
#include <sys/ioctl.h>

using namespace std;

/**
 * keyboard detector detect when keyboard is pressed, is used by CApplication and CMenu
 */
struct TKeyboardDetector {
    TKeyboardDetector() = default;

    ~TKeyboardDetector() = default;

    /**
     * detect if keyboard was pressed
     * @return true -> keyboard was hit, false -> keyboard wan't hit
     */
    static bool KeyboardPressed() {
        int bytesWaiting;
        static const int STDIN = 0;
        ioctl( STDIN, FIONREAD, & bytesWaiting );
        return bytesWaiting; // if bytesWaiting = 0 -> there are no bytes waiting
    }
};