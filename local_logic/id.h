#ifndef ID_H
#define ID_H

/*********ID系统************/
//所有对象的基类，实现编号系统
namespace AbstractID {
	template<typename T>
	class ID {
	private:
		unsigned _id;             //记录编号
		static unsigned count;    //记录当前该类对象总数
	protected:
		ID();
		virtual ~ID() = default;
	public:
		unsigned id()const;
		unsigned& id();
	};

	template<typename T>
	unsigned& AbstractID::ID<T>::id()
	{
		return _id;
	}
	template<typename T>
	unsigned ID<T>::id()const
	{
		return _id;
	}

	template<typename T>
	ID<T>::ID()
	{
		_id = ++count;            //只在默认构造函数中增加count的值，保证在拷贝的时候不会增加
	}

	template<typename T>
	unsigned ID<T>::count = 0;
}

#endif // !ID_H