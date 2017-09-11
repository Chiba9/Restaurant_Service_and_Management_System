#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "dish.h"
#include "comment.h"
#include "task.h"
#include "account.h"
#include "menu.h"
#include "table.h"
#include "discount.h"
#include "order.h"
#include <map>
#include<vector>
#include <string>
#include <memory>
using std::map;
const unsigned Nodata = -1;
namespace RESTAURANT
{
	class Restaurant
	{
	public:
		static map<DISH::DishId, std::shared_ptr<DISH::Dish> >DishMap;
		static map<MENU::MenuId, std::shared_ptr<MENU::Menu> >MenuMap;
		static map<COMMENT::CommentId, std::shared_ptr<COMMENT::Comment> >CommentMap;
		static map<ACCOUNT::AccountID, std::shared_ptr<ACCOUNT::Account> >AccountMap;
		static map<ACCOUNT::AccountID, std::shared_ptr<ACCOUNT::CustomerAccount> >CustomerAccountMap;
		static map<ACCOUNT::AccountID, std::shared_ptr<ACCOUNT::WaiterAccount> >WaiterAccountMap;
		static map<ACCOUNT::AccountID, std::shared_ptr<ACCOUNT::ChefAccount> >ChefAccountMap;
		static map<ACCOUNT::AccountID, std::shared_ptr<ACCOUNT::ManagerAccount> >ManagerAccountMap;
		static map<TASK::TaskId, std::shared_ptr<TASK::Task> >TaskMap;
		static map<TASK::TaskId, std::shared_ptr<TASK::Task> >CurrentTaskMap;
		static map<COMMENT::CommentListId, std::shared_ptr<COMMENT::CommentList> >CommentListMap;
		static map<TABLE::TableId, std::shared_ptr<TABLE::Table> > TableMap;
		static map<ORDER::OrderId, std::shared_ptr<ORDER::Order> >OrderMap;
		static DISCOUNT::Discount * getDiscount() { return discount; }
		static void setDiscount(DISCOUNT::Discount * val) { discount = val; }
	private:
		static DISCOUNT::Discount *discount;
	};
}

#endif // !RESTAURANT_H