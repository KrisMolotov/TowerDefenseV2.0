#include <iostream>
#include "Square.h"

using std::cin;
using std::cout;
using std::endl;
using namespace TD;

int main()
{
    Square a;
    cout << "Coordinate is " << a.getX() << endl;
    cout << "Type is " << a.S_getInfo() << endl;
    Square b(5, 4);
    cout << "Coordinate is " << b.getX() << endl;
    cout << "Type is " << b.S_getInfo() << endl;
    a.setCastle();
    cout << "Coordinate is " << a.getX() << endl;
    cout << "Type is " << a.S_getInfo() << endl;
    return 0;
}

