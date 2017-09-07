#pragma once
#include <set>
#include "id.h"
/**********菜单类 Menu**********/
//包含菜品的列表
void swap(Menu&, Menu&);
class Menu :public AbstractID::ID<Menu>
{
	friend void swap(Menu&, Menu&);
private:
	std::set<unsigned> dishIdSet;

	std::string name;
	std::string _type;
public:
	Menu() = default;
	Menu(std::string n) :ID(), name(n) {}
	~Menu();
	Menu(const Menu&);
	Menu(Menu&&);
	Menu& addDishId(const unsigned&);
	const std::string& type() const { return _type; }
	std::string& type() { return _type; }
	unsigned count()const;
	void sortByName();               //按菜名进行排序
	void sortByPrice();              //按价格进行排序
	void sortByStar();               //按菜品的评星进行排序
	void sortByHeat();               //按热度（评论数量）进行排序
	const std::set<unsigned>& getDishesId()const;
};