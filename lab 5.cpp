//Разработать проект для работы с деревом поиска, содержащий следующие обработчики, которые должны :
//– ввести информацию(желательно, используя StringGrid), 
// состоящую из целочисленного ключа и строки текста(например, номер паспорта и ФИО);
//– записать информацию в дерево поиска;
//– сбалансировать дерево поиска;
//– добавить в дерево поиска новую запись;
//– по заданному ключу найти информацию и отобразить ее;
//– удалить из дерева поиска информацию с заданным ключом;
//– распечатать информацию прямым, обратным обходом и в порядке возрастания ключа;
//– решить одну из следующих задач.
//Решение поставленной задачи оформить в виде блок - схемы.
//
//13. Между максимальным и минимальным значениями ключей найти запись с ключом со значением,
//ближайшим к среднему значению.

#include <iostream>
#include <string>
#include <Windows.h>
#include <cmath>
using namespace std;

struct Tree {
	pair<int, string> info;
	Tree* left, * right;
};

Tree* List(int inf, string str); // Создаёт дерево
void Add_List(Tree* root, int key, string str); // Добавляет элемент в дерево
void View_Tree(Tree* p, int level); //  Просмотр дерева
void View_Tree_Element(Tree* p, int key); // Просмотр данных элемента
Tree* Del_Info(Tree* root, int key); // Удаление элемента 

void Del_Tree(Tree* t); // Удаление дерева

void preOrderTravers(Tree* root); // Прямой 
void inOrderTravers(Tree* root); // По возрастанию
void postOrderTravers(Tree* root); // Обратный

void SearhMinMax(Tree* root, int& min, int& max, int& i);
void SearhAvg(Tree* root, double& avg, pair <int, double>& result);

template <typename T>
void SetNumber(T& a);

int main() {
	Tree* root;
	root = NULL;
	setlocale(0, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true) {
		cout << "\n\tСоздать - 1.\n\tДобавить - 2.\n\tПосмотреть дерево - 3.\n\tУдалить элемент - 4.\n\tУдалить дерево - 5.\n\tЗадание - 6.\n\tВыход - 0. :" << endl;
		int choice; SetNumber(choice);
		string str;
		pair <int, double> result;
		int min, max, i = 0;
		double avg;
		switch (choice) {
		case 1:
			if (root != NULL) Del_Tree(root);
			cout << "Введите номер ключа:" << endl;
			int n; SetNumber(n);
			cout << "Введите пасспортные данные и ФИО:" << endl;
			cin.ignore();
			getline(cin, str);
			root = List(n, str);
			break;
		case 2:
			if (root == NULL) {
				cout << "Сначала создайте дерево!";
				break;
			}
			else {
				while (true) {
					cout << "Введите номер ключа:\n0 - для выхода" << endl;
					int n; SetNumber(n);
					if (n == 0) break;
					cout << "Введите пасспортные данные и ФИО:" << endl;
					cin.ignore();
					getline(cin, str);
					Add_List(root, n, str);
				}
			}
			break;
		case 3:
			if (root == NULL) cout << " Дерево не создано !" << endl;
			else {
				cout << "---------- Просмотр -----------" << endl;
				View_Tree(root, 0);
				cout << "Каким обходом распечатать дерево?\n1.Прямым\n2.Симметричный(в порядке возрастания)\n3.Обратным\n";
				SetNumber(choice);
				switch (choice) {
				case 1:
					preOrderTravers(root);
					break;
				case 2:
					inOrderTravers(root);
					break;
				case 3:
					postOrderTravers(root);
					break;
				}
				cout << "\nВведите номер ключа для просмотра данных" << endl;
				SetNumber(choice);
				View_Tree_Element(root, choice);

			}
			break;
		case 4:
			cout << "Введите номер для удаления" << endl;
			int b; SetNumber(b);
			root = Del_Info(root, b);
			break;
		case 5:
			Del_Tree(root);
			cout << "Дерево удалено!" << endl;
			root = NULL;
			break;
		case 6:
			cout << "Task!" << endl;

			SearhMinMax(root, min, max, i);

			avg = (min + max) / i;
			SearhAvg(root, avg, result);
			cout << "min = " << min << " max = " << max << " avg = " << avg << "\nresult = " << result.first << endl;
			break;
		case 0:
			if (root != NULL) {
				Del_Tree(root);
				cout << "Дерево удалено!" << endl;
			}
			return 0;
		}
	}



}

Tree* List(int inf, string str) {
	Tree* t = new Tree; // Захват памяти
	t->info = make_pair(inf, str); // Формирование информационной части
	t->left = t->right = NULL; // Формирование адресных частей
	return t; // Возврат созданного указателя
}

