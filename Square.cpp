#include "Square.h"
#include <stdexcept>

namespace TD
{

    Square::Square(int X, int ind)
    {
        if (X < 0)
            throw std::invalid_argument("Incorrect value of coordinate x");
        if (ind < 1 || ind > 7)
            throw std::invalid_argument("Incorrect type of landscape");
        if (ind == 1)
        {
            info = reservoir;
            tr = nullptr;
            wl = nullptr;
            lr = nullptr;
            cl = nullptr;
        }
        else if (ind == 2)
        {
            info = mountain;
            tr = nullptr;
            wl = nullptr;
            lr = nullptr;
            cl = nullptr;
        }
        else if (ind == 3)
        {
            info = plain;
            tr = nullptr;
            wl = nullptr;
            lr = nullptr;
            cl = nullptr;
        }
        else if (ind == 4)
        {
            info = wall;
            tr = nullptr;
            wl = new Wall();
            lr = nullptr;
            cl = nullptr;
        }
        else if (ind == 5)
        {
            info = tower;
            tr = new Tower();
            wl = nullptr;
            lr = nullptr;
            cl = nullptr;
        }
        else if (ind == 6)
        {
            info = castle;
            tr = nullptr;
            wl = nullptr;
            lr = nullptr;
            cl = new Castle();
        }
        else if (ind == 7)
        {
            info = lair;
            tr = nullptr;
            wl = nullptr;
            lr = new Lair();
            cl = nullptr;
        }
        x = X;
    }

    Square &Square::setTower()
    {
        if(info != plain)
        {
            throw std::invalid_argument("The tower can be built only on plain!");
        }
        if(tr != nullptr)
        {
            throw std::invalid_argument("The tower can be built only on plain!");
        }
        tr = new Tower();
        info = tower;
        return *this;
    }

    Square &Square::setWall(int me)
    {
        if(info != plain)
        {
            throw std::invalid_argument("The wall can be built only on plain!");
        }
        if(wl != nullptr)
        {
            throw std::invalid_argument("The wall can be built only on plain!");
        }
        wl = new Wall(me);
        info = wall;
        return *this;
    }

    Square &Square::setLair()
    {
        if(lr != nullptr)
            throw std::invalid_argument("The lair is already built");
        if(wl != nullptr)
        {
            if (wl->WgetCE() > 0)
            {
                throw std::invalid_argument("The wall cant be deleted");
            }
            delete wl;
            wl = nullptr;
        }
        if(tr != nullptr)
        {
            delete tr;
            tr = nullptr;
        }
        if(cl != nullptr)
        {
            if (cl->CgetCE() > 0)
            {
                throw std::invalid_argument("The castle cant be deleted");
            }
            delete cl;
            cl = nullptr;
        }
        lr = new Lair();
        info = lair;
        return *this;
    }

    Square &Square::setCastle()
    {
        if(cl != nullptr)
        {
            if (cl->CgetCE() > 0)
            {
                throw std::invalid_argument("The castle cant be deleted");
            }
        }
        if(tr != nullptr)
        {
            delete wl;
            wl = nullptr;
        }
        if(lr != nullptr)
        {
            delete lr;
            lr = nullptr;
        }
        if(wl != nullptr)
        {
            if (wl->WgetCE() > 0)
            {
                throw std::invalid_argument("The wall cant be deleted");
            }
            delete wl;
            wl = nullptr;
        }
        cl = new Castle();
        info = castle;
        return *this;
    }

    Square &Square::setOthers(int ind)
    {
        if(ind < 1 || ind > 3)
            throw std::invalid_argument("Incorrect type");
        if(tr != nullptr)
        {
            delete tr;
            tr = nullptr;
        }
        if(wl != nullptr)
        {
            if (wl->WgetCE() > 0)
            {
                throw std::invalid_argument("The wall cant be deleted");
            }
            delete wl;
            wl = nullptr;
        }
        if(lr != nullptr)
        {
            delete lr;
            lr = nullptr;
        }
        if(cl != nullptr)
        {
            if (cl->CgetCE() > 0)
            {
                throw std::invalid_argument("The castle cant be deleted");
            }
            delete cl;
            cl = nullptr;
        }
        if(ind == 1)
        {
            info = reservoir;
        }
        else if(ind == 2)
        {
            info = mountain;
        }
        else if(ind == 3)
        {
            info = plain;
        }
        return *this;
    }

    /*Square::~Square()
    {
        if(tr != nullptr)
        {
            delete tr;
            tr = nullptr;
        }
        else if(wl != nullptr)
        {
            delete wl;
            wl = nullptr;
        }
        else if(cl != nullptr)
        {
            delete cl;
            cl = nullptr;
        }
        else if(lr != nullptr)
        {
            delete lr;
            lr = nullptr;
        }
    }*/
}



