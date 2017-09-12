#ifndef COMMENT_H
#define COMMENT_H
#include "common.h"
#include "id.h"
#include <time.h>
#include<vector>
#include<string>
#include<stdexcept>
#include<initializer_list>
#include "restaurant.h"

/************************************************************************/
/* ������Comment,�����б�CommentList                                     */
/************************************************************************/

namespace COMMENT {
	using std::string;
	enum target{dish,order,waiter};
	class Comment:public AbstractID::ID<Comment>
	{
	public:
		Comment() = default;
		Comment(AccountID _customerId,const int _star,const string& _text = ""
			, CommentListId _commentListId = Nodata);
		Comment(AccountID _customerId, const int _star, const string& _text
			, CommentListId _commentListId, time_t _timeCreated);
		const string& getText()const;
		double getStar()const;
		AccountID getCustomeId()const;
		CommentListId getCommentListId()const;
		void setText(const string& _text);
		time_t getTime()const;
		void reTarget(CommentListId cli);       //�ض�λ,ͬʱ��commentList�����
		void remove();                          //ͬʱ��commentList���Ƴ�
	private:
		time_t timeCreated;
		int star = Nodata;
		string text;
		AccountID customerId;
		CommentListId commentListId = Nodata;      //Nodata���������κ������б�
	};

	class CommentList :public AbstractID::ID<CommentList>
	{
	public:
		CommentList() = default;
		CommentList(std::initializer_list<CommentId> il);
		void addComment(CommentId);                      //��������/Comment����Ϊ���ڴ˴�����
		void sortByTime(bool reverse = false);           //��ʱ������
		void sortByStar(bool reverse = false);           //����������
		void removeComment(unsigned commentId);          //ɾ���б�������/Comment����Ϊ���ڴ˴�����
		size_t size()const { return CommentIdList.size(); }
		double star();
		//����Ϊ�����ڲ��ṹ���
		std::vector<unsigned>::iterator begin();
		std::vector<unsigned>::iterator end();  
		std::vector<unsigned>::const_iterator cbegin()const;
	    std::vector<unsigned>::const_iterator cend()const;
	private:
		std::vector<CommentId> CommentIdList;             //����ID�б�
		void n_sort(bool compareCommentId(const CommentId& lhs,const CommentId& rhs), bool reverse);  //�����ڲ�ʵ��
	};
}

#endif //COMMENT_H