#include "Castle.h"
#include <stdexcept>

namespace TD
{
    Castle::Castle():name("Eyes of dragon"), level(1), C_cur_endurance(200)
    {
        vector<pair<string, int>> v1 = {{"Profitability", 10}, {"Max Endurance", 200}, {"Repair Speed", 10}, {"Cost", 20}};
        for(int i = 1; i <= 5; ++i)
        {
            castle_info[i] = v1;
            for(auto j : v1)
            {
                j.second += 10;
            }
        }
    }

    Castle::Castle(const string& nm, const map<int, vector<pair<string, int>>> &ci, int lvl)
    {
        if(lvl < 1 || lvl > 5)
            throw std::invalid_argument("Incorrect value for level");
        auto it = ci.begin();
        int i = 1;
        while(i != lvl)
        {
            ++it;
            ++i;
        }
        name = nm;
        C_cur_endurance = it->second[1].second;
        level = lvl;
        castle_info = ci;
    }

    Castle &Castle::UpLevel()
    {
        if(level == 5)
            throw std::invalid_argument("The level is maximum!");
        ++level;
        auto it = castle_info[level];
        C_cur_endurance = it[1].second;
        return *this;
    }

    Castle &Castle::setDamage(int harm)
    {
        if(harm < 0)
        {
            throw std::invalid_argument("Incorrect value of harm!");
        }
        C_cur_endurance -= harm;
        return *this;
    }

    Castle &Castle::Repair(int x)
    {
        auto info = castle_info[level];
        if(x < 0)
        {
            throw std::invalid_argument("Incorrect value of index!");
        }
        if((C_cur_endurance + C_cur_endurance*x/100) > info[1].second)
        {
            throw std::invalid_argument("The result is higher than max endurance");
        }
        else
        {
            C_cur_endurance += C_cur_endurance*x/100;
            C_cur_endurance += info[2].second;
        }
        return *this;
    }

}

