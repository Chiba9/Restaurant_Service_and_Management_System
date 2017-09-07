#ifndef TASK_H
#define TASK_H
#include<string>


namespace TASK {
	
	enum taskStatus {
		choosing/*刚刚被用户创立、选择中*/, waiting/*在任务列表中等待提交*/, cooking/*厨师烹饪中*/
		, serving/*上菜中*/, eating/*顾客正在吃*/,quitted/*用户已放弃该菜*/, finished/*已完成*/
	};
	class task:public AbstractID::ID<task>
	{
		friend void ACCOUNT::CustomerAccount::urgeTask(unsigned taskId);
	private:
		unsigned dishId;               //包含的菜品ID
		unsigned orderId;              //所属订单ID
		taskStatus status;             //任务完成情况
		unsigned chefId;               //负责厨师ID，默认为-1
		time_t createdTime;	           //创建时间
		bool urgement = false;         //用户催单情况，默认为false
	public:
		double price() const;                //返回菜价
		bool Urged() const;                  //返回催单情况，不能修改
		void setStatus(taskStatus _status);  //设定任务情况
		//设定厨师、只完成自身的操作、被厨师的接受任务函数调用
		void setChef(unsigned _chefId);      
		unsigned getDishId() const;
		unsigned getOrderId() const;
		unsigned getChefId() const;
		taskStatus getStatus() const;
		
	};
}
#endif //TASK_H
