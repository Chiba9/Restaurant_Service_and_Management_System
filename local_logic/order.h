#ifndef ORDER_H
#define ORDER_H

#include "common.h"

#include "id.h"
#include<time.h>
#include<set>



/************************************************************************/
/* 订单类Order   订单列表OrderList(用于未分配选单和存储服务员负责的订单表)   */
/************************************************************************/

namespace ORDER
{
	enum OrderStatus {
		waitingForComming, /*顾客尚未到达餐馆*/
		ordering,          /*点菜中*/
		cooking,           /*部分菜正在做尚未完毕*/
		eating,            /*全部上完，顾客正在吃*/
		finished           /*全部完成*/
	};
	class Order :public AbstractID::ID<Order>
	{
	private:
		AccountID customerId = -1;       /*顾客ID*/
		AccountID waiterId = -1;		 /*服务员ID*/
		TableId tableId = -1;				 /*对应桌号*/
		OrderStatus status = waitingForComming;                  /*订单状态*/
		time_t timeCreated;				     /*创建时间*/
		std::set<TaskId> taskIdSet;    /*购物车(菜篮）*/
		CommentId commentId = -1;        /*订单评价*/
	public:
		Order() { time(&timeCreated); }
		Order(const Order&) = default;
		//全构造函数
		Order(AccountID _customerId, AccountID _waiterId,
			TableId _tableId, OrderStatus _status, const time_t& _timeCreated,
			std::set<TaskId> _taskIdSet, CommentId _commentId, unsigned _id);
		//该构造函数在顾客创建订单时调用，提供有限的参数
		Order(AccountID _customerId, TableId _tableId);

		double price() const;
		double priceAfterDiscount() const;
		//下面两个函数将进行task对象的设定
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
