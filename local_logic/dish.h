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

	/**********��Ʒ�� Dish*********/
	//����ÿһ�ֲ˵���Ϣ
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
		//���ȵ�ö������
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
		double star()const;                 //��������
	private:
		std::string picture;                //��ͼ
		std::string name;                   //����
		CommentListId commentList;    //�����б���ֵ��Ϊ��
		std::string description;
		double price;                   //�۸�
		Spicy spice;                    //���ȣ�ö�����ͣ�
	};

	void swap(Dish &, Dish &);

	class DishIdList :AbstractID::ID<DishIdList>
	{
	private:
		std::vector<DishId> dishVec;    //�洢Dish��ID
		void n_sort(bool compareDishId(const DishId&,const DishId&)); //������ڲ�ʵ��
	public:
		DishIdList() {}
		const std::vector<DishId>& getDishVec()const{ return dishVec; }
		DishId& operator[](size_t);
		const DishId& operator[](size_t) const;
		void addDish(DishId);
		//���۸�/����/����/�÷�/�ȶȣ�������������������reverse������
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