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
		friend void ACCOUNT::WaiterAccount::setTable(TableId _tableId);            //����Աѡ�����������Ա/״̬
		friend void ACCOUNT::CustomerAccount::startOrder(TABLE::TableId _tableId); //�û��µ��󶩵�/����״̬
	private:
		TableStatus status;
		ORDER::OrderId currentOrder;
		ACCOUNT::AccountID waiterId;
		unsigned tableSize;                /*������*/
	public:
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