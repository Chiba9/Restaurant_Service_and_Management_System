#pragma once
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
		TableStatus status;
		ORDER::OrderId currentOrder;
		ACCOUNT::AccountID waiterId;
		unsigned tableSize;                /*几人桌*/
	public:
		TableStatus getStatus();
		void reset();                      //重置该桌信息
		ORDER::OrderId getOrder() const;
		ACCOUNT::AccountID getWaiter() const;
		unsigned getTableSize();
	};
}