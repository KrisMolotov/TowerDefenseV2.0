#include <iostream>
#include "Evil.h"

using std::cin;
using std::cout;
using std::endl;
using namespace TD;
int main()
{
    Evil a;
    cout << "Name is " << a.getName() << endl;
    cout << "Max health is " << a.getMaxHealth() << endl;
    cout << "Current health is " << a.getCurHealth() << endl;
    cout << "Move speed is " << a.getMoveSpeed() << endl;
    cout << "Regen speed is " << a.getRegenSpeed() << endl;
    cout << "Damage index is " << a.getDamageIndex() << endl;
    return 0;
}
