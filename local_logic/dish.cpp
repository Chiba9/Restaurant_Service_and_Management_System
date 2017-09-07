#include"dish.h"
#include"comment.h"
#include<algorithm>
#include<iomanip>
#include<set>
#include<map>

using namespace DISH;
/**************����ͨ����***************/
std::map<unsigned,COMMENT::Comment> CommentSet;
std::map<unsigned,Dish> DishSet;
/**************����ͨ����***************/


Dish::Dish(const Dish &rhs) = default;

Dish::Dish(Dish &&rhs) = default;

Dish &Dish::operator=(Dish rhs)
{
	swap(*this, rhs);
	return *this;
}

Dish::~Dish() = default;

unsigned Dish::CommentNumber()const
{
	return CommentIdSet.size();
}

const std::string &Dish::getName() const
{
	return name;
}

const std::string &Dish::getPicture() const
{
	return picture;
}

const std::set<unsigned> &Dish::getCommentIdSet() const
{
	return CommentIdSet;
}

const Spicy &Dish::getSpice() const
{
	return spice;
}

double Dish::getPrice() const
{
	return price;
}

void Dish::setName(const std::string &n)
{
	name = n;
}

void Dish::setPicture(const std::string &pic)
{
	picture = pic;
}

void Dish::addComment(unsigned commentId)
{
	CommentIdSet.insert(commentId);
}

void Dish::setSpice(const Spicy &s)
{
	spice = s;
}

std::ostream& DISH::operator<<(std::ostream& os, const Dish& d)
{
	os << std::left << "ID: " << d.id() << " ������ " << std::setw(15)
		<< d.getName() << " �۸� " << std::fixed;
	os.precision(2);
	os<<d.getPrice() << " ͼƬ�� " << d.getPicture() << " ���ȣ� " << d.getSpice() << std::endl;
	return os;
}

std::ostream& DISH::operator<<(std::ostream& os, const Menu& m)
{
	for (auto i : m.getDishesId())
	{
		os << DishSet[i];
	}
	return os;
}

void DISH::swap(Dish &lhs, Dish &rhs)
{
	std::swap(lhs.name, rhs.name);
	std::swap(lhs.picture, rhs.picture);
	std::swap(lhs.price, rhs.price);
	std::swap(lhs.spice, rhs.spice);
	std::swap(lhs.id(), rhs.id());
	std::swap(lhs.CommentIdSet, rhs.CommentIdSet);
}

