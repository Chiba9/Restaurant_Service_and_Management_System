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

TABLE::Table::Table(TableStatus _status, OrderId _currentOrder, AccountID _waiterId, unsigned _tableSize) :
	status(_status), currentOrder(_currentOrder),
	waiterId(_waiterId), tableSize(_tableSize)
{

}

TABLE::TableStatus TABLE::Table::getStatus()
{
	return getStatus();
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

AccountID TABLE::Table::getWaiter() const
{
	return getWaiter();
}

unsigned TABLE::Table::getTableSize()
{
	return tableSize;
}

void TABLE::Table::setWaiter(AccountID val)
{
	waiterId = val;
}

OrderId TABLE::Table::getCurrentOrder() const
{
	return currentOrder;
}
