//Написать и отладить программу вычисления интеграла указанным 
//методом двумя способами – по заданному количеству разбиений n и 
//заданной точности E(метод 1) (задания табл. 8.1).
//Реализацию указанного метода оформить отдельной функцией, алгоритм
//которой описать в виде блок - схемы.
//Вариант 13. sin(x)^2 - 3 * cos(x); a = 1 b = 7 Значение = 3.533 Метод = средних

#include <iostream>
#include <cmath>

using namespace std;

typedef double (*type_f)(double);
double fun(double);
double Metod(type_f f, double a, double b, int n);

//--------------------- Текст функции-обработчика кнопки РАСЧЕТ --------------------
int main() {
	setlocale(0, "rus");
	double a, b, x, eps, Int1, Int2, pogr;
	int n, n1;
	cout << "a = "; cin >> a;
	cout << "b = "; cin >> b;
	cout << "eps = "; cin >> eps;
	cout << "n = "; cin >> n;

	cout << "Расчет по разбиению на n = " << n << endl;
	Int1 = Metod(fun, a, b, n);
	cout << "Значение интеграла = " << Int1 << endl << endl;

	n1 = 2;
	cout << "Расчет по точности eps" << endl;
	Int1 = Metod(fun, a, b, n1);
	do {
		n1 *= 2;
		Int2 = Metod(fun, a, b, n1);
		pogr = fabs(Int2 - Int1);
		Int1 = Int2;
	} while (pogr > eps);
	cout << "При n = " << n1 << endl;
	cout << "Значение интеграла = " << Int1 << endl;
}

//------------------------------- Метод Средних -----------------------------------------------
double Metod(type_f f, double a, double b, int n) {
	double h = (b - a) / n;
	cout << h << " ";
	double result = 0;
	for (int i = 0; i < n; i++) {
		result += f(a + (i + 0.5) * h) * h;
	}
	return result;
}

//------------------------------ Подынтегральная функция f(x) ------------------------------
double fun(double x) {
	return pow(sin(x), 2) - 3 * cos(x);
}