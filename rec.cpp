/*��������� �������� � ���� ����-�����,�������� � �������� ������������ ������
� �������������� ����������� � ������� �������. �������� ���������� ����������.
13. ��������� y = x^n �� ���������� �������: y = ( x ^(n/2) )^2, ���� n ������ � y = x * y^(n�1), ���� n ��������.*/

#include <iostream>
using namespace std;

double Rec(double x, int n);
double Def(double x, int n);

template <typename T>
void SetNumber(T& a);

template <typename T1, typename T2>
void Check(T1 x, T2 n);

int main() {

    setlocale(0, "rus");

    double x;
    int n;
    cout << "������� x: ";
    SetNumber(x);

    cout << "������� n: ";
    SetNumber(n);

    double rec = Rec(x, n), def = Def(x, n);

    cout << "��������� ����������� ������� = " << rec << endl;
    cout << "��������� ������� ������� = " << def << endl;
    Check(rec, def);
    return 0;
}

template <typename T>
void SetNumber(T& a) {
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "������, ������� �������� ��������!" << endl;
    }
}

double Rec(double x, int n) {
    if (n % 2 == 0) {
        double t = pow(x, n / 2);
        return t * t;
    }
    else return x * Rec(x, n - 1);
}

double Def(double x, int n) {
    if (n % 2 == 0) {
        double t = pow(x, n / 2);
        return t * t;
    }
    else {
        double t = pow(x, (n - 1) / 2);
        return x * t * t;
    }
}

template <typename T1, typename T2>
void Check(T1 x, T2 n) {
    cout << "\n�������� ������...." << endl;
    if (x == n) cout << "������ ��������!!!" << endl;
    else cout << "������ �� ��������!!!" << endl;
}