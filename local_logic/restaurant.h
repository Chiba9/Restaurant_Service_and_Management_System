#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <map>
#include<vector>
#include <string>
#include <memory>
#include "common.h"

using std::map;

namespace RESTAURANT
{

	class Restaurant
	{
	public:
		static map<DishId, std::shared_ptr<DISH::Dish> >DishMap;
		static map<MenuId, std::shared_ptr<MENU::Menu> >MenuMap;
		static map<CommentId, std::shared_ptr<COMMENT::Comment> >CommentMap;
		static map<AccountID, std::shared_ptr<ACCOUNT::Account> >AccountMap;
		static map<AccountID, std::shared_ptr<ACCOUNT::CustomerAccount> >CustomerAccountMap;
		static map<AccountID, std::shared_ptr<ACCOUNT::WaiterAccount> >WaiterAccountMap;
		static map<AccountID, std::shared_ptr<ACCOUNT::ChefAccount> >ChefAccountMap;
		static map<AccountID, std::shared_ptr<ACCOUNT::ManagerAccount> >ManagerAccountMap;
		static map<TaskId, std::shared_ptr<TASK::Task> >TaskMap;
		static map<TaskId, std::shared_ptr<TASK::Task> >CurrentTaskMap;
		static map<CommentListId, std::shared_ptr<COMMENT::CommentList> >CommentListMap;
		static map<TableId, std::shared_ptr<TABLE::Table> > TableMap;
		static map<OrderId, std::shared_ptr<ORDER::Order> >OrderMap;
		static DISCOUNT::Discount * getDiscount() { return discount; }
		static void setDiscount(DISCOUNT::Discount * val) { discount = val; }
	private:
		static DISCOUNT::Discount *discount;
	};
}

#endif // !RESTAURANT_H