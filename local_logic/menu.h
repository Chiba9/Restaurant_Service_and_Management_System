#ifndef MENU_H
#define MENU_H

#include "common.h"
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
		void sortByName(bool reserve = false) { dishIdList.sortByName(reserve); }              //��������������Ĭ�Ͻ���
		void sortByPrice(bool reserve = false) { dishIdList.sortByPrice(reserve); }              //���۸��������Ĭ�Ͻ���
		void sortBySpice(bool reserve = false) { dishIdList.sortBySpice(reserve); }              //���۸��������Ĭ�Ͻ���
		void sortByStar(bool reserve = false) { dishIdList.sortByStar(reserve); }               //����Ʒ�����ǽ�������Ĭ�Ͻ���
		void sortByHeat(bool reserve = false) { dishIdList.sortByHeat(reserve); }               //���ȶȣ�������������������Ĭ�Ͻ���
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