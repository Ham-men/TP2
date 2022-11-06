#include "queue.h"

Queue::Queue() {
	size = 0;
	tail = nullptr;
}
void Queue::insert(Fabric data) {
	tail = new item{ data, tail };
	size++;
}
int Queue::Queue_Size() {
	return size;
}
Fabric Queue::remove() {
	item* iterator = tail;
	item* prevElement = iterator;
	if (tail == nullptr) {
		throw (404);
	}
	while (iterator->point_Next != nullptr) {
		prevElement = iterator;
		iterator = iterator->point_Next;
	}
	prevElement->point_Next = nullptr;
	Fabric save = iterator->value;

	delete iterator;
	size--;
	if (size == 0)
		tail = nullptr;
	return save;
}
void Queue::printQueue(string type)
{

	int flag_order = 0;
	int i = size;
	Fabric save;
	while (i != 0) {
		save = this->remove();

		if (type == "order")
		{
			cout << save.order1.order_info();
			flag_order = 1;
		}


		if (type == to_string(save.order1.pay_current_account_return()))
		{
			cout << save.order1.order_info();
			flag_order = 1;
		}



		this->insert(save);
		i--;
	}
	if (flag_order == 0)
		cout << "\nОшибка: счет плательщика не найден";
	cout << endl;
}
Queue* Queue::copy()	//сделать сортировку
{
	int* nomber = new int[this->size];	//1(значение) 2(значение) 3(значение) 4(значение)
	Queue* queue = new Queue();
	Queue* queue2 = new Queue();
	Queue* queue3 = new Queue();
	int i = this->size;
	int i2 = i;

	Fabric save;
	Fabric save2;
	queue2 = this;	//скопировали нашу очередь
	while (i != 0) {
		save = this->remove();
		queue->insert(save);

		i--;
	}

	return queue;
}


string Queue::order_info()
{
	int i = size;
	Fabric save;
	string result = "";
	while (i != 0) {
		save = this->remove();
		result += save.order1.order_info();
		this->insert(save);
		i--;
	}

	return result;
}

int Queue::pay_current_account_return()//выводит прошлый номер плательщика
{
	Fabric save = this->remove();
	this->insert(save);
	return save.order1.pay_current_account_return();
}

