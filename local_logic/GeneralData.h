#pragma once
#include "dish.h"
#include "comment.h"
#include "task.h"
#include "account.h"
#include "menu.h"
#include <map>
#include<vector>
#include <string>
using std::map;
map<DISH::DishId, DISH::Dish*>DishMap;
map<MENU::MenuId, MENU::Menu*>MenuMap;
map<COMMENT::CommentId, COMMENT::Comment*>CommentMap;
map<ACCOUNT::AccountID, ACCOUNT::Account*>AccountMap;
map<TASK::TaskId, TASK::task*>TaskMap;
map<TASK::TaskId, TASK::task*>CurrrentTaskMap;
map<COMMENT::CommentListId, COMMENT::CommentList*>CommentListMap;