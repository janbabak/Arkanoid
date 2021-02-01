/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 04.05.20
*/

#pragma once

#include "CBonus.h"

/**
 * child class of class CBonus
 * slow time to one third
 */
class CBonusSlowTime
        : public CBonus {
public:

    static const int ACTIVATION_TIME = 200;
    static const int END_OF_ACTIVATION_COLOR_CHANGE = 38;

    CBonusSlowTime();

    CBonusSlowTime( const CBonusSlowTime & ) = default;

    ~CBonusSlowTime() override = default;

    /**
     * slow time to ist third
     * @param paddle not used
     * @param speed speed/time/frequency is reference on time which will be slow down (multiply by 3)
     * @param board playing board
     */
    void
    Activate( TPaddle & paddle, std::chrono::milliseconds & speed, std::vector<std::string> & board ) const override;

    /**
     * return time to default
     * @param paddle not used
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

