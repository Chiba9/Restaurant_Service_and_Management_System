#pragma once
namespace DISCOUNT
{
	enum DiscountType {overPercent,allPercent,overMinus};  //�ж��ۿ�����
	class Discount
	{
	public:
		//���ؼ��ۺ�Ľ��
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
		virtual double netPrice(double price, bool VIP) const override;
	};

	class AllPercentDiscount :public Discount      //�������������
	{
	private:
		double discount = 0.0;       //������0��1֮��
		double discount_VIP = 0.0;   //VIP�ۿ�
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
