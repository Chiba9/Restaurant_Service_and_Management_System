#ifndef MENU_H
#define MENU_H

#include "common.h"
#include <set>
#include "id.h"
#include "dish.h"

/**********菜单类 Menu**********/
//包含菜品的列表
namespace MENU {
	class Menu;
	void swap(Menu&, Menu&);
	using MenuId = unsigned;
	class Menu :public AbstractID::ID<Menu>
	{
		friend void swap(Menu&, Menu&);
	private:
		DISH::DishIdList dishIdList;
		std::string _type;
	public:
		Menu() = default;
		Menu(std::string t) :ID(), _type(t) {
			RESTAURANT::Restaurant::MenuMap.insert({ id(),std::make_shared<Menu>(*this) });
		}
		~Menu();
		Menu& addDishId(const unsigned&);
		const std::string& type() const { return _type; }
		std::string& type() { return _type; }
		unsigned size()const;
		void sortByName(bool reserve = false) { dishIdList.sortByName(reserve); }              //按菜名进行排序，默认降序
		void sortByPrice(bool reserve = false) { dishIdList.sortByPrice(reserve); }              //按价格进行排序，默认降序
		void sortBySpice(bool reserve = false) { dishIdList.sortBySpice(reserve); }              //按价格进行排序，默认降序
		void sortByStar(bool reserve = false) { dishIdList.sortByStar(reserve); }               //按菜品的评星进行排序，默认降序
		void sortByHeat(bool reserve = false) { dishIdList.sortByHeat(reserve); }               //按热度（评论数量）进行排序，默认降序
		const DISH::DishIdList& getDishesId()const;
	};
	std::ostream& operator<<(std::ostream& os, const Menu& m);

	template<typename... Args>
	Menu& newMenu(Args&&... args)
	{
		MenuId _id = Menu(std::forward<Args>(args)...).id();
		return *RESTAURANT::Restaurant::MenuMap.at(_id);
	}
}
#endif // !MENU_H