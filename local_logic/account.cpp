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
		throw std::runtime_error("������δ�´");
	else return true;
}

bool ACCOUNT::CustomerAccount::checkTask(TASK::TaskId _taskId)
{
	checkOrder();
	if (Restaurant::OrderMap.at(currentOrderId)->getTaskIdSet().find(_taskId)
		== Restaurant::OrderMap.at(currentOrderId)->getTaskIdSet().cend())   //δ�ҵ���Ӧ����
		throw std::runtime_error("�����ڶ����У�");
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
		else throw std::runtime_error("����״̬����");
	}
}

void ACCOUNT::CustomerAccount::urgeTask(TASK::TaskId _taskId)
{
	checkTask(_taskId);
	shared_ptr<TASK::Task> _task = Restaurant::TaskMap.at(_taskId);
	if (_task->getStatus() != TASK::cooking || _task->getStatus() != TASK::serving)
		throw std::runtime_error("�ò��Ѿ���ɣ����شߵ���");
	if (_task->getUrgement())
		throw std::runtime_error("�ò��Ѿ������˴ߵ���");
	_task->urge();
}

void ACCOUNT::CustomerAccount::writeWaiterComment(int _star, string _text /*= ""*/)
{
	checkOrder();
	AccountID _waiterId = Restaurant::OrderMap.at(currentOrderId)->getWaiterId();
	shared_ptr<COMMENT::Comment> _comment = make_shared<COMMENT::Comment>(id(), _star, _text);
	auto _waiter = dynamic_cast<WaiterAccount*>(Restaurant::AccountMap.at(_waiterId).get());
	_comment->reTarget(_waiter->getCommentIdList().id());//ֻ��Ҫ��Comment�в�������comment.h��
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
