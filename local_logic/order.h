#ifndef ORDER_H
#define ORDER_H

#include "common.h"

#include "id.h"
#include<time.h>
#include<set>



/************************************************************************/
/* ������Order   �����б�OrderList(����δ����ѡ���ʹ洢����Ա����Ķ�����)   */
/************************************************************************/

namespace ORDER
{
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
		AccountID customerId = -1;       /*�˿�ID*/
		AccountID waiterId = -1;		 /*����ԱID*/
		TableId tableId = -1;				 /*��Ӧ����*/
		OrderStatus status = waitingForComming;                  /*����״̬*/
		time_t timeCreated;				     /*����ʱ��*/
		std::set<TaskId> taskIdSet;    /*���ﳵ(������*/
		CommentId commentId = -1;        /*��������*/
	public:
		Order() { time(&timeCreated); }
		Order(const Order&) = default;
		//ȫ���캯��
		Order(AccountID _customerId, AccountID _waiterId,
			TableId _tableId, OrderStatus _status, const time_t& _timeCreated,
			std::set<TaskId> _taskIdSet, CommentId _commentId, unsigned _id);
		//�ù��캯���ڹ˿ʹ�������ʱ���ã��ṩ���޵Ĳ���
		Order(AccountID _customerId, TableId _tableId);

		double price() const;
		double priceAfterDiscount() const;
		//������������������task������趨
		void addTask(TaskId _taskId);
		void removeTask(TaskId _taskId);
		OrderStatus getStatus() const;
		void setStatus(OrderStatus _status);
		CommentId getCommentId() const;
		double star() const;
		TableId getTableId()const;
		const std::set<TaskId>& getTaskIdSet()const;
		AccountID getWaiterId() const;
		void setWaiterId(AccountID val);
		void setTable(TableId _tableId) { tableId = _tableId; }
		void setCustomer(AccountID _customer) { customerId = _customer; }
	};
	bool operator<(const Order& lhs, const Order& rhs);

	template<typename... Args>
	Order& newOrder(Args&&... args)
	{
		OrderId _id = Order(std::forward<Args>(args)...).id();
		return *RESTAURANT::Restaurant::OrderMap.at(_id);
	}
}

#endif // !ORDER_H
