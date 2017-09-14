#include "account.h"
#include "people.h"
#include "order.h"
#include "table.h"
#include "dish.h"
#include <stdexcept>
#include <vector>
#include <memory>
#include <map>
#include <time.h>

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

ACCOUNT::Account::Account(Permission pm, string n, string p) :type(pm),userName(n), passWord(p)
{
	time(&timeCreated);
	Restaurant::AccountMap.insert({ id(), std::make_shared<Account>(*this) });
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

ACCOUNT::Account::Account(Permission pm, string n, string p, string pic) :
	type(pm), userName(n), passWord(p), headPicture(pic)
{
	time(&timeCreated);
	Restaurant::AccountMap.insert({ id(), std::make_shared<Account>(*this) });
}

ACCOUNT::Account::Account(Permission pm, string n, string p, string pic, time_t t,unsigned _id) :
	ID(_id), type(pm), userName(n), passWord(p), timeCreated(t), headPicture(pic)
{
	
}



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
		== Restaurant::OrderMap.at(currentOrderId)->getTaskIdSet().end())   //未找到相应任务
		throw std::runtime_error("任务不在订单中！");
	else
		return true;
}

void ACCOUNT::CustomerAccount::creatCommentList()
{
	if (commentListId == Nodata) {
		commentListId = COMMENT::newCommentList().id();
	}
}

ACCOUNT::CustomerAccount::CustomerAccount(string n, string p)
	:Account(customer,n,p)
{
	creatCommentList();
	type = customer;
	Restaurant::CustomerAccountMap.insert({ id(),std::make_shared<CustomerAccount>(*this) });
}

ACCOUNT::CustomerAccount::CustomerAccount(string n, string p, string pic)
	:Account(customer,n,p,pic)
{
	creatCommentList();
	type = customer;
	Restaurant::CustomerAccountMap.insert({ id(),std::make_shared<CustomerAccount>(*this) });
}

ACCOUNT::CustomerAccount::CustomerAccount(string n, string p, string pic, time_t t, CommentListId c_id, unsigned _id)
	:Account(customer,n,p,pic,t,_id),commentListId(c_id)
{
	creatCommentList();
	type = customer;
}

ACCOUNT::CustomerAccount& ACCOUNT::CustomerAccount::removeComment(CommentId id)
{
	Restaurant::CommentMap.at(id)->reTarget(-1);
	Restaurant::CommentListMap.at(commentListId)->removeComment(id);
	return *this;
}

ORDER::Order& ACCOUNT::CustomerAccount::getOrder() const
{
	return *RESTAURANT::Restaurant::OrderMap.at(currentOrderId);
}

ORDER::Order& ACCOUNT::CustomerAccount::startOrder(TableId _tableId)
{
	if (RESTAURANT::Restaurant::TableMap.at(_tableId)->getStatus() == TABLE::empty) {
		shared_ptr<ORDER::Order> temp = make_shared<ORDER::Order>(id(), _tableId);
		currentOrderId = temp->id();
		Restaurant::TableMap.at(_tableId)->setStatus(TABLE::unassigned);
		Restaurant::TableMap.at(_tableId)->setCurrentOrder(currentOrderId);
		currentOrderId = temp->id();
		return getOrder();
	}
	else
		throw std::runtime_error("该桌有人！");
}

TASK::Task& ACCOUNT::CustomerAccount::addTask(DishId _dishId)
{
	if (checkOrder()) {
		const ORDER::OrderStatus& orderStatus = getOrder().getStatus();
		if (orderStatus == ORDER::waitingForComming
			|| orderStatus == ORDER::ordering
			|| orderStatus == ORDER::cooking
			|| orderStatus == ORDER::eating)
		{
			if (orderStatus == ORDER::waitingForComming)
				getOrder().setStatus(ORDER::ordering);
			TASK::Task& temp = TASK::newTask(_dishId, currentOrderId);
			getOrder().addTask(temp.id());
			return temp;
		}
		else throw std::runtime_error("订单状态有误！");
	}
}

void ACCOUNT::CustomerAccount::quitTask(TaskId _taskId)
{
	checkTask(_taskId);
	shared_ptr<TASK::Task> _task = Restaurant::TaskMap.at(_taskId);
	if (_task->getStatus() == TASK::choosing || _task->getStatus() == TASK::waiting) {
		if (_task->getStatus() == TASK::waiting) {
			Restaurant::CurrentTaskMap.erase(_taskId);
		}
		getOrder().removeTask(_taskId);
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
		for (TaskId _taskId : _order->getTaskIdSet()) {
			if (Restaurant::TaskMap.at(_taskId)->getStatus() == TASK::choosing) {
				Restaurant::TaskMap.at(_taskId)->setStatus(TASK::waiting);
				Restaurant::CurrentTaskMap.insert({ _taskId, Restaurant::TaskMap.at(_taskId) });
			}
		}
		_order->setStatus(ORDER::cooking);
	}
}

