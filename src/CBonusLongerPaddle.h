/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 04.05.20
*/

#pragma once

#include "CBonus.h"

/** child class of CBonus
 * make paddle longer
 * default activation time is 200
 */
class CBonusLongerPaddle
        : public CBonus {
public:

    static const int ACTIVATION_TIME = 200;
    static const int END_OF_ACTIVATION_COLOR_CHANGE = 50;

    CBonusLongerPaddle();

    CBonusLongerPaddle( const CBonusLongerPaddle & ) = default;

    ~CBonusLongerPaddle() override = default;

    /**
     * make paddle longer by one unit on each side
     * activate bonus for ACTIVATION_TIME
     * @param paddle paddle which will be extended
     * @param speed not used
     * @param board playing board
     */
    void
    Activate( TPaddle & paddle, std::chrono::milliseconds & speed, std::vector<std::string> & board ) const override;

    /**
     * deactivate bonus - make paddle shorter (default)
     * @param paddle paddle which will be narrow down
     * @param speed not used
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

