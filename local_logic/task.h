#ifndef TASK_H
#define TASK_H
#include<string>


namespace TASK {
	
	enum taskStatus {
		choosing/*�ոձ��û�������ѡ����*/, waiting/*�������б��еȴ��ύ*/, cooking/*��ʦ�����*/
		, serving/*�ϲ���*/, eating/*�˿����ڳ�*/,quitted/*�û��ѷ����ò�*/, finished/*�����*/
	};
	class task:public AbstractID::ID<task>
	{
		friend void ACCOUNT::CustomerAccount::urgeTask(unsigned taskId);
	private:
		unsigned dishId;               //�����Ĳ�ƷID
		unsigned orderId;              //��������ID
		taskStatus status;             //����������
		unsigned chefId;               //�����ʦID��Ĭ��Ϊ-1
		time_t createdTime;	           //����ʱ��
		bool urgement = false;         //�û��ߵ������Ĭ��Ϊfalse
	public:
		double price() const;                //���ز˼�
		bool Urged() const;                  //���شߵ�����������޸�
		void setStatus(taskStatus _status);  //�趨�������
		//�趨��ʦ��ֻ�������Ĳ���������ʦ�Ľ�������������
		void setChef(unsigned _chefId);      
		unsigned getDishId() const;
		unsigned getOrderId() const;
		unsigned getChefId() const;
		taskStatus getStatus() const;
		
	};
}
#endif //TASK_H
