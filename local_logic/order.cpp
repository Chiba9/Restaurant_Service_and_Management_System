#include "order.h"
#include "restaurant.h"
#include <time.h>
#include "discount.h"
#include "task.h"
#include "comment.h"
#include "account.h"

ORDER::Order::Order(AccountID _customerId, AccountID _waiterId,
	TableId _tableId, OrderStatus _status, const time_t& _timeCreated,
	std::set<TaskId> _taskIdSet, CommentId _commentId, unsigned _id):
	ID(_id),
	customerId(_customerId), waiterId(_waiterId), tableId(_tableId),
	status(_status), timeCreated(_timeCreated), taskIdSet(_taskIdSet),
	commentId(_commentId) {}

ORDER::Order::Order(AccountID _customerId, TableId _tableId):
	commentId(Nodata), customerId(_customerId), status(waitingForComming),
	tableId(_tableId), waiterId(Nodata), taskIdSet()
{
	time(&timeCreated);
	RESTAURANT::Restaurant::OrderMap.insert({ id(),std::make_shared<Order>(*this) });
}

double ORDER::Order::price()const
{
	double ret = 0.0;
	for (TaskId id : taskIdSet)
		ret += RESTAURANT::Restaurant::TaskMap.at(id)->price();
	return ret;
}

void ORDER::Order::addTask(TaskId _taskId)
{
	taskIdSet.insert(_taskId);
}

void ORDER::Order::removeTask(TaskId _taskId)
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

CommentId ORDER::Order::getCommentId() const
{
	return commentId;
}

double ORDER::Order::star() const
{
	return RESTAURANT::Restaurant::CommentMap.at(commentId)->getStar();
}

TableId ORDER::Order::getTableId() const
{
	return tableId;
}

const std::set<TaskId>& ORDER::Order::getTaskIdSet() const
{
	return taskIdSet;
}

AccountID ORDER::Order::getWaiterId() const
{
	return waiterId;
}

void ORDER::Order::setWaiterId(AccountID val)
{
	waiterId = val;
}

double ORDER::Order::priceAfterDiscount()const
{
	return RESTAURANT::Restaurant::getDiscount()->netPrice(price(),
		RESTAURANT::Restaurant::CustomerAccountMap.at(customerId)->isVIP());
}

bool ORDER::operator<(const Order& lhs, const Order& rhs)
{
	return lhs.id() < rhs.id();
}

