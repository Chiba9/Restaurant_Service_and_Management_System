#ifndef DISH_H
#define DISH_H
#include"id.h"
#include<string>
#include<set>

namespace DISH {
	class Dish;
	class Menu;
	class COMMENT::Comment;
	std::ostream& operator<<(std::ostream&, const Dish&);
	std::ostream& operator<<(std::ostream&, const Menu&);


	enum Spicy { Not = 1, Little, Normal, Much, Very };

	/**********菜品类 Dish*********/
	//包含每一种菜的信息
	class Dish:public AbstractID::ID<Dish>
	{
		friend void swap(Dish&, Dish&);
	public:
		Dish(const std::string& n, double p, const std::string& pic = "", Spicy s = Normal) :
			ID(),name(n), price(p), picture(pic), spice(s), CommentIdSet(std::set<unsigned>()) {}
		Dish(const Dish&);
		Dish(Dish&&);
		Dish& operator=(Dish);
		~Dish();
		//辣度的枚举类型
		unsigned CommentNumber()const;
		const std::string& getName()const;
		const std::string& getPicture()const;
		const std::set<unsigned>& getCommentIdSet()const;
		const Spicy& getSpice()const;
		double getPrice()const;
		void setName(const std::string&);
		void setPicture(const std::string&);
		void addComment(unsigned commentId);
		void setSpice(const Spicy&);
		double star()const { return 0; }                   //返回评星//还未实现
	private:
		std::string picture;                //菜图
		std::string name;                   //菜名
		std::set<unsigned> CommentIdSet;    //评价列表（类值行为）
		double price;                   //价格
		Spicy spice;                    //辣度（枚举类型）
	};

	void swap(Dish &, Dish &);
}
#endif // DISH_H

