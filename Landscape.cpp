#include "Landscape.h"
#include <stdexcept>
using std::cin;
using std::cout;
using std::endl;

namespace TD {
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

    Landscape::Landscape()
    {
        vector<Square> v1;
        vector<Point> p1;
        v1.emplace_back(Square(0, 7));
        v1.emplace_back(Square(1, 3));
        p1.emplace_back(Point());
        p1.emplace_back(Point(1));
        vector<Square> v2;
        vector<Point> p2;
        v2.emplace_back(Square(0, 2));
        v2.emplace_back(Square(1, 3));
        p2.emplace_back(Point());
        p2.emplace_back(Point(1));
        game_field.insert(std::make_pair(1, v1));
        game_field.insert(std::make_pair(2, v2));
        evil_table.insert((std::make_pair(1, p1)));
        evil_table.insert((std::make_pair(2, p2)));
    }

    Landscape::Landscape(const map<int, vector<Square>> &field, const map<int, vector<Point>> &table) {
        game_field = field;
        evil_table = table;
    }

    std::ostream &Landscape::getSizeOfField(std::ostream &out) {
        map<int, vector<Square>>::size_type i;
        i = game_field.size();
        if (i != 0) {
            auto iter = game_field.cbegin();
            vector<Square>::size_type j;
            j = iter->second.size();
            out << "The length of game field is " << j << std::endl;
            out << "The width of game field is " << i << std::endl;
            return out;
        } else {
            out << "The field is empty" << std::endl;
            return out;
        }
    }

    string Landscape::getTypeOfSquare(int x, int y) {
        auto i = game_field.find(y);
        if (i == game_field.end()) {
            throw std::invalid_argument("Incorrect value of y");
        } else {
            auto j = i->second.cbegin();
            for (; j != i->second.cend(); ++j) {
                if (j->getX() == x) {
                    break;
                }
            }
            if (j == i->second.cend()) {
                throw std::invalid_argument("Incorrect value of x");
            } else {
                switch (j->S_getInfo()) {
                    case reservoir: {
                        return "Reservoir";
                    }
                        break;
                    case mountain: {
                        return "Mountain";
                    }
                        break;
                    case plain: {
                        return "Plain";
                    }
                        break;
                    case wall: {
                        return "Wall";
                    }
                        break;
                    case tower: {
                        return "Tower";
                    }
                        break;
                    case castle: {
                        return "Castle";
                    }
                        break;
                    case lair: {
                        return "Lair";
                    }
                }
            }
        }
    }

