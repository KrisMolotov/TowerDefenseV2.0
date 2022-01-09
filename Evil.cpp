#include "Evil.h"
#include <stdexcept>

namespace TD
{

    Evil::Evil(int info, int ih):name("Common enemy"), max_health(10), cur_health(10), regen_speed(3), move_speed(5),damage_index(2)
    {
        if(info < 1 || info > 3)
            throw std::invalid_argument("Incorrect value of type");
        if(info == 1)
        {
            evil_info = light;
        }
        else if(info == 2)
        {
            evil_info = heavy;
        }
        else
        {
            evil_info = aviation;
        }
        if(ih != 0 && ih != 1)
            throw std::invalid_argument("Incorrect value for hero index");
        if(ih == 1)
        {
            aura = {{"Max Health", 5}, {"Cur Health", 5}, {"Regeneration Speed", 2}, {"Move Speed", 3}, {"Damage Index", 2}};
        }
        is_hero = ih;
    }

    Evil::Evil(int ih, const map<string, int>& au, string nm, int mh, int rs, int ms, int di, int info):name(std::move(nm))
    {
        if(mh < 0)
            throw std::invalid_argument("Incorrect number of max health!");
        if(rs < 0)
            throw std::invalid_argument("Incorrect number of regeneration speed!");
        if(ms < 0)
            throw std::invalid_argument("Incorrect number of move speed!");
        if(di < 0)
            throw std::invalid_argument("Incorrect number of damage index!");
        if(info == 1)
        {
            evil_info = light;
        }
        else if(info == 2)
        {
            evil_info = heavy;
        }
        else
        {
            evil_info = aviation;
        }
        max_health = mh;
        cur_health = mh;
        regen_speed = rs;
        move_speed = ms;
        damage_index = di;
        if(ih != 0 && ih != 1)
            throw std::invalid_argument("Incorrect value for hero index");
        is_hero = ih;
        aura = au;
    }

    bool Evil::getIsHero() const
    {
        if(is_hero == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Evil &Evil::setCH(int dop)
    {
        if(cur_health + dop > max_health)
            throw std::invalid_argument("Current health cant be more than maximum!");
        cur_health += dop;
        return *this;
    }

    Evil &Evil::setIsHero()
    {
        if(is_hero == 1)
        {
            throw std::invalid_argument("Evil is already a hero");
        }
        is_hero = 1;
        aura = {{"Max Health", 5}, {"Cur Health", 5}, {"Regeneration Speed", 2}, {"Move Speed", 3}, {"Damage Index", 2}};
        return *this;
    }

    int Evil::getTypeOfEvil() const
    {
        if(evil_info == light)
        {
            return 1;
        }
        else if(evil_info == heavy)
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }

    Evil &Evil::setDamage(int harm)
    {
        if(harm < 0)
        {
            throw std::invalid_argument("Incorrect value of harm!");
        }
        cur_health -= harm;
        return *this;
    }

    Evil &Evil::Repair()
    {
        if((cur_health + regen_speed) > max_health)
        {
            throw std::invalid_argument("The result is higher than max endurance");
        }
        else
        {
            cur_health += regen_speed;
        }
        return *this;
    }
}