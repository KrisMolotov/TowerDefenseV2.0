/*!
\file
\brief Заголовочный файл с описанием класса Клетка,являющегося одним из частей игрового поля

Данный файл содержит в себе описания членов и методов класса,
 используемых в основной программе
*/
#ifndef TOWERDEFENSEV2_SQUARE_H
#define TOWERDEFENSEV2_SQUARE_H
#include "Tower.h"
#include "Wall.h"
#include "Lair.h"
#include "Castle.h"
namespace TD
{
    /// Возможные типы ландшафта
    enum TypeL{
        reservoir, ///< водоем
        mountain, ///< гора
        plain, ///< равнина
        wall, ///< стена
        tower, ///< башня
        castle, ///< замок
        lair ///< логово
    };
    /*!
	\brief  Самостоятельный класс
	\author Christian Shander
	\version 1.0
	\date декабрь 2021 года

	Класс, который композиционно связан с классом Ландшафт игрового поля и
    является его элементарной структурной единицей
    */
    class Square{
    private:
        int x; ///< координата х клетки игрового поля
        TypeL info; ///< тип ландшафта данной клетки поля
        Tower* tr; ///< указатель на объект класса Башня
        Wall* wl; ///< указатель на объект класса Стена
        Lair* lr; ///< указатель на объект класса Логово
        Castle* cl; ///< указатель на объект класса Замок
    public:
        /*!
        пустой конструктор
        \param  не имеет параметров
        \return не имеет возвращаемого значения
        \throw не выбрасывает исключения
        */
        Square(): x(0), info(plain), tr(nullptr), wl(nullptr), lr(nullptr), cl(nullptr){}
        /*!
        Инициализирующий конструктор 1
        \param  Х координата клетки игрового поля по оси Х
        \param  ind тип ландшафта
        \return не имеет возвращаемого значения
        \throw invalid_argument В случае некорретно переданных координаты и типа клетки
        */
        Square(int X, int ind);
        /*!
        Деструктор
        \param  не имеет параметров
        \return не возвращает
        \throw не выбрасывает исключения
        */
        [[nodiscard]] Wall* getWall() const {return wl;}
        [[nodiscard]] Tower* getTower() const {return tr;}
        [[nodiscard]] Lair* getLair() const {return lr;}
        [[nodiscard]] Castle*getCastle() const {return cl;}
        /*!
        Получить координату клеткипо оси Х
        \param  не имеет параметров
        \return координату клетки
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int getX() const { return x; }
        /*!
        получить тип ландшафта клетки
        \param  не имеет параметров
        \return тип ландшафта
        \throw не выбрасывает исключения
        */
        [[nodiscard]] TypeL S_getInfo() const {return info;}
        /*!
        установить на клетку Башню
        \param  не имеет параметров
        \return ссылку на измененный объект класса
        \throw invalid_argument в случае, если башня уже установлена
        */
        Square &setTower();
        /*!
        установить на клетку Стену
        \param  me опциональный параметр, максимальная прочность стены
        \return ссылку на измененный объект класса
        \throw invalid_argument в случае, если прочность стены > 0
        */
        Square &setWall(int me = 100);
        /*!
        установить на клетку Логово
        \param  не имеет параметров
        \return ссылку на измененный объект класса
        \throw invalid_argument в случае, если логово уже установлено
        */
        Square &setLair();
        /*!
        установить на клетку Замок
        \param  не имеет параметров
        \return ссылку на измененный объект класса
        \throw invalid_argument в случае, если прочность замка > 0
        */
        Square &setCastle();
        /*!
        установить на клетку базовый тип ланшдафта
        \param  не имеет параметров
        \return ссылку на измененный объект класса
        \throw invalid_argument в случае, если передается не базовый тип клетки
        */
        Square& setOthers(int ind);
        /*!
        Перегруженный оператор сравнения
        \param dot1 объект класса Клетка
        \param dot2 объект класса Клетка
        \return меньше или нет координата по оси Х первого объекта относительного второго
        \throw не выбрасывает исключений
        */
        bool operator < (const Square& dot2) const {return getX() < dot2.getX();}
    };
}
#endif //TOWERDEFENSEV2_SQUARE_H
