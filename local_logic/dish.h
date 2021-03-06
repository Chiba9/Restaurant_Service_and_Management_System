#ifndef DISH_H
#define DISH_H

#include "common.h"
#include "restaurant.h"
#include"id.h"
#include<string>
#include<set>
#include<vector>
#include "comment.h"

namespace DISH {
	std::ostream& operator<<(std::ostream&, const Dish&);
	enum Spicy { Not = 1, Little, Normal, Much, Very };

	/**********菜品类 Dish*********/
	//包含每一种菜的信息
	class Dish:public AbstractID::ID<Dish>
	{
		friend void swap(Dish&, Dish&);
	public:
		Dish(const std::string& n, double p, const std::string& pic = "", Spicy s = Normal,
			std::string _description = "", CommentListId c = Nodata,unsigned _id = Nodata):
			ID(_id),name(n), price(p),description(_description), picture(pic), spice(s), commentList(c)
		{
			if (commentList == Nodata) {
				COMMENT::CommentList _commentList;
				commentList = _commentList.id();
				RESTAURANT::Restaurant::DishMap.insert({ id(),std::make_shared<Dish>(*this) });
			}
		}
		Dish(const Dish&);
		Dish(Dish&&);
		Dish& operator=(Dish);
		~Dish();
		//辣度的枚举类型
		unsigned CommentNumber()const;
		const std::string& getName()const;
		const std::string& getPicture()const;
		const COMMENT::CommentList& getCommentList()const;
		const Spicy& getSpice()const;
		const std::string& getDescription();
		double getPrice()const;
		void setName(const std::string&);
		void setPicture(const std::string&);
		void setDescription(const std::string&);
		void addComment(CommentId commentId);
		void setSpice(const Spicy&);
		double star()const;                 //返回评星
	private:
		std::string picture;                //菜图
		std::string name;                   //菜名
		CommentListId commentList;    //评价列表（类值行为）
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
		DishIdList() {}
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

	template<typename... Args>
	Dish& newDish(Args&&... args)
	{
		DishId _id = Dish(std::forward<Args>(args)...).id();
		return *RESTAURANT::Restaurant::DishMap.at(_id);
	}
}
#endif // !DISH_H