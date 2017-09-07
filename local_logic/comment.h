#ifndef COMMENT_H
#define COMMENT_H

namespace COMMENT {
	using std::string;
	enum target{dish,order,waiter};
	class Comment:public AbstractID::ID<Comment>
	{
	public:
		Comment() = default;
		Comment(unsigned _customerId,const string& _text,target _targetType,unsigned _targeId):
			ID(),customerId(_customerId),text(_text),targetType(_targetType),targetId(_targeId){}
		const string& getText()const;
		unsigned getCustomeId()const;
		target getTargetType()const;
		unsigned getTargetId()const;
		void setText(const string& _text);
		void reTarget(target _targetType, unsigned _targetId);
		void remove();
	private:
		time_t timeWroten;
		string text;
		unsigned customerId;
		target targetType;
		unsigned targetId;
	};

	class CommentList :public AbstractID::ID<CommentList>
	{
	public:
		void addComment();                               //增加评论
		void sortByTime(bool reverse = false);           //按时间排序
		void sortByStar(bool reverse = false);           //按评分排序
		void removeComment(unsigned commentId);          //删除列表内评论
		//以下为隐藏内部结构设计
		std::vector<unsigned>::iterator begin();
		std::vector<unsigned>::iterator end();     
	private:
		std::vector<unsigned> CommentIdList;             //评论ID列表
		template<typename T>
		n_sort(T, bool reverse);                         //排序内部实现
	};
}

#endif //COMMENT_H