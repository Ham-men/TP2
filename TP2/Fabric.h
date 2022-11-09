#pragma once

#include "Order.h"

class Fabric
{

public:

	//расчетные счета
	Order order1;
	Fabric();
	void Fab_order_add(int pay1, int pay2, int sum);
};

