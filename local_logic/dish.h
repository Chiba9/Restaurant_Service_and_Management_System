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

	/**********��Ʒ�� Dish*********/
	//����ÿһ�ֲ˵���Ϣ
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
		//���ȵ�ö������
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
		double star()const;                 //��������//��δʵ��
	private:
		std::string picture;                //��ͼ
		std::string name;                   //����
		COMMENT::CommentListId commentListId;    //�����б���ֵ��Ϊ��
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
}
#endif // DISH_H