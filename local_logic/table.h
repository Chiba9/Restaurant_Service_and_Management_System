#ifndef TABLE_H
#define TABLE_H

#include"id.h"
#include"account.h"
#include "common.h"


namespace TABLE 
{

	enum TableStatus{empty,unassigned,occupied};
	class Table : public AbstractID::ID<Table>
	{
		friend void ACCOUNT::WaiterAccount::addTable(TableId _tableId);            //����Աѡ�����������Ա/״̬
		friend ORDER::Order& ACCOUNT::CustomerAccount::startOrder(TableId _tableId); //�û��µ��󶩵�/����״̬
	private:
		TableStatus status = empty;
		OrderId currentOrder = Nodata;
		AccountID waiterId = Nodata;
		unsigned tableSize = Nodata;                /*������*/
	public:
		Table() = default;
		explicit Table(unsigned _size);
		Table(TableStatus _status, OrderId _currentOrder,
			AccountID _waiterId, unsigned _tableSize,unsigned _id);
		TableStatus getStatus();
		void reset();                      //���ø�����Ϣ
		ACCOUNT::WaiterAccount& getWaiter() const;
		void setWaiter(AccountID val);
		unsigned getTableSize();
		ORDER::Order& getCurrentOrder() const;
		void setCurrentOrder(OrderId val);
		TABLE::TableStatus getStatus() const;
		void setStatus(TABLE::TableStatus val);
	};

	template<typename... Args>
	Table& newTable(Args&&... args)
	{
		TableId _id = Table(std::forward<Args>(args)...).id();
		return *RESTAURANT::Restaurant::TableMap.at(_id);
	}
}

#endif // TABLE_H