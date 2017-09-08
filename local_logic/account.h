#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<time.h>
#include<set>
#include "people.h"

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
		string headPicture;//�ǵ�����Ĭ��ֵ��������������������������������������������������������������������������������������
		string userName;
		string passWord;
		time_t timeCreated;
	};

	class CustomerAccount :public Account
	{
	private:
		set<unsigned> CommentIdSet;
		set<unsigned> prevoiseOrderIdSet;             //��ǰ�Ķ���
		unsigned currentOrderId;
		static string defaultCustomerHeadPicture;
		bool VIP = false;                             //�Ƿ���VIP
		double moneyUsed = 0.0;                       //������Ǯ

	public:
		using Account::Account;
		CustomerAccount& removeComment(unsigned id);   //ɾ������
		virtual Permission permission()const override{return customer;}
		void startOrder();
		void addTask();                                               //���Ӷ���
		void urgeTask(unsigned taskId);                               //�ߵ�
		void writeComment();
		void finishOrder();
		void SendMessage(const string& m);                            //������Ա������Ϣ
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

		//ʣ�µĶ���֮����ȥʵ��
	};

	class ChefAccount :public Account 
	{

	public:
		virtual Permission permission() const override{return chef;}
		void getTask(unsigned id);
		void FinishTask();
		double star();                      //��������
		unsigned finishedTaskCount();       //������ɵ�������
		//����ȱ�ٹ��캯����
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
		double star();                        //��������
		unsigned finishedOrderCount();        //������ɵĶ���
		void reserveMassage(const string& m); //���չ˿ͷ�������Ϣ
											  //����ȱ�ٹ��캯����
	private:
		void FinishTable();                 //��CustomerAccount::finishOrder()���ã����ܵ�������
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
		//����ȱ�ٹ��캯����
	private:
		set<unsigned> chefSet;
		set<unsigned> waiterSet;
		
	};
}








#endif //ACCOUNT_H