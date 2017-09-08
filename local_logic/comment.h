#ifndef COMMENT_H
#define COMMENT_H
#include "id.h"
#include <time.h>
#include<vector>
#include<string>
#include<stdexcept>
#include "account.h"
/************************************************************************/
/* 评论类Comment,评论列表CommentList                                     */
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
			if (_star < 0 || star>5)throw std::runtime_error("评分不对！");
			star = _star;
			time(&timeCreated);
		}
		const string& getText()const;
		const double& getStar()const;
		ACCOUNT::AccountID getCustomeId()const;
		CommentListId getCommentListId()const;
		void setText(const string& _text);
		time_t getTime()const;
		void reTarget(CommentListId cli);       //重定位,同时在commentList中添加
		void remove();                          //同时从commentList中移除
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
		void addComment(CommentId);                      //增加评论/Comment的行为不在此处处理
		void sortByTime(bool reverse = false);           //按时间排序
		void sortByStar(bool reverse = false);           //按评分排序
		void removeComment(unsigned commentId);          //删除列表内评论/Comment的行为不在此处处理
		size_t size()const { return CommentIdList.size(); }
		//以下为隐藏内部结构设计
		std::vector<unsigned>::iterator begin();
		std::vector<unsigned>::iterator end();  
		std::vector<unsigned>::const_iterator cbegin()const;
	    std::vector<unsigned>::const_iterator cend()const;
	private:
		std::vector<CommentId> CommentIdList;             //评论ID列表
		void n_sort(bool compareCommentId(const CommentId& lhs,const CommentId& rhs), bool reverse);  //排序内部实现
	};
}

#endif //COMMENT_H