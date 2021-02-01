/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 02.06.20
*/

#pragma once

#include "CBonus.h"

/** child class of CBonus
 * make paddle longer and time slower
 * default activation time is 200
 */
class CBonusSlowTimeLongerPaddle
        : public CBonus {
public:

    static const int ACTIVATION_TIME = 200;
    static const int END_OF_ACTIVATION_COLOR_CHANGE = 30;

    CBonusSlowTimeLongerPaddle();

    CBonusSlowTimeLongerPaddle( const CBonusSlowTimeLongerPaddle & ) = default;

    ~CBonusSlowTimeLongerPaddle() override = default;

    /**
     * make paddle longer by one unit on each side and slow time to its half
     * activate bonus for ACTIVATION_TIME
     * @param paddle paddle which will be extended
     * @param speed speed/time/frequency is reference on time which will be slow down (multiply by 3)
     * @param board playing board
     */
    void
    Activate( TPaddle & paddle, std::chrono::milliseconds & speed, std::vector<std::string> & board ) const override;

    /**
     * deactivate bonus - make paddle shorter (default) and return time to default
     * @param paddle paddle which will be narrow down
     * @param speed speed/time/frequency is reference on time which will be slow down (divide by 3)
     * @param board playing board
     */
    void
    Deactivate( TPaddle & paddle, std::chrono::milliseconds & speed, std::vector<std::string> & board ) const override;

    /**
     * print name of bonus and remaining time to the output stream
     * @param os output stream
     * @return output stream
     */
    std::ostream & Print( std::ostream & os ) const override;
};

