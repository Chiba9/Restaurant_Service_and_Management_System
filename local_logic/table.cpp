#include"table.h"
#include "RestaurantSystem.h"
void TABLE::Table::setCurrentOrder(OrderId val)
{
	currentOrder = val;
}

TABLE::Table::Table(unsigned _size) :tableSize(_size)
{
	RESTAURANT::Restaurant::TableMap.insert({ id(),std::make_shared<Table>(*this) });
}

TABLE::Table::Table(TableStatus _status, OrderId _currentOrder, AccountID _waiterId, unsigned _tableSize,unsigned _id) :
	ID(_id),
	status(_status), currentOrder(_currentOrder),
	waiterId(_waiterId), tableSize(_tableSize)
{

}

TABLE::TableStatus TABLE::Table::getStatus()
{
	return status;
}

TABLE::TableStatus TABLE::Table::getStatus() const
{
	return status;
}

void TABLE::Table::setStatus(TABLE::TableStatus val)
{
	status = val;
}

void TABLE::Table::reset()
{
	setStatus(empty);
	setCurrentOrder(Nodata);
	setWaiter(Nodata);
}

ACCOUNT::WaiterAccount& TABLE::Table::getWaiter() const
{
	return *RESTAURANT::Restaurant::WaiterAccountMap.at(waiterId);
}

unsigned TABLE::Table::getTableSize()
{
	return tableSize;
}

void TABLE::Table::setWaiter(AccountID val)
{
	waiterId = val;
}

ORDER::Order& TABLE::Table::getCurrentOrder() const
{
	return *RESTAURANT::Restaurant::OrderMap.at(currentOrder);
}
