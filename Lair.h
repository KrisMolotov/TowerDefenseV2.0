/*!
\file
\brief Заголовочный файл с описанием класса Логово,являющегося одним из типов ландшафта

Данный файл содержит в себе описания членов и методов класса,
 используемых в основной программе
*/
#ifndef TOWERDEFENSEV2_LAIR_H
#define TOWERDEFENSEV2_LAIR_H
#include "Evil.h"
#include <vector>
using std::vector;
namespace TD
{
    /// Вспомогательная структура - ячейка таблицы описателей врагов
    struct EvilByTime
    {
        Evil enemy; ///< описатель врага
        int hours; ///< время выхода врага из логова в часах
        int minutes; ///< время выхода врага из логова в минутах
        int seconds; ///< время выхода врага из логова в секундах
        int ind; ///< индикатор того, выпущен враг из логова или еще нет
        EvilByTime(int type, int h, int m, int s, int ih):hours(h), minutes(m), seconds(s), ind(0), enemy(type, ih){}
    };
    /*!
	\brief  Самостоятельный класс
	\author Christian Shander
	\version 1.0
	\date декабрь 2021 года

	Класс, который композиционно связан с классом Клетка игрового поля,
    управляйемый им с помощью динамического выделения памяти
    */
    class Lair
    {
    private:
        vector<EvilByTime> lair_info; ///< таблица описателей врагов и времени их выхода
    public:
        /*!
        Пустой конструктор
        \param  не имеет параметров
        \return не имеет возвращаемого значения
        \throw не выбрасывает исключения
        */
        Lair();
        /*!
        Инициализирующий конструктор
        \param  info таблица описателей врагов и времени выхода
        \return не имеет возвращаемого значения
        \throw invalid_argument в случае отрицательных значений времен и некорретных индикаторов
        */
        explicit Lair(const vector<EvilByTime>& info);
        /*!
        получить таблицу описателей врагов и времени выхода
        \param не имеет параметров
        \return таблица описателей и времени
        \throw не выбрасывает исключения
        */
        vector<EvilByTime> getLI() {return lair_info;}
        Lair& CrossEvil();
        Evil& getEvilFromLair();
        Lair& CrossEvilByTime(int h, int m, int s);
        Evil& getEvilFromLairByTime(int h, int m, int s);
    };
}
#endif //TOWERDEFENSEV2_LAIR_H
