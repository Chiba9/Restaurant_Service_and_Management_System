#include "people.h"
#include "RestaurantSystem.h"
const std::string & PEOPLE::People::getName() const
{
	return name;
}

std::ostream& PEOPLE::operator<<(std::ostream& os, const People& p)
{
	os << "(People ��) ID: " << p.id() << " ����: " << p.getName() << std::endl;
	return os;
}