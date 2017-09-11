#include"table.h"

void TABLE::Table::setCurrentOrder(ORDER::OrderId val)
{
	currentOrder = val;
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
	setCurrentOrder(-1);
	setWaiter(-1);
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
