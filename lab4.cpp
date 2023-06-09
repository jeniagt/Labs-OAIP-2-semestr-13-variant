/*Написать программу формирования ОПЗ и расчета полученного выражения.
Разработать удобный интерфейс ввода исходных данных и вывода результатов.
Работу программы проверить на конкретном примере (табл. 4.1).
13. a/(b+c–d*e) a = 7.6 b = 4.8 c = 3.5 d = 9.1 e = 0.2 Ответ = 1.173
*/

#include <iostream>
#include <string>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;

struct Stack {
    char info;
    Stack* next;
};

int Prior(char a);

Stack* Push(Stack* p, char in);

Stack* Pop(Stack* p, char* out);

double Rezult(char* str, Stack*& begin);

template <typename T>
void SetNumber(T& a);

int main() {
    Stack* begin;
    Stack* t, * Op = NULL;
    char a, In[81], Out[81];
    int k = 0, l = 0;
    cout << "enter formula: ";
    cin >> In;
    while (In[k] != '\0') {
        if (In[k] >= 'a' && In[k] <= 'z') Out[l++] = In[k];
        else if (In[k] == '(') Op = Push(Op, In[k]);
        else if (In[k] == ')') {
            while ((Op->info) != '(') {
                Op = Pop(Op, &a);
                if (!Op) a = '\0';
                Out[l++] = a;
            }
            t = Op;
            Op = Op->next;
            delete t;
        }
        else if (In[k] == '+' || In[k] == '-' || In[k] == '*' || In[k] == '/') {
            while (Op != NULL && Prior(Op->info) >= Prior(In[k])) {
                Op = Pop(Op, &a);
                Out[l++] = a;
            }
            Op = Push(Op, In[k]);
        }
        k++;
    }
    while (Op != NULL) {
        Op = Pop(Op, &a);
        Out[l++] = a;
    }
    Out[l] = '\0';
    cout << "\nPolish = " << Out << endl;
    cout << "Res = " << Rezult(Out, begin) << endl;
    return 0;
}

Stack* Push(Stack* p, char in) {
    Stack* t = new Stack; // Захватываем память для элемента
    t->info = in; // Формируем информационную часть
    t->next = p; // Формируем адресную часть
    return t;
}

Stack* Pop(Stack* p, char* out)
{
    Stack* t = p; // Устанавливаем указатель t на вершину p
    *out = p->info;
    p = p->next; // Переставляем вершину p на следующий
    delete t; // Удаляем бывшую вершину t
    return p; // Возвращаем новую вершину p
}

int Prior(char a) {
    switch (a) {
    case '^': return 4;
    case '*': case '/': return 3;
    case '-': case '+': return 2;
    case '(': return 1;
    }
    return 0;
}

double Rezult(char* str, Stack*& begin) {
    int i;
    char ch, ch1, ch2, chR = 'z' + 1;
    double op1, op2, rez = 0, mas[200];
    cout << "Input data" << endl;
    for (i = 0; str[i] != '\0'; i++) {
        ch = str[i];
        if (ch >= 'a' && ch <= 'z') {
            cout << ch << " = ";
            SetNumber(mas[int(ch)]);
        }
    }
    for (i = 0; str[i] != '\0'; i++) {
        ch = str[i];
        if (!(ch == '+' || ch == '-' || ch == '*' || ch == '/')) begin = Push(begin, ch);
        else {
            begin = Pop(begin, &ch2);
            begin = Pop(begin, &ch1);
            op2 = mas[int(ch2)];
            op1 = mas[int(ch1)];

            switch (ch) {
            case '+': rez = op1 + op2; break;
            case '-': rez = op1 - op2; break;
            case '*': rez = op1 * op2; break;
            case '/': rez = op1 / op2;
                if (op2 == 0) {
                    cout << "Error!!!\nDivision by zero!";
                    exit(0);
                }
                break;
            case '^': rez = pow(op2, op1); break;
            }

            mas[int(chR)] = rez;
            begin = Push(begin, chR);
            chR++;
        }
    }
    return rez;
}

template <typename T>
void SetNumber(T& a) {
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Error, input number!" << endl;
    }
}