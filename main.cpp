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
			cout << "����������� ������� ������. ��������� �������.";
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
	cout << "\n������� ������������: ";
	cin >> item.name;
	cout << "\n������� �����: ";
	cin >> item.manufactorer;
	item.ready = input("\n������� ����� �� �����(0 - ���, 1 - ��): ", 0, 1);
	item.date.day = input("\n���� ���� ������\n������� ����: ", 1, 31);
	item.date.mounth = input("\n������� �����: ", 1, 12);
	item.date.year = input("\n������� ���: ", 0, 3000);
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
	if (!(*size)) { cout << "\n��� ���������\n"; return; }
	for (int i = 0; i < *size; i++) {
		cout << "\nID: " << i
			<< "\n������������: " << (*items)[i].name
			<< "\n�������������: " << (*items)[i].manufactorer
			<< "\n����������: " << (*items)[i].ready
			<< "\n���� ������: " << (*items)[i].date.day << '/' << (*items)[i].date.mounth << '/' << (*items)[i].date.year;
		cout << '\n';
	}
}
void removeItem(Item** items, int* size) {
	if (!(*size)) { cout << "\n��� ���������\n"; return; }

	showItems(items, size);

	int id = input("������� ����� �������� � ��������", 0, *size);

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
		cout << "\n1 - �������� ��������"
			<< "\n2 - �������� ��������"
			<< "\n3 - ������� �������"
			<< "\n0 - �����";

		int choice = input("�������� ��������", 0, 3);

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