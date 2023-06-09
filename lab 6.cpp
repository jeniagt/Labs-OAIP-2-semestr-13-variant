//Написать и отладить программу поиска всех корней функции f(x)
// на отрезке[a, b] в соответствии с вариантом(табл. 6.1).Метод нахождения корня
//оформить в виде отдельной функции, алгоритм которой описать блок - схемой.
//Вариант 13 sin(x)^2 - 3*cosx a = -7 b = 3 

#include <iostream>
#include <cmath>
using namespace std;
//---------------------------------------------------------------------------
double Fun(double);
double FindRoot(double (*f)(double), double a, double b, double eps, int& count);
//---------------------------------------------------------------------------

int main()
{
	setlocale(0, "rus");
	double a, b, x, eps, h, y;
	int nom = 0;
	cout << "a = "; cin >> a;
	cout << "b = "; cin >> b;
	cout << "h = "; h = 0.01; cout << h;
	cout << " eps = "; eps = 0.001; cout << eps;
	cout << "\nФункция sin(x)^2 - 3*cosx" << endl;
	cout << "Метод секущих " << endl;
	cout << "------ Корни ------" << endl;
	for (x = a; x <= b; x += h) {
		if (Fun(x) * Fun(x + h) < 0) {
			int count = 0;
			nom++;
			y = FindRoot(Fun, x, x + h, eps, count);
			cout << nom << "-й = " << y << endl;
			cout << "Делаем проверку..." << endl;
			if (round(Fun(y) * 1000000) / 1000000 == 0) // Делаем проверку корня
				cout << y << " действительно является корнем!" << endl;
			cout << "Количество итераций для поиска корня, было проведено " << count << endl;
		}
	}
	if (nom == 0) cout << "На отрезке корней НЕТ!" << endl;
}

double FindRoot(double (*f)(double), double a, double b, double eps, int& count) {
	double c;
	while (abs(f(b) - f(a)) > eps) {
		count++;
		c = (f(b) * a - f(a) * b) / (f(b) - f(a));
		if ((f(a) * f(c)) > 0) a = c; // Проверка лучшей сходимости по знаку
		else b = c;
	}
	return c;
}
//------------------------------- Заданная функция f(x) ----------------------------------------
double Fun(double x) {
	return pow(sin(x), 2) - 3 * cos(x);
}