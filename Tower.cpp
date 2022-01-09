#include "Tower.h"
#include <stdexcept>

namespace TD
{

    Tower::Tower(): level(1)
    {
        vector<pair<string, int>> v1 = {{"Range", 3}, {"Damage", 2}, {"Rate", 3}, {"Cost", 5}};
        for(int i = 1; i <= 5; ++i)
        {
            tower_info[i] = v1;
            for(auto j : v1)
            {
                j.second += 2;
            }
        }
    }

    Tower::Tower(const map<int, vector<pair<string, int>>>& info, int lvl)
    {
        if(lvl < 0 || lvl > 5)
        {
            throw std::invalid_argument("Incorrect value for level");
        }
        level = lvl;
        tower_info = info;
    }

    Tower &Tower::setLevel()
    {
        if(level == 5)
            throw std::invalid_argument("The level is maximum!");
        ++level;
        return *this;
    }
}

