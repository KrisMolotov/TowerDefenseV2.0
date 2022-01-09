#include <iostream>
#include "Lair.h"
using std::cin;
using std::cout;
using std::endl;
using namespace TD;
int main()
{
    Lair a;
    vector<EvilByTime> dop = a.getLI();
    auto it = dop.cbegin();
    for(; it != dop.cend(); ++it)
    {
        cout << "Type is " << it->enemy.getTypeOfEvil() << endl;
        cout << "Hero or not:  " << it->enemy.getIsHero() << endl;
        cout << "Hours is " << it->hours << endl;
        cout << "Minutes is " << it->minutes << endl;
        cout << "Seconds is " << it->seconds << endl;
        cout << "Ind is " << it->ind << endl;
        cout << "\n";
    }
    return 0;
}

