#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<time.h>
#include<set>
#include "people.h"

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
		const string& UserName()const { return userName; }
		string& UserName() { return userName; }
		const string& PassWord()const { return passWord; }
		string& PassWord() { return passWord; }
		const string& HeadPicture()const { return headPicture; }
		string& HeadPicture() { return headPicture; }
	protected:
		virtual ~Account() = default;
		Account() = default;
		Account(string n,string p):userName(n),passWord(p)
		{time(&timeCreated);}
		Account(string n,string p,time_t t):
			userName(n),passWord(p),timeCreated(t){}
		Account(string n, string p, time_t t,string pic) :
			userName(n), passWord(p), timeCreated(t),headPicture(pic) {}
	private:
		PEOPLE::People _people;
		string headPicture;//记得设置默认值！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
		string userName;
		string passWord;
		time_t timeCreated;
	};

	class CustomerAccount :public Account
	{
	private:
		set<unsigned> CommentIdSet;
		set<unsigned> prevoiseOrderIdSet;             //以前的订单
		unsigned currentOrderId;
		static string defaultCustomerHeadPicture;
		bool VIP = false;                             //是否是VIP
		double moneyUsed = 0.0;                       //花掉的钱

	public:
		using Account::Account;
		CustomerAccount& removeComment(unsigned id);   //删除评论
		virtual Permission permission()const override{return customer;}
		void startOrder();
		void addTask();                                               //增加订单
		void urgeTask(unsigned taskId);                               //催单
		void writeComment();
		void finishOrder();
		void SendMessage(const string& m);                            //给服务员发送信息
	};

	class AdministratorAccount:public Account
	{
	public:
		virtual Permission permission() const override { return administrator; }
		void addAccount(Permission);
		void removeAccount(unsigned id);
		void addComment();
		void removeComment(unsigned id);
		void addDish();
		void removeDish(unsigned id);
		void addDishToMenu(unsigned dishId, unsigned menuId);
		void removeDishFromMenu(unsigned dishId, unsigned menuId);

		//剩下的东西之后再去实现
	};

	class ChefAccount :public Account 
	{

	public:
		virtual Permission permission() const override{return chef;}
		void getTask(unsigned id);
		void FinishTask();
		double star();                      //返回评级
		unsigned finishedTaskCount();       //返回完成的任务数
		//现在缺少构造函数！
	private:
		unsigned currentTask;
		set<unsigned> taskIdSet;            
		set<unsigned> taskIdFinished;
	};

	class WaiterAccount:public Account
	{
		friend void CustomerAccount::finishOrder();
	public:
		virtual Permission permission() const override { return waiter; }
		void getTable(unsigned id);
		double star();                        //返回评级
		unsigned finishedOrderCount();        //返回完成的订单
		void reserveMassage(const string& m); //接收顾客发出的信息
											  //现在缺少构造函数！
	private:
		void FinishTable();                 //被CustomerAccount::finishOrder()调用，不能单独调用
		unsigned currentTable;
		set<unsigned> tableIdSet;
		set<unsigned> OrderIdFinished;
		set<unsigned> commentIdSet;
	};

	class ManagerAccount :public Account
	{
	public:
		virtual Permission permission() const override { return manager; }
		WaiterAccount* getWaiter(unsigned id);
		ChefAccount* getChef(unsigned id);
		//现在缺少构造函数！
	private:
		set<unsigned> chefSet;
		set<unsigned> waiterSet;
		
	};
}








#endif //ACCOUNT_H