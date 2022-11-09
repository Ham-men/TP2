#include "Order.h"

Order::Order()
{
	pay_current_account = 0;
	beneficiary_current_account = 0;
	amount = 0;
}

Order::Order(int pay1, int pay2, int sum)
{
	pay_current_account = pay1;
	beneficiary_current_account = pay2;
	amount = sum;
}

void Order::Order_add(int pay1, int pay2, int sum)
{
	pay_current_account = pay1;
	beneficiary_current_account = pay2;
	amount = sum;
}

string Order::order_info()
{
	if (pay_current_account == 0)
		return "";
	else
		return "\n	pay_current_account = " + to_string(pay_current_account) + "\n	beneficiary_current_account = " + to_string(beneficiary_current_account) + "\n	amount = " + to_string(amount);
}

int Order::pay_current_account_return()
{
	return pay_current_account;
}

int Order::beneficiary_current_account_return()
{
	return beneficiary_current_account;
}

int Order::amount_return()
{
	return amount;
}

