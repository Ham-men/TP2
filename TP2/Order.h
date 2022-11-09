#pragma once
#include "lib_all.h"
class Order
{
private:
	int pay_current_account;	//����������. ���������� �� ��������
	int beneficiary_current_account;	//����������
	int amount;	//�����

public:
	Order();
	Order(int pay1, int pay2, int sum);

	void Order_add(int pay1, int pay2, int sum);
	string order_info();
	int pay_current_account_return();
	int beneficiary_current_account_return();
	int amount_return();

};

