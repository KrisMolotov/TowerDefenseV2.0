/*!
\file
\brief Заголовочный файл с описанием класса Враг,являющегося общим для всех дочерних разновидностей врагов

Данный файл содержит в себе описания членов и методов класса,
 используемых в основной программе
*/
#ifndef TOWERDEFENSEV2_EVIL_H
#define TOWERDEFENSEV2_EVIL_H
#include <string>
#include <map>
using std::map;
using std::string;
namespace TD
{
    /// Возможные типы врагов
    enum TypeE{
        light, ///< Легкая артиллерия
        heavy, ///< Тяжелая артиллерия
        aviation ///< Авиация
    };
    /*!
	\brief  Родительский абстрактный класс
	\author Christian Shander
	\version 1.0
	\date Декабрь 2021 года

	Родительский класс,от которого наследуются три дочерних класса
    и переопределяют все его методы
    */
    class Evil
    {
    private:
        TypeE evil_info; ///< Тип врага
        string name; ///< Имя врага
        int max_health; ///< Максимальное здоровье
        int cur_health; ///< Текущее здоровье
        int regen_speed; ///< Скорость регенерации
        int move_speed; ///< Скорость перемещения
        int damage_index; ///< Коэффициент урона
        int is_hero; ///< индикатор того, является ли враг героем
        map<string, int> aura; ///< список аур, повышающих характеристики героев
    public:
        /*!
        Пустой конструктор + инициализирующий конструктор 1
        \param  info опциональный параметр, тип героя
        \return не имеет возвращаемого значения
        \throw invalid_argument В случае отрицательного значения типа врага
        */
        explicit Evil(int info = 1, int ih = 0); // иниц. конструктор 1
        /*!
        Инициализирующий конструктор 2
        \param nm имя героя
        \param mh максимальное здоровье врага
        \param rs скорость регенерации здоровья
        \param ms скорость передвижения врага
        \param di коэффициент урона
        \param  info тип героя
        \return не имеет возвращаемого значения
        \throw std::invalid_argument В случае некорретно переданных параметров
        */
        Evil(int ih, const map<string, int>& au, string nm, int mh, int rs, int ms, int di, int info); // иниц. конструктор 2
        /*!
        получить имя врага
        \param  не имеет параметров
        \return имя врага
        \throw не выбрасывает исключения
        */
        [[nodiscard]] string getName() const {return name;}
        /*!
        получить максимальное здоровье врага
        \param  не имеет параметров
        \return максимальное здоровье
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int getMaxHealth() const {return max_health;}
        /*!
        получить текущее здоровье врага
        \param  не имеет параметров
        \return текущее здоровье
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int getCurHealth() const {return cur_health;}
        /*!
        получить скорость регенерации врага
        \param  не имеет параметров
        \return скорость регенерации
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int getRegenSpeed() const {return regen_speed;}
        /*!
        получить скорость перемещения врага
        \param  не имеет параметров
        \return скорость перемещения
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int getMoveSpeed() const {return move_speed;}
        /*!
        получить коэффициент урона врага
        \param  не имеет параметров
        \return коэффициент урона
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int getDamageIndex() const {return damage_index;}
        /*!
        получить тип врага
        \param  не имеет параметров
        \return индикатор типа врага
        \throw не выбрасывает исключения
        */
        [[nodiscard]] int getTypeOfEvil() const;
        /*!
        узнать, является ли враг героем
        \param  не имеет параметров
        \return является/не является героем
        \throw не выбрасывает исключения
        */
        [[nodiscard]] bool getIsHero() const;
        /*!
        получить список аур врага
        \param  не имеет параметров
        \return список повышающих характеристик
        \throw не выбрасывает исключения
        */
        [[nodiscard]] map<string, int> getAura() {return aura;}
        /*!
        повысить максимальное здоровье врага
        \param  dop значение из списка аур, на которое нужно повысить параметр
        \return ссылку на измененный объект класса
        \throw не выбрасывает исключения
        */
        [[nodiscard]] Evil& setMH(int dop) { max_health += dop; return *this;}
        /*!
        повысить текущее здоровье врага
        \param  dop значение из списка аур, на которое нужно повысить параметр
        \return ссылку на измененный объект класса
        \throw invalid_argument если текущее здоровье становится больше максимального
        */
        [[nodiscard]] Evil& setCH(int dop);
        /*!
        повысить скорость регенерации врага
        \param  dop значение из списка аур, на которое нужно повысить параметр
        \return ссылку на измененный объект класса
        \throw не выбрасывает исключения
        */
        [[nodiscard]] Evil& setRS(int dop) {regen_speed += dop; return *this;}
        /*!
        повысить скорость перемещения врага
        \param  dop значение из списка аур, на которое нужно повысить параметр
        \return ссылку на измененный объект класса
        \throw не выбрасывает исключения
        */
        [[nodiscard]] Evil& setMS(int dop) {move_speed += dop; return *this;}
        /*!
        повысить коэффициент урона врага
        \param  dop значение из списка аур, на которое нужно повысить параметр
        \return ссылку на измененный объект класса
        \throw не выбрасывает исключения
        */
        [[nodiscard]] Evil& setDI(int dop) {damage_index += dop; return *this;}
        /*!
        сделать врага героем
        \param  не имеет параметтров
        \return ссылку на измененный объект класса
        \throw invalid_argument если враг уже является героем
        */
        [[nodiscard]] Evil& setIsHero();
        Evil& setDamage(int harm);
        Evil& Repair();
    };
}
#endif //TOWERDEFENSEV2_EVIL_H
