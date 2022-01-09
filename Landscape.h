/*!
\file
\brief Заголовочный файл с описанием класса Ландшафт,являющегося главным создаваемым объектом программы

Данный файл содержит в себе описания членов и методов класса,
 используемых в основной программе
*/
#ifndef TOWERDEFENSEV2_LANDSCAPE_H
#define TOWERDEFENSEV2_LANDSCAPE_H
#include <map>
#include <vector>
#include "Evil.h"
#include "Tower.h"
#include "Wall.h"
#include "Lair.h"
#include "Castle.h"
#include "Square.h"
#include <iostream>
#include <algorithm>
using std::pair;
namespace TD
{
    /// Вспомогательная структура для таблицы расположения врагов
    struct Point
    {
        int x; ///< координата х таблицы расположения врагов
        Evil* enemy; ///< указатель на врага, находящегося в данной клетке поля
        /*!
        Пустой конструктор
        \param  не имеет параметров
        \return не имеет возвращаемого значения
        \throw не выбрасывает исключения
        */
        Point():x(0), enemy(nullptr){}
        /*!
        Инициализирующий конструктор
        \param X координата х таблицы расположения врагов
        \return не имеет возвращаемого значения
        \throw invalid_argument в случае отрицательного значения координаты
        */
        explicit Point(int X, Evil* enm = nullptr):enemy(enm)
        {
            if(X < 0)
                throw std::invalid_argument("Incorrect value of coordinate x");
            x = X;
        }
        /*!
        Получить координату клеткипо оси Х
        \param  не имеет параметров
        \return координату клетки
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int getX() const { return x;}
        /*!
        Получить тип врага в данной клетке
        \param  не имеет параметров
        \return индикатор тиипа врага
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int getEvil() const { return enemy->getTypeOfEvil();}
        /*!
        Перегруженный оператор сравнения
        \param dot1 объект класса Клетка
        \param dot2 объект класса Клетка
        \return меньше или нет координата по оси Х первого объекта относительного второго
        \throw не выбрасывает исключений
        */
        bool operator < (const Point& dot2) const { return getX() < dot2.getX();}
    };
    /*!
	\brief  Центральный класс
	\author Christian Shander
	\version 1.0
	\date декабрь 2021 года

	Главный объект программы, с которым связаны все остальные побочные объекты и классы,
     все ключевые действия в программе происходят именно с объектами этого класса
    */
    class Landscape
    {
    private:
        map <int, vector<Square>> game_field; ///< прямоугольное игровое поле
        map <int, vector<Point>> evil_table; ///< таблица расположения врагов
    public:
        /*!
        Пустой конструктор
        \param  не имеет параметров
        \return не имеет возвращаемого значения
        \throw не выбрасывает исключения
        */
        Landscape();
        /*!
        Инициализирующий конструктор
        \param field игровое поле
        \param table таблица расположения врагов
        \return не имеет возвращаемого значения
        \throw не выбрасывает исключения
        */
        Landscape(const map<int, vector<Square>>& field, const map <int, vector<Point>>& table);
        /*!
        Изменить размеры игрового поля
        \param type тип ландшафта клетки
        \param x координата клетки поля по оси Х
        \param y координата клетки поля по оси Y
        \return ссылка на измененный объект класса
        */
        Landscape& AddSquareToField(int x, int y, int type);
        /*!
        Изменить тип ландшафта клетки игрового поля
        \param type тип ландшафта клетки
        \param x координата клетки поля по оси Х
        \param y координата клетки поля по оси Y
        \return ссылка на измененный объект класса
        \throw invalid_argument в случае некорретных значений координат и типа клетки
        */
        Landscape& setTypeOfSquare(int x, int y, int type);
        /*!
        Сделать очередной ход врагом
        \param x координата врага по оси Х
        \param y координата врага по оси Y
        \return ссылка на измененный объект класса
        \throw invalid_argument в случае некорретных значений координат
        */
        Landscape& MakeMove(int x1, int y1);
        /*!
        получить размеры игрового поля
        \param out ссылка на стандартный поток вывода
        \return ссылка на измененный поток вывода
        \throw не выбрасывает исключений
        */
        std::ostream& getSizeOfField(std::ostream& out);
        /*!
        Получить тип клетки игрового поля
        \param x координата поля по оси Х
        \param y координата поля по оси Y
        \return тип ландшафта клетки
        \throw invalid_argument в случае некорретных значений координат
        */
        string getTypeOfSquare(int x, int y);
        /*!
        выпустить очередного врага из логова
        \param field игровое поле
        \param x координата логова по оси Х
        \param y координата логова по оси Y
        \return ссылка на измененный объект класса
        */
        Landscape& ReleaseEvil(int x1, int y1);
        /*!
        выпустить очередного врага из логова по переданному времени выхода
        \param field игровое поле
        \param time массив компонентов времени выхода
        \return ссылка на измененный объект класса
        */
        Landscape& ReleaseEvilByTime(int x1, int y1, int h, int m, int s);
        Landscape& DamageWall(int x1, int y1);
        Landscape& DamageCastle(int x1, int y1);
        Landscape& BeatEvil(int x1, int y1);
        Landscape& RepairWall(int k, int x1, int y1);
        Landscape& RepairCastle(int k, int x1, int y1);
        Landscape& RepairEvil(int x1, int y1);
        Landscape& UpLevelOfTower(int x1, int y1);
        Landscape& UpLevelOfCastle(int x1, int y1);
        [[nodiscard]] map <int, vector<Square>> getField() const {return game_field;}
        [[nodiscard]] map <int, vector<Point>> getTable() const {return evil_table;}
        int getWallHealth(int x1, int y1);
        int getCastleHealth(int x1, int y1);
        int getEvilHealth(int x1, int y1);
    };
}
#endif //TOWERDEFENSEV2_LANDSCAPE_H
