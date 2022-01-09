#include "gtest/gtest.h"
#include "../Wall.h"
#include "../Wall.cpp"
#include "../Tower.h"
#include "../Tower.cpp"
#include "../Castle.h"
#include "../Castle.cpp"
#include "../Lair.h"
#include "../Lair.cpp"
#include "../Evil.h"
#include "../Evil.cpp"
#include "../Square.h"
#include "../Square.cpp"
#include "../Landscape.h"
#include "../Landscape.cpp"
using namespace TD;

TEST(WallConctructor, DefaultConstructor)
{
    Wall a1;
    ASSERT_EQ(100, a1.getME());
    ASSERT_EQ(100, a1.WgetCE());
}

TEST(WallConctructor, InitConstructor)
{
    Wall a1(50);
    ASSERT_EQ(50, a1.getME());
    ASSERT_EQ(50, a1.WgetCE());
}

TEST(WallConctructor, TestException)
{
    ASSERT_ANY_THROW(Wall(-2));
    ASSERT_ANY_THROW(Wall(0));
}

TEST(WallConctructor, Setters)
{
    Wall a1;
    a1.Damage(0);
    ASSERT_EQ(100, a1.WgetCE());
    a1.Damage(50);
    ASSERT_EQ(50, a1.WgetCE());
    ASSERT_ANY_THROW(a1.Damage(-10));
    a1.Repair(50);
    ASSERT_EQ(75, a1.WgetCE());
    ASSERT_ANY_THROW(a1.Repair(-5));
    ASSERT_ANY_THROW(a1.Repair(75));
}

TEST(TowerConctructor, DefaultConstructor)
{
    Tower a1;
    ASSERT_EQ(1, a1.getLevel());
    map <int, vector<pair<string, int>>> m1;
    vector<pair<string, int>> v1 = {{"Range", 3}, {"Damage", 2}, {"Rate", 5}, {"Cost", 5}};
    for(int i = 1; i <= 5; ++i)
    {
        m1[i] = v1;
        for(auto j : v1)
        {
            j.second += 2;
        }
    }
    map <int, vector<pair<string, int>>> m2 = a1.T_getInfo();
    for(int i = 1; i <= 5; ++i)
    {
        ASSERT_EQ(m1[i], m2[i]);
    }
}

TEST(TowerConctructor, InitConstructor)
{
    map <int, vector<pair<string, int>>> m1;
    vector<pair<string, int>> v1 = {{"Range", 3}, {"Damage", 2}, {"Rate", 5}, {"Cost", 5}};
    for(int i = 1; i <= 5; ++i)
    {
        m1[i] = v1;
        for(auto j : v1)
        {
            j.second += 2;
        }
    }
    Tower a1(m1);
    ASSERT_EQ(5, a1.getLevel());
    ASSERT_EQ(m1, a1.T_getInfo());
    Tower a2(m1, 3);
    ASSERT_EQ(3, a2.getLevel());
    ASSERT_EQ(m1, a2.T_getInfo());
}

TEST(TowerConctructor, TestException)
{
    map <int, vector<pair<string, int>>> m1;
    vector<pair<string, int>> v1 = {{"Range", 3}, {"Damage", 2}, {"Rate", 5}, {"Cost", 5}};
    for(int i = 1; i <= 5; ++i)
    {
        m1[i] = v1;
        for(auto j : v1)
        {
            j.second += 2;
        }
    }
    ASSERT_ANY_THROW(Tower(m1, 10));
    ASSERT_ANY_THROW(Tower(m1, -5));
}

TEST(TowerConctructor, Setters)
{
    Tower a1;
    a1.setLevel();
    ASSERT_EQ(2, a1.getLevel());
    map <int, vector<pair<string, int>>> m1;
    vector<pair<string, int>> v1 = {{"Range", 3}, {"Damage", 2}, {"Rate", 5}, {"Cost", 5}};
    for(int i = 1; i <= 5; ++i)
    {
        m1[i] = v1;
        for(auto j : v1)
        {
            j.second += 2;
        }
    }
    Tower a2(m1);
    ASSERT_ANY_THROW(a2.setLevel());
}

TEST(CastleConctructor, DefaultConstructor)
{
    Castle a1;
    ASSERT_EQ("Eyes of dragon", a1.getName());
    ASSERT_EQ(1, a1.getLvl());
    ASSERT_EQ(200, a1.CgetCE());
    map <int, vector<pair<string, int>>> m1;
    vector<pair<string, int>> v1 = {{"Profitability", 10}, {"Max Endurance", 200}, {"Repair Speed", 10}, {"Cost", 20}};
    for(int i = 1; i <= 5; ++i)
    {
        m1[i] = v1;
        for(auto j : v1)
        {
            j.second += 10;
        }
    }
    ASSERT_EQ(m1, a1.getInfo());
}

