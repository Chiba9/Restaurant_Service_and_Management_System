#ifndef ORDER_H
#define  ORDER_H
#include "id.h"
#include "task.h"
#include<set>
#include "account.h"
#include "table.h"
#include"time.h"
#include"discount.h"
#include "comment.h"
/************************************************************************/
/* ������Order   �����б�OrderList(����δ����ѡ���ʹ洢����Ա����Ķ�����)   */
/************************************************************************/

namespace ORDER
{
	using OrderId = unsigned;
	enum OrderStatus{waitingForComming, /*�˿���δ����͹�*/
				    ordering,          /*�����*/
					cooking,           /*���ֲ���������δ���*/
					eating,            /*ȫ�����꣬�˿����ڳ�*/
					finished           /*ȫ�����*/};
	class Order:public AbstractID::ID<Order>
	{
	private:
		std::set<TASK::TaskId> taskIdSet;    /*���ﳵ(������*/
		COMMENT::CommentId commentId;        /*��������*/
		ACCOUNT::AccountID customerId;       /*�˿�ID*/
		ACCOUNT::AccountID waiterId;		 /*����ԱID*/
		TABLE::TableId tableId;				 /*��Ӧ����*/
		OrderStatus status;                  /*����״̬*/
		time_t timeCreated;				     /*����ʱ��*/
	public:
		double price();
		double price(const DISCOUNT::Discount *discount);
		//������������������task������趨
		void addTask(TASK::TaskId _taskId);
		void removeTask(TASK::TaskId _taskId);
		OrderStatus getStatus() const;
		void setStatus(OrderStatus _status);
		COMMENT::CommentId getCommentId() const;
		double star() const;
	};
}

#endif // !ORDER_H
