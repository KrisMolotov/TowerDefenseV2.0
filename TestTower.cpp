#include <iostream>
#include "Tower.h"

using std::cin;
using std::cout;
using std::endl;
using namespace TD;
int main()
{
    Tower a;
    cout << "Level is " << a.getLevel() << endl;
    a.setLevel();
    cout << "Level is " << a.getLevel() << endl;
    return 0;
}

