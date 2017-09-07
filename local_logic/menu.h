#pragma once
#include <set>
#include "id.h"
/**********�˵��� Menu**********/
//������Ʒ���б�
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
	void sortByName();               //��������������
	void sortByPrice();              //���۸��������
	void sortByStar();               //����Ʒ�����ǽ�������
	void sortByHeat();               //���ȶȣ�������������������
	const std::set<unsigned>& getDishesId()const;
};