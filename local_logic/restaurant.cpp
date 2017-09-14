#include "restaurant.h"
#include "discount.h"
using namespace RESTAURANT;

map<DishId, std::shared_ptr<DISH::Dish> > RESTAURANT::Restaurant::DishMap = 
map<DishId, std::shared_ptr<DISH::Dish> >();
map<MenuId, std::shared_ptr<MENU::Menu> > RESTAURANT::Restaurant::MenuMap =
map<MenuId, std::shared_ptr<MENU::Menu> >();
map<CommentId, std::shared_ptr<COMMENT::Comment> > RESTAURANT::Restaurant::CommentMap =
map<CommentId, std::shared_ptr<COMMENT::Comment> >();
map<AccountID, std::shared_ptr<ACCOUNT::Account> > RESTAURANT::Restaurant::AccountMap = 
map<AccountID, std::shared_ptr<ACCOUNT::Account> >();
map<AccountID, std::shared_ptr<ACCOUNT::CustomerAccount> > RESTAURANT::Restaurant::CustomerAccountMap = 
map<AccountID, std::shared_ptr<ACCOUNT::CustomerAccount> >();
map<AccountID, std::shared_ptr<ACCOUNT::WaiterAccount> > RESTAURANT::Restaurant::WaiterAccountMap = 
map<AccountID, std::shared_ptr<ACCOUNT::WaiterAccount> >();
map<AccountID, std::shared_ptr<ACCOUNT::ChefAccount> > RESTAURANT::Restaurant::ChefAccountMap = 
map<AccountID, std::shared_ptr<ACCOUNT::ChefAccount> >();
map<AccountID, std::shared_ptr<ACCOUNT::ManagerAccount> > RESTAURANT::Restaurant::ManagerAccountMap = 
map<AccountID, std::shared_ptr<ACCOUNT::ManagerAccount> >();
map<TaskId, std::shared_ptr<TASK::Task> > RESTAURANT::Restaurant::TaskMap = 
map<TaskId, std::shared_ptr<TASK::Task> >();
map<TaskId, std::shared_ptr<TASK::Task> > RESTAURANT::Restaurant::CurrentTaskMap = 
map<TaskId, std::shared_ptr<TASK::Task> >();
map<CommentListId, std::shared_ptr<COMMENT::CommentList> > RESTAURANT::Restaurant::CommentListMap = 
map<CommentListId, std::shared_ptr<COMMENT::CommentList> >();
map<TableId, std::shared_ptr<TABLE::Table> > RESTAURANT::Restaurant::TableMap = 
map<TableId, std::shared_ptr<TABLE::Table> >();
map<OrderId, std::shared_ptr<ORDER::Order> > RESTAURANT::Restaurant::OrderMap = 
map<OrderId, std::shared_ptr<ORDER::Order> >();

void RESTAURANT::Restaurant::setDiscount(DISCOUNT::Discount* val)
{
	discount = val;
}



double RESTAURANT::Restaurant::VIPmoney = 500;

void RESTAURANT::Restaurant::setDiscount()
{
	discount = new DISCOUNT::OverPercentDiscount(0, 0);     //ƒ¨»œ’€ø€£¨≤ª¥Ú’€
}

void RESTAURANT::Restaurant::setDiscount(DiscountType _type, double _threshold, 
	double _threshold_VIP, double _discount, double _discount_VIP)
{
	switch (_type)
	{
	case RESTAURANT::overPercent:
		discount = new DISCOUNT::OverPercentDiscount
		(_threshold, _threshold_VIP, _discount, _discount_VIP);
		break;
	case RESTAURANT::allPercent:
		discount = new DISCOUNT::AllPercentDiscount
		(_threshold, _threshold_VIP, _discount, _discount_VIP);
		break;
	case RESTAURANT::overMinus:
		discount = new DISCOUNT::OverMinusDiscount
		(_threshold, _threshold_VIP, _discount, _discount_VIP);
		break;
	default:
		break;
	}
}

void RESTAURANT::Restaurant::setDiscount(DiscountType _type, double _threshold, double _discount)
{
	switch (_type)
	{
	case RESTAURANT::overPercent:
		discount = new DISCOUNT::OverPercentDiscount
		(_threshold, _discount);
		break;
	case RESTAURANT::allPercent:
		discount = new DISCOUNT::AllPercentDiscount
		(_threshold, _discount);
		break;
	case RESTAURANT::overMinus:
		discount = new DISCOUNT::OverMinusDiscount
		(_threshold, _discount);
		break;
	default:
		break;
	}
}

DISCOUNT::Discount* RESTAURANT::Restaurant::discount = 
	new DISCOUNT::OverPercentDiscount(0, 0);