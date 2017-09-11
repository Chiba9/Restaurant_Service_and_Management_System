#include "discount.h"

DISCOUNT::Discount::Discount(double _threshold) :
	threshold(_threshold), threshold_VIP(_threshold){}

DISCOUNT::Discount::Discount(double _threshold, double _threshold_VIP) :
	threshold(_threshold), threshold_VIP(_threshold_VIP) {}

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


DISCOUNT::OverPercentDiscount::OverPercentDiscount(double _threshold, double _discount):
	Discount(_threshold),discount(_discount){}

DISCOUNT::OverPercentDiscount::OverPercentDiscount(double _threshold, double _threshold_VIP,
	double _discount, double _discount_VIP):
	Discount(_threshold,_threshold_VIP),discount(_discount),discount_VIP(_discount_VIP){}

double DISCOUNT::OverPercentDiscount::netPrice(double price, bool VIP) const
{
	if (!VIP)
		return price > threshold ?
			threshold + (1 - discount)*(price - threshold) : price;
	else
		return price > threshold_VIP ?
			threshold_VIP + (1 - discount_VIP)*(price - threshold_VIP) : price;
}

DISCOUNT::AllPercentDiscount::AllPercentDiscount(double _threshold, double _discount) :
	Discount(_threshold), discount(_discount) {}

DISCOUNT::AllPercentDiscount::AllPercentDiscount(double _threshold, double _threshold_VIP,
	double _discount, double _discount_VIP) :
	Discount(_threshold, _threshold_VIP), discount(_discount), discount_VIP(_discount_VIP) {}

double DISCOUNT::AllPercentDiscount::netPrice(double price, bool VIP) const
{
	if (!VIP)
		return price > threshold ?
			(1 - discount) * price : price;
	else
		return price > threshold_VIP ?
			(1 - discount_VIP)* price : price;
}

DISCOUNT::OverMinusDiscount::OverMinusDiscount(double _threshold, double _minus) :
	Discount(_threshold), minus(_minus) {}

DISCOUNT::OverMinusDiscount::OverMinusDiscount(double _threshold, double _threshold_VIP,
	double _minus, double _minus_VIP) :
	Discount(_threshold, _threshold_VIP), minus(_minus), minus_VIP(_minus_VIP) {}

double DISCOUNT::OverMinusDiscount::netPrice(double price, bool VIP) const
{
	if (!VIP)
		return price > threshold ?
			price - minus : price;
	else
		return price > threshold_VIP ?
			price - minus_VIP : price;
}
