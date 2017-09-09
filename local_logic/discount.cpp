#include "discount.h"

double DISCOUNT::Discount::getThreshold() const
{
	return threshold;
}

double DISCOUNT::Discount::getThreshold_VIP() const
{
	return threshold_VIP;
}

void DISCOUNT::Discount::setThreshold(double thr)
{
	threshold = thr;
}

void DISCOUNT::Discount::setThreshold_VIP(double thr)
{
	threshold_VIP = thr;
}


double DISCOUNT::OverPercentDiscount::netPrice(double price, bool VIP) const
{
	if (!VIP)
		return price > threshold ?
			threshold + (1 - discount)*(price - threshold) : price;
	else
		return price > threshold_VIP ?
			threshold_VIP + (1 - discount_VIP)*(price - threshold_VIP) : price;
}

double DISCOUNT::AllPercentDiscount::netPrice(double price, bool VIP) const
{
	if (!VIP)
		return price > threshold ?
			(1 - discount) * price : price;
	else
		return price > threshold_VIP ?
			(1 - discount_VIP)* price : price;
}

double DISCOUNT::OverMinusDiscount::netPrice(double price, bool VIP) const
{
	if (!VIP)
		return price > threshold ?
			price - minus : price;
	else
		return price > threshold_VIP ?
			price - minus_VIP : price;
}
