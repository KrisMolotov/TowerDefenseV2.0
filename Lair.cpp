#include "Lair.h"
#include <stdexcept>

namespace TD {

    Lair::Lair() {
        vector<EvilByTime> dop;
        EvilByTime evil1(1, 1, 1, 1, 0);
        EvilByTime evil2(1, 2, 2, 2, 0);
        EvilByTime evil3(2, 3, 3, 3, 1);
        EvilByTime evil4(2, 4, 4, 4, 0);
        EvilByTime evil5(3, 5, 5, 5, 0);
        dop.push_back(evil1);
        dop.push_back(evil2);
        dop.push_back(evil3);
        dop.push_back(evil4);
        dop.push_back(evil5);
        lair_info = dop;
    }

    Lair::Lair(const vector<EvilByTime> &info)
    {
        auto iter = info.cbegin();
        for(; iter != info.cend(); ++iter)
        {
            if(iter->hours < 0 || iter->minutes < 0 || iter->seconds < 0)
                throw std::invalid_argument("Incorrect value of time");
            if(iter->ind != 0 && iter->ind != 1)
                throw std::invalid_argument("Incorrect value of indicator");
        }
        lair_info = info;
    }

    Lair &Lair::CrossEvil()
    {
        auto iter = lair_info.begin();
        while(iter->ind != 0)
        {
            ++iter;
            if(iter == lair_info.end())
            {
                throw std::invalid_argument("All evils are already released!");
            }
        }
        iter->ind = 1;
        return *this;
    }

    Evil& Lair::getEvilFromLair()
    {
        auto iter = lair_info.begin();
        while(iter->ind != 0)
        {
            ++iter;
            if(iter == lair_info.end())
            {
                throw std::invalid_argument("All evils are already released!");
            }
        }
        return iter->enemy;
    }

    Lair &Lair::CrossEvilByTime(int h, int m, int s)
    {
        auto iter = lair_info.begin();
        while(iter->hours != h || iter->minutes != m || iter->seconds != s)
        {
            ++iter;
            if(iter == lair_info.end())
            {
                throw std::invalid_argument("There are no evil this this time!");
            }
        }
        iter->ind = 1;
        return *this;
    }

    Evil &Lair::getEvilFromLairByTime(int h, int m, int s)
    {
        auto iter = lair_info.begin();
        while(iter->hours != h || iter->minutes != m || iter->seconds != s)
        {
            ++iter;
            if(iter == lair_info.end())
            {
                throw std::invalid_argument("There are no evil this this time!");
            }
        }
        return iter->enemy;
    }
}



