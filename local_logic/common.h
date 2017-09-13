#ifndef COMMON_H
#define COMMON_H


using AccountID = unsigned;
using CommentId = unsigned;
using CommentListId = unsigned;
using DishId = unsigned;
using MenuId = unsigned;
using OrderId = unsigned;
using TableId = unsigned;
using TaskId = unsigned;

const unsigned Nodata = -1;
namespace DISH {
	class Dish;
	class DishIdList;
}

namespace ACCOUNT{
	class Account;
	class ChefAccount;
	class CustomerAccount;
	class ManagerAccount;
	class WaiterAccount;
}

namespace COMMENT {
	class Comment;
	class CommentList;
}

namespace DISCOUNT {
	class Discount;
}

namespace MENU {
	class Menu;
}

namespace ORDER {
	class Order;
}

namespace RESTAURANT {
	class Restaurant;
}

namespace TABLE {
	class Table;
}

namespace TASK {
	class Task;
	class TaskList;
}

#include "restaurant.h"
#endif // COMMON_H