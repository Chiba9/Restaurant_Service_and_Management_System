#include "order.h"


ORDER::Order::Order(ACCOUNT::AccountID _customerId, ACCOUNT::AccountID _waiterId, 
		TABLE::TableId _tableId, OrderStatus _status, const time_t& _timeCreated, 
		std::set<TASK::TaskId> _taskIdSet, COMMENT::CommentId _commentId):
	customerId(_customerId), waiterId(_waiterId), tableId(_tableId),
	status(_status), timeCreated(_timeCreated), taskIdSet(_taskIdSet),
	commentId(_commentId) {}

ORDER::Order::Order(ACCOUNT::AccountID _customerId, TABLE::TableId _tableId) :
	commentId(-1), customerId(_customerId), status(waitingForComming),
	tableId(_tableId), waiterId(-1), taskIdSet()
{
	time(&timeCreated);
}

double ORDER::Order::price()const
{
	double ret = 0.0;
	for (TASK::TaskId id : taskIdSet)
		ret += RESTAURANT::Restaurant::TaskMap.at(id)->price();
	return ret;
}

void ORDER::Order::addTask(TASK::TaskId _taskId)
{
	taskIdSet.insert(_taskId);
}

void ORDER::Order::removeTask(TASK::TaskId _taskId)
{
	if (taskIdSet.find(_taskId) != taskIdSet.cend())
		taskIdSet.erase(_taskId);
	else
		throw std::runtime_error("订单中无此任务，ID: " + std::to_string(_taskId));
}

ORDER::OrderStatus ORDER::Order::getStatus() const
{
	return status;
}

void ORDER::Order::setStatus(OrderStatus _status)
{
	status = _status;
}

COMMENT::CommentId ORDER::Order::getCommentId() const
{
	return commentId;
}

double ORDER::Order::star() const
{
	return CommentMap.at(commentId)->getStar();
}

TABLE::TableId ORDER::Order::getTableId() const
{
	return tableId;
}

const std::set<TASK::TaskId> ORDER::Order::getTaskIdSet() const
{
	return taskIdSet;
}

ACCOUNT::AccountID ORDER::Order::getWaiterId() const
{
	return waiterId;
}

void ORDER::Order::setWaiterId(ACCOUNT::AccountID val)
{
	waiterId = val;
}

double ORDER::Order::price(const DISCOUNT::Discount *discount)const
{
	return discount->netPrice(price(), 
		dynamic_cast<ACCOUNT::CustomerAccount*>
		(RESTAURANT::Restaurant::AccountMap.at(customerId).get())->isVIP());
}

