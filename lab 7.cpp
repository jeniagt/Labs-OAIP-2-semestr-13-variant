//Написать и отладить программу(задания из табл. 7.1) аппроксимации
//функции f(x) на интервале[a, b] заданным методом, m – количество точек, 
//в которых известна функция(размер таблицы).Вид функции задан для получения
//значений таблицы(xi, yi), i = 1, 2, …, m и проверки качества аппроксимации.
//Решение задачи оформить отдельной функцией, алгоритм которой описать в виде блок - схемы.
//Вариант 13sin(x)^2 - 3 * cos(x) a = 1 b = 7 m = 11 Многочлен Лагранжа

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
//---------------------------------------------------------------------------
double fun(double);
double Mn_Lagr(double*, double, int);
//---------------------------------------------------------------------------

int main()
{
	setlocale(0, "rus");
	double x, h, h1, a, b, * mas_x, * mas_y_t;
	int i, n, m;

	cout << "a = "; cin >> a;
	cout << "b = "; cin >> b;
	cout << "m = "; cin >> m;
	cout << "n(Количество рассчитываемых значений) = "; cin >> n;

	h = (b - a) / (m - 1);
	h1 = (b - a) / (n - 1);

	mas_x = new double[m + 1];
	mas_y_t = new double[n + 1];

	for (x = a, i = 0; i < m; i++) {
		mas_x[i] = x;
		x += h;
	}

	cout << "---- Многочлен Лагранжа ---" << endl;
	cout << "Получили " << n << " значений:" << endl;

	for (x = a, i = 0; i < n; i++, x += h1) {
		mas_y_t[i] = Mn_Lagr(mas_x, x, m);
		cout << "x = " << fixed << setprecision(6) << x << " f*(x) = " << mas_y_t[i] << endl;
	}

	return 0;
}

//------------------------------ Исходная функция f(x) -----------------------------------------
double fun(double x) {
	return pow(sin(x), 2) - 3 * cos(x);
}
//----------------------------- Многочлен Лагранжа -------------------------------------------
double Mn_Lagr(double* x, double xt, int kol) {
	int i, k;
	double e, p = 0;
	for (k = 0; k < kol; k++) {
		e = 1.;
		for (i = 0; i < kol; i++)
			if (i != k) e *= ((xt - x[i]) / (x[k] - x[i]));
		p += e * fun(x[k]);
	}
	return p;
}