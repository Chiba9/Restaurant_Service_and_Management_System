#ifndef ORDER_H
#define ORDER_H
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
		ACCOUNT::AccountID customerId;       /*�˿�ID*/
		ACCOUNT::AccountID waiterId;		 /*����ԱID*/
		TABLE::TableId tableId;				 /*��Ӧ����*/
		OrderStatus status;                  /*����״̬*/
		time_t timeCreated;				     /*����ʱ��*/
		std::set<TASK::TaskId> taskIdSet;    /*���ﳵ(������*/
		COMMENT::CommentId commentId;        /*��������*/
	public:
		Order() = default;
		//ȫ���캯��
		Order(ACCOUNT::AccountID _customerId, ACCOUNT::AccountID _waiterId,
			TABLE::TableId _tableId, OrderStatus _status, const time_t& _timeCreated,
			std::set<TASK::TaskId> _taskIdSet, COMMENT::CommentId _commentId);
		//�ù��캯���ڹ˿ʹ�������ʱ���ã��ṩ���޵Ĳ���
		Order(ACCOUNT::AccountID _customerId, TABLE::TableId _tableId);
		double price() const;
		double price(const DISCOUNT::Discount *discount) const;
		//������������������task������趨
		void addTask(TASK::TaskId _taskId);
		void removeTask(TASK::TaskId _taskId);
		OrderStatus getStatus() const;
		void setStatus(OrderStatus _status);
		COMMENT::CommentId getCommentId() const;
		double star() const;
		TABLE::TableId getTableId()const;
		const std::set<TASK::TaskId> getTaskIdSet()const;
		ACCOUNT::AccountID getWaiterId() const;
		void setWaiterId(ACCOUNT::AccountID val);
	};
}

#endif // !ORDER_H
