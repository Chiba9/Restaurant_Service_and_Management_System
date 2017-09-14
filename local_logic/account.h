#ifndef ACCOUNT_H
#define ACCOUNT_H

#include<time.h>
#include<set>
#include "people.h"
#include "common.h"
#include "task.h"
#include "comment.h"
/*********账户类**********/

namespace ACCOUNT {

	using std::string; using std::set;

	//代表权限的枚举类型
	enum Permission { customer = 1, administrator, chef, waiter, manager };
	//其他账户类的虚基类
	class Account :public AbstractID::ID<Account>
	{
	public:
		virtual Permission permission() const {return type;}
		const string& UserName()const;
		string& UserName();
		const string& PassWord()const;
		string& PassWord();
		const string& HeadPicture()const;
		string& HeadPicture();
		void changePassword(const string& prevPassWord, const string& newPassWord);
		virtual ~Account() = default;
	protected:

		Account() = default;
		Account(Permission pm, string n, string p);
		Account(Permission pm, string n, string p, string pic);
		Account(Permission pm, string n, string p, string pic, time_t t,unsigned _id = Nodata);
		void setDefaultHeadPicture(Permission _permission);
		Permission type;   //账号属性
	private:
		PEOPLE::People _people;
		string headPicture;
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
		CommentListId commentListId = Nodata;
		set<OrderId> previousOrderIdSet;             //以前的订单
		OrderId currentOrderId = Nodata;
		bool VIP = false;                             //是否是VIP
		double moneyUsed = 0.0;                       //花掉的钱
		bool checkOrder();                            //检查订单是否下达
		bool checkTask(TaskId _taskId);         //检查任务是否在订单中
		void creatCommentList();                //在构造时调用
		void checkVIP();
	public:
		CustomerAccount(string n, string p);
		CustomerAccount(string n, string p, string pic);
		CustomerAccount(string n, string p, string pic, time_t t,CommentListId c_id,unsigned _id = Nodata);
		CustomerAccount& removeComment(CommentId id);   //删除评论
		virtual Permission permission()const override { return customer; }
		ORDER::Order& getOrder() const;                        //返回订单
		ORDER::Order& startOrder(TableId _tableId);                     //选桌开始
		TASK::Task& addTask(DishId _dishId);                           //增加任务
		void quitTask(TaskId _taskId);
		void finishOrdering();                                        //完成加菜
		void urgeTask(TaskId _taskId);                               //催单
		COMMENT::Comment& writeWaiterComment(int star, string _text = "");
		COMMENT::Comment& writeDishComment(TaskId _taskId, int _star, string _text = "");
		COMMENT::Comment& writeOrderComment(int _star, string _text = "");
		void finishCurrentOrder();
		void SendMessage(const string& m);                            //给服务员发送信息
		bool isVIP() const;

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
		ChefAccount(string n, string p);
		ChefAccount(string n, string p, string pic);
		ChefAccount(string n, string p, string pic, time_t t, unsigned _id = Nodata);
		virtual Permission permission() const override { return chef; }
		void getTask(TaskId _id);
		void FinishTask();
		bool free();                        //是否有空
		double star();                      //返回评分
		unsigned finishedTaskCount();       //返回完成的任务数
		TASK::TaskList getPreviousTaskList() const;

	private:
		TaskId currentTask = Nodata;
		TASK::TaskList previousTaskList;
	};

	class WaiterAccount :public Account
	{
		friend void CustomerAccount::finishCurrentOrder();
	public:
		WaiterAccount(string n, string p);
		WaiterAccount(string n, string p, string pic);
		WaiterAccount(string n, string p, string pic, time_t t, CommentListId c_id, unsigned _id);
		virtual Permission permission() const override { return waiter; }
		const std::set<TableId>& getTables() const;
		TABLE::Table& getTable(TableId _id) const;
		bool free();
		double star();                        //返回评级
		unsigned finishedOrderCount();        //返回完成的订单数量
		string reserveMassage(const string& m, TableId _id); //接收顾客发出的信息
		void addTable(TableId _tableId);//同时改变Table类中的服务员对象和订单的服务员对象
		void addComment(CommentId _commetId);
		void serveTask(TaskId _id);
		COMMENT::CommentList getCommentIdList() const;
		//现在缺少构造函数！
	private:
		//被CustomerAccount::finishOrder()调用，不能单独调用，同时设定桌子（桌子由服务员管理）
		void FinishTable(TableId _id);
		set<TableId> currentTables = set<TableId>();
		set<OrderId> previousOrder;
		CommentListId commentListId = Nodata;
		void creatCommentList();                //在构造时调用
	};

	class ManagerAccount :public Account
	{
	public:
		ManagerAccount(string n, string p);
		ManagerAccount(string n, string p, string pic);
		ManagerAccount(string n, string p, string pic, time_t t, unsigned _id = Nodata);
		virtual Permission permission() const override { return manager; }
		ManagerAccount() = default;
		//WaiterAccount* getWaiter(unsigned id);
		//ChefAccount* getChef(unsigned id);
		//现在缺少构造函数！
	private:

	};

	template<typename... Args>
	CustomerAccount& newCustomer(Args&&... args)
	{
		auto temp = CustomerAccount(std::forward<Args>(args)...);
		unsigned _id = temp.id();
		return *RESTAURANT::Restaurant::CustomerAccountMap.at(_id);
	}

	template<typename... Args>
	ChefAccount& newChef(Args&&... args)
	{
		AccountID _id = ChefAccount(std::forward<Args>(args)...).id();
		return *RESTAURANT::Restaurant::ChefAccountMap.at(_id);
	}

	template<typename... Args>
	WaiterAccount& newWaiter(Args&&... args)
	{
		AccountID _id = WaiterAccount(std::forward<Args>(args)...).id();
		auto temp = RESTAURANT::Restaurant::AccountMap;
		return *RESTAURANT::Restaurant::WaiterAccountMap.at(_id);
	}

	template<typename... Args>
	ManagerAccount& newManager(Args&&... args)
	{
		AccountID _id = ManagerAccount(std::forward<Args>(args)...).id();
		return *RESTAURANT::Restaurant::ManagerAccountMap.at(_id);
	}
}

#endif //ACCOUNT_H