void ACCOUNT::CustomerAccount::urgeTask(TaskId _taskId)
{
	checkTask(_taskId);
	shared_ptr<TASK::Task> _task = Restaurant::TaskMap.at(_taskId);
	if (_task->getStatus() != TASK::waiting 
		&& _task->getStatus() != TASK::cooking 
		&& _task->getStatus() != TASK::serving)
		throw std::runtime_error("该菜已经完成，不必催单！");
	if (_task->getUrgement())
		throw std::runtime_error("该菜已经进行了催单！");
	_task->urge();
}

COMMENT::Comment& ACCOUNT::CustomerAccount::writeWaiterComment(int _star, string _text /*= ""*/)
{
	checkOrder();
	AccountID _waiterId = Restaurant::OrderMap.at(currentOrderId)->getWaiterId();
	COMMENT::Comment& _comment = COMMENT::newComment(id(),_star, _text,
		RESTAURANT::Restaurant::WaiterAccountMap.at(_waiterId)->getCommentIdList().id());
	Restaurant::CommentListMap.at(commentListId)->addComment(_comment.id());
	return _comment;
}


COMMENT::Comment& ACCOUNT::CustomerAccount::writeDishComment(TaskId _taskId, int _star, string _text /*= ""*/)
{
	checkTask(_taskId);
	shared_ptr<DISH::Dish> _pDish = Restaurant::DishMap.at(Restaurant::TaskMap.at(_taskId)->getDishId());
	COMMENT::Comment& _comment = COMMENT::newComment(id(),_star, _text,
		_pDish->getCommentList().id());
	Restaurant::TaskMap.at(_taskId)->setStar(_star);
	Restaurant::CommentListMap.at(commentListId)->addComment(_comment.id());
	return _comment;
}

COMMENT::Comment& ACCOUNT::CustomerAccount::writeOrderComment(int _star, string _text /*= ""*/)
{
	checkOrder();
	auto _pOrder = Restaurant::OrderMap.at(currentOrderId);
	COMMENT::Comment& _comment = COMMENT::newComment(id(), _star, _text);
	Restaurant::CommentListMap.at(commentListId)->addComment(_comment.id());
	return _comment;
}

void ACCOUNT::CustomerAccount::finishCurrentOrder()
{
	checkOrder();
	previousOrderIdSet.insert(currentOrderId);
	shared_ptr<ORDER::Order> _order = Restaurant::OrderMap.at(currentOrderId);
	moneyUsed += _order->price();
	currentOrderId = Nodata;
	AccountID _waiterId = _order->getWaiterId();
	for (TaskId _taskId : _order->getTaskIdSet())
		Restaurant::TaskMap.at(_taskId)->setStatus(TASK::finished);
	auto _waiter = Restaurant::WaiterAccountMap.at(_waiterId);
	_waiter->FinishTable(_order->getTableId());
	_order->setStatus(ORDER::finished);
	checkVIP();
}

void ACCOUNT::CustomerAccount::SendMessage(const string& m)
{
	AccountID _waiterId = Restaurant::OrderMap.at(currentOrderId)->getWaiterId();
	auto _waiter = Restaurant::WaiterAccountMap.at(_waiterId);
	_waiter->reserveMassage(m,id());
}

bool ACCOUNT::CustomerAccount::isVIP() const
{
	return VIP;
}


