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
		const std::set<unsigned>& getCommentIdSet()const;
		const Spicy& getSpice()const;
		double getPrice()const;
		void setName(const std::string&);
		void setPicture(const std::string&);
		void addComment(unsigned commentId);
		void setSpice(const Spicy&);
		double star()const { return 0; }                   //��������//��δʵ��
	private:
		std::string picture;                //��ͼ
		std::string name;                   //����
		std::set<unsigned> CommentIdSet;    //�����б���ֵ��Ϊ��
		double price;                   //�۸�
		Spicy spice;                    //���ȣ�ö�����ͣ�
	};

	void swap(Dish &, Dish &);
}
#endif // DISH_H

