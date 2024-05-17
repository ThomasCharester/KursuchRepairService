#include <iostream>
#include <fstream>
#include "Windows.h"
#include <string>

using namespace std;

int input(string text, int min = 0, int max = 0) {
	int input;
	cout << text;
	while (true) {
		cin >> input;

		if (cin.fail() || ((input > max || input < min) || min == max)) {
			cin.clear();
			cin.ignore(INT_MAX);
			cout << "Неправильно введены данные. Повторите попытку.";
		}
		else return input;
	}
}
struct Date {
	int day;
	int mounth;
	int year;
};
struct Item {
	string name;
	string manufactorer;
	Date date;
	bool ready;
};
Item createItem() {
	Item item;
	cout << "\nВведите наименование: ";
	cin >> item.name;
	cout << "\nВведите марку: ";
	cin >> item.manufactorer;
	item.ready = input("\nВведите готов ли товар(0 - Нет, 1 - Да): ", 0, 1);
	item.date.day = input("\nВвод даты приёмки\nВведите день: ", 1, 31);
	item.date.mounth = input("\nВведите месяц: ", 1, 12);
	item.date.year = input("\nВведите год: ", 0, 3000);
	return item;
}
void addItem(Item** items, int* size) {
	Item* temp = new Item[*size + 1];

	if (*items != nullptr)
		for (int i = 0; i < *size; i++) {
			temp[i] = (*items)[i];
		}

	temp[(*size)++] = createItem();

	*items = temp;
}
void showItems(Item** items, int* size) {
	if (!(*size)) { cout << "\nНет элементов\n"; return; }
	for (int i = 0; i < *size; i++) {
		cout << "\nID: " << i
			<< "\nНаименование: " << (*items)[i].name
			<< "\nПроизводитель: " << (*items)[i].manufactorer
			<< "\nГотовность: " << (*items)[i].ready
			<< "\nДата приёмки: " << (*items)[i].date.day << '/' << (*items)[i].date.mounth << '/' << (*items)[i].date.year;
		cout << '\n';
	}
}
void removeItem(Item** items, int* size) {
	if (!(*size)) { cout << "\nНет элементов\n"; return; }

	showItems(items, size);

	int id = input("Введите номер элемента к удалению", 0, *size);

	Item* temp = new Item[*size - 1];

	for (int i = 0, j = 0; i < *size - 1; i++, j++) {
		if (i == id) j++;

		temp[j] = (*items)[i];
	}
	delete[] * items;

	*items = temp;

	(*size)--;
}
void mainMenu(Item** items, int* size) {
	while (true) {
		cout << "\n1 - Показать элементы"
			<< "\n2 - Добавить элементы"
			<< "\n3 - Удалить элемент"
			<< "\n0 - Выход";

		int choice = input("Выберите действие", 0, 3);

		switch (choice) {
		case 0:
			return;
			break;
		case 1:
			showItems(items, size);
			break;
		case 2:
			addItem(items, size);
			break;
		case 3:
			removeItem(items, size);
			break;
		}
	}
}
int main() {
	int size = 0;
	Item* items = nullptr;
	bool sorted = false;

	setlocale(LC_ALL, "Russian");

	mainMenu(&items, &size);


	return 0;
}