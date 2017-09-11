#include"table.h"

void TABLE::Table::setCurrentOrder(ORDER::OrderId val)
{
	currentOrder = val;
}

TABLE::Table::Table(unsigned _size) :tableSize(_size)
{

}

TABLE::Table::Table(TableStatus _status, ORDER::OrderId _currentOrder, ACCOUNT::AccountID _waiterId, unsigned _tableSize) :
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

ACCOUNT::AccountID TABLE::Table::getWaiter() const
{
	return getWaiter();
}

unsigned TABLE::Table::getTableSize()
{
	return tableSize;
}

void TABLE::Table::setWaiter(ACCOUNT::AccountID val)
{
	waiterId = val;
}

ORDER::OrderId TABLE::Table::getCurrentOrder() const
{
	return currentOrder;
}