TEST(CastleConctructor, InitConstructor)
{
    map <int, vector<pair<string, int>>> m1;
    vector<pair<string, int>> v1 = {{"Profitability", 10}, {"Max Endurance", 200}, {"Repair Speed", 10}, {"Cost", 20}};
    for(int i = 1; i <= 5; ++i)
    {
        m1[i] = v1;
        for(auto j : v1)
        {
            j.second += 10;
        }
    }
    Castle a1("abc", m1, 3);
    ASSERT_EQ("abc", a1.getName());
    ASSERT_EQ(3, a1.getLvl());
    ASSERT_EQ(m1, a1.getInfo());
    ASSERT_EQ(200, a1.CgetCE());
}

TEST(CastleConctructor, TestException)
{
    map <int, vector<pair<string, int>>> m1;
    vector<pair<string, int>> v1 = {{"Profitability", 10}, {"Max Endurance", 200}, {"Repair Speed", 10}, {"Cost", 20}};
    for(int i = 1; i <= 5; ++i)
    {
        m1[i] = v1;
        for(auto j : v1)
        {
            j.second += 10;
        }
    }
    ASSERT_ANY_THROW(Castle("abc",m1, -5));
    ASSERT_ANY_THROW(Castle("abc", m1, 10));
}

TEST(CastleConctructor, Setters)
{
    Castle a1;
    a1.UpLevel();
    ASSERT_EQ(2, a1.getLvl());
    a1.UpLevel();
    a1.UpLevel();
    a1.UpLevel();
    ASSERT_ANY_THROW(a1.UpLevel());
    a1.setDamage(100);
    ASSERT_EQ(100, a1.CgetCE());
    ASSERT_ANY_THROW(a1.setDamage(-50));
    a1.Repair(50);
    ASSERT_EQ(160, a1.CgetCE());
    ASSERT_ANY_THROW(a1.Repair(-10));
    ASSERT_ANY_THROW(a1.Repair(100));
}

TEST(LairConctructor, DefaultConstructor)
{
    Lair a1;
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
    auto iter = dop.cbegin();
    int i = 0;
    for(; iter != dop.cend(); ++iter)
    {
        ASSERT_EQ(iter->hours, a1.getLI()[i].hours);
        ASSERT_EQ(iter->minutes, a1.getLI()[i].minutes);
        ASSERT_EQ(iter->seconds, a1.getLI()[i].seconds);
        ASSERT_EQ(iter->ind, a1.getLI()[i].ind);
        ++i;
    }
}

TEST(LairConctructor, InitConstructor)
{
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
    Lair a2(dop);
    auto iter = dop.cbegin();
    int i = 0;
    for(; iter != dop.cend(); ++iter)
    {
        ASSERT_EQ(iter->hours, a2.getLI()[i].hours);
        ASSERT_EQ(iter->minutes, a2.getLI()[i].minutes);
        ASSERT_EQ(iter->seconds, a2.getLI()[i].seconds);
        ASSERT_EQ(iter->ind, a2.getLI()[i].ind);
        ++i;
    }
}

TEST(LairConctructor, Setters)
{
    vector<EvilByTime> dop;
    EvilByTime evil1(1, 1, 1, 1, 0);
    EvilByTime evil2(1, 2, 2, 2, 0);
    dop.push_back(evil1);
    dop.push_back(evil2);
    Lair a2(dop);
    a2.CrossEvil();
    ASSERT_EQ(1, a2.getLI()[0].ind);
    a2.CrossEvilByTime(2, 2, 2);
    ASSERT_EQ(1, a2.getLI()[1].ind);
    ASSERT_ANY_THROW(a2.CrossEvil());
    ASSERT_ANY_THROW(a2.CrossEvilByTime(2, 2, 3));
}

TEST(EvilConctructor, DefaultConstructor)
{
    Evil a1;
    ASSERT_EQ("Common enemy", a1.getName());
    ASSERT_EQ(10, a1.getMaxHealth());
    ASSERT_EQ(10, a1.getCurHealth());
    ASSERT_EQ(3, a1.getRegenSpeed());
    ASSERT_EQ(5, a1.getMoveSpeed());
    ASSERT_EQ(1, a1.getDamageIndex());
    ASSERT_EQ(false, a1.getIsHero());
    ASSERT_EQ(1, a1.getTypeOfEvil());
}

