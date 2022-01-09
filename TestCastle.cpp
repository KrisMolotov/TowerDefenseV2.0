#include <iostream>
#include "Castle.h"

using std::cin;
using std::cout;
using std::endl;
using namespace TD;
int main()
{
    Castle a;
    cout << "Name is " << a.getName() << endl;
    cout << "Level is " << a.getLvl() << endl;
    cout << "Current endurance is " << a.CgetCE() << endl;
    return 0;
}
