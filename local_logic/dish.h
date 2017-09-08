#ifndef DISH_H
#define DISH_H
#include"id.h"
#include<string>
#include<set>
#include<vector>
#include "comment.h"
namespace DISH {
	class Dish;
	class Menu;
	class COMMENT::Comment;
	using COMMENT::CommentId;
	std::ostream& operator<<(std::ostream&, const Dish&);
	using DishId = unsigned;

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
		const COMMENT::CommentListId& getCommentListId()const;
		const Spicy& getSpice()const;
		const std::string& getDescription();
		double getPrice()const;
		void setName(const std::string&);
		void setPicture(const std::string&);
		void setDescription(const std::string&);
		void addComment(CommentId commentId);
		void setSpice(const Spicy&);
		double star()const;                 //返回评星//还未实现
	private:
		std::string picture;                //菜图
		std::string name;                   //菜名
		COMMENT::CommentListId commentListId;    //评价列表（类值行为）
		std::string description;
		double price;                   //价格
		Spicy spice;                    //辣度（枚举类型）
	};

	void swap(Dish &, Dish &);

	class DishIdList :AbstractID::ID<DishIdList>
	{
	private:
		std::vector<DishId> dishVec;    //存储Dish的ID
		void n_sort(bool compareDishId(const DishId&,const DishId&)); //排序的内部实现
	public:
		const std::vector<DishId>& getDishVec()const{ return dishVec; }
		DishId& operator[](size_t);
		const DishId& operator[](size_t) const;
		void addDish(DishId);
		//按价格/名字/辣度/得分/热度（评论数量）进行排序，reverse代表反向
		void sortByPrice(bool reverse = false);
		void sortByName(bool reverse = false);
		void sortByStar(bool reverse = false);
		void sortBySpice(bool reverse = false);
		void sortByHeat(bool reverse = false);
		unsigned size() const{ return dishVec.size(); }
	};
}
#endif // DISH_H