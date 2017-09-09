#pragma once
namespace DISCOUNT
{
	enum DiscountType {overPercent,allPercent,overMinus};  //判定折扣类型
	class Discount
	{
	public:
		//返回减价后的结果
		virtual double netPrice(double price, bool VIP) const = 0;
		double getThreshold() const;
		double getThreshold_VIP() const;
		void setThreshold(double thr);
		void setThreshold_VIP(double thr);
	protected:
		double threshold = 0.0;      //控制各种政策的阈值
		double threshold_VIP = 0.0;  //对于VIP特别阈值
	};

	class OverPercentDiscount:public Discount     //对超过的部分进行百分比减价
	{
	private:
		double discount = 0.0;       //控制在0与1之间
		double discount_VIP = 0.0;   //VIP折扣
	public:
		virtual double netPrice(double price, bool VIP) const override;
	};

	class AllPercentDiscount :public Discount      //超过后整体打折
	{
	private:
		double discount = 0.0;       //控制在0与1之间
		double discount_VIP = 0.0;   //VIP折扣
	public:
		virtual double netPrice(double price, bool VIP) const override;
	};

	class OverMinusDiscount :public Discount
	{
	private:
		double minus = 0.0;
		double minus_VIP = 0.0;
	public:
		virtual double netPrice(double price, bool VIP) const override;

	};
}
