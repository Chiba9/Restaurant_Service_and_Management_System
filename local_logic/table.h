#ifndef TABLE_H
#define TABLE_H

#include"id.h"
#include"order.h"
#include"account.h"
namespace TABLE 
{
	using TableId = unsigned;
	enum TableStatus{empty,unassigned,occupied};
	class Table : AbstractID::ID<Table>
	{
		friend void ACCOUNT::WaiterAccount::setTable(TableId _tableId);            //服务员选单后重设服务员/状态
		friend void ACCOUNT::CustomerAccount::startOrder(TABLE::TableId _tableId); //用户下单后订单/重设状态
	private:
		TableStatus status = empty;
		ORDER::OrderId currentOrder = Nodata;
		ACCOUNT::AccountID waiterId = Nodata;
		unsigned tableSize = Nodata;                /*几人桌*/
	public:
		Table() = default;
		Table(unsigned _size);
		Table(TableStatus _status, ORDER::OrderId _currentOrder,
			ACCOUNT::AccountID _waiterId, unsigned _tableSize);
		TableStatus getStatus();
		void reset();                      //重置该桌信息
		ACCOUNT::AccountID getWaiter() const;		
		void setWaiter(ACCOUNT::AccountID val);
		unsigned getTableSize();
		ORDER::OrderId getCurrentOrder() const;
		void setCurrentOrder(ORDER::OrderId val);
		TABLE::TableStatus getStatus() const;
		void setStatus(TABLE::TableStatus val);
	};
}

#endif // TABLE_H