#include "account.h"
#include "people.h"
#include "order.h"
#include "table.h"
#include "dish.h"
#include <stdexcept>
#include <vector>
#include <memory>
#include <map>

using std::shared_ptr;
using std::make_shared;
using RESTAURANT::Restaurant;

ACCOUNT::string& ACCOUNT::Account::UserName()
{
	return userName;
}

const ACCOUNT::string& ACCOUNT::Account::UserName() const
{
	return userName;
}

ACCOUNT::string& ACCOUNT::Account::PassWord()
{
	return passWord;
}

const ACCOUNT::string& ACCOUNT::Account::PassWord() const
{
	return passWord;
}

ACCOUNT::string& ACCOUNT::Account::HeadPicture()
{
	return headPicture;
}

const ACCOUNT::string& ACCOUNT::Account::HeadPicture() const
{
	return headPicture;
}

void ACCOUNT::Account::changePassword(const string& prevPassWord, const string& newPassWord)
{
	if (prevPassWord == passWord)
		passWord = newPassWord;
	else
		throw std::runtime_error("密码错误！");
}

std::string ACCOUNT::Account::defaultCustomerHeadPicture = "defaultCustomerHeadPicture";

ACCOUNT::string ACCOUNT::Account::defaultWaiterHeadPicture = "defaultWaiterHeadPicture";

ACCOUNT::string ACCOUNT::Account::defaultChefHeadPicture = "defaultChefHeadPicture";

ACCOUNT::string ACCOUNT::Account::defaultAdministratorHeadPicture = "defaultAdministratorHeadPicture";

ACCOUNT::string ACCOUNT::Account::defaultManagerHeadPicture = "defaultManagerHeadPicture";

ACCOUNT::Account::Account(string n, string p) :userName(n), passWord(p)
{
	time(&timeCreated);
}

void ACCOUNT::Account::setDefaultHeadPicture(Permission _permission)
{
	switch (_permission)
	{
	case ACCOUNT::customer:
		headPicture = defaultCustomerHeadPicture;
		break;
	case ACCOUNT::administrator:
		headPicture = defaultAdministratorHeadPicture;
		break;
	case ACCOUNT::chef:
		headPicture = defaultChefHeadPicture;
		break;
	case ACCOUNT::waiter:
		headPicture = defaultWaiterHeadPicture;
		break;
	case ACCOUNT::manager:
		headPicture = defaultManagerHeadPicture;
		break;
	default:
		break;
	}
}

ACCOUNT::Account::Account(string n, string p, string pic) :
	userName(n), passWord(p), headPicture(pic)
{

}

ACCOUNT::Account::Account(string n, string p, time_t t, string pic) :
	userName(n), passWord(p), timeCreated(t), headPicture(pic)
{
	time(&timeCreated);
}

double ACCOUNT::CustomerAccount::VIPmoney = 500;

bool ACCOUNT::CustomerAccount::checkOrder()
{
	if (currentOrderId == Nodata)
		throw std::runtime_error("订单尚未下达！");
	else return true;
}

bool ACCOUNT::CustomerAccount::checkTask(TaskId _taskId)
{
	checkOrder();
	if (Restaurant::OrderMap.at(currentOrderId)->getTaskIdSet().find(_taskId)
		== Restaurant::OrderMap.at(currentOrderId)->getTaskIdSet().cend())   //未找到相应任务
		throw std::runtime_error("任务不在订单中！");
	else
		return true;
}

ACCOUNT::CustomerAccount& ACCOUNT::CustomerAccount::removeComment(CommentId id)
{
	commentIdList.removeComment(id);
}

void ACCOUNT::CustomerAccount::startOrder(TableId _tableId)
{
	shared_ptr<ORDER::Order> temp = make_shared<ORDER::Order>(id(), _tableId);
	Restaurant::TableMap.at(_tableId)->setStatus(TABLE::unassigned);
	Restaurant::OrderMap.insert({ temp->id(),temp });
}

void ACCOUNT::CustomerAccount::addTask(DishId _dishId)
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

void ACCOUNT::CustomerAccount::quitTask(TaskId _taskId)
{
	checkTask(_taskId);
	shared_ptr<TASK::Task> _task = Restaurant::TaskMap.at(_taskId);
	if (_task->getStatus() == TASK::choosing || _task->getStatus() == TASK::choosing) {
		if (_task->getStatus() == TASK::choosing) {
			Restaurant::CurrentTaskMap.erase(_taskId);
		}
		_task->setStatus(TASK::quitted);
		_task->setChef(Nodata);
		_task->setOrder(Nodata);
	}
	else throw std::runtime_error("菜已煮好不能放弃！");
}

void ACCOUNT::CustomerAccount::finishOrdering()
{
	if (checkOrder())
	{
		shared_ptr<ORDER::Order> _order = Restaurant::OrderMap.at(currentOrderId);
		for (TaskId _taskId : _order->getTaskIdSet())
			Restaurant::TaskMap.at(_taskId)->setStatus(TASK::waiting);
		_order->setStatus(ORDER::cooking);
	}
}

