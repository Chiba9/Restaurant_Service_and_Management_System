#ifndef TABLE_H
#define TABLE_H

#include"id.h"
#include"account.h"
#include "common.h"


namespace TABLE 
{

	enum TableStatus{empty,unassigned,occupied};
	class Table : AbstractID::ID<Table>
	{
		friend void ACCOUNT::WaiterAccount::setTable(TableId _tableId);            //����Աѡ�����������Ա/״̬
		friend void ACCOUNT::CustomerAccount::startOrder(TableId _tableId); //�û��µ��󶩵�/����״̬
	private:
		TableStatus status = empty;
		OrderId currentOrder = Nodata;
		AccountID waiterId = Nodata;
		unsigned tableSize = Nodata;                /*������*/
	public:
		Table() = default;
		Table(unsigned _size);
		Table(TableStatus _status, OrderId _currentOrder,
			AccountID _waiterId, unsigned _tableSize);
		TableStatus getStatus();
		void reset();                      //���ø�����Ϣ
		AccountID getWaiter() const;		
		void setWaiter(AccountID val);
		unsigned getTableSize();
		OrderId getCurrentOrder() const;
		void setCurrentOrder(OrderId val);
		TABLE::TableStatus getStatus() const;
		void setStatus(TABLE::TableStatus val);
	};
}

#endif // TABLE_H