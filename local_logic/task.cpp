#include "task.h"
#include "id.h"

#include "dish.h"
#include "account.h"
#include "order.h"

TASK::Task::Task(DISH::DishId _dishId, ORDER::OrderId _orderId, taskStatus _status,
	ACCOUNT::AccountID _chefId, time_t _timeCreated, bool _urgement):
	dishId(_dishId),orderId(_orderId),status(_status),
	chefId(_chefId),timeCreated(_timeCreated),urgement(_urgement){}

TASK::Task::Task(DISH::DishId _dishId, ORDER::OrderId _orderId):
	dishId(_dishId),orderId(_orderId),status(TASK::choosing),
	chefId(-1),urgement(false)
{
	time(&timeCreated);
}

double TASK::Task::price() const
{
	return DishMap.at(dishId)->getPrice();
}

void TASK::Task::urge()
{
	urgement = true;
}

bool TASK::Task::getUrgement() const
{
	return urgement;
}

void TASK::Task::setStatus(taskStatus _status)
{
	status = _status;
}

void TASK::Task::setOrder(ORDER::OrderId _orderId)
{
	orderId = _orderId;
}

void TASK::Task::setChef(unsigned _chefId)
{
	chefId = _chefId;
}

DISH::DishId TASK::Task::getDishId() const
{
	return dishId;
}

ORDER::OrderId TASK::Task::getOrderId() const
{
	return orderId;
}

ACCOUNT::AccountID TASK::Task::getChefId() const
{
	return chefId;
}

TASK::taskStatus TASK::Task::getStatus() const
{
	return status;
}

void TASK::TaskList::addTask(const TaskId& _taskId)
{
	taskIdList.push_back(_taskId);
}

void TASK::TaskList::removeTask(const TaskId& _taskId)
{
	for (auto it = taskIdList.begin(); it != taskIdList.end();)
		if (*it = _taskId)
			taskIdList.erase(it);
		else
			++it;
}

std::vector<TASK::TaskId>::iterator TASK::TaskList::begin()
{
	return taskIdList.begin();
}

std::vector<TASK::TaskId>::iterator TASK::TaskList::end()
{
	return taskIdList.end();
}

std::vector<TASK::TaskId>::const_iterator TASK::TaskList::cbgin() const
{
	return taskIdList.cbegin();
}

std::vector<TASK::TaskId>::const_iterator TASK::TaskList::cend() const
{
	return cend();
}

