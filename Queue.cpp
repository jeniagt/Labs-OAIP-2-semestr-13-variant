/*Написать программу по созданию, добавлению (в начало, в конец), просмотру (с начала, с конца) и решению поставленной в лаб. работе № 2 задачи
для двунаправленных линейных списков.
13. В созданном списке определить максимальное значение и удалить его.*/
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

struct Spis2 {
	int info;
	Spis2* prev, * next;
};

void Create(Spis2*& b, Spis2*& e, int in);
void Add(Spis2*& b, Spis2*& e, int in);

void Peek(Spis2* p, Spis2* e);

void Del_All(Spis2*& p);

void Search_Maximum(Spis2*& p, Spis2*& e);


template <typename T>
void SetNumber(T& a);

int main()
{
	Spis2* begin = NULL;
	Spis2* end = NULL;
	int in, n, kod;
	while (true) {
		cout << "\n\tCreate - 1\n\tAdd - 2\n\tView - 3\n\tDel - 4\n\tTask - 5\n\tEXIT - 0 : ";
		SetNumber(kod);
		switch (kod) {
		case 1:
			if (begin) {
				// Если создаем новый стек, должны освободить память, занятую предыдущим
				cout << "Clear Memory!" << endl;
				break;
			}
			cout << "Begin Info = ";
			SetNumber(in);

			Create(begin, end, in);
			cout << "Create Begin = " << begin->info << endl;
		case 2:
			if (!begin) {
				cout << "Create queue!" << endl;
				break;
			}
			cout << "Input kol = ";
			SetNumber(n);

			for (int i = 1; i <= n; i++) {
				cout << "number -  ";
				SetNumber(in);

				Add(begin, end, in);
			}
			if (kod == 1) cout << "Create " << n << endl;
			else cout << "Add " << n << endl;
			break;
		case 3: if (!begin) {
			cout << "Queue Pyst!" << endl;
			break;
		}
			  Peek(begin, end);
			  break;
		case 4:
			Del_All(begin);
			cout << "Memory Free!" << endl;
			break;
		case 5:
			if (!begin) {
				cout << "Queue Pyst!" << endl;
				break;
			}
			Search_Maximum(begin, end);
			if (begin) Peek(begin, end);
			else cout << "Queue Pyst!" << endl;
			break;
		case 0: if (begin)
			Del_All(begin);
			return 0;
		}
	}
}


void Create(Spis2*& b, Spis2*& e, int in) { // in – переданная информация
	Spis2* t = new Spis2;
	t->info = in; // Формирование информационной части
	t->next = t->prev = NULL; // Формирование адресной части
	b = e = t;
}
void Add(Spis2*& b, Spis2*& e, int in) {
	Spis2* t = new Spis2;
	t->info = in; // Формирование информационной части
	t->next = t->prev = NULL; // Формирование адресной части
	int n;
	cout << "Enter 1 - start queue \nEnter 2 - finish queue" << endl;
	SetNumber(n);

	switch (n) {
	case 1:
		t->prev = NULL; // Предыдущего нет
		t->next = b; // Связываем новый элемент с первым
		b->prev = t; // Изменяем адрес prev бывшего первого
		b = t; // Переставляем указатель begin на новый
		break;
	case 2:
		t->next = NULL; // Следующего нет
		t->prev = e; // Связываем новый с последним
		e->next = t; // Изменяем адрес next бывшего последнего
		e = t; // Изменяем указатель end
		break;
	}
}

void Peek(Spis2* b, Spis2* e) {


	cout << "-- Begin --" << endl;
	while (b) {
		cout << b->info << ' ';
		b = b->next;
	}

	cout << "\n--- End --" << endl;
	while (e) {
		cout << e->info << ' ';
		e = e->prev;
	}

}

void Del_All(Spis2*& p) {
	Spis2* t;
	while (p) {
		t = p;
		p = p->next;
		delete t;
	}
}

void Search_Maximum(Spis2*& b, Spis2*& e)
{
	Spis2* t = b;
	int max = t->info;
	while (t) {
		if (max < t->info) max = t->info;
		t = t->next;
	}
	t = b;
	while (t) {
		if (t->info == max) {
			if (b == e) {
				Del_All(b);
				break;
			}
			if (t == b) {
				b = b->next;
				b->prev = NULL;
			}
			else if (t == e) {
				e = e->prev;
				e->next = NULL;
			}
			else {
				(t->prev)->next = t->next;
				(t->next)->prev = t->prev;
			}
		}
		t = t->next;
	}
	cout << "Successfull!!!\n Max number " << max << " deleted!" << endl;
}


template <typename T>
void SetNumber(T& a) {
	while (!(cin >> a) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error, enter number!" << endl;
	}
}