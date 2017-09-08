#include "account.h"
#include "people.h"
#include "GeneralData.h"
#include <vector>

ACCOUNT::string ACCOUNT::CustomerAccount::defaultCustomerHeadPicture;

ACCOUNT::CustomerAccount& ACCOUNT::CustomerAccount::removeComment(unsigned id)
{

}

void ACCOUNT::CustomerAccount::startOrder(TABLE::TableId _tableId)
{

}

void ACCOUNT::CustomerAccount::addTask()
{

}

void ACCOUNT::CustomerAccount::urgeTask(unsigned taskId)
{

}

void ACCOUNT::CustomerAccount::writeComment()
{

}

void ACCOUNT::CustomerAccount::finishOrder()
{

}

void ACCOUNT::CustomerAccount::SendMessage(const string& m)
{

}

bool ACCOUNT::CustomerAccount::isVIP() const
{

}

void ACCOUNT::CustomerAccount::setVIP(bool)
{

}

void ACCOUNT::AdministratorAccount::addAccount(Permission)
{

}

void ACCOUNT::AdministratorAccount::removeAccount(unsigned id)
{

}

void ACCOUNT::AdministratorAccount::addComment()
{

}

void ACCOUNT::AdministratorAccount::removeComment(unsigned id)
{

}

void ACCOUNT::AdministratorAccount::addDish()
{

}

void ACCOUNT::AdministratorAccount::removeDish(unsigned id)
{

}

void ACCOUNT::AdministratorAccount::addDishToMenu(unsigned dishId, unsigned menuId)
{

}

void ACCOUNT::AdministratorAccount::removeDishFromMenu(unsigned dishId, unsigned menuId)
{

}

void ACCOUNT::ChefAccount::getTask(unsigned id)
{

}

void ACCOUNT::ChefAccount::FinishTask()
{

}

double ACCOUNT::ChefAccount::star()
{

}

unsigned ACCOUNT::ChefAccount::finishedTaskCount()
{

}

void ACCOUNT::WaiterAccount::getTable(unsigned id)
{

}

double ACCOUNT::WaiterAccount::star()
{

}

unsigned ACCOUNT::WaiterAccount::finishedOrderCount()
{

}

void ACCOUNT::WaiterAccount::reserveMassage(const string& m)
{

}

void ACCOUNT::WaiterAccount::setTable(TABLE::TableId _tableId)
{

}

void ACCOUNT::WaiterAccount::FinishTable()
{

}
