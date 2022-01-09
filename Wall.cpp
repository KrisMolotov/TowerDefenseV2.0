#include <stdexcept>
#include "Wall.h"

namespace TD
{
    Wall::Wall(int me)
    {
        if(me <= 0)
        {
            throw std::invalid_argument("Incorrect number of max endurance!");
        }
        max_endurance = me;
        W_cur_endurance = me;
    }

    Wall& Wall::Damage(int harm)
    {
        if(harm < 0)
        {
            throw std::invalid_argument("Incorrect value of harm!");
        }
        W_cur_endurance -= harm;
        return *this;
    }

    Wall& Wall::Repair(int x)
    {
        if(x < 0)
        {
            throw std::invalid_argument("Incorrect value of index!");
        }
        if((W_cur_endurance + W_cur_endurance*x/100) > max_endurance)
        {
            throw std::invalid_argument("The result is higher than max endurance");
        }
        else
        {
            W_cur_endurance += W_cur_endurance*x/100;
        }
        return *this;
    }
}

