#ifndef ID_H
#define ID_H
/*********IDϵͳ************/
//���ж���Ļ��࣬ʵ�ֱ��ϵͳ
namespace AbstractID {
	template<typename T>
	class ID {
	private:
		unsigned m_id;             //��¼���
		static unsigned count;    //��¼��ǰ�����������
	protected:
		ID();
		ID(unsigned _id);
		virtual ~ID() = default;
	public:
		unsigned id()const;
		unsigned& id();
	};
	//�ж��Ƿ�Ϊ�����Ԫ��
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
		m_id = ++count;            //ֻ��Ĭ�Ϲ��캯��������count��ֵ����֤�ڿ�����ʱ�򲻻�����
	}

	template<typename T>
	unsigned ID<T>::count = 0;
}

#endif // !ID_H