#include "menu.h"
#include "id.h"
#include "dish.h"
#include<string>
#include<set>


void swap(Menu &lhs, Menu &rhs)
{
	std::swap(lhs.id(), rhs.id());
	std::swap(lhs.dishIdSet, rhs.dishIdSet);
}

Menu::~Menu()
{

}

Menu::Menu(const Menu &m) :ID(m)
{
	for (unsigned d : m.dishIdSet)
		dishIdSet.insert(d);
}


Menu::Menu(Menu&& m) :ID(m)
{
	for (unsigned d : m.dishIdSet) {
		dishIdSet.insert(d);
	}
}

Menu& Menu::addDishId(const unsigned &d)
{
	dishIdSet.insert(d);
	return *this;
}

unsigned Menu::count() const
{
	return dishIdSet.size();
}

void Menu::sortByName()
{
	n_sort([](const unsigned lhs, const unsigned rhs)->bool {return DishSet[lhs].getName() < DishSet[rhs].getName(); });
}

void Menu::sortByPrice()
{
	n_sort([](const unsigned lhs, const unsigned rhs)->bool {return DishSet[lhs].getPrice() < DishSet[rhs].getPrice(); });
}

void Menu::sortByStar()
{
	n_sort([](const unsigned lhs, const unsigned rhs)->bool {return DishSet[lhs].star() < DishSet[rhs].star(); });
}

void Menu::sortByHeat()
{
	dishList.n_sort([](const unsigned lhs, const unsigned rhs)->bool {return DishSet[lhs].CommentNumber() < DishSet[rhs].CommentNumber(); });
}

const std::set<unsigned> &Menu::getDishesId() const
{
	return dishIdSet;
}


template<typename F>
void Menu::n_sort(F f, bool reserve)
{
	std::sort(dishIdSet.begin(), dishIdSet.end(), f);
}
