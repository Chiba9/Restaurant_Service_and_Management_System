#ifndef ABSTRACTLIST_H
#define ABSTRACTLIST_H
#include<algorithm>
#include<vector>
/**************抽象列表模板**************/
//用于构造各种列表
//底层用vector实现，便于排序

namespace AbstractList {
	class AbstractList_List
	{
	private:
		vector<unsigned> m_vector;
		//各种排序算法的内部实现
		template<typename F/*排序原则*/>
		void n_sort(F f, bool reverse);
	public:
		unsigned& operator[](std::size_t n);
		cosnt T& operator[](std::size_t n)const;
	};
}

#endif //ABSTRACTLIST_H