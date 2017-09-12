#include "task.h"
#include "id.h"
#include "restaurant.h"
#include "dish.h"
#include "account.h"
#include "order.h"
#include "RestaurantSystem.h"

TASK::Task::Task(DishId _dishId, OrderId _orderId, taskStatus _status,
	AccountID _chefId, time_t _timeCreated, bool _urgement):
	dishId(_dishId),orderId(_orderId),status(_status),
	chefId(_chefId),timeCreated(_timeCreated),urgement(_urgement){}

TASK::Task::Task(DishId _dishId, OrderId _orderId):
	dishId(_dishId),orderId(_orderId),status(TASK::choosing),
	chefId(Nodata),urgement(false)
{
	time(&timeCreated);
}

double TASK::Task::price() const
{
	return RESTAURANT::Restaurant::DishMap.at(dishId)->getPrice();
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

void TASK::Task::setOrder(OrderId _orderId)
{
	orderId = _orderId;
}

void TASK::Task::setChef(unsigned _chefId)
{
	chefId = _chefId;
}

DishId TASK::Task::getDishId() const
{
	return dishId;
}

OrderId TASK::Task::getOrderId() const
{
	return orderId;
}

AccountID TASK::Task::getChefId() const
{
	return chefId;
}

TASK::taskStatus TASK::Task::getStatus() const
{
	return status;
}

double TASK::Task::getStar() const
{
	return star;
}

void TASK::Task::setStar(double val)
{
	star = val;
}

double TASK::TaskList::star() const
{
	double sum = 0.0;
	unsigned count = 0;
	for (TaskId _id : taskIdList)
		if (RESTAURANT::Restaurant::TaskMap.at(_id)->getStar() != Nodata) {
			sum += RESTAURANT::Restaurant::TaskMap.at(_id)->getStar();
			++count;
		}
	if (count != 0)
		return sum / count;
	else
		return Nodata;
}

std::size_t TASK::TaskList::size() const
{
	return taskIdList.size();
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

std::vector<TaskId>::iterator TASK::TaskList::begin()
{
	return taskIdList.begin();
}

std::vector<TaskId>::iterator TASK::TaskList::end()
{
	return taskIdList.end();
}

std::vector<TaskId>::const_iterator TASK::TaskList::cbgin() const
{
	return taskIdList.cbegin();
}

std::vector<TaskId>::const_iterator TASK::TaskList::cend() const
{
	return cend();
}

