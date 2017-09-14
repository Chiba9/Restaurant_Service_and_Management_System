#ifndef ACCOUNT_H
#define ACCOUNT_H

#include<time.h>
#include<set>
#include "people.h"
#include "common.h"
#include "task.h"
#include "comment.h"
/*********�˻���**********/

namespace ACCOUNT {

	using std::string; using std::set;

	//����Ȩ�޵�ö������
	enum Permission { customer = 1, administrator, chef, waiter, manager };
	//�����˻���������
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
		Permission type;   //�˺�����
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
		set<OrderId> previousOrderIdSet;             //��ǰ�Ķ���
		OrderId currentOrderId = Nodata;
		bool VIP = false;                             //�Ƿ���VIP
		double moneyUsed = 0.0;                       //������Ǯ
		bool checkOrder();                            //��鶩���Ƿ��´�
		bool checkTask(TaskId _taskId);         //��������Ƿ��ڶ�����
		void creatCommentList();                //�ڹ���ʱ����
		void checkVIP();
	public:
		CustomerAccount(string n, string p);
		CustomerAccount(string n, string p, string pic);
		CustomerAccount(string n, string p, string pic, time_t t,CommentListId c_id,unsigned _id = Nodata);
		CustomerAccount& removeComment(CommentId id);   //ɾ������
		virtual Permission permission()const override { return customer; }
		ORDER::Order& getOrder() const;                        //���ض���
		ORDER::Order& startOrder(TableId _tableId);                     //ѡ����ʼ
		TASK::Task& addTask(DishId _dishId);                           //��������
		void quitTask(TaskId _taskId);
		void finishOrdering();                                        //��ɼӲ�
		void urgeTask(TaskId _taskId);                               //�ߵ�
		COMMENT::Comment& writeWaiterComment(int star, string _text = "");
		COMMENT::Comment& writeDishComment(TaskId _taskId, int _star, string _text = "");
		COMMENT::Comment& writeOrderComment(int _star, string _text = "");
		void finishCurrentOrder();
		void SendMessage(const string& m);                            //������Ա������Ϣ
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

	//ʣ�µĶ���֮����ȥʵ��
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
		bool free();                        //�Ƿ��п�
		double star();                      //��������
		unsigned finishedTaskCount();       //������ɵ�������
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
		double star();                        //��������
		unsigned finishedOrderCount();        //������ɵĶ�������
		string reserveMassage(const string& m, TableId _id); //���չ˿ͷ�������Ϣ
		void addTable(TableId _tableId);//ͬʱ�ı�Table���еķ���Ա����Ͷ����ķ���Ա����
		void addComment(CommentId _commetId);
		void serveTask(TaskId _id);
		COMMENT::CommentList getCommentIdList() const;
		//����ȱ�ٹ��캯����
	private:
		//��CustomerAccount::finishOrder()���ã����ܵ������ã�ͬʱ�趨���ӣ������ɷ���Ա����
		void FinishTable(TableId _id);
		set<TableId> currentTables = set<TableId>();
		set<OrderId> previousOrder;
		CommentListId commentListId = Nodata;
		void creatCommentList();                //�ڹ���ʱ����
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
		//����ȱ�ٹ��캯����
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