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
	class PEOPLE::People;
	class Comment;//�����ࣨ��δʵ�֣�
	class Order;  //�����ࣨ��δʵ�֣�
	class Task;   //�����ࣨ��δʵ�֣�
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
		Account(string n, string p);
		Account(string n, string p, string pic);
		Account(string n, string p, string pic, time_t t);
		void setDefaultHeadPicture(Permission _permission);
		Permission type;   //�˺�����
	private:
		PEOPLE::People _people;
		string headPicture;//�ǵ�����Ĭ��ֵ��������������������������������������������������������������������������������������
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
		CommentListId commentListId;
		set<OrderId> previousOrderIdSet;             //��ǰ�Ķ���
		unsigned currentOrderId = Nodata;
		static string defaultCustomerHeadPicture;
		static double VIPmoney;
		bool VIP = false;                             //�Ƿ���VIP
		double moneyUsed = 0.0;                       //������Ǯ
		bool checkOrder();                            //��鶩���Ƿ��´�
		bool checkTask(TaskId _taskId);         //��������Ƿ��ڶ�����
		void creatCommentList();                //�ڹ���ʱ����
	public:
		CustomerAccount(string n, string p);
		CustomerAccount(string n, string p, string pic);
		CustomerAccount(string n, string p, string pic, time_t t);
		CustomerAccount& removeComment(CommentId id);   //ɾ������
		virtual Permission permission()const override { return customer; }
		void startOrder(TableId _tableId);                     //ѡ����ʼ
		void addTask(DishId _dishId);                           //��������
		void quitTask(TaskId _taskId);
		void finishOrdering();                                        //��ɼӲ�
		void urgeTask(TaskId _taskId);                               //�ߵ�
		void writeWaiterComment(int star, string _text = "");
		void writeDishComment(TaskId _taskId, int _star, string _text = "");
		void writeOrderComment(int _star, string _text = "");
		void finishCurrentOrder();
		void SendMessage(const string& m);                            //������Ա������Ϣ
		bool isVIP() const;
		void checkVIP();
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
		ChefAccount(string n, string p, string pic, time_t t);
		virtual Permission permission() const override { return chef; }
		void getTask(TaskId _id);
		void FinishTask();
		bool free();                        //�Ƿ��п�
		double star();                      //��������
		unsigned finishedTaskCount();       //������ɵ�������
		TASK::TaskList getPreviousTaskList() const;
		//����ȱ�ٹ��캯����
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
		WaiterAccount(string n, string p, string pic, time_t t);
		virtual Permission permission() const override { return waiter; }
		TableId getTable() const;
		bool free();
		double star();                        //��������
		unsigned finishedOrderCount();        //������ɵĶ�������
		string reserveMassage(const string& m); //���չ˿ͷ�������Ϣ
		void setTable(TableId _tableId);//ͬʱ�ı�Table���еķ���Ա����
		void addComment(CommentId _commetId);
		COMMENT::CommentList getCommentIdList() const;
		//����ȱ�ٹ��캯����
	private:
		//��CustomerAccount::finishOrder()���ã����ܵ������ã�ͬʱ�趨���ӣ������ɷ���Ա����
		void FinishTable();
		TableId currentTable = Nodata;
		set<OrderId> previousOrder;
		CommentListId commentListId;
		void creatCommentList();                //�ڹ���ʱ����
	};

	class ManagerAccount :public Account
	{
	public:
		ManagerAccount(string n, string p);
		ManagerAccount(string n, string p, string pic);
		ManagerAccount(string n, string p, string pic, time_t t);
		virtual Permission permission() const override { return manager; }
		ManagerAccount() = default;
		using Account::Account;
		//WaiterAccount* getWaiter(unsigned id);
		//ChefAccount* getChef(unsigned id);
		//����ȱ�ٹ��캯����
	private:

	};
}

#endif //ACCOUNT_H