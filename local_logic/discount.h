#ifndef DISCOUNT_H
#define DISCOUNT_H

#include "common.h"
namespace DISCOUNT
{
	
	class Discount
	{
	public:
		//���ؼ��ۺ�Ľ��
		Discount() = default;
		Discount(double _threshold);
		Discount(double _threshold, double _threshold_VIP);
		virtual double netPrice(double price, bool VIP) const = 0;
		double getThreshold() const;
		double getThreshold_VIP() const;
		void setThreshold(double thr);
		void setThreshold_VIP(double thr);
	protected:
		double threshold = 0.0;      //���Ƹ������ߵ���ֵ
		double threshold_VIP = 0.0;  //����VIP�ر���ֵ
	};

	class OverPercentDiscount:public Discount     //�Գ����Ĳ��ֽ��аٷֱȼ���
	{
	private:
		double discount = 0.0;       //������0��1֮��
		double discount_VIP = 0.0;   //VIP�ۿ�
	public:
		OverPercentDiscount() = default;
		OverPercentDiscount(double _threshold, double _discount);
		OverPercentDiscount(double _threshold, double _threshold_VIP,
			double _discount, double _discount_VIP);
		virtual double netPrice(double price, bool VIP) const override;
	};

	class AllPercentDiscount :public Discount      //�������������
	{
	private:
		double discount = 0.0;       //������0��1֮��
		double discount_VIP = 0.0;   //VIP�ۿ�
	public:
		AllPercentDiscount() = default;
		AllPercentDiscount(double _threshold, double _discount);
		AllPercentDiscount(double _threshold, double _threshold_VIP,
			double _discount, double _discount_VIP);
		virtual double netPrice(double price, bool VIP) const override;
	};

	class OverMinusDiscount :public Discount
	{
	private:
		double minus = 0.0;
		double minus_VIP = 0.0;
	public:
		virtual double netPrice(double price, bool VIP) const override;
		OverMinusDiscount() = default;
		OverMinusDiscount(double _threshold, double _discount);
		OverMinusDiscount(double _threshold, double _threshold_VIP,
			double _discount, double _discount_VIP);
	};
}
#endif // DISCOUNT_H