/*!
\file
\brief Заголовочный файл с описанием класса Стена,являющегося одним из типов ландшафта

Данный файл содержит в себе описания членов и методов класса,
 используемых в основной программе
*/
#ifndef TOWERDEFENSEV2_WALL_H
#define TOWERDEFENSEV2_WALL_H
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
    class Wall
    {
    private:
        int max_endurance;  ///< максимальная прочность стены
        int W_cur_endurance; ///< текущая прочность стены
    public:
        /*!
        Пустой конструктор
        \param  не имеет параметров
        \return не имеет возвращаемого значения
        \throw не выбрасывает исключения
        */
        explicit Wall(): W_cur_endurance(100), max_endurance(100){}
        /*!
        Инициализирующий конструктор
        \param me максимальная прочность стены
        \return не имеет возвращаемого значения
        \throw invalid_argument в случае некорретного значения прочности
        */
        explicit Wall(int me);
        /*!
        получить максимальную прочность стены
        \param не имеет параметров
        \return максимальная прочность
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int getME() const {return max_endurance;}
        /*!
        получить текущую прочность стены
        \param не имеет параметров
        \return текущую прочность
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int WgetCE() const {return W_cur_endurance;}
        /*!
        Нанести урон стене
        \param harm количество наносимого урона
        \return ссылку на измененый объект класса
        \throw invalid_argument в случае отрицательного значения урона
        */
        Wall& Damage(int harm);
        /*!
        Отремонтировать стену
        \param x процент повышения прочности
        \return ссылку на измененный объект класса
        \throw invalid_argument в случае отрицательного значения процента либо превышения уровня максимальной прочности
        */
        Wall& Repair(int x);
    };
}
#endif //TOWERDEFENSEV2_WALL_H
