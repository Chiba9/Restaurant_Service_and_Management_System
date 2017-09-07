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
		void addComment();                               //��������
		void sortByTime(bool reverse = false);           //��ʱ������
		void sortByStar(bool reverse = false);           //����������
		void removeComment(unsigned commentId);          //ɾ���б�������
		//����Ϊ�����ڲ��ṹ���
		std::vector<unsigned>::iterator begin();
		std::vector<unsigned>::iterator end();     
	private:
		std::vector<unsigned> CommentIdList;             //����ID�б�
		template<typename T>
		n_sort(T, bool reverse);                         //�����ڲ�ʵ��
	};
}

#endif //COMMENT_H