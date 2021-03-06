#include"dish.h"
#include"comment.h"
#include "restaurant.h"
#include<algorithm>
#include<iomanip>
#include<set>
#include<map>
#include<stdexcept>
#include "RestaurantSystem.h"

using namespace DISH;
using RESTAURANT::Restaurant;


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
	return Restaurant::CommentListMap.at(commentList)->size();
}

const std::string &Dish::getName() const
{
	return name;
}

const std::string &Dish::getPicture() const
{
	return picture;
}

const COMMENT::CommentList& Dish::getCommentList() const
{
	return *RESTAURANT::Restaurant::CommentListMap.at(commentList);
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

void Dish::addComment(CommentId commentId)
{
	Restaurant::CommentListMap[commentList]->addComment(commentId);
}

void Dish::setSpice(const Spicy &s)
{
	spice = s;
}

const std::string& DISH::Dish::getDescription()
{
	return description;
}

void DISH::Dish::setDescription(const std::string& d)
{
	description = d;
}

double DISH::Dish::star() const
{
	return RESTAURANT::Restaurant::CommentListMap.at(commentList)->star();
}

std::ostream& DISH::operator<<(std::ostream& os, const Dish& d)
{
	os << std::left << "ID: " << d.id() << " 菜名： " << std::setw(15)
		<< d.getName() << " 价格： " << std::fixed;
	os.precision(2);
	os<<d.getPrice() << " 图片： " << d.getPicture() << " 辣度： " << d.getSpice() << std::endl;
	return os;
}



void DISH::swap(Dish &lhs, Dish &rhs)
{
	std::swap(lhs.name, rhs.name);
	std::swap(lhs.picture, rhs.picture);
	std::swap(lhs.price, rhs.price);
	std::swap(lhs.spice, rhs.spice);
	std::swap(lhs.id(), rhs.id());
	std::swap(lhs.commentList, rhs.commentList);
}

void DishIdList::n_sort(bool compareDishId(const DishId&, const DishId&))
{
	std::sort(dishVec.begin(), dishVec.end(), compareDishId);
}

DishId& DishIdList::operator[](size_t n)
{
	if (n > dishVec.size())
		throw std::out_of_range("输入下标过大！");
	return dishVec[n];
}

const DishId & DishIdList::operator[](size_t n) const
{
	if (n > dishVec.size())
		throw std::out_of_range("输入下标过大！");
	return dishVec[n];
}

void DishIdList::addDish(DishId id)
{
	dishVec.push_back(id);
}

void DishIdList::sortByPrice(bool reverse /*= false*/)
{
	if(reverse)
		n_sort([](const DishId& lhs, const DishId& rhs)->bool
		{return Restaurant::DishMap.at(lhs)->getPrice() < Restaurant::DishMap.at(rhs)->getPrice(); });
	else
		n_sort([](const DishId& lhs, const DishId& rhs)->bool
		{return Restaurant::DishMap.at(lhs)->getPrice() > Restaurant::DishMap.at(rhs)->getPrice(); });
}

void DishIdList::sortByName(bool reverse /*= false*/)
{
	if (reverse)
		n_sort([](const DishId& lhs, const DishId& rhs)->bool
	{return Restaurant::DishMap.at(lhs)->getName() < Restaurant::DishMap.at(rhs)->getName(); });
	else
		n_sort([](const DishId& lhs, const DishId& rhs)->bool
	{return Restaurant::DishMap.at(lhs)->getName() > Restaurant::DishMap.at(rhs)->getName(); });
}

void DishIdList::sortByStar(bool reverse /*= false*/)
{
	if (reverse)
		n_sort([](const DishId& lhs, const DishId& rhs)->bool
	{return Restaurant::DishMap.at(lhs)->star() < Restaurant::DishMap.at(rhs)->star(); });
	else
		n_sort([](const DishId& lhs, const DishId& rhs)->bool
	{return Restaurant::DishMap.at(lhs)->star() > Restaurant::DishMap.at(rhs)->star(); });
}

void DishIdList::sortBySpice(bool reverse /*= false*/)
{
	if (reverse)
		n_sort([](const DishId& lhs, const DishId& rhs)->bool
	{return Restaurant::DishMap.at(lhs)->getSpice() < Restaurant::DishMap.at(rhs)->getSpice(); });
	else
		n_sort([](const DishId& lhs, const DishId& rhs)->bool
	{return Restaurant::DishMap.at(lhs)->getSpice() > Restaurant::DishMap.at(rhs)->getSpice(); });
}

void DishIdList::sortByHeat(bool reverse /*= false*/)
{
	if (reverse)
		n_sort([](const DishId& lhs, const DishId& rhs)->bool
	{return Restaurant::DishMap.at(lhs)->getCommentList().size() < Restaurant::DishMap.at(rhs)->getCommentList().size(); });
	else
		n_sort([](const DishId& lhs, const DishId& rhs)->bool
	{return Restaurant::DishMap.at(lhs)->getCommentList().size() > Restaurant::DishMap.at(rhs)->getCommentList().size(); });
}
