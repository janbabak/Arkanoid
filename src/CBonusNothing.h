/**
* @autor Jan Babak <babakjan@fit.cvut.cz>
* @date 06.05.20
*/

#pragma once

#include "CBonus.h"

/**
 * child class of class CBonus
 * do nothing
 */
class CBonusNothing
        : public CBonus {
public:
    CBonusNothing()
            : CBonus() {}

    CBonusNothing( const CBonusNothing & ) = default;

    ~CBonusNothing() override = default;

    /**
     * default bonus do nothing
     * @param paddle not used
     * @param speed not used
     * @param board not used
     */
    void
    Activate( TPaddle & paddle, std::chrono::milliseconds & speed, std::vector<std::string> & board ) const override {
        ( void ) paddle;  //not used
        ( void ) speed;  //not used
        ( void ) board; //not used
    }

    /**
     * default bonus do nothing
     * @param paddle not used
     * @param speed not used
     * @param board not used
     */
    void
    Deactivate( TPaddle & paddle, std::chrono::milliseconds & speed, std::vector<std::string> & board ) const override {
        ( void ) paddle;  //not used
        ( void ) speed;  //not used
        ( void ) board; //not used
    }

    /**
     * print nothing
     * @param os output stream
     * @return output stream
     */
    std::ostream & Print( std::ostream & os ) const override {
        return os;  //not used
    }
};
