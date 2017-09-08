#ifndef ORDER_H
#define  ORDER_H
#include "id.h"
#include "task.h"
#include<set>
#include "account.h"
#include "table.h"
#include"time.h"
/************************************************************************/
/* ������Order                                                          */
/************************************************************************/

namespace ORDER
{
	using OrderId = unsigned;
	enum OrderStatus{waitingForWaiter,  /*�˿����µ����ȴ�����Ա*/
					waitingForComming, /*�˿���δ����͹�*/
				    ordering,          /*�����*/
					cooking,           /*���ֲ���������δ���*/
					eating,            /*ȫ�����꣬�˿����ڳ�*/
					finished           /*ȫ�����*/};
	class Order:public AbstractID::ID<Order>
	{
	private:
		std::set<TASK::TaskId> taskIdSet;    /*���ﳵ(������*/
		ACCOUNT::AccountID customerId;       /*�˿�ID*/
		ACCOUNT::AccountID waiterId;		 /*����ԱID*/
		TABLE::TableId tableId;				 /*��Ӧ����*/
		OrderStatus status;                  /*����״̬*/
		time_t timeCreated;				     /*����ʱ��*/
	public:
		double price();
		double price(DISCOUNT::)
	};
}

#endif // !ORDER_H
