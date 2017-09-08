#ifndef COMMENT_H
#define COMMENT_H
#include "id.h"
#include <time.h>
#include<vector>
#include<string>
#include<stdexcept>
#include "account.h"
/************************************************************************/
/* ������Comment,�����б�CommentList                                     */
/************************************************************************/
namespace COMMENT {
	using std::string;
	using CommentId = unsigned;
	using CommentListId = unsigned;
	enum target{dish,order,waiter};
	class Comment:public AbstractID::ID<Comment>
	{
	public:
		Comment() = default;
		Comment(ACCOUNT::AccountID _customerId,const double _star,const string& _text, CommentListId _commentListId):
			ID(),customerId(_customerId),text(_text),commentListId(_commentListId)
		{
			if (_star < 0 || star>5)throw std::runtime_error("���ֲ��ԣ�");
			star = _star;
			time(&timeCreated);
		}
		const string& getText()const;
		const double& getStar()const;
		ACCOUNT::AccountID getCustomeId()const;
		CommentListId getCommentListId()const;
		void setText(const string& _text);
		time_t getTime()const;
		void reTarget(CommentListId cli);       //�ض�λ,ͬʱ��commentList�����
		void remove();                          //ͬʱ��commentList���Ƴ�
	private:
		time_t timeCreated;
		double star;
		time_t timeWroten;
		string text;
		ACCOUNT::AccountID customerId;
		CommentListId commentListId;
	};

	class CommentList :public AbstractID::ID<CommentList>
	{
	public:
		void addComment(CommentId);                      //��������/Comment����Ϊ���ڴ˴�����
		void sortByTime(bool reverse = false);           //��ʱ������
		void sortByStar(bool reverse = false);           //����������
		void removeComment(unsigned commentId);          //ɾ���б�������/Comment����Ϊ���ڴ˴�����
		size_t size()const { return CommentIdList.size(); }
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