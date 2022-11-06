#pragma once
#include <iostream>
#include "Fabric.h"
class Queue {
public:
	Queue();
	void insert(Fabric data);

	Fabric remove();
	//Queue(Fabric data);
	void printQueue(string type);
	Queue* copy();
	int Queue_Size();
	string order_info();
	int pay_current_account_return();


private:
	struct item {
		Fabric value;
		item* point_Next;
	};
	int size = 0;
	item* tail = nullptr;

};
