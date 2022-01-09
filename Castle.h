/*!
\file
\brief Заголовочный файл с описанием класса Замок,являющегося одним из типов ландшафта

Данный файл содержит в себе описания членов и методов класса,
 используемых в основной программе
*/
#ifndef TOWERDEFENSEV2_CASTLE_H
#define TOWERDEFENSEV2_CASTLE_H
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "Map.h"
using std::pair;
using std::map;
using std::vector;
using std::string;
namespace TD
{
    /*!
	\brief  Самостоятельный класс
	\author Christian Shander
	\version 1.0
	\date декабрь 2021 года

	Класс, который композиционно связан с классом Клетка игрового поля,
    управляйемый им с помощью динамического выделения памяти
    */
    class Castle
    {
    private:
        string name; ///< Название замка
        int level; ///< Уровень замка
        int C_cur_endurance; ///< Текущая прочность замка
        map <int, vector<pair<string, int>>> castle_info; ///< Таблица характеристик замка
    public:
        /*!
        Пустой конструктор
        \param  не имеет параметров
        \return не имеет возвращаемого значения
        \throw не выбрасывает исключения
        */
        Castle();
        /*!
        Инициализирующий конструктор
        \param nm название замка
        \param ci таблица характеристик
        \param lvl уровень замка
        \return не имеет возвращаемого значения
        \throw invalid_argument в случае некорретного значения уровня
        */
        Castle(const string& nm, const map <int, vector<pair<string, int>>>& ci, int lvl = 1);
        /*!
        получить название замка
        \param не имеет параметров
        \return название замка
        \throw не выбрасывает исключения
        */
        [[nodiscard]] string getName() const {return name;}
        /*!
        получить уровень замка
        \param не имеет параметров
        \return уровень замка
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int getLvl() const {return level;}
        /*!
        получить текущую прочность замка
        \param не имеет параметров
        \return текущая прочность
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int CgetCE() const {return C_cur_endurance;}
        /*!
        получить таблицу характеристик замка
        \param не имеет параметров
        \return таблица характеристик
        \throw не выбрасывает исключения
        */
        [[nodiscard]] map <int, vector<pair<string, int>>> getInfo() {return castle_info;}
        /*!
        повысить уровень замка
        \param не имеет параметров
        \return ссылку на измененный объект класса
        \throw invalid_argument в случае попытки повышения максимального уровня
        */
        Castle& UpLevel();
        /*!
        нанести урон замку
        \param harm количество урона
        \return ссылку на измененный объект класса
        \throw invalid_argument в случае отрицательного значения урона
        */
        Castle& setDamage(int harm);
        Castle& Repair(int x);
    };

}
#endif //TOWERDEFENSEV2_CASTLE_H
