#ifndef ORDER_H
#define ORDER_H

#include "common.h"

#include "id.h"

#include<set>



/************************************************************************/
/* ������Order   �����б�OrderList(����δ����ѡ���ʹ洢����Ա����Ķ�����)   */
/************************************************************************/

namespace ORDER
{
	using OrderId = unsigned;
	enum OrderStatus {
		waitingForComming, /*�˿���δ����͹�*/
		ordering,          /*�����*/
		cooking,           /*���ֲ���������δ���*/
		eating,            /*ȫ�����꣬�˿����ڳ�*/
		finished           /*ȫ�����*/
	};
	class Order :public AbstractID::ID<Order>
	{
	private:
		AccountID customerId;       /*�˿�ID*/
		AccountID waiterId;		 /*����ԱID*/
		TableId tableId;				 /*��Ӧ����*/
		OrderStatus status;                  /*����״̬*/
		time_t timeCreated;				     /*����ʱ��*/
		std::set<TaskId> taskIdSet;    /*���ﳵ(������*/
		CommentId commentId;        /*��������*/
	public:
		Order() = default;
		Order(const Order&) = default;
		//ȫ���캯��
		Order(AccountID _customerId, AccountID _waiterId,
			TableId _tableId, OrderStatus _status, const time_t& _timeCreated,
			std::set<TaskId> _taskIdSet, CommentId _commentId);
		//�ù��캯���ڹ˿ʹ�������ʱ���ã��ṩ���޵Ĳ���
		Order(AccountID _customerId, TableId _tableId);

		double price() const;
		double price(const DISCOUNT::Discount *discount) const;
		//������������������task������趨
		void addTask(TaskId _taskId);
		void removeTask(TaskId _taskId);
		OrderStatus getStatus() const;
		void setStatus(OrderStatus _status);
		CommentId getCommentId() const;
		double star() const;
		TableId getTableId()const;
		const std::set<TaskId> getTaskIdSet()const;
		AccountID getWaiterId() const;
		void setWaiterId(AccountID val);
	};
}

#endif // !ORDER_H
