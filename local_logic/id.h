#ifndef ID_H
#define ID_H
/*********ID系统************/
//所有对象的基类，实现编号系统
namespace AbstractID {
	template<typename T>
	class ID {
	private:
		unsigned m_id;             //记录编号
		static unsigned count;    //记录当前该类对象总数
	protected:
		ID();
		ID(unsigned _id);
		virtual ~ID() = default;
	public:
		unsigned id()const;
		unsigned& id();
	};
	//判断是否为新添加元素
	template<typename T>
	AbstractID::ID<T>::ID(unsigned _id)
	{
		if(_id == -1)
			m_id = ++count;
		else
			m_id = _id;
	}

	template<typename T>
	unsigned& ID<T>::id()
	{
		return m_id;
	}
	template<typename T>
	unsigned ID<T>::id()const
	{
		return m_id;
	}

	template<typename T>
	ID<T>::ID()
	{
		m_id = ++count;            //只在默认构造函数中增加count的值，保证在拷贝的时候不会增加
	}

	template<typename T>
	unsigned ID<T>::count = 0;
}

#endif // !ID_H