TEST(EvilConctructor, TestException)
{
    ASSERT_ANY_THROW(Evil(-2));
    ASSERT_ANY_THROW(Evil(5));
    ASSERT_ANY_THROW(Evil(2, 5));
}

TEST(EvilConctructor, Setters)
{
    Evil a1;
    a1.setMH(3);
    ASSERT_EQ(13, a1.getMaxHealth());
    a1.setCH(2);
    ASSERT_EQ(12, a1.getCurHealth());
    ASSERT_ANY_THROW(a1.setCH(5));
    a1.setRS(3);
    ASSERT_EQ(6, a1.getRegenSpeed());
    a1.setMS(3);
    ASSERT_EQ(8, a1.getMoveSpeed());
    a1.setDI(1);
    ASSERT_EQ(2, a1.getDamageIndex());
    a1.setIsHero();
    ASSERT_EQ(1, a1.getIsHero());
    ASSERT_ANY_THROW(a1.setIsHero());
    a1.setDamage(5);
    ASSERT_EQ(7, a1.getCurHealth());
    ASSERT_ANY_THROW(a1.setDamage(-2));
    a1.Repair();
    ASSERT_EQ(13, a1.getCurHealth());
    ASSERT_ANY_THROW(a1.Repair());
}

TEST(SquareConctructor, DefaultConstructor)
{
    Square a1;
    ASSERT_EQ(0, a1.getX());
    ASSERT_EQ(2, a1.S_getInfo());
    ASSERT_EQ(nullptr, a1.getWall());
    ASSERT_EQ(nullptr, a1.getCastle());
    ASSERT_EQ(nullptr, a1.getLair());
    ASSERT_EQ(nullptr, a1.getTower());
}

TEST(SquareConctructor, InitConstructor)
{
    Square a1(1, 3);
    ASSERT_EQ(1, a1.getX());
    ASSERT_EQ(2, a1.S_getInfo());
    ASSERT_EQ(nullptr, a1.getWall());
    ASSERT_EQ(nullptr, a1.getCastle());
    ASSERT_EQ(nullptr, a1.getLair());
    ASSERT_EQ(nullptr, a1.getTower());
}

TEST(SquareConctructor, TestException)
{
    ASSERT_ANY_THROW(Square(-2, 1));
    ASSERT_ANY_THROW(Square(2, 0));
    ASSERT_ANY_THROW(Square(2, 9));
}

TEST(SquareConctructor, Setters)
{
    Square a1(3, 2);
    ASSERT_ANY_THROW(a1.setTower());
    ASSERT_ANY_THROW(a1.setWall());
    a1.setOthers(3);
    a1.setWall();
    ASSERT_ANY_THROW(a1.setWall());
    ASSERT_ANY_THROW(a1.setLair());
    ASSERT_ANY_THROW(a1.setCastle());
    ASSERT_ANY_THROW(a1.setOthers(3));
    Square a2(2, 2);
    a2.setCastle();
    ASSERT_ANY_THROW(a2.setWall());
    ASSERT_ANY_THROW(a2.setLair());
    ASSERT_ANY_THROW(a2.setCastle());
    ASSERT_EQ(nullptr, a2.getWall());
    ASSERT_EQ(nullptr, a2.getLair());
    ASSERT_EQ(nullptr, a2.getTower());
    ASSERT_EQ(true, a2 < a1);

}

TEST(LandscapeConctructor, DefaultConstructor)
{
    Landscape a1;
    map <int, vector<Square>> dop1;
    map <int, vector<Point>> dop2;
    vector<Square> v1;
    vector<Point> p1;
    v1.emplace_back(Square(0, 7));
    v1.emplace_back(Square(1, 3));
    p1.emplace_back(Point());
    p1.emplace_back(Point(1));
    vector<Square> v2;
    vector<Point> p2;
    v2.emplace_back(Square(0, 2));
    v2.emplace_back(Square(1, 6));
    p2.emplace_back(Point());
    p2.emplace_back(Point(1));
    dop1.insert(std::make_pair(1, v1));
    dop1.insert(std::make_pair(2, v2));
    dop2.insert((std::make_pair(1, p1)));
    dop2.insert((std::make_pair(2, p2)));
    auto extra = dop1.cbegin();
    ASSERT_EQ(extra->first, 1);
    ASSERT_EQ(extra->second[0].getX(), 0);
    ASSERT_EQ(extra->second[1].getX(), 1);
    auto extra1 = dop2.cbegin();
    ASSERT_EQ(extra->first, 1);
    ASSERT_EQ(extra->second[0].getX(), 0);
    ASSERT_EQ(extra->second[1].getX(), 1);
}