    Landscape &Landscape::setTypeOfSquare(int x, int y, int type) {
        if (type < 1 || type > 7) {
            throw std::invalid_argument("Incorrect type of square");
        }
        auto i = game_field.find(y);
        if (i == game_field.end()) {
            throw std::invalid_argument("Incorrect value of y");
        } else {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j) {
                if (j->getX() == x) {
                    break;
                }
            }
            if (j == i->second.end()) {
                throw std::invalid_argument("Incorrect value of x");
            } else {
                if ((type == 4 && j->S_getInfo() != plain) || (type == 5 && j->S_getInfo() != plain)) {
                    throw std::invalid_argument("Wall or tower can be built only on plains!");
                }
                if (type == 4) {
                    j->setWall();
                }
                if (type >= 1 && type <= 3) {
                    j->setOthers(type);
                }
                if (type == 5) {
                    j->setTower();
                }
                if (type == 6) {
                    j->setCastle();
                }
                if (type == 7) {
                    j->setLair();
                }
            }
        }
        return *this;
    }

    Landscape &Landscape::AddSquareToField(int x, int y, int type) {
        if (type < 1 || type > 7) {
            throw std::invalid_argument("Incorrect type of square");
        }
        auto i = game_field.find(y);
        if (i != game_field.end()) {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j) {
                if (j->getX() == x) {
                    break;
                }
            }
            if (j != i->second.end()) {
                throw std::invalid_argument("This square is already exist!");
            } else {
                int dop = i->first;
                for (i = game_field.begin(); i != game_field.end(); ++i) {
                    if (i->first == dop) {
                        game_field[dop].emplace_back(Square(x, type));
                        sort(game_field[dop].begin(), game_field[dop].end());
                        evil_table[dop].emplace_back(Point(x));
                        sort(evil_table[dop].begin(), evil_table[dop].end());
                    } else {
                        game_field[i->first].emplace_back(Square(x, 3));
                        sort(game_field[i->first].begin(), game_field[i->first].end());
                        evil_table[i->first].emplace_back(Point(x));
                        sort(evil_table[i->first].begin(), evil_table[i->first].end());
                    }
                }
            }
        } else {
            auto j = game_field.begin()->second.begin();
            for (; j != game_field.begin()->second.end(); ++j) {
                if (j->getX() == x) {
                    break;
                }
            }
            if (j == game_field.begin()->second.end()) {
                vector<Square> v1;
                vector<Point> v2;
                auto it = game_field.begin()->second.begin();
                for (; it != game_field.begin()->second.end(); ++it) {
                    v1.emplace_back(Square(it->getX(), 3));
                    v2.emplace_back(Point(it->getX()));
                }
                v1.emplace_back(Square(x, type));
                v2.emplace_back(Point(x));
                sort(v1.begin(), v1.end());
                sort(v2.begin(), v2.end());
                game_field.insert(pair<int, vector<Square>>(y, v1));
                evil_table.insert(pair<int, vector<Point>>(y, v2));
                for (i = game_field.begin(); i != game_field.end(); ++i) {
                    if (i->first == y) {
                        continue;
                    } else {
                        game_field[i->first].emplace_back(Square(x, 3));
                        sort(game_field[i->first].begin(), game_field[i->first].end());
                        evil_table[i->first].emplace_back(Point(x));
                        sort(evil_table[i->first].begin(), evil_table[i->first].end());
                    }
                }
            } else {
                vector<Square> v1;
                vector<Point> v2;
                auto it = game_field.begin()->second.begin();
                for (; it != game_field.begin()->second.end(); ++it) {
                    if (it->getX() == j->getX()) {
                        v1.emplace_back(Square(x, type));
                        v2.emplace_back(Point(x));
                    }
                    else
                    {
                        v1.emplace_back(Square(it->getX(), 3));
                        v2.emplace_back(Point(it->getX()));
                    }
                }
                sort(v1.begin(), v1.end());
                sort(v2.begin(), v2.end());
                game_field.insert(pair<int, vector<Square>>(y, v1));
                evil_table.insert(pair<int, vector<Point>>(y, v2));
            }
        }
        return *this;
    }

    Landscape &Landscape::MakeMove(int x1, int y1) {
        auto i = evil_table.find(y1);
        if (i == evil_table.end()) {
            throw std::invalid_argument("Incorrect value of y");
        } else {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j) {
                if (j->x == x1) {
                    break;
                }
            }
            if (j == i->second.end()) {
                throw std::invalid_argument("Incorrect value of x");
            } else {
                if (j->enemy != nullptr) {
                    if (y1 == 1) {
                        if (y1 == evil_table.size()) {
                            if (x1 == 0) {
                                if (1 == evil_table[y1].size()) {
                                    throw std::invalid_argument("There are no options to make move!");
                                } else {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 + 1].S_getInfo() == wall ||
                                            iter->second[x1 + 1].S_getInfo() == tower ||
                                            iter->second[x1 + 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to make move!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 + 1 && b == y1) {
                                                auto extra = evil_table.find(y1);
                                                extra->second[x1 + 1].enemy = j->enemy;
                                                j->enemy = nullptr;
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 + 1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to make move evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 + 1 && b == y1) {
                                                auto extra = evil_table.find(y1);
                                                extra->second[x1 + 1].enemy = j->enemy;
                                                j->enemy = nullptr;
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (x1 + 1 == evil_table[y1].size()) {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 - 1].S_getInfo() == wall ||
                                            iter->second[x1 - 1].S_getInfo() == tower ||
                                            iter->second[x1 - 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to make move evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 - 1 && b == y1) {
                                                auto extra = evil_table.find(y1);
                                                extra->second[x1 - 1].enemy = j->enemy;
                                                j->enemy = nullptr;
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 - 1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 - 1 && b == y1) {
                                                auto extra = evil_table.find(y1);
                                                extra->second[x1 - 1].enemy = j->enemy;
                                                j->enemy = nullptr;
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 - 1].S_getInfo() == wall ||
                                            iter->second[x1 - 1].S_getInfo() == tower ||
                                            iter->second[x1 - 1].S_getInfo() == tower) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 + 1].S_getInfo() == wall ||
                                            iter->second[x1 + 1].S_getInfo() == tower ||
                                            iter->second[x1 + 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 - 1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 + 1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if (x1 == 0) {
                                if (1 == evil_table[y1].size()) {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1 + 1);
                                        if (iter->second[x1].S_getInfo() == wall || iter->second[x1].S_getInfo() == tower ||
                                            iter->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 && b == y1 + 1) {
                                                auto extra = evil_table.find(y1 + 1);
                                                extra->second[x1].enemy = j->enemy;
                                                j->enemy = nullptr;
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1 + 1);
                                        if (iter->second[x1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 && b == y1 + 1) {
                                                auto extra = evil_table.find(y1 + 1);
                                                extra->second[x1].enemy = j->enemy;
                                                j->enemy = nullptr;
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 + 1].S_getInfo() == wall ||
                                            iter->second[x1 + 1].S_getInfo() == tower ||
                                            iter->second[x1 + 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (x1 + 1 == evil_table[y1].size()) {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 - 1].S_getInfo() == wall ||
                                            iter->second[x1 - 1].S_getInfo() == tower ||
                                            iter->second[x1 - 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == wall || iter1->second[x1].S_getInfo() == tower ||
                                            iter1->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 + 1].S_getInfo() == wall ||
                                            iter->second[x1 + 1].S_getInfo() == tower ||
                                            iter->second[x1 + 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == wall ||
                                            iter->second[x1 - 1].S_getInfo() == tower ||
                                            iter->second[x1 - 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (y1 == evil_table.size()) {
                            if (x1 == 0) {
                                if (1 == evil_table[y1].size()) {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter1->second[x1].S_getInfo() == wall || iter1->second[x1].S_getInfo() == tower ||
                                            iter1->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 && b == y1 - 1)) {
                                                auto extra = evil_table.find(y1 - 1);
                                                extra->second[x1].enemy = j->enemy;
                                                j->enemy = nullptr;
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter1->second[x1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 && b == y1 - 1)) {
                                                auto extra = evil_table.find(y1 - 1);
                                                extra->second[x1].enemy = j->enemy;
                                                j->enemy = nullptr;
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == wall ||
                                            iter->second[x1 + 1].S_getInfo() == tower ||
                                            iter->second[x1 + 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == wall || iter1->second[x1].S_getInfo() == tower ||
                                            iter1->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (x1 + 1 == evil_table[y1].size()) {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 - 1].S_getInfo() == wall ||
                                            iter->second[x1 - 1].S_getInfo() == tower ||
                                            iter->second[x1 - 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == wall || iter1->second[x1].S_getInfo() == tower ||
                                            iter1->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 - 1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == wall ||
                                            iter->second[x1 + 1].S_getInfo() == tower ||
                                            iter->second[x1 + 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == wall ||
                                            iter->second[x1 - 1].S_getInfo() == tower ||
                                            iter->second[x1 - 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if (x1 == 0) {
                                if (1 == evil_table[y1].size()) {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1 - 1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1].S_getInfo() == wall || iter->second[x1].S_getInfo() == tower ||
                                            iter->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == wall || iter1->second[x1].S_getInfo() == tower ||
                                            iter1->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 && b == y1 - 1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1 - 1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 && b == y1 - 1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == wall ||
                                            iter->second[x1 + 1].S_getInfo() == tower ||
                                            iter->second[x1 + 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == wall || iter2->second[x1].S_getInfo() == tower ||
                                            iter2->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == wall || iter1->second[x1].S_getInfo() == tower ||
                                            iter1->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 - 1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 - 1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (x1 + 1 == evil_table[y1].size()) {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 - 1].S_getInfo() == wall ||
                                            iter->second[x1 + 1].S_getInfo() == tower ||
                                            iter->second[x1 + 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == wall || iter2->second[x1].S_getInfo() == tower ||
                                            iter2->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == wall || iter1->second[x1].S_getInfo() == tower ||
                                            iter1->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 - 1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 - 1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 - 1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    if (j->enemy->getTypeOfEvil() == 1 || j->enemy->getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == wall ||
                                            iter->second[x1 + 1].S_getInfo() == tower ||
                                            iter->second[x1 + 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == wall ||
                                            iter->second[x1 - 1].S_getInfo() == tower ||
                                            iter->second[x1 - 1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == wall || iter2->second[x1].S_getInfo() == tower ||
                                            iter2->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == wall || iter1->second[x1].S_getInfo() == tower ||
                                            iter1->second[x1].S_getInfo() == castle) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 + 1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else if (a == x1 && b == y1 + 1) {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (j->enemy->getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == mountain) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 + 1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else if (a == x1 && b == y1 + 1) {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = j->enemy;
                                                    j->enemy = nullptr;
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    throw std::invalid_argument("There are no enemy!");
                }
            }
        }
        return *this;
    }

    Landscape &Landscape::ReleaseEvil(int x1, int y1) {
        auto i = game_field.find(y1);
        if (i == game_field.end()) {
            throw std::invalid_argument("Incorrect value of y");
        } else {
            auto j = i->second.cbegin();
            for (; j != i->second.cend(); ++j) {
                if (j->getX() == x1) {
                    break;
                }
            }
            if (j == i->second.cend()) {
                throw std::invalid_argument("Incorrect value of x");
            } else {
                if (j->S_getInfo() != lair) {
                    throw std::invalid_argument("There are no lair on this square!");
                } else {
                    if (y1 == 1) {
                        if (y1 == game_field.size()) {
                            if (x1 == 0) {
                                if (1 == game_field[y1].size()) {
                                    throw std::invalid_argument("There are no options to release evil!");
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 + 1 && b == y1) {
                                                auto extra = evil_table.find(y1);
                                                extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                j->getLair()->CrossEvil();
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 + 1 && b == y1) {
                                                auto extra = evil_table.find(y1);
                                                extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                j->getLair()->CrossEvil();
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (x1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 - 1 && b == y1) {
                                                auto extra = evil_table.find(y1);
                                                extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                j->getLair()->CrossEvil();
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 - 1 && b == y1) {
                                                auto extra = evil_table.find(y1);
                                                extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                j->getLair()->CrossEvil();
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if (x1 == 0) {
                                if (1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1 + 1);
                                        if (iter->second[x1].S_getInfo() == 4 || iter->second[x1].S_getInfo() == 5 ||
                                            iter->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 && b == y1 + 1) {
                                                auto extra = evil_table.find(y1 + 1);
                                                extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                j->getLair()->CrossEvil();
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1 + 1);
                                        if (iter->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 && b == y1 + 1) {
                                                auto extra = evil_table.find(y1 + 1);
                                                extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                j->getLair()->CrossEvil();
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (x1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (y1 == game_field.size()) {
                            if (x1 == 0) {
                                if (1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 && b == y1 - 1)) {
                                                auto extra = evil_table.find(y1 - 1);
                                                extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                j->getLair()->CrossEvil();
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 && b == y1 - 1)) {
                                                auto extra = evil_table.find(y1 - 1);
                                                extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                j->getLair()->CrossEvil();
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (x1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if (x1 == 0) {
                                if (1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1 - 1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1].S_getInfo() == 4 || iter->second[x1].S_getInfo() == 5 ||
                                            iter->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 && b == y1 - 1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1 - 1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 && b == y1 - 1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == 4 || iter2->second[x1].S_getInfo() == 5 ||
                                            iter2->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 - 1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 - 1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (x1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == 4 || iter2->second[x1].S_getInfo() == 5 ||
                                            iter2->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 - 1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 - 1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->ind != 0) {
                                        ++it;
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == 4 || iter2->second[x1].S_getInfo() == 5 ||
                                            iter2->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 + 1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else if (a == x1 && b == y1 + 1) {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 + 1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else if (a == x1 && b == y1 + 1) {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return *this;
    }

    Landscape &Landscape::ReleaseEvilByTime(int x1, int y1, int h, int m, int s) {
        auto i = game_field.find(y1);
        if (i == game_field.end()) {
            throw std::invalid_argument("Incorrect value of y");
        } else {
            auto j = i->second.cbegin();
            for (; j != i->second.cend(); ++j) {
                if (j->getX() == x1) {
                    break;
                }
            }
            if (j == i->second.cend()) {
                throw std::invalid_argument("Incorrect value of x");
            } else {
                if (j->S_getInfo() != lair) {
                    throw std::invalid_argument("There are no lair on this square!");
                } else {
                    if (y1 == 1) {
                        if (y1 == game_field.size()) {
                            if (x1 == 0) {
                                if (1 == game_field[y1].size()) {
                                    throw std::invalid_argument("There are no options to release evil!");
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 + 1 && b == y1) {
                                                auto extra = evil_table.find(y1);
                                                extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                j->getLair()->CrossEvilByTime(h, m, s);
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 + 1 && b == y1) {
                                                auto extra = evil_table.find(y1);
                                                extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                j->getLair()->CrossEvilByTime(h, m, s);
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (x1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 - 1 && b == y1) {
                                                auto extra = evil_table.find(y1);
                                                extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                j->getLair()->CrossEvilByTime(h, m, s);
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 - 1 && b == y1) {
                                                auto extra = evil_table.find(y1);
                                                extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                j->getLair()->CrossEvilByTime(h, m, s);
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                } else {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLair());
                                                    j->getLair()->CrossEvil();
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if (x1 == 0) {
                                if (1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1 + 1);
                                        if (iter->second[x1].S_getInfo() == 4 || iter->second[x1].S_getInfo() == 5 ||
                                            iter->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 && b == y1 + 1) {
                                                auto extra = evil_table.find(y1 + 1);
                                                extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h, m,
                                                                                                                s));
                                                j->getLair()->CrossEvilByTime(h, m, s);
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1 + 1);
                                        if (iter->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if (a == x1 && b == y1 + 1) {
                                                auto extra = evil_table.find(y1 + 1);
                                                extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h, m,
                                                                                                                s));
                                                j->getLair()->CrossEvilByTime(h, m, s);
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (x1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (y1 == game_field.size()) {
                            if (x1 == 0) {
                                if (1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 && b == y1 - 1)) {
                                                auto extra = evil_table.find(y1 - 1);
                                                extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h, m,
                                                                                                                s));
                                                j->getLair()->CrossEvilByTime(h, m, s);
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 && b == y1 - 1)) {
                                                auto extra = evil_table.find(y1 - 1);
                                                extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h, m,
                                                                                                                s));
                                                j->getLair()->CrossEvilByTime(h, m, s);
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (x1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if (x1 == 0) {
                                if (1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1 - 1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1].S_getInfo() == 4 || iter->second[x1].S_getInfo() == 5 ||
                                            iter->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 && b == y1 - 1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1 - 1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        if (iter->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 && b == y1 - 1) || (a == x1 && b == y1 + 1)) {
                                                if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == 4 || iter2->second[x1].S_getInfo() == 5 ||
                                            iter2->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 - 1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 && b == y1 - 1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (x1 == game_field[y1].size()) {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == 4 || iter2->second[x1].S_getInfo() == 5 ||
                                            iter2->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 - 1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 - 1 && b == y1) || (a == x1 && b == y1 - 1) ||
                                                (a == x1 && b == y1 + 1)) {
                                                if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else if (a == x1 && b == y1 - 1) {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                } else {
                                    vector<EvilByTime> dop = j->getLair()->getLI();
                                    auto it = dop.begin();
                                    while (it->hours != h && it->minutes != m && it->seconds != s) {
                                        ++it;
                                        if (it == dop.end()) {
                                            throw std::invalid_argument("There are no evil with this time!");
                                        }
                                    }
                                    if (it->enemy.getTypeOfEvil() == 1 || it->enemy.getTypeOfEvil() == 2) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 4 ||
                                            iter->second[x1 + 1].S_getInfo() == 5 ||
                                            iter->second[x1 + 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 4 ||
                                            iter->second[x1 - 1].S_getInfo() == 5 ||
                                            iter->second[x1 - 1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == 4 || iter2->second[x1].S_getInfo() == 5 ||
                                            iter2->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 4 || iter1->second[x1].S_getInfo() == 5 ||
                                            iter1->second[x1].S_getInfo() == 6) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 + 1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else if (a == x1 && b == y1 + 1) {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    } else if (it->enemy.getTypeOfEvil() == 3) {
                                        auto iter = game_field.find(y1);
                                        auto iter1 = game_field.find(y1 + 1);
                                        auto iter2 = game_field.find(y1 - 1);
                                        if (iter->second[x1 + 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter->second[x1 - 1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter2->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        }
                                        if (iter1->second[x1].S_getInfo() == 2) {
                                            throw std::invalid_argument("There are no options to release evil!");
                                        } else {
                                            cout << "Your options are:" << endl;
                                            cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                            cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                            int a, b;
                                            cout << "Enter your choice to release: " << endl;
                                            while (!getNum(a)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            while (!getNum(b)) {
                                                cout << "Enter the correct symbol!" << endl;
                                            }
                                            if ((a == x1 + 1 && b == y1) || (a == x1 - 1 && b == y1) ||
                                                (a == x1 && b == y1 + 1) || (a == x1 && b == y1 - 1)) {
                                                if (a == x1 + 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 + 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else if (a == x1 - 1 && b == y1) {
                                                    auto extra = evil_table.find(y1);
                                                    extra->second[x1 - 1].enemy = &(j->getLair()->getEvilFromLairByTime(
                                                            h, m, s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else if (a == x1 && b == y1 + 1) {
                                                    auto extra = evil_table.find(y1 + 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                } else {
                                                    auto extra = evil_table.find(y1 - 1);
                                                    extra->second[x1].enemy = &(j->getLair()->getEvilFromLairByTime(h,
                                                                                                                    m,
                                                                                                                    s));
                                                    j->getLair()->CrossEvilByTime(h, m, s);
                                                }
                                            } else {
                                                throw std::invalid_argument("Choose option only from available!");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return *this;
    }

    Landscape &Landscape::DamageWall(int x1, int y1)
    {
        auto i = game_field.find(y1);
        if (i == game_field.end())
        {
            throw std::invalid_argument("Incorrect value of y");
        }
        else
        {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j)
            {
                if (j->getX() == x1)
                {
                    break;
                }
            }
            if (j == i->second.end())
            {
                throw std::invalid_argument("Incorrect value of x");
            }
            else
            {
                if (j->S_getInfo() != wall)
                {
                    throw std::invalid_argument("There are no wall on this square!");
                }
                else
                {
                    if (y1 == 1)
                    {
                        if (y1 == game_field.size())
                        {
                            if (x1 == 0)
                            {
                                if (1 == game_field[y1].size())
                                {
                                    throw std::invalid_argument("There are no evils near wall!");
                                }
                                else
                                {
                                    auto it = evil_table[y1];
                                    if(it[x1 + 1].enemy == nullptr || it[x1 + 1].enemy->getTypeOfEvil() == 1)
                                    {
                                        throw std::invalid_argument("There are no evils near wall!");
                                    }
                                    else
                                    {
                                        cout << "Your options are:" << endl;
                                        cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                        int a, b;
                                        cout << "Enter your choice to release: " << endl;
                                        while (!getNum(a))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        while (!getNum(b))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        if (a == x1 + 1 && b == y1)
                                        {
                                            int harm = it[x1 + 1].enemy->getCurHealth() * it[x1 + 1].enemy->getDamageIndex();
                                            j->getWall()->Damage(harm);
                                            if(j->getWall()->WgetCE() <= 0)
                                            {
                                                j->setOthers(3);
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("Choose option only from available!");
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if(x1 == game_field[y1].size())
                                {
                                    auto it = evil_table[y1];
                                    if(it[x1 - 1].enemy == nullptr || it[x1 - 1].enemy->getTypeOfEvil() == 1)
                                    {
                                        throw std::invalid_argument("There are no evils near wall!");
                                    }
                                    else
                                    {
                                        cout << "Your options are:" << endl;
                                        cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                        int a, b;
                                        cout << "Enter your choice to release: " << endl;
                                        while (!getNum(a))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        while (!getNum(b))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        if (a == x1 - 1 && b == y1)
                                        {
                                            int harm = it[x1 - 1].enemy->getCurHealth() * it[x1 - 1].enemy->getDamageIndex();
                                            j->getWall()->Damage(harm);
                                            if(j->getWall()->WgetCE() <= 0)
                                            {
                                                j->setOthers(3);
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("Choose option only from available!");
                                        }
                                    }
                                }
                                else
                                {
                                    auto it = evil_table[y1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it[x1 + 1].enemy == nullptr || it[x1 + 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it[x1 + 1].enemy->getCurHealth() * it[x1 + 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it[x1 - 1].enemy == nullptr || it[x1 - 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it[x1 - 1].enemy->getCurHealth() * it[x1 - 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (x1 == 0)
                            {
                                if (1 == game_field[y1].size())
                                {
                                    auto it = evil_table[y1 + 1];
                                    if(it[x1].enemy == nullptr || it[x1].enemy->getTypeOfEvil() == 1)
                                    {
                                        throw std::invalid_argument("There are no evils near wall!");
                                    }
                                    else
                                    {
                                        cout << "Your options are:" << endl;
                                        cout << "x2: " << x1 << "y2: " << y1 + 1<< endl;
                                        int a, b;
                                        cout << "Enter your choice to release: " << endl;
                                        while (!getNum(a))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        while (!getNum(b))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        if (a == x1 && b == y1 + 1)
                                        {
                                            int harm = it[x1].enemy->getCurHealth() * it[x1].enemy->getDamageIndex();
                                            j->getWall()->Damage(harm);
                                            if(j->getWall()->WgetCE() <= 0)
                                            {
                                                j->setOthers(3);
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("Choose option only from available!");
                                        }
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 + 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1<< endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr || it1[x1 + 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 + 1].enemy->getCurHealth() * it1[x1 + 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr || it2[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                            else
                            {
                                if(x1 == game_field[y1].size())
                                {
                                    auto it1 = evil_table[y1 + 1];
                                    auto it2 = evil_table[y1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 && b == y1 + 1)
                                    {
                                        if(it1[x1].enemy == nullptr || it1[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1].enemy->getCurHealth() * it1[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it2[x1 - 1].enemy == nullptr || it2[x1 - 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1 - 1].enemy->getCurHealth() * it2[x1 - 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 + 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr || it1[x1 + 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 + 1].enemy->getCurHealth() * it1[x1 + 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it1[x1 - 1].enemy == nullptr || it1[x1 - 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 - 1].enemy->getCurHealth() * it1[x1 - 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1 )
                                    {
                                        if(it2[x1].enemy == nullptr || it2[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if (y1 == game_field.size())
                        {
                            if (x1 == 0)
                            {
                                if (1 == game_field[y1].size())
                                {
                                    auto it = evil_table[y1 - 1];
                                    if(it[x1].enemy == nullptr || it[x1].enemy->getTypeOfEvil() == 1)
                                    {
                                        throw std::invalid_argument("There are no evils near wall!");
                                    }
                                    else
                                    {
                                        cout << "Your options are:" << endl;
                                        cout << "x2: " << x1 << "y2: " << y1 - 1<< endl;
                                        int a, b;
                                        cout << "Enter your choice to release: " << endl;
                                        while (!getNum(a))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        while (!getNum(b))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        if (a == x1 && b == y1 - 1)
                                        {
                                            int harm = it[x1].enemy->getCurHealth() * it[x1].enemy->getDamageIndex();
                                            j->getWall()->Damage(harm);
                                            if(j->getWall()->WgetCE() <= 0)
                                            {
                                                j->setOthers(3);
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("Choose option only from available!");
                                        }
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 - 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr || it1[x1 + 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 + 1].enemy->getCurHealth() * it1[x1 + 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 - 1)
                                    {
                                        if(it2[x1].enemy == nullptr || it2[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                            else
                            {
                                if(x1 == game_field[y1].size())
                                {
                                    auto it1 = evil_table[y1- 1];
                                    auto it2 = evil_table[y1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 && b == y1 - 1)
                                    {
                                        if(it1[x1].enemy == nullptr || it1[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1].enemy->getCurHealth() * it1[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it2[x1 - 1].enemy == nullptr || it2[x1 - 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1 - 1].enemy->getCurHealth() * it2[x1 - 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 -1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr || it1[x1 + 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 + 1].enemy->getCurHealth() * it1[x1 + 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it1[x1 - 1].enemy == nullptr || it1[x1 - 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 - 1].enemy->getCurHealth() * it1[x1 - 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 - 1)
                                    {
                                        if(it2[x1].enemy == nullptr || it2[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (x1 == 0)
                            {
                                if (1 == game_field[y1].size())
                                {
                                    auto it1 = evil_table[y1 - 1];
                                    auto it2 = evil_table[y1 + 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1<< endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 && b == y1 - 1)
                                    {
                                        if(it1[x1].enemy == nullptr || it1[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1].enemy->getCurHealth() * it1[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr || it2[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it3 = evil_table[y1 - 1];
                                    auto it2 = evil_table[y1 + 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1<< endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1<< endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1<< endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr || it1[x1 + 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 + 1].enemy->getCurHealth() * it1[x1 + 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr || it2[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 - 1)
                                    {
                                        if(it3[x1].enemy == nullptr || it3[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it3[x1].enemy->getCurHealth() * it3[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                            else
                            {
                                if(x1 == game_field[y1].size())
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 + 1];
                                    auto it3 = evil_table[y1 - 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr || it2[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    if (a == x1 && b == y1 - 1)
                                    {
                                        if(it3[x1].enemy == nullptr || it3[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it3[x1].enemy->getCurHealth() * it3[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it1[x1 - 1].enemy == nullptr || it1[x1 - 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 - 1].enemy->getCurHealth() * it1[x1 - 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 + 1];
                                    auto it3 = evil_table[y1 - 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr || it1[x1 + 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 + 1].enemy->getCurHealth() * it1[x1 + 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it1[x1 - 1].enemy == nullptr || it1[x1 - 1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 - 1].enemy->getCurHealth() * it1[x1 - 1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr || it2[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 - 1)
                                    {
                                        if(it3[x1].enemy == nullptr || it3[x1].enemy->getTypeOfEvil() == 1)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it3[x1].enemy->getCurHealth() * it3[x1].enemy->getDamageIndex();
                                        j->getWall()->Damage(harm);
                                        if(j->getWall()->WgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return *this;
    }

    Landscape &Landscape::DamageCastle(int x1, int y1)
    {
        auto i = game_field.find(y1);
        if (i == game_field.end())
        {
            throw std::invalid_argument("Incorrect value of y");
        }
        else
        {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j)
            {
                if (j->getX() == x1)
                {
                    break;
                }
            }
            if (j == i->second.end())
            {
                throw std::invalid_argument("Incorrect value of x");
            }
            else
            {
                if (j->S_getInfo() != castle)
                {
                    throw std::invalid_argument("There are no wall on this square!");
                }
                else
                {
                    if (y1 == 1)
                    {
                        if (y1 == game_field.size())
                        {
                            if (x1 == 0)
                            {
                                if (1 == game_field[y1].size())
                                {
                                    throw std::invalid_argument("There are no evils near wall!");
                                }
                                else
                                {
                                    auto it = evil_table[y1];
                                    if(it[x1 + 1].enemy == nullptr)
                                    {
                                        throw std::invalid_argument("There are no evils near wall!");
                                    }
                                    else
                                    {
                                        cout << "Your options are:" << endl;
                                        cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                        int a, b;
                                        cout << "Enter your choice to release: " << endl;
                                        while (!getNum(a))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        while (!getNum(b))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        if (a == x1 + 1 && b == y1)
                                        {
                                            int harm = it[x1 + 1].enemy->getCurHealth() * it[x1 + 1].enemy->getDamageIndex();
                                            j->getCastle()->setDamage(harm);
                                            if(j->getCastle()->CgetCE() <= 0)
                                            {
                                                j->setOthers(3);
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("Choose option only from available!");
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if(x1 == game_field[y1].size())
                                {
                                    auto it = evil_table[y1];
                                    if(it[x1 - 1].enemy == nullptr)
                                    {
                                        throw std::invalid_argument("There are no evils near wall!");
                                    }
                                    else
                                    {
                                        cout << "Your options are:" << endl;
                                        cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                        int a, b;
                                        cout << "Enter your choice to release: " << endl;
                                        while (!getNum(a))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        while (!getNum(b))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        if (a == x1 - 1 && b == y1)
                                        {
                                            int harm = it[x1 - 1].enemy->getCurHealth() * it[x1 - 1].enemy->getDamageIndex();
                                            j->getCastle()->setDamage(harm);
                                            if(j->getCastle()->CgetCE() <= 0)
                                            {
                                                j->setOthers(3);
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("Choose option only from available!");
                                        }
                                    }
                                }
                                else
                                {
                                    auto it = evil_table[y1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it[x1 + 1].enemy->getCurHealth() * it[x1 + 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it[x1 - 1].enemy->getCurHealth() * it[x1 - 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (x1 == 0)
                            {
                                if (1 == game_field[y1].size())
                                {
                                    auto it = evil_table[y1 + 1];
                                    if(it[x1].enemy == nullptr)
                                    {
                                        throw std::invalid_argument("There are no evils near wall!");
                                    }
                                    else
                                    {
                                        cout << "Your options are:" << endl;
                                        cout << "x2: " << x1 << "y2: " << y1 + 1<< endl;
                                        int a, b;
                                        cout << "Enter your choice to release: " << endl;
                                        while (!getNum(a))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        while (!getNum(b))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        if (a == x1 && b == y1 + 1)
                                        {
                                            int harm = it[x1].enemy->getCurHealth() * it[x1].enemy->getDamageIndex();
                                            j->getCastle()->setDamage(harm);
                                            if(j->getCastle()->CgetCE() <= 0)
                                            {
                                                j->setOthers(3);
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("Choose option only from available!");
                                        }
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 + 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1<< endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 + 1].enemy->getCurHealth() * it1[x1 + 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                            else
                            {
                                if(x1 == game_field[y1].size())
                                {
                                    auto it1 = evil_table[y1 + 1];
                                    auto it2 = evil_table[y1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 && b == y1 + 1)
                                    {
                                        if(it1[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1].enemy->getCurHealth() * it1[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it2[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1 - 1].enemy->getCurHealth() * it2[x1 - 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 + 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 + 1].enemy->getCurHealth() * it1[x1 + 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it1[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 - 1].enemy->getCurHealth() * it1[x1 - 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if (y1 == game_field.size())
                        {
                            if (x1 == 0)
                            {
                                if (1 == game_field[y1].size())
                                {
                                    auto it = evil_table[y1 - 1];
                                    if(it[x1].enemy == nullptr)
                                    {
                                        throw std::invalid_argument("There are no evils near wall!");
                                    }
                                    else
                                    {
                                        cout << "Your options are:" << endl;
                                        cout << "x2: " << x1 << "y2: " << y1 - 1<< endl;
                                        int a, b;
                                        cout << "Enter your choice to release: " << endl;
                                        while (!getNum(a))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        while (!getNum(b))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        if (a == x1 && b == y1 - 1)
                                        {
                                            int harm = it[x1].enemy->getCurHealth() * it[x1].enemy->getDamageIndex();
                                            j->getCastle()->setDamage(harm);
                                            if(j->getCastle()->CgetCE() <= 0)
                                            {
                                                j->setOthers(3);
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("Choose option only from available!");
                                        }
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 - 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 + 1].enemy->getCurHealth() * it1[x1 + 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 - 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                            else
                            {
                                if(x1 == game_field[y1].size())
                                {
                                    auto it1 = evil_table[y1- 1];
                                    auto it2 = evil_table[y1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 && b == y1 - 1)
                                    {
                                        if(it1[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1].enemy->getCurHealth() * it1[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it2[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1 - 1].enemy->getCurHealth() * it2[x1 - 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 -1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 + 1].enemy->getCurHealth() * it1[x1 + 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it1[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 - 1].enemy->getCurHealth() * it1[x1 - 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 - 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (x1 == 0)
                            {
                                if (1 == game_field[y1].size())
                                {
                                    auto it1 = evil_table[y1 - 1];
                                    auto it2 = evil_table[y1 + 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1<< endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 && b == y1 - 1)
                                    {
                                        if(it1[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1].enemy->getCurHealth() * it1[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it3 = evil_table[y1 - 1];
                                    auto it2 = evil_table[y1 + 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1<< endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1<< endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1<< endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 + 1].enemy->getCurHealth() * it1[x1 + 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 - 1)
                                    {
                                        if(it3[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it3[x1].enemy->getCurHealth() * it3[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                            else
                            {
                                if(x1 == game_field[y1].size())
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 + 1];
                                    auto it3 = evil_table[y1 - 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    if (a == x1 && b == y1 - 1)
                                    {
                                        if(it3[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it3[x1].enemy->getCurHealth() * it3[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it1[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 - 1].enemy->getCurHealth() * it1[x1 - 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 + 1];
                                    auto it3 = evil_table[y1 - 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 + 1].enemy->getCurHealth() * it1[x1 + 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it1[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it1[x1 - 1].enemy->getCurHealth() * it1[x1 - 1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it2[x1].enemy->getCurHealth() * it2[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else if(a == x1 && b == y1 - 1)
                                    {
                                        if(it3[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        int harm = it3[x1].enemy->getCurHealth() * it3[x1].enemy->getDamageIndex();
                                        j->getCastle()->setDamage(harm);
                                        if(j->getCastle()->CgetCE() <= 0)
                                        {
                                            j->setOthers(3);
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return *this;
    }

    Landscape &Landscape::BeatEvil(int x1, int y1)
    {
        auto i = game_field.find(y1);
        if (i == game_field.end())
        {
            throw std::invalid_argument("Incorrect value of y");
        }
        else
        {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j)
            {
                if (j->getX() == x1)
                {
                    break;
                }
            }
            if (j == i->second.end())
            {
                throw std::invalid_argument("Incorrect value of x");
            }
            else
            {
                if (j->S_getInfo() != tower)
                {
                    throw std::invalid_argument("There are no tower on this square!");
                }
                else
                {
                    if (y1 == 1)
                    {
                        if (y1 == game_field.size())
                        {
                            if (x1 == 0)
                            {
                                if (1 == game_field[y1].size())
                                {
                                    throw std::invalid_argument("There are no evils near tower!");
                                }
                                else
                                {
                                    auto it = evil_table[y1];
                                    if(it[x1 + 1].enemy == nullptr)
                                    {
                                        throw std::invalid_argument("There are no evils near tower!");
                                    }
                                    else
                                    {
                                        cout << "Your options are:" << endl;
                                        cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                        int a, b;
                                        cout << "Enter your choice to release: " << endl;
                                        while (!getNum(a))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        while (!getNum(b))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        if (a == x1 + 1 && b == y1)
                                        {
                                            auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                            int harm = info[1].second * info[2].second;
                                            it[x1 + 1].enemy->setDamage(harm);
                                            if(it[x1 + 1].enemy->getCurHealth() <= 0)
                                            {
                                                it[x1 + 1].enemy = nullptr;
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("Choose option only from available!");
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if(x1 == game_field[y1].size())
                                {
                                    auto it = evil_table[y1];
                                    if(it[x1 - 1].enemy == nullptr)
                                    {
                                        throw std::invalid_argument("There are no evils near wall!");
                                    }
                                    else
                                    {
                                        cout << "Your options are:" << endl;
                                        cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                        int a, b;
                                        cout << "Enter your choice to release: " << endl;
                                        while (!getNum(a))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        while (!getNum(b))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        if (a == x1 - 1 && b == y1)
                                        {
                                            auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                            int harm = info[1].second * info[2].second;
                                            it[x1 - 1].enemy->setDamage(harm);
                                            if(it[x1 - 1].enemy->getCurHealth() <= 0)
                                            {
                                                it[x1 - 1].enemy = nullptr;
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("Choose option only from available!");
                                        }
                                    }
                                }
                                else
                                {
                                    auto it = evil_table[y1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it[x1 + 1].enemy->setDamage(harm);
                                        if(it[x1 + 1].enemy->getCurHealth() <= 0)
                                        {
                                            it[x1 + 1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it[x1 - 1].enemy->setDamage(harm);
                                        if(it[x1 - 1].enemy->getCurHealth() <= 0)
                                        {
                                            it[x1 - 1].enemy = nullptr;
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (x1 == 0)
                            {
                                if (1 == game_field[y1].size())
                                {
                                    auto it = evil_table[y1 + 1];
                                    if(it[x1].enemy == nullptr)
                                    {
                                        throw std::invalid_argument("There are no evils near wall!");
                                    }
                                    else
                                    {
                                        cout << "Your options are:" << endl;
                                        cout << "x2: " << x1 << "y2: " << y1 + 1<< endl;
                                        int a, b;
                                        cout << "Enter your choice to release: " << endl;
                                        while (!getNum(a))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        while (!getNum(b))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        if (a == x1 && b == y1 + 1)
                                        {
                                            auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                            int harm = info[1].second * info[2].second;
                                            it[x1].enemy->setDamage(harm);
                                            if(it[x1].enemy->getCurHealth() <= 0)
                                            {
                                                it[x1].enemy = nullptr;
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("Choose option only from available!");
                                        }
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 + 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1<< endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1 + 1].enemy->setDamage(harm);
                                        if(it1[x1 + 1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1 + 1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it2[x1].enemy->setDamage(harm);
                                        if(it2[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it2[x1].enemy = nullptr;
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                            else
                            {
                                if(x1 == game_field[y1].size())
                                {
                                    auto it1 = evil_table[y1 + 1];
                                    auto it2 = evil_table[y1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 && b == y1 + 1)
                                    {
                                        if(it1[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1].enemy->setDamage(harm);
                                        if(it1[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it2[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it2[x1 - 1].enemy->setDamage(harm);
                                        if(it2[x1 - 1].enemy->getCurHealth() <= 0)
                                        {
                                            it2[x1 - 1].enemy = nullptr;
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 + 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1 + 1].enemy->setDamage(harm);
                                        if(it1[x1 + 1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1 + 1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it1[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1 - 1].enemy->setDamage(harm);
                                        if(it1[x1 - 1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1 - 1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it2[x1].enemy->setDamage(harm);
                                        if(it2[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it2[x1].enemy = nullptr;
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if (y1 == game_field.size())
                        {
                            if (x1 == 0)
                            {
                                if (1 == game_field[y1].size())
                                {
                                    auto it = evil_table[y1 - 1];
                                    if(it[x1].enemy == nullptr)
                                    {
                                        throw std::invalid_argument("There are no evils near wall!");
                                    }
                                    else
                                    {
                                        cout << "Your options are:" << endl;
                                        cout << "x2: " << x1 << "y2: " << y1 - 1<< endl;
                                        int a, b;
                                        cout << "Enter your choice to release: " << endl;
                                        while (!getNum(a))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        while (!getNum(b))
                                        {
                                            cout << "Enter the correct symbol!" << endl;
                                        }
                                        if (a == x1 && b == y1 - 1)
                                        {
                                            auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                            int harm = info[1].second * info[2].second;
                                            it[x1].enemy->setDamage(harm);
                                            if(it[x1].enemy->getCurHealth() <= 0)
                                            {
                                                it[x1].enemy = nullptr;
                                            }
                                        }
                                        else
                                        {
                                            throw std::invalid_argument("Choose option only from available!");
                                        }
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 - 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1 + 1].enemy->setDamage(harm);
                                        if(it1[x1 + 1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1 + 1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 && b == y1 - 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it2[x1].enemy->setDamage(harm);
                                        if(it2[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it2[x1].enemy = nullptr;
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                            else
                            {
                                if(x1 == game_field[y1].size())
                                {
                                    auto it1 = evil_table[y1- 1];
                                    auto it2 = evil_table[y1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 && b == y1 - 1)
                                    {
                                        if(it1[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1].enemy->setDamage(harm);
                                        if(it1[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it2[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it2[x1 - 1].enemy->setDamage(harm);
                                        if(it2[x1 - 1].enemy->getCurHealth() <= 0)
                                        {
                                            it2[x1 - 1].enemy = nullptr;
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 -1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1 + 1].enemy->setDamage(harm);
                                        if(it1[x1 + 1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1 + 1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it1[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1 - 1].enemy->setDamage(harm);
                                        if(it1[x1 - 1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1 - 1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 && b == y1 - 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it2[x1].enemy->setDamage(harm);
                                        if(it2[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it2[x1].enemy = nullptr;
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (x1 == 0)
                            {
                                if (1 == game_field[y1].size())
                                {
                                    auto it1 = evil_table[y1 - 1];
                                    auto it2 = evil_table[y1 + 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1<< endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 && b == y1 - 1)
                                    {
                                        if(it1[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1].enemy->setDamage(harm);
                                        if(it1[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it2[x1].enemy->setDamage(harm);
                                        if(it2[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it2[x1].enemy = nullptr;
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it3 = evil_table[y1 - 1];
                                    auto it2 = evil_table[y1 + 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1<< endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1<< endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1<< endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1 + 1].enemy->setDamage(harm);
                                        if(it1[x1 + 1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1 + 1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it2[x1].enemy->setDamage(harm);
                                        if(it2[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it2[x1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 && b == y1 - 1)
                                    {
                                        if(it3[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it3[x1].enemy->setDamage(harm);
                                        if(it3[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it3[x1].enemy = nullptr;
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                            else
                            {
                                if(x1 == game_field[y1].size())
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 + 1];
                                    auto it3 = evil_table[y1 - 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it2[x1].enemy->setDamage(harm);
                                        if(it2[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it2[x1].enemy = nullptr;
                                        }
                                    }
                                    if (a == x1 && b == y1 - 1)
                                    {
                                        if(it3[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it3[x1].enemy->setDamage(harm);
                                        if(it3[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it3[x1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it1[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1 - 1].enemy->setDamage(harm);
                                        if(it1[x1 - 1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1 - 1].enemy = nullptr;
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                                else
                                {
                                    auto it1 = evil_table[y1];
                                    auto it2 = evil_table[y1 + 1];
                                    auto it3 = evil_table[y1 - 1];
                                    cout << "Your options are:" << endl;
                                    cout << "x2: " << x1 + 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 - 1 << "y2: " << y1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 + 1 << endl;
                                    cout << "x2: " << x1 << "y2: " << y1 - 1 << endl;
                                    int a, b;
                                    cout << "Enter your choice to release: " << endl;
                                    while (!getNum(a))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    while (!getNum(b))
                                    {
                                        cout << "Enter the correct symbol!" << endl;
                                    }
                                    if (a == x1 + 1 && b == y1)
                                    {
                                        if(it1[x1 + 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1 + 1].enemy->setDamage(harm);
                                        if(it1[x1 + 1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1 + 1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 - 1 && b == y1)
                                    {
                                        if(it1[x1 - 1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it1[x1 - 1].enemy->setDamage(harm);
                                        if(it1[x1 - 1].enemy->getCurHealth() <= 0)
                                        {
                                            it1[x1 - 1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 && b == y1 + 1)
                                    {
                                        if(it2[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it2[x1].enemy->setDamage(harm);
                                        if(it2[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it2[x1].enemy = nullptr;
                                        }
                                    }
                                    else if(a == x1 && b == y1 - 1)
                                    {
                                        if(it3[x1].enemy == nullptr)
                                        {
                                            throw std::invalid_argument("There are no evils here!");
                                        }
                                        auto info = j->getTower()->T_getInfo()[j->getTower()->getLevel()];
                                        int harm = info[1].second * info[2].second;
                                        it3[x1].enemy->setDamage(harm);
                                        if(it3[x1].enemy->getCurHealth() <= 0)
                                        {
                                            it3[x1].enemy = nullptr;
                                        }
                                    }
                                    else
                                    {
                                        throw std::invalid_argument("Choose option only from available!");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return *this;
    }

    Landscape &Landscape::RepairWall(int k, int x1, int y1)
    {
        auto i = game_field.find(y1);
        if (i == game_field.end())
        {
            throw std::invalid_argument("Incorrect value of y");
        }
        else
        {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j)
            {
                if (j->getX() == x1)
                {
                    break;
                }
            }
            if (j == i->second.end())
            {
                throw std::invalid_argument("Incorrect value of x");
            } else
            {
                if (j->S_getInfo() != wall)
                {
                    throw std::invalid_argument("There are no wall on this square!");
                }
                else
                {
                    j->getWall()->Repair(k);
                }
            }
        }
        return *this;
    }

    Landscape &Landscape::RepairCastle(int k, int x1, int y1)
    {
        auto i = game_field.find(y1);
        if (i == game_field.end())
        {
            throw std::invalid_argument("Incorrect value of y");
        }
        else
        {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j)
            {
                if (j->getX() == x1)
                {
                    break;
                }
            }
            if (j == i->second.end())
            {
                throw std::invalid_argument("Incorrect value of x");
            } else
            {
                if (j->S_getInfo() != castle)
                {
                    throw std::invalid_argument("There are no castle on this square!");
                }
                else
                {
                    j->getCastle()->Repair(k);
                }
            }
        }
        return *this;
    }

    Landscape &Landscape::UpLevelOfTower(int x1, int y1)
    {
        auto i = game_field.find(y1);
        if (i == game_field.end())
        {
            throw std::invalid_argument("Incorrect value of y");
        }
        else
        {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j)
            {
                if (j->getX() == x1)
                {
                    break;
                }
            }
            if (j == i->second.end())
            {
                throw std::invalid_argument("Incorrect value of x");
            } else
            {
                if (j->S_getInfo() != tower)
                {
                    throw std::invalid_argument("There are no tower on this square!");
                }
                else
                {
                    j->getTower()->setLevel();
                }
            }
        }
        return *this;
    }

    Landscape &Landscape::UpLevelOfCastle(int x1, int y1)
    {
        auto i = game_field.find(y1);
        if (i == game_field.end())
        {
            throw std::invalid_argument("Incorrect value of y");
        }
        else
        {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j)
            {
                if (j->getX() == x1)
                {
                    break;
                }
            }
            if (j == i->second.end())
            {
                throw std::invalid_argument("Incorrect value of x");
            } else
            {
                if (j->S_getInfo() != castle)
                {
                    throw std::invalid_argument("There are no castle on this square!");
                }
                else
                {
                    j->getCastle()->UpLevel();
                }
            }
        }
        return *this;
    }

    Landscape &Landscape::RepairEvil(int x1, int y1)
    {
        auto i = evil_table.find(y1);
        if (i == evil_table.end())
        {
            throw std::invalid_argument("Incorrect value of y");
        }
        else
        {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j)
            {
                if (j->getX() == x1)
                {
                    break;
                }
            }
            if (j == i->second.end())
            {
                throw std::invalid_argument("Incorrect value of x");
            } else
            {
                if (j->enemy == nullptr)
                {
                    throw std::invalid_argument("There are no evil on this square!");
                }
                else
                {
                    j->enemy->Repair();
                }
            }
        }
        return *this;
    }

    int Landscape::getWallHealth(int x1, int y1)
    {
        auto i = game_field.find(y1);
        if (i == game_field.end())
        {
            throw std::invalid_argument("Incorrect value of y");
        }
        else
        {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j)
            {
                if (j->getX() == x1)
                {
                    break;
                }
            }
            if (j == i->second.end())
            {
                throw std::invalid_argument("Incorrect value of x");
            } else
            {
                if (j->S_getInfo() != wall)
                {
                    throw std::invalid_argument("There are no wall on this square!");
                }
                else
                {
                    return j->getWall()->WgetCE();
                }
            }
        }
    }

    int Landscape::getCastleHealth(int x1, int y1)
    {
        auto i = game_field.find(y1);
        if (i == game_field.end())
        {
            throw std::invalid_argument("Incorrect value of y");
        }
        else
        {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j)
            {
                if (j->getX() == x1)
                {
                    break;
                }
            }
            if (j == i->second.end())
            {
                throw std::invalid_argument("Incorrect value of x");
            } else
            {
                if (j->S_getInfo() != castle)
                {
                    throw std::invalid_argument("There are no wall on this square!");
                }
                else
                {
                    return j->getCastle()->CgetCE();
                }
            }
        }
    }

    int Landscape::getEvilHealth(int x1, int y1)
    {
        auto i = evil_table.find(y1);
        if (i == evil_table.end())
        {
            throw std::invalid_argument("Incorrect value of y");
        }
        else
        {
            auto j = i->second.begin();
            for (; j != i->second.end(); ++j)
            {
                if (j->getX() == x1)
                {
                    break;
                }
            }
            if (j == i->second.end())
            {
                throw std::invalid_argument("Incorrect value of x");
            } else
            {
                if (j->enemy == nullptr)
                {
                    throw std::invalid_argument("There are no evil on this square!");
                }
                else
                {
                    return j->enemy->getCurHealth();
                }
            }
        }
    }
}