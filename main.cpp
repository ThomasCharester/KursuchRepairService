#include <iostream>
#include <fstream>
#include "Windows.h"
#include <string>

using namespace std;

/// <summary>
/// Ввод целочисленных данных в заданном диапазоне.
/// </summary>
/// <param name="text">Текст для отображения.</param>
/// <param name="min">Нижняя граница диапазона.</param>
/// <param name="max">Верхняя граница.</param>
/// <returns>Введённое значение.</returns>
int input(string text, int min = 0, int max = 0) {
	int input;
	while (true) {
		cout << text;

		cin >> input;

		if (cin.fail() || ((input > max || input < min) || min == max)) {
			cin.clear();
			cin.ignore();
			cout << "\nНеправильно введены данные. Повторите попытку.";
		}
		else return input;
	}
}
// Дата День/Месяц/Год
struct Date {
	int day;
	int mounth;
	int year;
};
// Аппаратура
struct Item {
	string name;
	string manufactorer;
	Date date;
	bool ready;
};
/// <summary>
/// Создать объект аппаратуры.
/// </summary>
/// <returns>Новая аппаратура</returns>
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
/// <summary>
/// Добавить аппаратуру в список.
/// </summary>
/// <param name="items">Указатель на массив аппаратуры.</param>
/// <param name="size">Размер массива</param>
void addItem(Item** items, int* size) {
	Item* temp = new Item[*size + 1];

	if (*items != nullptr)
		for (int i = 0; i < *size; i++) {
			temp[i] = (*items)[i];
		}

	temp[(*size)++] = createItem();

	*items = temp;
}
/// <summary>
/// Вывести список аппаратуры.
/// </summary>
/// <param name="items">Указатель на массив аппаратуры.</param>
/// <param name="size">Размер массива</param>
void showItems(Item** items, int* size) {
	if (!(*size)) { cout << "\nНет элементов\n"; return; }
	for (int i = 0; i < *size; i++) {
		cout << "\nID: " << i
			<< "\nНаименование: " << (*items)[i].name
			<< "\nПроизводитель: " << (*items)[i].manufactorer
			<< "\nГотовность: " << (*items)[i].ready
			<< "\nДата приёмки: " << (*items)[i].date.day << '/' << (*items)[i].date.mounth << '/' << (*items)[i].date.year;
		cout << "\n\n";
	}
}
/// <summary>
/// Удалить аппаратуру из массива.
/// </summary>
/// <param name="items">Указатель на массив аппаратуры.</param>
/// <param name="size">Размер массива</param>
void removeItem(Item** items, int* size) {
	if (!(*size)) { cout << "\nНет элементов\n"; return; }

	showItems(items, size);

	int id = input("\nВведите номер элемента к удалению: ", 0, *size);

	Item* temp;

	if (*size == 1) temp = nullptr;
	else
	{
		temp = new Item[*size - 1];

		for (int i = 0, j = 0; i < *size - 1; i++, j++) {
			if (i == id) j++;

			temp[i] = (*items)[j];
		}
	}

	delete[] * items;

	*items = temp;

	(*size)--;
}

// Файл вывод
void writeFile(Item** items, int* size, string filename) {
	fstream file(filename, ios::out);
	file << *size << '\n';
	for (int i = 0; i < *size; i++) {
		file << (*items)[i].name << ' ' << (*items)[i].manufactorer << ' ' << (*items)[i].ready << ' '
			<< (*items)[i].date.day << '/' << (*items)[i].date.mounth << '/' << (*items)[i].date.year << '\n';
	}

	file.close();
}
// Файл ввод
void readFile(Item** items, int* size, string filename)
{
	fstream file(filename, ios::in);

	if (file.eof() || !file.is_open())
	{
		file.close();
		return;
	}

	if (*size) delete[] * items;

	string temp;

	getline(file, temp, '\n');
	*size = stoi(temp);

	Item* tempItems = new Item[*size];

	for (int i = 0; i < *size; i++)
	{
		string name, manufactorer;
		int ready, day, mounth, year;

		getline(file, name, ' ');
		getline(file, manufactorer, ' ');

		getline(file, temp, ' ');
		ready = stoi(temp);

		getline(file, temp, '/');
		day = stoi(temp);
		getline(file, temp, '/');
		mounth = stoi(temp);
		getline(file, temp, '\n');
		year = stoi(temp);

		tempItems[i].name = name;
		tempItems[i].manufactorer = manufactorer;
		tempItems[i].ready = ready;

		tempItems[i].date.day = day;
		tempItems[i].date.mounth = mounth;
		tempItems[i].date.year = year;
	}

	*items = tempItems;


	file.close();
}


// Сортировки

// Сортировка методом выбора
void selectionSort(Item** items, int* size, bool* isSorted) {

	int i, j, min;

	for (i = 0; i < *size - 1; i++) {
		min = i;
		for (j = i + 1; j < *size; j++)
			if (!(((*items)[j].date.day == (*items)[min].date.day && ((*items)[j].date.mounth == (*items)[min].date.mounth && (*items)[j].date.year == (*items)[min].date.year))
				|| ((*items)[j].date.mounth > (*items)[min].date.mounth && (*items)[j].date.year == (*items)[min].date.year)
				|| (*items)[j].date.year > (*items)[min].date.year))
				min = j;

		Item temp = (*items)[min];
		(*items)[min] = (*items)[i];
		(*items)[i] = temp;
	}

	*isSorted = true;
}