TEST(LandscapeConctructor, Setters)
{
    Landscape a1;
    ASSERT_EQ("Lair", a1.getTypeOfSquare(0, 1));
    ASSERT_EQ("Plain", a1.getTypeOfSquare(1, 1));
    ASSERT_EQ("Mountain", a1.getTypeOfSquare(0, 2));
    ASSERT_EQ("Castle", a1.getTypeOfSquare(1, 2));
    ASSERT_ANY_THROW(a1.getTypeOfSquare(0, 5));
    ASSERT_ANY_THROW(a1.getTypeOfSquare(4, 1));
    a1.setTypeOfSquare(1, 1, 4);
    ASSERT_EQ("Wall", a1.getTypeOfSquare(1, 1));
    ASSERT_ANY_THROW(a1.setTypeOfSquare(0, 2, 5));
    ASSERT_ANY_THROW(a1.setTypeOfSquare(9, 2, 3));
    ASSERT_ANY_THROW(a1.setTypeOfSquare(0, 5, 5));
    ASSERT_ANY_THROW(a1.setTypeOfSquare(0, 2, 11));
    ASSERT_ANY_THROW(a1.AddSquareToField(1, 1, 3));
    a1.AddSquareToField(2, 1, 3);
    ASSERT_EQ("Plain", a1.getTypeOfSquare(2, 1));
    ASSERT_EQ("Plain", a1.getTypeOfSquare(2, 2));
    a1.AddSquareToField(1, 3, 1);
    ASSERT_EQ("Reservoir", a1.getTypeOfSquare(1, 3));
    ASSERT_EQ("Plain", a1.getTypeOfSquare(0, 3));
    ASSERT_EQ("Plain", a1.getTypeOfSquare(2, 3));
    a1.AddSquareToField(3, 4, 2);
    ASSERT_EQ("Plain", a1.getTypeOfSquare(3, 1));
    ASSERT_EQ("Plain", a1.getTypeOfSquare(3, 2));
    ASSERT_EQ("Plain", a1.getTypeOfSquare(3, 3));
    ASSERT_EQ("Mountain", a1.getTypeOfSquare(3, 4));
    ASSERT_EQ("Plain", a1.getTypeOfSquare(2, 4));
    ASSERT_EQ("Plain", a1.getTypeOfSquare(1, 4));
    ASSERT_EQ("Plain", a1.getTypeOfSquare(0, 4));
    ASSERT_ANY_THROW(a1.AddSquareToField(0, 1, 1));
    ASSERT_ANY_THROW(a1.MakeMove(10, 2));
    ASSERT_ANY_THROW(a1.ReleaseEvil(2, 10));
    ASSERT_ANY_THROW(a1.ReleaseEvil(10, 2));
    ASSERT_ANY_THROW(a1.MakeMove(2, 10));
    ASSERT_ANY_THROW(a1.ReleaseEvilByTime(10, 2, 1, 1, 1));
    ASSERT_ANY_THROW(a1.ReleaseEvilByTime(2, 10, 1, 1, 1));
    ASSERT_ANY_THROW(a1.DamageWall(10, 2));
    ASSERT_ANY_THROW(a1.DamageWall(2, 10));
    ASSERT_ANY_THROW(a1.DamageCastle(10, 2));
    ASSERT_ANY_THROW(a1.DamageCastle(2, 10));
    ASSERT_ANY_THROW(a1.BeatEvil(10, 2));
    ASSERT_ANY_THROW(a1.BeatEvil(2, 10));
    ASSERT_ANY_THROW(a1.RepairWall(3, 10, 2));
    ASSERT_ANY_THROW(a1.RepairWall(3, 2, 10));
    ASSERT_ANY_THROW(a1.RepairCastle(3, 10, 2));
    ASSERT_ANY_THROW(a1.RepairCastle(3, 2, 10));
    ASSERT_ANY_THROW(a1.RepairEvil(10, 2));
    ASSERT_ANY_THROW(a1.RepairEvil(2, 10));
    ASSERT_ANY_THROW(a1.UpLevelOfCastle(10, 2));
    ASSERT_ANY_THROW(a1.UpLevelOfCastle(2, 10));
    ASSERT_ANY_THROW(a1.UpLevelOfTower(10, 2));
    ASSERT_ANY_THROW(a1.UpLevelOfTower(2, 10));
}





