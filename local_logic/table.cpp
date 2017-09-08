#include"table.h"
TABLE::TableStatus TABLE::Table::getStatus()
{
	return status;
}

void TABLE::Table::reset()
{
	status = empty;
	currentOrder = -1;
	waiterId = -1;
}

ORDER::OrderId TABLE::Table::getOrder() const
{
	return currentOrder;
}

ACCOUNT::AccountID TABLE::Table::getWaiter() const
{
	return waiterId;
}

unsigned TABLE::Table::getTableSize()
{
	return tableSize;
}