void Add_List(Tree* root, int key, string str) {
	Tree* prev{}, * t; // prev – указатель предка нового листа
	bool find = true;
	t = root;
	while (t && find) {
		prev = t;
		if (key == t->info.first) {
			find = false; // Ключ должен быть уникален
			cout << "Dublucate Key!" << endl;
		}
		else
			if (key < t->info.first) t = t->left;
			else t = t->right;
	}
	if (find) { // Нашли нужное место
		t = List(key, str); // Создаем новый лист
		if (key < prev->info.first) prev->left = t;
		else prev->right = t;
	}
}

void View_Tree(Tree* p, int level) {
	string str;
	if (p) {
		View_Tree(p->right, level + 1); // Правое поддерево
		for (int i = 0; i < level; i++) str = str + " ";
		cout << str + to_string(p->info.first) << endl;
		View_Tree(p->left, level + 1); // Левое поддерево
	}
}

void View_Tree_Element(Tree* p, int key) {
	if (p) {
		View_Tree_Element(p->right, key); // Правое поддерево
		if (p->info.first == key) {
			cout << p->info.second << endl;
			return;
		}
		View_Tree_Element(p->left, key); // Левое поддерево
		if (p->info.first == key) {
			cout << p->info.second << endl;
			return;
		}
	}
}

Tree* Del_Info(Tree* root, int key) {
	Tree* Del, * Prev_Del, * R, * Prev_R;
	// Del, Prev_Del – удаляемый узел и его предыдущий (предок);
	// R, Prev_R – элемент, на который заменяется удаляемый, и его предок;
	Del = root;
	Prev_Del = NULL;
	//------------ Поиск удаляемого элемента и его предка по ключу key ------------------
	while (Del != NULL && Del->info.first != key) {
		Prev_Del = Del;
		if (Del->info.first > key) Del = Del->left;
		else Del = Del->right;
	}
	if (Del == NULL) { // Элемент не найден
		cout << "NOT Key!" << endl;
		return root;
	}
	//-------------------------- Поиск элемента R для замены -----------------------------------
	if (Del->right == NULL) R = Del->left;
	else
		if (Del->left == NULL) R = Del->right;
		else {
			//------------------- Ищем самый правый узел в левом поддереве -----------------------
			Prev_R = Del;
			R = Del->left;
			while (R->right != NULL) {
				Prev_R = R;
				R = R->right;
			}
			//---------------- Формируем связи элемента R и его предка Prev_R -------------------
			if (Prev_R == Del) R->right = Del->right;
			else {
				R->right = Del->right;
				Prev_R->right = R->left;
				R->left = Prev_R;
			}
		}
	if (Del == root) root = R; // Удаляя корень, заменяем его на R
	else
		//--------------- Поддерево R присоединяем к предку удаляемого узла ----------------
		if (Del->info < Prev_Del->info)
			Prev_Del->left = R; // На левую ветвь
		else Prev_Del->right = R; // На правую ветвь
	delete Del;
	return root;
}

void Del_Tree(Tree* t) {
	if (t != NULL) {
		Del_Tree(t->left); // На левую ветвь
		Del_Tree(t->right); // На правую ветвь
		delete t;
	}
}

void preOrderTravers(Tree* root) {
	if (root) {
		printf("%d ", root->info.first);
		preOrderTravers(root->left);
		preOrderTravers(root->right);
	}
}

void inOrderTravers(Tree* root) {
	if (root) {
		inOrderTravers(root->left);
		printf("%d ", root->info.first);
		inOrderTravers(root->right);
	}
}

void postOrderTravers(Tree* root) {
	if (root) {
		postOrderTravers(root->left);
		postOrderTravers(root->right);
		printf("%d ", root->info.first);
	}
}

void SearhMinMax(Tree* root, int& min, int& max, int& i) {
	if (root) {
		SearhMinMax(root->left, min, max, i);
		i++;
		if (i == 1) {
			min = root->info.first;
			max = root->info.first;
		}
		else {
			if (root->info.first < min) min = root->info.first;
			else if (root->info.first > max) max = root->info.first;
		}
		SearhMinMax(root->right, min, max, i);
	}
}

void  SearhAvg(Tree* root, double& avg, pair <int, double>& result) {
	if (root) {
		SearhAvg(root->left, avg, result);
		if (result.first) {
			if (abs(root->info.first - avg) < result.second) {
				result.first = root->info.first;
				result.second = abs(root->info.first - avg);
			}
		}
		else {
			result.first = root->info.first;
			result.second = abs(root->info.first - avg);
		}
		if (result.second == 0) return;
		SearhAvg(root->right, avg, result);
	}
}

template <typename T>
void SetNumber(T& a) {
	while (!(cin >> a) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка, введите числовое значение!" << endl;
	}
}