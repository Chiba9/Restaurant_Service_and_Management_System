#ifndef ABSTRACTLIST_H
#define ABSTRACTLIST_H
#include<algorithm>
#include<vector>
/**************�����б�ģ��**************/
//���ڹ�������б�
//�ײ���vectorʵ�֣���������

namespace AbstractList {
	class AbstractList_List
	{
	private:
		vector<unsigned> m_vector;
		//���������㷨���ڲ�ʵ��
		template<typename F/*����ԭ��*/>
		void n_sort(F f, bool reverse);
	public:
		unsigned& operator[](std::size_t n);
		cosnt T& operator[](std::size_t n)const;
	};
}

#endif //ABSTRACTLIST_H