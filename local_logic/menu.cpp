#include "menu.h"
#include "id.h"
#include "dish.h"
#include<string>
#include<set>
#include "RestaurantSystem.h"
#include "dish.h"

using namespace MENU;
void MENU::swap(Menu &lhs, Menu &rhs)
{
	std::swap(lhs.id(), rhs.id());
	std::swap(lhs._type, rhs._type);
	std::swap(lhs.dishIdList, rhs.dishIdList);
}

Menu::~Menu()
{

}

Menu& Menu::addDishId(const unsigned &d)
{
	dishIdList.addDish(d);
	return *this;
}

unsigned Menu::size() const
{
	return dishIdList.size();
}

const DISH::DishIdList& Menu::getDishesId() const
{
	return dishIdList;
}

std::ostream&MENU::operator<<(std::ostream& os, const Menu& m)
{
	for (auto i : m.getDishesId().getDishVec())
	{
		os << *RESTAURANT::Restaurant::DishMap.at(i);
	}
	return os;
}