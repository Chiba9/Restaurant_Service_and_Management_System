#pragma once
#include "dish.h"
#include "comment.h"
#include "task.h"
#include "account.h"
#include "menu.h"
#include "table.h"
#include "discount.h"
#include <map>
#include<vector>
#include <string>


namespace RESTAURANT
{
	using std::map;
	class Restaurant
	{
	public:
		static map<DISH::DishId, DISH::Dish*>DishMap;
		static map<MENU::MenuId, MENU::Menu*>MenuMap;
		static map<COMMENT::CommentId, COMMENT::Comment*>CommentMap;
		static map<ACCOUNT::AccountID, ACCOUNT::Account*>AccountMap;
		static map<TASK::TaskId, TASK::Task*>TaskMap;
		static map<TASK::TaskId, TASK::Task*>CurrrentTaskMap;
		static map<COMMENT::CommentListId, COMMENT::CommentList*>CommentListMap;
		static map<TABLE::TableId, TABLE::Table*> TableMap;
		static DISCOUNT::Discount * getDiscount() { return discount; }
		static void setDiscount(DISCOUNT::Discount * val) { discount = val; }
	private:
		static DISCOUNT::Discount *discount;
	};
}