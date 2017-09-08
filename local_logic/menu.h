#pragma once
#include <set>
#include "id.h"
#include "dish.h"
/**********�˵��� Menu**********/
//������Ʒ���б�
namespace MENU {
	class Menu;
	void swap(Menu&, Menu&);
	using MenuId = unsigned;
	class Menu :public AbstractID::ID<Menu>
	{
		friend void swap(Menu&, Menu&);
	private:
		DISH::DishIdList dishIdList;
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
		unsigned size()const;
		void sortByName(bool reserve = false) { dishIdList.sortByName(reserve); }              //��������������
		void sortByPrice(bool reserve = false) { dishIdList.sortByPrice(reserve); }              //���۸��������
		void sortBySpice(bool reserve = false) { dishIdList.sortBySpice(reserve); }              //���۸��������
		void sortByStar(bool reserve = false) { dishIdList.sortByStar(reserve); }               //����Ʒ�����ǽ�������
		void sortByHeat(bool reserve = false) { dishIdList.sortByHeat(reserve); }               //���ȶȣ�������������������
		const DISH::DishIdList& getDishesId()const;
	};
	std::ostream& operator<<(std::ostream& os, const Menu& m);

}