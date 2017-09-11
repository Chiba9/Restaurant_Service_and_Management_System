#ifndef TASK_H
#define TASK_H
#include<string>
#include<vector>
#include "id.h"
#include "dish.h"
#include "account.h"
#include "order.h"
#include <initializer_list>

namespace TASK {
	using TaskId = unsigned;
	enum taskStatus {
		choosing/*�ոձ��û�������ѡ����*/, 
		waiting/*�������б��еȴ���ʦ����*/,
		cooking/*��ʦ�����*/, 
		serving/*�ϲ���*/, 
		eating/*�˿����ڳ�*/,
		quitted/*�û��ѷ����ò�*/, 
		finished/*�����*/
	};
	class Task:public AbstractID::ID<Task>
	{
	private:
		DISH::DishId dishId;           //�����Ĳ�ƷID
		ORDER::OrderId orderId;        //��������ID
		taskStatus status;             //����������
		ACCOUNT::AccountID chefId;     //�����ʦID��Ĭ��ΪNodata
		time_t timeCreated;	           //����ʱ��
		bool urgement = false;         //�û��ߵ������Ĭ��Ϊfalse
		double star = Nodata ;
	public:
		Task() = default;
		//ȫ���캯��
		Task(DISH::DishId _dishId, ORDER::OrderId _orderId, taskStatus _status,
			ACCOUNT::AccountID _chefId, time_t _timeCreated, bool _urgement);
		//�û��㵥ʱ�Ĺ��캯��
		Task(DISH::DishId _dishId, ORDER::OrderId _orderId);
		double price() const;                //���ز˼�
		void urge();
		bool getUrgement() const;                  //���شߵ�����������޸�
		void setStatus(taskStatus _status);  //�趨�������
		//�趨������ֻ�������Ĳ��������������������������
		void setOrder(ORDER::OrderId _orderId);
		//�趨��ʦ��ֻ�������Ĳ���������ʦ�Ľ�������������
		void setChef(unsigned _chefId);      
		DISH::DishId getDishId() const;
		ORDER::OrderId getOrderId() const;
		ACCOUNT::AccountID getChefId() const;
		taskStatus getStatus() const;
		double getStar() const;
		void setStar(double val);
	};

	class TaskList:AbstractID::ID<TaskList>
	{
	private:
		std::vector<TaskId> taskIdList;
	public:
		TaskList() = default;
		TaskList(std::initializer_list<TaskId> il) :
			taskIdList(il){}
		double star() const;
		std::size_t size() const;
		void addTask(const TaskId& _taskId);
		void removeTask(const TaskId& _taskId);
		std::vector<TaskId>::iterator begin();
		std::vector<TaskId>::iterator end();
		std::vector<TaskId>::const_iterator cbgin()const;
		std::vector<TaskId>::const_iterator cend()const;
	};
}
#endif //TASK_H