void ACCOUNT::CustomerAccount::checkVIP()
{
	if (moneyUsed > RESTAURANT::Restaurant::VIPmoney)
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

ACCOUNT::ChefAccount::ChefAccount(string n, string p)
	:Account(chef, n, p)
{
	type = chef;
	Restaurant::ChefAccountMap.insert({ id(),std::make_shared<ChefAccount>(*this) });
}

ACCOUNT::ChefAccount::ChefAccount(string n, string p, string pic)
	: Account(chef, n, p, pic)
{
	type = chef;
	Restaurant::ChefAccountMap.insert({ id(),std::make_shared<ChefAccount>(*this) });
}

ACCOUNT::ChefAccount::ChefAccount(string n, string p, string pic, time_t t,unsigned _id)
	: Account(chef, n, p, pic, t, _id)
{
	type = chef;
}

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

ACCOUNT::WaiterAccount::WaiterAccount(string n, string p)
	:Account(waiter, n, p)
{
	type = waiter;
	creatCommentList();
	Restaurant::WaiterAccountMap.insert({ id(),std::make_shared<WaiterAccount>(*this) });
}

ACCOUNT::WaiterAccount::WaiterAccount(string n, string p, string pic)
	:Account(waiter, n, p, pic)
{
	type = waiter;
	creatCommentList();
	Restaurant::WaiterAccountMap.insert({ id(),std::make_shared<WaiterAccount>(*this) });
}

ACCOUNT::WaiterAccount::WaiterAccount(string n, string p, string pic, time_t t, CommentListId c_id, unsigned _id)
	: Account(waiter, n, p, pic, t, _id),commentListId(c_id)
{
	type = waiter;
	creatCommentList();
}

const std::set<TableId>& ACCOUNT::WaiterAccount::getTables() const
{
	return currentTables;
}

TABLE::Table& ACCOUNT::WaiterAccount::getTable(TableId _id) const
{
	if (currentTables.find(_id) != currentTables.end())
		return *RESTAURANT::Restaurant::TableMap.at(_id);
	else
		throw std::runtime_error("没有在服务此桌！");
}

bool ACCOUNT::WaiterAccount::free()
{
	return currentTables.empty();
}

double ACCOUNT::WaiterAccount::star()
{
	return Restaurant::CommentListMap.at(commentListId)->star();
}

unsigned ACCOUNT::WaiterAccount::finishedOrderCount()
{
	return previousOrder.size();
}

std::string ACCOUNT::WaiterAccount::reserveMassage(const string& m, TableId _id)
{
	return m;
}

void ACCOUNT::WaiterAccount::addTable(TableId _tableId)
{
	currentTables.insert(_tableId);
	getTable(_tableId).setWaiter(this->id());
	getTable(_tableId).setStatus(TABLE::occupied);
	getTable(_tableId).getCurrentOrder().setWaiterId(id());
}

void ACCOUNT::WaiterAccount::addComment(CommentId _commetId)
{
	Restaurant::CommentListMap.at(commentListId)->addComment(_commetId);
}

void ACCOUNT::WaiterAccount::serveTask(TaskId _id)
{
	auto _tableId = currentTables.find(RESTAURANT::Restaurant::TaskMap.at(_id)->getTableId());
	if (_tableId != currentTables.end())
	{
		if (Restaurant::TaskMap.at(_id)->getStatus() == TASK::serving) {
			Restaurant::TaskMap.at(_id)->setStatus(TASK::eating);
			bool flag = true;  //使订单状态变化的bool值
			for (auto i : RESTAURANT::Restaurant::TableMap.at(*_tableId)->getCurrentOrder().getTaskIdSet())
				if (RESTAURANT::Restaurant::TaskMap.at(i)->getStatus() != TASK::eating)
				{
					flag = false;
				}
			if (flag)
				RESTAURANT::Restaurant::TableMap.at(*_tableId)->getCurrentOrder().setStatus(ORDER::eating);
		}
		else throw std::runtime_error("该菜还没做好！");
	}
	else
		throw std::runtime_error("该菜不由您服务！");
}

COMMENT::CommentList ACCOUNT::WaiterAccount::getCommentIdList() const
{
	return *Restaurant::CommentListMap.at(commentListId);
}

void ACCOUNT::WaiterAccount::FinishTable(TableId _id)
{
	if (currentTables.find(_id) != currentTables.end()) {
		currentTables.erase(_id);
		previousOrder.insert(RESTAURANT::Restaurant::TableMap.at(_id)->getCurrentOrder().id());
		Restaurant::TableMap.at(_id)->reset();
	}
	else
		throw std::runtime_error("不在服务此桌！");
}

void ACCOUNT::WaiterAccount::creatCommentList()
{
	if (commentListId == Nodata) {
		commentListId = COMMENT::newCommentList().id();
	}
}

ACCOUNT::ManagerAccount::ManagerAccount(string n, string p)
	:Account(manager, n, p)
{
	type = manager;	
	Restaurant::ManagerAccountMap.insert({ id(),std::make_shared<ManagerAccount>(*this) });
}

ACCOUNT::ManagerAccount::ManagerAccount(string n, string p, string pic)
	: Account(manager, n, p, pic)
{
	type = manager;
	Restaurant::ManagerAccountMap.insert({ id(),std::make_shared<ManagerAccount>(*this) });
}

ACCOUNT::ManagerAccount::ManagerAccount(string n, string p, string pic, time_t t, unsigned _id)
	: Account(manager, n, p, pic, t, _id)
{
	type = manager;
}