/*Написать программу по созданию, добавлению, просмотру и решению
поставленной задачи (в рассмотренных примерах это действие отсутствует) для
однонаправленного линейного списка типа СТЕК. Реализовать сортировку стека двумя рассмотренными выше методами.
Решение поставленной задачи представить в виде блок-схемы.
Во всех заданиях создать список из положительных и отрицательных
случайных целых чисел.
13. В созданном списке определить максимальное значение и удалить его.
*/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

struct Stack {
    int info; // Информационная часть элемента, например int
    Stack* next; // Адресная часть – указатель на следующий элемент
};

Stack* Push(Stack* p, int in);

Stack* Pop(Stack* p, int* out);

void Peek(Stack* p);
void RecPeek(Stack* p);

void Del_All(Stack*& p);

void Sort_p(Stack** p);
void Sort_info(Stack* p);

void Search_Maximum(Stack*& p);

int main() {
    int i, in, n, kod;
    Stack* begin = NULL;
    while (true) {
        cout << "\n\tCreate - 1.\n\tAdd - 2.\n\tView - 3.\n\tDel - 4.\n\tSort1 - 5.\n\tSort2 - 6.\n\tTask - 7.\n\tEXIT - 0. :" << endl;
        cin >> kod;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error, enter kod NUMBER! " << endl;
            cin >> kod;
        }
        switch (kod) {
        case 1: case 2:
            if (kod == 1 && begin) {
                // Если создаем новый стек, должны освободить память, занятую предыдущим
                cout << "Clear Memory!" << endl;
                break;
            }
            cout << "Input kol = ";
            cin >> n;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Error, enter kol NUMBERS! " << endl;
                cin >> n;
            }
            for (i = 1; i <= n; i++) {
                cout << "number -  ";
                cin >> in;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error, enter NUMBER! " << endl;
                    cin >> in;
                }
                begin = Push(begin, in);
            }
            if (kod == 1) cout << "Create " << n << endl;
            else cout << "Add " << n << endl;
            break;
        case 3: if (!begin) {
            cout << "Stack Pyst!" << endl;
            break;
        }
              cout << "--- Stack ---" << endl;
              RecPeek(begin);
              break;
        case 4:
            Del_All(begin);
            cout << "Memory Free!" << endl;
            break;
        case 5:
            if (!begin) {
                cout << "Stack Pyst!" << endl;
                break;
            }
            Sort_info(begin);
            RecPeek(begin);
            break;
        case 6:
            if (!begin) {
                cout << "Stack Pyst!" << endl;
                break;
            }
            Sort_p(&begin);
            RecPeek(begin);
            break;
        case 7:
            if (!begin) {
                cout << "Stack Pyst!" << endl;
                break;
            }
            Search_Maximum(begin);
            RecPeek(begin);
            break;
        case 0:
            if (begin != NULL)
                Del_All(begin);
            return 0; // Выход – EXIT
        }
    }
}

Stack* Push(Stack* p, int in) { // begin = Push(begin, a);
    Stack* t = new Stack; // Захватываем память для элемента
    t->info = in; // Формируем информационную часть
    t->next = p; // Формируем адресную часть
    return t;
}

Stack* Pop(Stack* p, int* out) //begin = Pop(begin, &a);
{
    Stack* t = p; // Устанавливаем указатель t на вершину p
    *out = p->info;
    p = p->next; // Переставляем вершину p на следующий
    delete t; // Удаляем бывшую вершину t
    return p; // Возвращаем новую вершину p
}

void Peek(Stack* p) { // Peek(begin);
    while (p) {
        // Вывод на экран информационной части, например, cout << t -> info << endl;
        cout << p->info << ' ';
        p = p->next;
    }
}
void RecPeek(Stack* p) { // RecPeek(begin);
    if (p) {
        cout << p->info << ' ';
        RecPeek(p->next);
    }
}

void Del_All(Stack*& p) { // Del_All(begin);
    Stack* t;
    while (p) {
        t = p;
        p = p->next;
        delete t;
    }
}

void Sort_p(Stack** p) { // Sort_p (&begin);
    Stack* t = NULL, * t1, * r;
    if ((*p)->next->next == NULL) return;
    do {
        for (t1 = *p; t1->next->next != t; t1 = t1->next)
            if (t1->next->info > t1->next->next->info) {
                r = t1->next->next;
                t1->next->next = r->next;
                r->next = t1->next;
                t1->next = r;
            }
        t = t1->next;
    } while ((*p)->next->next != t);
}

void Sort_info(Stack* p) { // Sort_info(begin);
    Stack* t = NULL, * t1;
    int r;
    do {
        for (t1 = p; t1->next != t; t1 = t1->next)
            if (t1->info > t1->next->info) {
                r = t1->info;
                t1->info = t1->next->info;
                t1->next->info = r;
            }
        t = t1;
    } while (p->next != t);

}

void Search_Maximum(Stack*& p) //Search_Maximum(begin);
{
    Stack* t = p;
    int max = t->info;
    while (t) {
        if (max < t->info) max = t->info;
        t = t->next;
    }
    int a;
    while (p) {
        p = Pop(p, &a);
        if (a != max) t = Push(t, a);
    }
    while (t) {
        t = Pop(t, &a);
        p = Push(p, a);
    }
}