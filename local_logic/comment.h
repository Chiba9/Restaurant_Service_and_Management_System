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
/* 评论类Comment,评论列表CommentList                                     */
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
		void reTarget(CommentListId cli);       //重定位,同时在commentList中添加
		void remove();                          //同时从commentList中移除
	private:
		time_t timeCreated;
		int star = Nodata;
		string text;
		AccountID customerId;
		CommentListId commentListId = Nodata;      //Nodata代表不属于任何评论列表
	};

	class CommentList :public AbstractID::ID<CommentList>
	{
	public:
		CommentList() = default;
		CommentList(std::initializer_list<CommentId> il);
		void addComment(CommentId);                      //增加评论/Comment的行为不在此处处理
		void sortByTime(bool reverse = false);           //按时间排序
		void sortByStar(bool reverse = false);           //按评分排序
		void removeComment(unsigned commentId);          //删除列表内评论/Comment的行为不在此处处理
		size_t size()const { return CommentIdList.size(); }
		double star();
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