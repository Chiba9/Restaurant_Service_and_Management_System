#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<time.h>
#include<set>
#include "people.h"
#include "table.h"
#include "restaurant.h"

/*********账户类**********/

namespace ACCOUNT {
	class PEOPLE::People;
	class Comment;//评论类（尚未实现）
	class Order;  //订单类（尚未实现）
	class Task;   //任务类（尚未实现）
	using std::string; using std::set;
	using AccountID = unsigned;
	//代表权限的枚举类型
	enum Permission{customer,administrator,chef,waiter,manager};
	//其他账户类的虚基类
	class Account :public AbstractID::ID<Account>
	{
	public:
		virtual Permission permission() const = 0;
		const string& UserName()const;
		string& UserName();
		const string& PassWord()const;
		string& PassWord();
		const string& HeadPicture()const;
		string& HeadPicture();
		void changePassword(const string& prevPassWord, const string& newPassWord);
	protected:
		virtual ~Account() = default;
		Account() = default;
		Account(string n,string p);
		Account(string n,string p, string pic);
		Account(string n, string p, time_t t,string pic);
		void setDefaultHeadPicture(Permission _permission);
	private:
		PEOPLE::People _people;
		string headPicture;//记得设置默认值！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
		string userName;
		string passWord;
		time_t timeCreated;
		static string defaultCustomerHeadPicture;
		static string defaultWaiterHeadPicture;
		static string defaultChefHeadPicture;
		static string defaultAdministratorHeadPicture;
		static string defaultManagerHeadPicture;
	};

	class CustomerAccount :public Account
	{
	private:
		COMMENT::CommentList commentIdList = Nodata;
		set<ORDER::Order> previousOrderIdSet;             //以前的订单
		unsigned currentOrderId = Nodata;
		static string defaultCustomerHeadPicture;
		static double VIPmoney;
		bool VIP = false;                             //是否是VIP
		double moneyUsed = 0.0;                       //花掉的钱
		bool checkOrder();                            //检查订单是否下达
		bool checkTask(TASK::TaskId _taskId);         //检查任务是否在订单中
	public:
		using Account;
		CustomerAccount& removeComment(COMMENT::CommentId id);   //删除评论
		virtual Permission permission()const override{return customer;}
		void startOrder(TABLE::TableId _tableId);                     //选桌开始
		void addTask(DISH::DishId _dishId);                           //增加任务
		void quitTask(TASK::TaskId _taskId);
		void finishOrdering();                                        //完成加菜
		void urgeTask(TASK::TaskId _taskId);                               //催单
		void writeWaiterComment(int star, string _text = "");
		void writeDishComment(TASK::TaskId _taskId, int _star, string _text = "");
		void writeOrderComment(int _star, string _text = "");
		void finishCurrentOrder();
		void SendMessage(const string& m);                            //给服务员发送信息
		bool isVIP() const;
		bool checkVIP();
	};
/*
	class AdministratorAccount:public Account
	{
	public:
		virtual Permission permission() const override { return administrator; }
		void addAccount(Permission _permission);
		void removeAccount(unsigned id);
		void addComment();
		void removeComment(unsigned id);
		void addDish();
		void removeDish(unsigned id);
		void addDishToMenu(unsigned dishId, unsigned menuId);
		void removeDishFromMenu(unsigned dishId, unsigned menuId);

		//剩下的东西之后再去实现
	private:
		void addCustomer(string _userName, string _password,  string _name = "",string _headpic = "");
	};
*/

	class ChefAccount :public Account
	{
	public:
		Account() = default;
		using Account;
		virtual Permission permission() const override { return chef; }
		void getTask(TASK::TaskId _id);
		void FinishTask();
		bool free();                        //是否有空
		double star();                      //返回评分
		unsigned finishedTaskCount();       //返回完成的任务数
		TASK::TaskList getPreviousTaskList() const;
		//现在缺少构造函数！
	private:
		TASK::TaskId currentTask = Nodata;
		TASK::TaskList previousTaskList;
	};

	class WaiterAccount:public Account
	{
		friend void CustomerAccount::finishCurrentOrder();
	public:
		WaiterAccount() = default;
		using Account;
		virtual Permission permission() const override { return waiter; }
		TABLE::TableId getTable() const;
		bool free();
		double star();                        //返回评级
		unsigned finishedOrderCount();        //返回完成的订单数量
		string reserveMassage(const string& m); //接收顾客发出的信息
		void setTable(TABLE::TableId _tableId);//同时改变Table类中的服务员对象
		void addComment(COMMENT::CommentId _commetId);
		COMMENT::CommentList getCommentIdList() const;
		//现在缺少构造函数！
	private:
		//被CustomerAccount::finishOrder()调用，不能单独调用，同时设定桌子（桌子由服务员管理）
		void FinishTable();           
		TABLE::TableId currentTable = Nodata;
		set<ORDER::OrderId> previousOrder;
		COMMENT::CommentListId commentListId;
	};

	class ManagerAccount :public Account
	{
	public:
		virtual Permission permission() const override { return manager; }
		ManagerAccount() = default;
		using ACCOUNT;
		//WaiterAccount* getWaiter(unsigned id);
		//ChefAccount* getChef(unsigned id);
		//现在缺少构造函数！
	private:
		
	};
}

#endif //ACCOUNT_H