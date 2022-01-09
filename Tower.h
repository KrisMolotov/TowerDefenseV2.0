/*!
\file
\brief Заголовочный файл с описанием класса Башня,являющегося одним из типов ландшафта

Данный файл содержит в себе описания членов и методов класса,
 используемых в основной программе
*/
#ifndef TOWERDEFENSEV2_TOWER_H
#define TOWERDEFENSEV2_TOWER_H
//#include "Landscape.h"
#include <map>
#include <vector>
#include <string>
#include <utility>
using std::map;
using std::vector;
using std::pair;
using std::string;
namespace TD {
    /*!
	\brief  Самостоятельный класс
	\author Christian Shander
	\version 1.0
	\date декабрь 2021 года

	Класс, который композиционно связан с классом Клетка игрового поля,
    управляйемый им с помощью динамического выделения памяти
    */
    class Tower{
    private:
        int level; ///< уровень башни
        map<int, vector<pair<string, int>>> tower_info; ///< таблица характеристик башни
    public:
        /*!
        Пустой конструктор
        \param  не имеет параметров
        \return не имеет возвращаемого значения
        \throw не выбрасывает исключения
        */
        Tower();
        /*!
        Инициализирующий конструктор
        \param info таблица характеристик
        \param lvl уровень башни
        \return не имеет возвращаемого значения
        \throw invalid_argument в случае некорретного значения уровня
        */
        explicit Tower(const map<int, vector<pair<string, int>>> &info, int lvl = 5);

        /*!
        получить уровень башни
        \param не имеет параметров
        \return уровень башни
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int getLevel() const { return level; }

        /*!
        получить таблицу характеристик башни
        \param не имеет параметров
        \return таблицу характеристик башни
        \throw не выбрасывает исключения
        */
        [[nodiscard]] map<int, vector<pair<string, int>>> T_getInfo() const { return tower_info; }

        /*!
        повысить уровень башни
        \param не имеет параметров
        \return ссылку на измененный объект класса
        \throw invalid_argument в случае попытки повысить максимальный уровень башни
        */
        Tower& setLevel();
        /*!
        Нанести урон ближайшему врагу
        \param damage значение наносимого урона
        \param x координата ячейки с врагом в таблице расположения по оси Х
        \param y координата ячейки с врагом в таблице расположения по оси У
        \return не имеет возвращаемого значения
        \throw invalid_argument в случае некорректных значений любого из аргументов
        */
    };
}
#endif //TOWERDEFENSEV2_TOWER_H
