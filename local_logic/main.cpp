#include"dish.h"
#include<iostream>
#include<time.h>
using std::cout;using std::cin;using std::endl;
int main()
{
	DISH::Dish dish1("«‡Ω∑≥¥»‚", 28.8, "N", DISH::Very);
	DISH::Dish dish2("Œ˜∫Ï ¡≥¥µ∞", 19.8, "N", DISH::Little);
	DISH::Menu menu;
	menu.addDishId(dish1).addDishId(dish2);
	std::cout << dish1 << dish2 << menu;
	menu.sortByPrice();
	std::cout << menu;

}
