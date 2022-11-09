#include "Fabric.h"

Fabric::Fabric()
{
	order1;
}


void Fabric::Fab_order_add(int pay1, int pay2, int sum)
{
	order1.Order_add(pay1, pay2, sum);
}




