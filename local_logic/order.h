#ifndef ORDER_H
#define  ORDER_H
#include "id.h"
#include "task.h"
#include<set>
#include "account.h"
#include "table.h"
#include"time.h"
/************************************************************************/
/* 订单类Order                                                          */
/************************************************************************/

namespace ORDER
{
	using OrderId = unsigned;
	enum OrderStatus{waitingForWaiter,  /*顾客已下单，等待服务员*/
					waitingForComming, /*顾客尚未到达餐馆*/
				    ordering,          /*点菜中*/
					cooking,           /*部分菜正在做尚未完毕*/
					eating,            /*全部上完，顾客正在吃*/
					finished           /*全部完成*/};
	class Order:public AbstractID::ID<Order>
	{
	private:
		std::set<TASK::TaskId> taskIdSet;    /*购物车(菜篮）*/
		ACCOUNT::AccountID customerId;       /*顾客ID*/
		ACCOUNT::AccountID waiterId;		 /*服务员ID*/
		TABLE::TableId tableId;				 /*对应桌号*/
		OrderStatus status;                  /*订单状态*/
		time_t timeCreated;				     /*创建时间*/
	public:
		double price();
		double price(DISCOUNT::)
	};
}

#endif // !ORDER_H
