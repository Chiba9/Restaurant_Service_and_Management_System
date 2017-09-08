#include "order.h"
#include "GeneralData.h"
double ORDER::Order::price()
{
	double ret = 0.0;
	for (TASK::TaskId id : taskIdSet)
		ret += TaskMap.at(id)->price();
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

double ORDER::Order::price(const DISCOUNT::Discount *discount)
{
	return discount->netPrice(price(), 
		dynamic_cast<ACCOUNT::CustomerAccount*>(AccountMap.at(customerId))->isVIP());
}