void ACCOUNT::CustomerAccount::urgeTask(TaskId _taskId)
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
	auto _waiter = Restaurant::WaiterAccountMap.at(_waiterId).get();
	_comment->reTarget(_waiter->getCommentIdList().id());//只需要在Comment中操作（见comment.h）
	commentIdList.addComment(_comment->id());
}


void ACCOUNT::CustomerAccount::writeDishComment(TaskId _taskId, int _star, string _text /*= ""*/)
{
	checkTask(_taskId);
	shared_ptr<DISH::Dish> _pDish = Restaurant::DishMap.at(Restaurant::TaskMap.at(_taskId)->getDishId());
	shared_ptr<COMMENT::Comment> _comment = make_shared<COMMENT::Comment>(id(), _star, _text);
	_comment->reTarget(_pDish->getCommentListId());
	commentIdList.addComment(_comment->id());
	Restaurant::TaskMap.at(_taskId)->setStar(_star);
}

void ACCOUNT::CustomerAccount::writeOrderComment(int _star, string _text /*= ""*/)
{
	checkOrder();
	auto _pOrder = Restaurant::OrderMap.at(currentOrderId);
	shared_ptr<COMMENT::Comment> _comment = make_shared<COMMENT::Comment>(id(), _star, _text);
	_comment->reTarget(_pOrder->getCommentId());
	commentIdList.addComment(_comment->id());
}

void ACCOUNT::CustomerAccount::finishCurrentOrder()
{
	checkOrder();
	previousOrderIdSet.emplace(currentOrderId);
	shared_ptr<ORDER::Order> _order = Restaurant::OrderMap.at(currentOrderId);
	moneyUsed += _order->price();
	AccountID _waiterId = _order->getWaiterId();
	for (TaskId _taskId : _order->getTaskIdSet())
		Restaurant::TaskMap.at(_taskId)->setStatus(TASK::finished);
	auto _waiter = Restaurant::WaiterAccountMap.at(_waiterId);
	_waiter->FinishTable();
	_waiter->setTable(Nodata);
	_order->setStatus(ORDER::finished);
	checkVIP();
}

void ACCOUNT::CustomerAccount::SendMessage(const string& m)
{
	AccountID _waiterId = Restaurant::OrderMap.at(currentOrderId)->getWaiterId();
	auto _waiter = Restaurant::WaiterAccountMap.at(_waiterId);
	_waiter->reserveMassage(m);
}

bool ACCOUNT::CustomerAccount::isVIP() const
{
	return VIP;
}


bool ACCOUNT::CustomerAccount::checkVIP()
{
	if (moneyUsed > VIPmoney)
		VIP = true;
}

/*void ACCOUNT::AdministratorAccount::addAccount(Permission _permission)
{
switch (_permission)
{
case ACCOUNT::customer:
break;
case ACCOUNT::administrator:
break;
case ACCOUNT::chef:
break;
case ACCOUNT::waiter:
break;
case ACCOUNT::manager:
break;
default:
break;
}
}*/


void ACCOUNT::ChefAccount::getTask(TaskId _id)
{
	if (Restaurant::CurrentTaskMap.find(_id) != Restaurant::CurrentTaskMap.end())
	{
		currentTask = _id;
		Restaurant::CurrentTaskMap.at(_id)->setChef(id());
		Restaurant::CurrentTaskMap.at(_id)->setStatus(TASK::cooking);
		Restaurant::CurrentTaskMap.erase(_id);
	}
	else throw std::runtime_error("当前订单列表中未找到此订单！");
}

void ACCOUNT::ChefAccount::FinishTask()
{
	if (!free()) {
		previousTaskList.addTask(currentTask);
		Restaurant::TaskMap.at(currentTask)->setStatus(TASK::serving);
		currentTask = Nodata;
	}
}

bool ACCOUNT::ChefAccount::free()
{
	return currentTask == Nodata;
}

double ACCOUNT::ChefAccount::star()
{
	return previousTaskList.star();
}

unsigned ACCOUNT::ChefAccount::finishedTaskCount()
{
	return previousTaskList.size();
}

TASK::TaskList ACCOUNT::ChefAccount::getPreviousTaskList() const
{
	return previousTaskList;
}

TableId ACCOUNT::WaiterAccount::getTable() const
{
	return currentTable;
}

bool ACCOUNT::WaiterAccount::free()
{
	return currentTable == Nodata;
}

double ACCOUNT::WaiterAccount::star()
{
	return Restaurant::CommentListMap.at(commentListId)->star();
}

unsigned ACCOUNT::WaiterAccount::finishedOrderCount()
{
	return previousOrder.size();
}

std::string ACCOUNT::WaiterAccount::reserveMassage(const string& m)
{
	return m;
}

void ACCOUNT::WaiterAccount::setTable(TableId _tableId)
{
	currentTable = _tableId;
}

void ACCOUNT::WaiterAccount::addComment(CommentId _commetId)
{
	Restaurant::CommentListMap.at(commentListId)->addComment(_commetId);
}

COMMENT::CommentList ACCOUNT::WaiterAccount::getCommentIdList() const
{
	return *Restaurant::CommentListMap.at(commentListId);
}

void ACCOUNT::WaiterAccount::FinishTable()
{
	Restaurant::TableMap.at(currentTable)->reset();
	currentTable = Nodata;
}