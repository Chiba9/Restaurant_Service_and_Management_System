#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<time.h>
#include<set>
#include "people.h"
#include "table.h"
#include "restaurant.h"

/*********�˻���**********/

namespace ACCOUNT {
	class PEOPLE::People;
	class Comment;//�����ࣨ��δʵ�֣�
	class Order;  //�����ࣨ��δʵ�֣�
	class Task;   //�����ࣨ��δʵ�֣�
	using std::string; using std::set;
	using AccountID = unsigned;
	//����Ȩ�޵�ö������
	enum Permission{customer,administrator,chef,waiter,manager};
	//�����˻���������
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
		COMMENT::CommentList commentIdList = Nodata;
		set<ORDER::Order> previousOrderIdSet;             //��ǰ�Ķ���
		unsigned currentOrderId = Nodata;
		static string defaultCustomerHeadPicture;
		static double VIPmoney;
		bool VIP = false;                             //�Ƿ���VIP
		double moneyUsed = 0.0;                       //������Ǯ
		bool checkOrder();                            //��鶩���Ƿ��´�
		bool checkTask(TASK::TaskId _taskId);         //��������Ƿ��ڶ�����
	public:
		using Account;
		CustomerAccount& removeComment(COMMENT::CommentId id);   //ɾ������
		virtual Permission permission()const override{return customer;}
		void startOrder(TABLE::TableId _tableId);                     //ѡ����ʼ
		void addTask(DISH::DishId _dishId);                           //��������
		void quitTask(TASK::TaskId _taskId);
		void finishOrdering();                                        //��ɼӲ�
		void urgeTask(TASK::TaskId _taskId);                               //�ߵ�
		void writeWaiterComment(int star, string _text = "");
		void writeDishComment(TASK::TaskId _taskId, int _star, string _text = "");
		void writeOrderComment(int _star, string _text = "");
		void finishCurrentOrder();
		void SendMessage(const string& m);                            //������Ա������Ϣ
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

		//ʣ�µĶ���֮����ȥʵ��
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
		bool free();                        //�Ƿ��п�
		double star();                      //��������
		unsigned finishedTaskCount();       //������ɵ�������
		TASK::TaskList getPreviousTaskList() const;
		//����ȱ�ٹ��캯����
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
		double star();                        //��������
		unsigned finishedOrderCount();        //������ɵĶ�������
		string reserveMassage(const string& m); //���չ˿ͷ�������Ϣ
		void setTable(TABLE::TableId _tableId);//ͬʱ�ı�Table���еķ���Ա����
		void addComment(COMMENT::CommentId _commetId);
		COMMENT::CommentList getCommentIdList() const;
		//����ȱ�ٹ��캯����
	private:
		//��CustomerAccount::finishOrder()���ã����ܵ������ã�ͬʱ�趨���ӣ������ɷ���Ա����
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
		//����ȱ�ٹ��캯����
	private:
		
	};
}

#endif //ACCOUNT_H