#pragma once
#include"id.h"
namespace DISCOUNT
{
	class Discount
	{
	public:
		virtual double netPrice(double price, bool VIP) const = 0;
	};
}
