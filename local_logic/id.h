#ifndef ID_H
#define ID_H

/*********IDϵͳ************/
//���ж���Ļ��࣬ʵ�ֱ��ϵͳ
namespace AbstractID {
	template<typename T>
	class ID {
	private:
		unsigned _id;             //��¼���
		static unsigned count;    //��¼��ǰ�����������
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
		_id = ++count;            //ֻ��Ĭ�Ϲ��캯��������count��ֵ����֤�ڿ�����ʱ�򲻻�����
	}

	template<typename T>
	unsigned ID<T>::count = 0;
}

#endif // !ID_H