#ifndef TASK_H
#define TASK_H
#include<string>
#include<vector>
#include "id.h"
#include "dish.h"
#include "account.h"
#include "order.h"

namespace TASK {
	using TaskId = unsigned;
	enum taskStatus {
		choosing/*�ոձ��û�������ѡ����*/, waiting/*�������б��еȴ��ύ*/, cooking/*��ʦ�����*/
		, serving/*�ϲ���*/, eating/*�˿����ڳ�*/,quitted/*�û��ѷ����ò�*/, finished/*�����*/
	};
	class Task:public AbstractID::ID<Task>
	{
		friend void ACCOUNT::CustomerAccount::urgeTask(unsigned taskId);
	private:
		DISH::DishId dishId;           //�����Ĳ�ƷID
		ORDER::OrderId orderId;        //��������ID
		taskStatus status;             //����������
		ACCOUNT::AccountID chefId;     //�����ʦID��Ĭ��Ϊ-1
		time_t timeCreated;	           //����ʱ��
		bool urgement = false;         //�û��ߵ������Ĭ��Ϊfalse
	public:
		double price() const;                //���ز˼�
		bool Urged() const;                  //���شߵ�����������޸�
		void setStatus(taskStatus _status);  //�趨�������
		//�趨��ʦ��ֻ�������Ĳ���������ʦ�Ľ�������������
		void setChef(unsigned _chefId);      
		DISH::DishId getDishId() const;
		ORDER::OrderId getOrderId() const;
		ACCOUNT::AccountID getChefId() const;
		taskStatus getStatus() const;
		
	};

	class TaskList:AbstractID::ID<TaskList>
	{
	private:
		std::vector<TaskId> taskIdList;
	public:
		void addTask(const TaskId& _taskId);
		void removeTask(const TaskId& _taskId);
		std::vector<TaskId>::iterator begin();
		std::vector<TaskId>::iterator end();
		std::vector<TaskId>::const_iterator cbgin()const;
		std::vector<TaskId>::const_iterator cend()const;
	};
}
#endif //TASK_H
