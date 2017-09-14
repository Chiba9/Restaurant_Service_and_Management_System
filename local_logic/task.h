#ifndef TASK_H
#define TASK_H

#include<string>
#include<vector>
#include "id.h"
#include <initializer_list>
#include "common.h"

namespace TASK {
	using TaskId = unsigned;
	enum taskStatus {
		choosing,//刚刚被用户创立、选择中
		waiting,//在任务列表中等待厨师认领
		cooking,//厨师烹饪中
		serving,//上菜中 
		eating,//顾客正在吃
		quitted,//用户已放弃该菜
		finished//完成
	};
	class Task:public AbstractID::ID<Task>
	{
	private:
		DishId dishId;           //包含的菜品ID
		OrderId orderId;        //所属订单ID
		taskStatus status;             //任务完成情况
		AccountID chefId;     //负责厨师ID，默认为Nodata
		time_t timeCreated;	           //创建时间
		bool urgement = false;         //用户催单情况，默认为false
		double star = Nodata ;
	public:
		Task() = default;
		//全构造函数
		Task(DishId _dishId, OrderId _orderId, taskStatus _status,
			AccountID _chefId, time_t _timeCreated, bool _urgement, unsigned _id);
		//用户点单时的构造函数
		Task(DishId _dishId, OrderId _orderId);
		double price() const;                //返回菜价
		void urge();
		bool getUrgement() const;                  //返回催单情况，不能修改
		void setStatus(taskStatus _status);  //设定任务情况
		//设定订单、只完成自身的操作、被订单的添加任务函数调用
		void setOrder(OrderId _orderId);
		//设定厨师、只完成自身的操作、被厨师的接受任务函数调用
		void setChef(unsigned _chefId);      
		DishId getDishId() const;
		OrderId getOrderId() const;
		AccountID getChefId() const;
		taskStatus getStatus() const;
		double getStar() const;
		void setStar(double val);
		TableId getTableId()const;
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

	template<typename... Args>
	Task& newTask(Args&&... args)
	{
		TaskId _id = Task(std::forward<Args>(args)...).id();
		return *RESTAURANT::Restaurant::TaskMap.at(_id);
	}
}
#endif //TASK_H
