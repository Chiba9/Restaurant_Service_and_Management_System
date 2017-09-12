#ifndef PEOPLE_H
#define PEOPLE_H

#include "common.h"

#include "id.h"
#include<iostream>
#include<string>

namespace PEOPLE {

	class People :public AbstractID::ID<People>
	{
	public:
		People() = default;
		explicit People(const std::string &n) :ID(), name(n) {}
		const std::string& getName()const;
	private:
		std::string name;
	};

	std::ostream& operator<<(std::ostream& os, const People&);

};
#endif // !PEOPLE_H