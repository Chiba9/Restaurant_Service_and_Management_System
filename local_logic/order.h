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
/* 订单类Order   订单列表OrderList(用于未分配选单和存储服务员负责的订单表)   */
/************************************************************************/

namespace ORDER
{
	using OrderId = unsigned;
	enum OrderStatus{waitingForComming, /*顾客尚未到达餐馆*/
				    ordering,          /*点菜中*/
					cooking,           /*部分菜正在做尚未完毕*/
					eating,            /*全部上完，顾客正在吃*/
					finished           /*全部完成*/};
	class Order:public AbstractID::ID<Order>
	{
	private:
		ACCOUNT::AccountID customerId;       /*顾客ID*/
		ACCOUNT::AccountID waiterId;		 /*服务员ID*/
		TABLE::TableId tableId;				 /*对应桌号*/
		OrderStatus status;                  /*订单状态*/
		time_t timeCreated;				     /*创建时间*/
		std::set<TASK::TaskId> taskIdSet;    /*购物车(菜篮）*/
		COMMENT::CommentId commentId;        /*订单评价*/
	public:
		Order() = default;
		//全构造函数
		Order(ACCOUNT::AccountID _customerId, ACCOUNT::AccountID _waiterId,
			TABLE::TableId _tableId, OrderStatus _status, const time_t& _timeCreated,
			std::set<TASK::TaskId> _taskIdSet, COMMENT::CommentId _commentId);
		//该构造函数在顾客创建订单时调用，提供有限的参数
		Order(ACCOUNT::AccountID _customerId, TABLE::TableId _tableId);
		double price() const;
		double price(const DISCOUNT::Discount *discount) const;
		//下面两个函数将进行task对象的设定
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
