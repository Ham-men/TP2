#include <math.h>
#include "Fabric.h"
#include "queue.h"
#include <fstream>


bool is_digit(const char* S) {		//проверка на число
	const char* temp = "0123456789-+";
	unsigned point_count = 0;

	for (int i = 0; i < strlen(S); i++) {
		if ((i > 0) && (S[i] == '+' || S[i] == '-')) return false;
		if (S[i] == '.') {
			point_count++;
			if (point_count > 1) return false;
		}
		if (!strchr(temp, S[i])) return false;
	}
	return true;
}
int return_int()
{
	const int N = 256;
	char S[N];

	cin >> S;
	while (!is_digit(S)) {	//сделать проверку на ввод числа
		cout << "введите число  = ";
		cin >> S;
	}
	cout << "ok\n";
	return atof(S);
}



int main() {
	ofstream Out_txt;          // поток для записи
	ifstream in_txt;			//поток для чтения

	//Order* order_input = new Order();
	Fabric* fabric1_input = new Fabric();
	Fabric* fabric2_input = new Fabric();

	//Queue_3 Keeper; // create queue. хранит все объекты класса фабрика

	/*Queue* copyKeeper;
	Queue* copyKeeper_1;*/
	Queue* Keeper2 = new Queue();
	Queue* copyKeeper1 = new Queue();
	Queue* Keeper_temp = new Queue();
	int** mass_order2;
	//int* mass_order;	//элементы Keeper
	//int value='s';
	setlocale(LC_ALL, "Russian");
	system("cls");
	int n = 1;
	//переменные для ввода значений в класс Fabric
	int a = NULL;
	int b = NULL;
	int c = NULL;
	int d = NULL;
	int nomer_stroki_read = 0;
	string text1 = "null";
	string text2 = "null";
	string text3 = "null";
	string text4_read = "null";
	int size_car = 0;
	int size_worker = 0;
	int size_furniture = 0;
	int size_order = 0;
	int size_order_temp = 0;
	int order_pay_max = -1;//максимальное число плательщика
	int order_pay_min = -1;//минимальное число плательщика
	int steps = 0;
	int i = 0;
	int i2 = 0;
	cout << "1:добавить order	2:вывод order	3:сортировка order	4:вывод информации о плательщике	5:чтение файла	6:выход";

	while (n != 6) {
		a = NULL;
		b = NULL;
		c = NULL;
		d = NULL;
		cout << "\nномер операции = ";
		n = return_int();
		switch (n) {
		case 1:
			// add value in Keeper and fabric create
			cout << "\nдобавить order";
			cout << "\nрасчетный счет плательщика = ";
			a = return_int();
			if (order_pay_max == -1 && order_pay_min == -1)
			{
				order_pay_max = a;
				order_pay_min = a;
			}
			cout << "\nрасчетный счет получателя = ";
			b = return_int();
			cout << "\nперечисляемая сумма в рублях = ";
			c = return_int();
			fabric1_input->Fab_order_add(a, b, c);

			Keeper2->insert(*fabric1_input);
			fabric1_input = new Fabric();
			size_worker++;
			break;
		case 2:
			// print queue
			cout << "\nвывод order\n";
			Keeper2->printQueue("order");

			break;
		case 3://сортировка
			//int* mass_order = new int[Keeper2->Queue_Size()];
			size_order = Keeper2->Queue_Size();
			mass_order2 = new int* [size_order];
			for (int count = 0; count < size_order; count++)
				mass_order2[count] = new int[2];

			for (int count_row = 0; count_row < size_order; count_row++)
			{
				*fabric2_input = Keeper2->remove();
				mass_order2[count_row][0] = fabric2_input->order1.pay_current_account_return();
				mass_order2[count_row][1] = fabric2_input->order1.beneficiary_current_account_return();
				mass_order2[count_row][2] = fabric2_input->order1.amount_return();
			}

			qsortRecursive(mass_order2, size_order);

			for (int count_row = 0; count_row < size_order; count_row++)
			{
				fabric2_input->Fab_order_add(mass_order2[count_row][0], mass_order2[count_row][1], mass_order2[count_row][2]);
				Keeper2->insert(*fabric2_input);

			}
			break;

		case 4:
			// print queue
			cout << "\nвведите номер плательщика\n";
			cout << "\nрасчетный счет плательщика = ";
			a = return_int();
			Keeper2->printQueue(to_string(a));
			break;


		case 5:
			cout << "\nчтения файла result.txt\n";
			in_txt.open("result.txt"); // окрываем файл для чтения
			if (in_txt.is_open())
			{
				while (getline(in_txt, text4_read))
				{
					nomer_stroki_read = 0;	//для номера строки
					cout << text4_read << endl;	//вывод всего текста
					if (text4_read == "worker_info")	//данные работника. отформатированные. проделать для машины и мебели
					{
						while (nomer_stroki_read != 5)
						{
							getline(in_txt, text4_read);
							switch (nomer_stroki_read)
							{
							case 0:
								text1 = text4_read.substr(7, text4_read.size() - 1);
								break;
							case 1:
								text2 = text4_read.substr(7, text4_read.size() - 1);
								break;
							case 2:
								a = stoi(text4_read.substr(6, text4_read.size() - 1));
								break;
							case 3:
								text3 = text4_read.substr(10, text4_read.size() - 1);
								break;
							case 4:
								b = stoi(text4_read.substr(12, text4_read.size() - 1));
								break;
							}

							cout << text4_read << endl;	//вывод всего текста
							nomer_stroki_read++;
						}

						fabric1_input->Fab_worker_add(text1, text2, a, text3, b);
						Keeper2->insert(*fabric1_input);
						fabric1_input = new Fabric();
					}

					if (text4_read == "car_info")	//данные машины
					{

						while (nomer_stroki_read != 3)
						{
							getline(in_txt, text4_read);
							switch (nomer_stroki_read)
							{
							case 0:
								text1 = text4_read.substr(9, text4_read.size() - 1);
								break;
							case 1:
								text2 = text4_read.substr(9, text4_read.size() - 1);
								break;
							case 2:
								text3 = text4_read.substr(14, text4_read.size() - 1);
								break;

							}

							cout << text4_read << endl;	//вывод всего текста
							nomer_stroki_read++;
						}

						fabric1_input->Fab_car_add(text1, text2, text3);
						Keeper2->insert(*fabric1_input);
						fabric1_input = new Fabric();
					}

					if (text4_read == "furniture_info")	//данные мебели
					{
						while (nomer_stroki_read != 6)
						{
							getline(in_txt, text4_read);
							switch (nomer_stroki_read)
							{
							case 0:
								text1 = text4_read.substr(8, text4_read.size() - 1);
								break;
							case 1:
								a = stoi(text4_read.substr(10, text4_read.size() - 1));
								break;
							case 2:
								b = stoi(text4_read.substr(11, text4_read.size() - 1));
								break;
							case 3:
								c = stoi(text4_read.substr(11, text4_read.size() - 1));
								break;
							case 4:
								text2 = text4_read.substr(9, text4_read.size() - 1);
								break;
							case 5:
								text3 = text4_read.substr(12, text4_read.size() - 1);
								break;
							case 6:
								d = stoi(text4_read.substr(9, text4_read.size() - 1));
								break;


							}

							cout << text4_read << endl;	//вывод всего текста
							nomer_stroki_read++;
						}

						fabric1_input->Fab_furniture_add(text1, a, b, c, text2, text3, d);
						Keeper2->insert(*fabric1_input);
						fabric1_input = new Fabric();
					}




				}
			}
			else
				cout << "файл не найден";
			in_txt.close();
			break;
		case 8:
			//close program
			cout << "\nвыход ";

			return 0;
			break;
		default: break;
		}

	}

	return 0;
}