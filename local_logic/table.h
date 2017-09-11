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
		friend void ACCOUNT::WaiterAccount::setTable(TableId _tableId);            //����Աѡ�����������Ա/״̬
		friend void ACCOUNT::CustomerAccount::startOrder(TABLE::TableId _tableId); //�û��µ��󶩵�/����״̬
	private:
		TableStatus status = empty;
		ORDER::OrderId currentOrder = Nodata;
		ACCOUNT::AccountID waiterId = Nodata;
		unsigned tableSize = Nodata;                /*������*/
	public:
		Table() = default;
		Table(unsigned _size);
		Table(TableStatus _status, ORDER::OrderId _currentOrder,
			ACCOUNT::AccountID _waiterId, unsigned _tableSize);
		TableStatus getStatus();
		void reset();                      //���ø�����Ϣ
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