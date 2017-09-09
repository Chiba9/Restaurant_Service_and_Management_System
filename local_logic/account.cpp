#include "account.h"
#include "people.h"

#include <stdexcept>
#include <vector>
#include <memory>
#include <map>
using std::shared_ptr;
using std::make_shared;
using RESTAURANT::Restaurant;

bool ACCOUNT::CustomerAccount::checkOrder()
{
	if (currentOrderId == -1)
		throw std::runtime_error("订单尚未下达！");
	else return true;
}

bool ACCOUNT::CustomerAccount::checkTask(TASK::TaskId _taskId)
{
	checkOrder();
	if (Restaurant::OrderMap.at(currentOrderId)->getTaskIdSet().find(_taskId)
		== Restaurant::OrderMap.at(currentOrderId)->getTaskIdSet().cend())   //未找到相应任务
		throw std::runtime_error("任务不在订单中！");
	else
		return true;
}

ACCOUNT::CustomerAccount& ACCOUNT::CustomerAccount::removeComment(COMMENT::CommentId id)
{
	commentIdList.removeComment(id);
}

void ACCOUNT::CustomerAccount::startOrder(TABLE::TableId _tableId)
{
	shared_ptr<ORDER::Order> temp = make_shared<ORDER::Order>();
	Restaurant::OrderMap.insert({ temp->id(),temp });

}

void ACCOUNT::CustomerAccount::addTask(DISH::DishId _dishId)
{
	if (checkOrder()) {
		if (Restaurant::OrderMap.at(currentOrderId)->getStatus() == ORDER::ordering
			|| Restaurant::OrderMap.at(currentOrderId)->getStatus() == ORDER::cooking
			|| Restaurant::OrderMap.at(currentOrderId)->getStatus() == ORDER::eating)
		{
			shared_ptr<TASK::Task> temp = make_shared<TASK::Task>(_dishId, currentOrderId);
			Restaurant::TaskMap.insert({ temp->id(),temp });
		}
		else throw std::runtime_error("订单状态有误！");
	}
}

void ACCOUNT::CustomerAccount::urgeTask(TASK::TaskId _taskId)
{
	checkTask(_taskId);
	shared_ptr<TASK::Task> _task = Restaurant::TaskMap.at(_taskId);
	if (_task->getStatus() != TASK::cooking || _task->getStatus() != TASK::serving)
		throw std::runtime_error("该菜已经完成，不必催单！");
	if (_task->getUrgement())
		throw std::runtime_error("该菜已经进行了催单！");
	_task->urge();
}

void ACCOUNT::CustomerAccount::writeWaiterComment(int _star, string _text /*= ""*/)
{
	checkOrder();
	AccountID _waiterId = Restaurant::OrderMap.at(currentOrderId)->getWaiterId();
	shared_ptr<COMMENT::Comment> _comment = make_shared<COMMENT::Comment>(id(), _star, _text);
	auto _waiter = dynamic_cast<WaiterAccount*>(Restaurant::AccountMap.at(_waiterId).get());
	_comment->reTarget(_waiter->getCommentIdList().id());//只需要在Comment中操作（见comment.h）
}


void ACCOUNT::CustomerAccount::writeDishComment(TASK::TaskId _taskId, int _star, string _text /*= ""*/)
{
	checkTask(_taskId);
	shared_ptr<DISH::Dish> _pDish = Restaurant::DishMap.at(Restaurant::TaskMap.at(_taskId)->getDishId());
	shared_ptr<COMMENT::Comment> _comment = make_shared<COMMENT::Comment>(id(), _star, _text);
	_comment->reTarget(_pDish->getCommentListId());
}

void ACCOUNT::CustomerAccount::writeOrderComment(int _star, string _text /*= ""*/)
{
	checkOrder();
	auto _pOrder = Restaurant::OrderMap.at(currentOrderId);
	shared_ptr<COMMENT::Comment> _comment = make_shared<COMMENT::Comment>(id(), _star, _text);
	_comment->reTarget(_pOrder->getCommentId());
}

COMMENT::CommentList ACCOUNT::WaiterAccount::getCommentIdList() const
{
	return commentIdList;
}
