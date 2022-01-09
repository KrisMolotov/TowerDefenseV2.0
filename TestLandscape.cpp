#include <iostream>
#include "Landscape.h"

using std::cin;
using std::cout;
using std::endl;
using namespace TD;
template<class T>
int getNum(T &a) {
    cin >> a;
    if (!std::cin.good()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return 1;
}

int main()
{
    Landscape a1;
    int key1;
    int Wallet = 100;
    cout << "Start the game!" << endl;
    while (true)
    {
        cout << "You have " << Wallet <<  " dollars in your wallet" << endl;
        cout << "Make your choice!" << endl;
        cout << "0. Quit" << endl;
        cout << "1. Print Game Field" << endl;
        cout << "2. Print Evil Table" << endl;
        cout << "3. Get size of game field" << endl;
        cout << "4. Add new square to field" << endl;
        cout << "5. Get type of square by coordinates" << endl;
        cout << "6. Set type of square by coordinates" << endl;
        cout << "7. Make move by enemy" << endl;
        cout << "8. Damage the wall" << endl;
        cout << "9. Damage the castle" << endl;
        cout << "10. Repair the wall" << endl;
        cout << "11. Get Up the level of tower" << endl;
        cout << "12. Beat Evil" << endl;
        cout << "13. Get Up the level of castle" << endl;
        cout << "14. Repair the castle" << endl;
        cout << "15. Repair the evil" << endl;
        cout << "16. Release evil from lair" << endl;
        cout << "17. Release evil from lair by time" << endl;
        cout << "18. Get Wall Health" << endl;
        cout << "19. Get Castle Health" << endl;
        cout << "20. Get Evil Health" << endl;
        if (!getNum(key1))
        {
            cout << "Enter the correct symbol!" << endl;
            continue;
        }
        if (key1 == 0)
        {
            break;
        }
        try
        {
            switch(key1)
            {
                case 1:
                {
                    cout << "Map legend:" << endl;
                    cout << "& is Reservoir" << endl;
                    cout << "§ is Mountain" << endl;
                    cout << "# is Plain" << endl;
                    cout << "! is Wall" << endl;
                    cout << "|| is Tower" << endl;
                    cout << "% is Lair" << endl;
                    cout << "* is Castle" << endl;
                    cout << endl;
                    map <int, vector<Square>> field = a1.getField();
                    auto it = field.begin();
                    for(; it != field.end(); ++ it)
                    {
                        auto dop = it->second.begin();
                        for(; dop != it->second.end(); ++dop)
                        {
                            if(dop->S_getInfo() == reservoir)
                            {
                                cout << "& ";
                            }
                            else if(dop->S_getInfo() == mountain)
                            {
                                cout << "§ ";
                            }
                            else if(dop->S_getInfo() == plain)
                            {
                                cout << "# ";
                            }
                            else if(dop->S_getInfo() == wall)
                            {
                                cout << "! ";
                            }
                            else if(dop->S_getInfo() == tower)
                            {
                                cout << "|| ";
                            }
                            else if(dop->S_getInfo() ==lair)
                            {
                                cout << "% ";
                            }
                            else if(dop->S_getInfo() == castle)
                            {
                                cout << "* ";
                            }
                        }
                        cout << endl;
                    }
                }
                break;
                case 2:
                {
                    cout << "Table legend:" << endl;
                    cout << "{} is Light Infantry" << endl;
                    cout << "[] is Heavy Infantry" << endl;
                    cout << "= is Aviation" << endl;
                    cout << "? is no Empty Point" << endl;
                    cout << endl;
                    map <int, vector<Point>> table = a1.getTable();
                    auto it = table.begin();
                    for(; it != table.end(); ++ it)
                    {
                        auto dop = it->second.begin();
                        for(; dop != it->second.end(); ++dop)
                        {
                            if(dop->enemy == nullptr)
                            {
                                cout << "? ";
                            }
                            else if(dop->enemy->getTypeOfEvil() == 1)
                            {
                                cout << "{} ";
                            }
                            else if(dop->enemy->getTypeOfEvil() == 2)
                            {
                                cout << "[] ";
                            }
                            else if(dop->enemy->getTypeOfEvil() == 3)
                            {
                                cout << "= ";
                            }
                        }
                        cout << endl;
                    }
                }
                break;
                case 3:
                {
                    a1.getSizeOfField(cout);
                }
                break;
                case 4:
                {
                    int x, y, type;
                    cout << "Enter the x coordinate of new square" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of new square" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the type of new square" << endl;
                    while(!getNum(type))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.AddSquareToField(x, y, type);
                }
                break;
                case 5:
                {
                    int x, y;
                    cout << "Enter the x coordinate of square" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of square" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << a1.getTypeOfSquare(x, y) << endl;
                }
                break;
                case 6:
                {
                    int x, y, type;
                    cout << "Enter the x coordinate of square" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of square" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the type of square" << endl;
                    while(!getNum(type))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.setTypeOfSquare(x, y, type);
                }
                break;
                case 7:
                {
                    int x, y;
                    cout << "Enter the x coordinate of evil" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of evil" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.MakeMove(x, y);
                }
                break;
                case 8:
                {
                    int x, y;
                    cout << "Enter the x coordinate of the wall you want to damage" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the wall you want to damage" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.DamageWall(x, y);
                }
                break;
                case 9:
                {
                    int x, y;
                    cout << "Enter the x coordinate of the castle you want to damage" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the castle you want to damage" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.DamageCastle(x, y);
                }
                break;
                case 10:
                {
                    int x, y, k;
                    cout << "Enter the x coordinate of the wall you want to repair" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the wall you want to repair" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the percentage of repair" << endl;
                    while(!getNum(k))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.RepairWall(k, x, y);
                }
                break;
                case 11:
                {
                    int x, y;
                    cout << "Enter the x coordinate of the tower you want to up level" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the tower you want to up level" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.UpLevelOfTower(x, y);
                }
                break;
                case 12:
                {
                    int x, y;
                    cout << "Enter the x coordinate of the tower you want to use to damage evil" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the tower you want to use to damage evil" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.BeatEvil(x, y);
                }
                break;
                case 13:
                {
                    int x, y;
                    cout << "Enter the x coordinate of the castle you want to up level" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the castle you want to up level" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.UpLevelOfCastle(x, y);
                }
                break;
                case 14:
                {
                    if(Wallet < 20)
                    {
                        throw std::invalid_argument("You have no money for repairing!");
                    }
                    int x, y, k;
                    cout << "Enter the x coordinate of the castle you want to repair" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the castle you want to repair" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the percentage of repair" << endl;
                    while(!getNum(k))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.RepairCastle(k, x, y);
                    Wallet -= 20;
                }
                break;
                case 15:
                {
                    int x, y;
                    cout << "Enter the x coordinate of the evil you want to repair" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the evil you want to repair" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.RepairEvil(x, y);
                }
                break;
                case 16:
                {
                    int x, y;
                    cout << "Enter the x coordinate of the lair" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the lair" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.ReleaseEvil(x, y);
                }
                break;
                case 17:
                {
                    int x, y, h, m, s;
                    cout << "Enter the x coordinate of the lair" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the lair" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the hours of the evil" << endl;
                    while(!getNum(h))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the minutes of evil" << endl;
                    while(!getNum(m))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the seconds of lair" << endl;
                    while(!getNum(s))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    a1.ReleaseEvilByTime(x, y, h, m, s);
                }
                break;
                case 18:
                {
                    int x, y;
                    cout << "Enter the x coordinate of the wall" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the wall" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << a1.getWallHealth(x, y) << endl;
                }
                break;
                case 19:
                {
                    int x, y;
                    cout << "Enter the x coordinate of the castle" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the castle" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << a1.getCastleHealth(x, y) << endl;
                }
                break;
                case 20:
                {
                    int x, y;
                    cout << "Enter the x coordinate of the evil" << endl;
                    while(!getNum(x))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the y coordinate of the evil" << endl;
                    while(!getNum(y))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << a1.getEvilHealth(x, y) << endl;
                }
                break;
                default:
                {
                    cout << "Please, enter correct operation code" << endl;
                }
            }
        }
        catch(std::exception &ex)
        {
            cout << ex.what() << endl;
        }
    }
    return 0;
}