void bubbleSort(Item** items, int* size, bool* isSorted) {
	int i, j;
	for (i = 0; i < *size - 1; i++)
		for (j = 0; j < *size - i - 1; j++)
			if ((((*items)[j].date.day == (*items)[j + 1].date.day && ((*items)[j].date.mounth == (*items)[j + 1].date.mounth && (*items)[j].date.year == (*items)[j + 1].date.year))
				|| ((*items)[j].date.mounth > (*items)[j + 1].date.mounth && (*items)[j].date.year == (*items)[j + 1].date.year)
				|| (*items)[j].date.year > (*items)[j + 1].date.year))
			{
				Item temp = (*items)[j];
				(*items)[j] = (*items)[j + 1];
				(*items)[j + 1] = temp;
			}
	*isSorted = true;
}
// Поиски

// Линейный поиск
int linearSearch(Item** items, int* size, Date key) {
	for (int i = 0; i < *size; i++)
		if ((*items)[i].date.day == key.day && (*items)[i].date.mounth == key.mounth && (*items)[i].date.year == key.year)
			return i;

	return -1;
}
// Бинарный поиск
int binarySearch(Item** items, int* size, Date key, bool* isSorted) {
	if (!isSorted) { 
		selectionSort(items, size, isSorted); 
		cout << "\nМассив был предварительно отсортирован методом прямого выбора.\n";
	}

	int high = *size, low = 0;
	while (low <= high) {
		int mid = low + (high - low) / 2;

		if ((*items)[mid].date.day == key.day && (*items)[mid].date.mounth == key.mounth && (*items)[mid].date.year == key.year)
			return mid;
		if (!(((*items)[mid].date.day == key.day && ((*items)[mid].date.mounth == key.mounth && (*items)[mid].date.year == key.year))
			|| ((*items)[mid].date.mounth > key.mounth && (*items)[mid].date.year == key.year)
			|| (*items)[mid].date.year > key.year))
			low = mid + 1;
		else
			high = mid - 1;
	}

	return -1;
}

// Шаблоны меню

// Меню поиска
void searchMenu(Item** items, int* size, bool *isSorted) {
	while (true) {
		system("cls");
		cout << "\n1 - Линейный поиск"
			<< "\n2 - Бинарный поиск"
			<< "\n0 - Выход";

		int choice = input("\nВыберите метод: ", 0, 2);

		switch (choice) {
		case 0:
			return;
			break;
		case 1:
		{
			Date key;

			cout << "\nВвод ключа поиска\n";

			key.day = input("\nВведите день: ", 1, 31);
			key.mounth = input("\nВведите месяц: ", 1, 12);
			key.year = input("\nВведите год: ", 0, 3000);

			int id = linearSearch(items, size, key);

			system("cls");
			if (id >= 0)
				cout << "Элемент найден, его индекс " << id << '\n';
			else
				cout << "Элемент не найден\n";
			system("pause");
		}
		break;
		case 2:
			Date key;

			cout << "\nВвод ключа поиска\n";

			key.day = input("\nВведите день: ", 1, 31);
			key.mounth = input("\nВведите месяц: ", 1, 12);
			key.year = input("\nВведите год: ", 0, 3000);

			int id = binarySearch(items, size, key, isSorted);

			system("cls");
			if (id >= 0)
				cout << "Элемент найден, его индекс " << id << '\n';
			else if (id == -1)
				cout << "Элемент не найден\n";
			else
				cout << "Массив не отсортирован\n";
			system("pause");
			break;
		}
	}
}
// Меню сортировки
void sortMenu(Item** items, int* size, bool* isSorted) {
	while (true) {
		system("cls");
		cout << "\n1 - Методом прямого выбора"
			<< "\n2 - Методом пузырька"
			<< "\n0 - Выход";

		int choice = input("\nВыберите метод: ", 0, 2);

		switch (choice) {
		case 0:
			return;
			break;
		case 1:
			selectionSort(items, size, isSorted);
			break;
		case 2:
			bubbleSort(items, size, isSorted);
			break;
		}
	}
}
// Главное меню
void mainMenu(Item** items, int* size, string fileName, bool* isSorted) {
	while (true) {
		system("cls");
		cout << "\n1 - Показать элементы"
			<< "\n2 - Добавить элементы"
			<< "\n3 - Удалить элемент"
			<< "\n4 - Поиск элемента"
			<< "\n5 - Сортировка элементов"
			<< "\n6 - Прочесть данные из файла"
			<< "\n7 - Записать данные в файл"
			<< "\n0 - Выход";

		int choice = input("\nВыберите действие: ", 0, 7);

		switch (choice) {
		case 0:
			return;
			break;
		case 1:
			system("cls");
			showItems(items, size);
			system("pause");
			break;
		case 2:
			addItem(items, size);
			break;
		case 3:
			removeItem(items, size);
			break;
		case 4:
			searchMenu(items, size, isSorted);
			break;
		case 5:
			sortMenu(items, size, isSorted);
			break;
		case 6:
			readFile(items, size, fileName);
			break;
		case 7:
			writeFile(items, size, fileName);
			break;
		}
	}
}

int main() {
	string fileName = "Items.txt";

	int size = 0;
	Item* items = nullptr;
	bool isSorted = false;

	setlocale(LC_ALL, "Russian");

	mainMenu(&items, &size, fileName, &isSorted);


	return 0;
}