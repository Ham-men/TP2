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

int** qsortRecursive(int** mas, int size) {	//сортировка
	//Указатели в начало и в конец массива
	int i = 0;
	int j = size - 1;
	int tmp[3];
	//Центральный элемент массива
	int mid = mas[size / 2][0];

	//Делим массив
	do {
		//Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
		//В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
		while (mas[i][0] < mid) {
			i++;
		}
		//В правой части пропускаем элементы, которые больше центрального
		while (mas[j][0] > mid) {
			j--;
		}

		//Меняем элементы местами
		if (i <= j) {
			tmp[0] = mas[i][0];
			tmp[1] = mas[i][1];
			tmp[2] = mas[i][2];
			mas[i][0] = mas[j][0];
			mas[i][1] = mas[j][1];
			mas[i][2] = mas[j][2];
			mas[j][0] = tmp[0];
			mas[j][1] = tmp[1];
			mas[j][2] = tmp[2];

			i++;
			j--;
		}
	} while (i <= j);


	//Рекурсивные вызовы, если осталось, что сортировать
	if (j > 0) {
		//"Левый кусок"
		qsortRecursive(mas, j + 1);
	}
	if (i < size) {
		//"Првый кусок"
		qsortRecursive(&mas[i], size - i);
	}
	return mas;
}


int main() {
	ofstream Out_txt;          // поток для записи
	ifstream in_txt;			//поток для чтения

	//Order* order_input = new Order();
	Fabric* fabric1_input = new Fabric();
	Fabric* fabric2_input = new Fabric();

	Queue* Keeper2 = new Queue();

	int** mass_order2;

	setlocale(LC_ALL, "Russian");
	system("cls");
	int n = 1;
	//переменные для ввода значений в класс Fabric
	int a = NULL;
	int b = NULL;
	int c = NULL;
	int d = NULL;	//номер строки

	int size_order = 0;
	int i3 = 0;	//счетчик массива строки где одинаковое количество символов пунктуации
	int* mas_strok_cout = new int[1];
	//чтение файла
	string text_temp = "null";
	string* text_max_punkt = new string[1];
	string* text_max_punkt2 = new string[1];
	int nomer_stroki_read = 0;
	//string text1 = "null";

	cout << "1:добавить order	2:вывод order	3:сортировка order	4:вывод информации о плательщике	5:чтение файла	6:выход";

	while (n != 6) {
		a = NULL;
		b = NULL;
		c = NULL;

		cout << "\nномер операции = ";
		n = return_int();
		switch (n) {
		case 1:
			// add value in Keeper and fabric create
			cout << "\nдобавить order";
			cout << "\nрасчетный счет плательщика = ";
			a = return_int();

			cout << "\nрасчетный счет получателя = ";
			b = return_int();
			cout << "\nперечисляемая сумма в рублях = ";
			c = return_int();
			fabric1_input->Fab_order_add(a, b, c);

			Keeper2->insert(*fabric1_input);
			fabric1_input = new Fabric();

			break;
		case 2:
			// print queue
			cout << "\nвывод order\n";
			Keeper2->printQueue("order");

			break;
		case 3://сортировка
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


		case 5:	//сделал номер строки где много символов пунктуации. сделать вывод самой строки в результате
			a = 0;
			b = 0;//кол-во символов пунктуации прошлой
			c = 0;//кол-во символов пунктуации сейчас
			d = 0;//номер строки


			cout << "\nчтения файла result.txt\n";
			in_txt.open("result.txt"); // окрываем файл для чтения
			if (!in_txt.is_open())
			{
				cout << "\n файл не найден";
				break;
			}
			if (in_txt.is_open())
			{

				while (getline(in_txt, text_temp))
				{

					//cout << text4_read << endl;	//вывод всего текста
					for (a = 0; a < text_temp.size(); a++)
					{
						cout << text_temp[a];

						if (text_temp[a] == ',' || text_temp[a] == ';' || text_temp[a] == ':' || text_temp[a] == '-' || text_temp[a] == '(' ||
							text_temp[a] == ')' || text_temp[a] == '"')
							b++;
						if (text_temp[a] == '.' || text_temp[a] == '!' || text_temp[a] == '?')
						{


							if (c < b)//запоминаю КОЛ-ВО ПУНКТУАЦИИ
							{
								c = b;

							}
							b = 0;
						}

					}

					cout << "\n";
					//text1 = text4_read.substr(7, text4_read.size() - 1);
					//cout << text4_read << endl;	//вывод всего текста
					nomer_stroki_read++;
				}
			}

			cout << "\n кол-во запятых = " << c;
			//c--;
			in_txt.close();
			a = 0;
			b = 0;//кол-во символов пунктуации прошлой
			//c = 0;//кол-во символов пунктуации сейчас
			d = 0;//номер строки

			in_txt.open("result.txt"); // окрываем файл для чтения

			if (in_txt.is_open())
			{

				while (getline(in_txt, text_temp))
				{
					for (a = 0; a < text_temp.size(); a++)
					{
						//cout << text_temp[a];

						if (text_temp[a] == ',' || text_temp[a] == ';' || text_temp[a] == ':' || text_temp[a] == '-' || text_temp[a] == '(' ||
							text_temp[a] == ')' || text_temp[a] == '"')
							b++;
						if (text_temp[a] == '.' || text_temp[a] == '!' || text_temp[a] == '?')
						{

							//d_temp++;
							//запоминает первую максимальную строку. если кол-во символов в следующией столько же, то не запоминает
							if (c == b)
							{
								i3++;
								text_max_punkt2 = new string[i3];
								for (d = 0; d < i3 - 1; d++)
									text_max_punkt2[d] = text_max_punkt[d];

								text_max_punkt = new string[i3];
								for (d = 0; d < i3 - 1; d++)
									text_max_punkt[d] = text_max_punkt2[d];
								text_max_punkt[i3 - 1] = text_temp;
							}


							b = 0;
						}
					}
				}
			}

			cout << "\nкол-во строк = " << nomer_stroki_read;
			cout << "\nстроки с наибольшим количеством символов пунктуации: \n";
			for (a = 0; a < i3; a++)
				cout << "\n nomber = " << a << " == " << text_max_punkt[a];
			in_txt.close();
			a = 0;
			b = 0;//кол-во символов пунктуации прошлой
			c = 0;//кол-во символов пунктуации сейчас
			d = 0;//номер строки
			nomer_stroki_read = 0;
			text_max_punkt = new string[1];
			text_max_punkt2 = new string[1];
			i3 = 0;
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
