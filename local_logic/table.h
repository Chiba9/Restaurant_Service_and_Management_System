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
		ORDER::OrderId getOrder() const;
		ACCOUNT::AccountID getWaiter() const;
		unsigned getTableSize();
	};
}