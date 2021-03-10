#include "stdio.h"
#include <iostream>
#include "conio.h"
#include <windows.h>
#include <malloc.h>
#define MAX 20

using namespace std;

// Создаем основной класс
class Item {
private:			// Закрытые поля
	string country;
	string name;
	double price;
public:
	
	Item() {
		country = "";
		name = "";
		price = 0;
	}

	Item(string newCountry, string newName, double newPrice) {
		country = newCountry;
		name = newName;
		price = newPrice;
	}

	string getCountry() {
		return(country);
	}
	string getName() {
		return(name);
	}
	double getPrice() {
		return(price);
	}
	void setCountry(string newCountry) {
		country = newCountry;
	}
	void setName(string newName) {
		name = newName;
	}
	void setPrice(double newPrice) {
		price = newPrice;
	}

	// Read  Функция ввода
	static Item input(int i) {
		string newCountry;
		string newName;
		double newPrice;
		do {
			cout << "Input country of " << i + 1 << " product: ";
			rewind(stdin);
			cin >> newCountry;
		} while (newCountry[0] == '\0' || newCountry[0] == ' ');

		do {
			cout << "Input name of " << i + 1 << " product: ";
			rewind(stdin);
			cin >> newName;
		} while (newName[0] == '\0' || newName[0] == ' ');

		do {
			cout << "Input price of " << i + 1 << " product: ";
			rewind(stdin);
			cin >> newPrice;
			if (cin.fail())
				cin.clear();
		} while (newPrice <= 0);
		cout << endl;
		Item newItem = Item(newCountry, newName, newPrice);
		return(newItem);
	}

	// Display Функция вывода на экран
	void output(Item prod, int i) {
		cout << i + 1 << " product:" << endl;
		cout << "Country: " << prod.country << endl;
		cout << "Product: " << prod.name << endl;
		cout << "Price = " << prod.price << endl << endl;
	}

	// Add   Функция сложения
	static int add(Item item, Item secondItem) {
		int sum;
		sum = item.price + secondItem.price;
		return sum;
	}

	// Add sale
	static void sale(Item* item, int num) {
		for (int i = 0; i < num; i++)
			(*item).setPrice((*item).getPrice() * 0.5);
	}

	// Add markup Отмена скидки
	void markup(Item* item, int num) {
		for (int i = 0; i < num; i++)
			(*item).setPrice((*item).getPrice() * 2);
	}
};
// Вспомогательный класс
class Shop {
private:     //Закрытые поля
	Item prod[MAX];
	int quantityProd;
public:
	Shop() {
		quantityProd = 0;
	}
	Shop(int newQuantityProd) {
		quantityProd = newQuantityProd;
	}
	int getQuantityProd() {
		return(quantityProd);
	}
	// Демонстрируем принцип ассоциации
	static Shop input(Shop ourshop) {
		int quantityProd;
		Item prod[MAX];
		do {		//Количество товаров
			cout << "How many products do you have in your shop?" << endl;
			rewind(stdin);
			cin >> quantityProd;
			if (cin.fail())
				cin.clear();
		} while (quantityProd <= 0 || quantityProd > MAX);
		ourshop.quantityProd = quantityProd;

		for (int i = 0; i < quantityProd; i++) {
			ourshop.prod[i] = Item::input(i);
			cout << "If you want to have the same products - enter their quantity without the one just entered." << endl;
			cout << "If you don't want to - enter anything and click enter." << endl;
			rewind(stdin);
			int num;
			cin >> num;
			if (cin.fail())
				cin.clear();
			if (num > 0 && num < (quantityProd - i)) {
				for (int j = i + 1; j <= (i + num); j++) {
					ourshop.prod[j] = ourshop.prod[i];
				}
				i = i + num;
			}
		}
		return(ourshop);
	}

	void output(Shop ourshop) {
		for (int i = 0; i < quantityProd; i++) {
			ourshop.prod->output(ourshop.prod[i], i);
		}
	}

	static int add(Shop ourshop) {
		return(Item::add(ourshop.prod[0], ourshop.prod[0]));
	}
	
	static int add(Item* item, Item* secondItem) {
		int sum;
		sum = item->getPrice() + secondItem->getPrice();
		return sum;
	}

	~Shop() {
	}

};


int main() {

	Shop ourshop = Shop();
	ourshop = Shop::input(ourshop);
	ourshop.output(ourshop);
	cout << "Sum price = " << Shop::add(ourshop) << endl << endl;
	cout << "Program is over. Press any key to exit.";

	/*// Демонстрируем работу со статическим объектом
	cout << "Now it is a static object:" << endl; // Инициализируем
	Item staticItem = Item();

	cout << "Item created, Init used." << endl; // Выводим
	staticItem.output(0);

	cout << "Now we need enter values of item:" << endl; // Ввод и вывод данных
	staticItem = Item::input(0);
	staticItem.output(0);

	cout << "If we are add 2 equal items, we will get:" << endl; // Складываем и выводим
	cout << "Sum price = " << Item::add(&staticItem, &staticItem) << endl << endl;
	staticItem.output(0);

	cout << "Sale! 50%!" << endl;
	staticItem.sale(&staticItem, 1);
	staticItem.output(0);

	cout << "Sale is over!" << endl;
	staticItem.markup(&staticItem, 1);
	staticItem.output(0);

	cout << "Press any key to continue";
	_getch();

	system("cls"); // Очистка консоли

	// Демонстрируем работу динамического массива объектов
	cout << "Now it is a dynamic array of objects:" << endl;
	int num;
	do {
		cout << "How many objects do you want to input?" << endl;
		rewind(stdin);
		cin >> num;
		if (cin.fail())
			cin.clear();
	} while (num <= 0);
	cout << endl;

	Item* badItem = (Item*)calloc(num, sizeof(Item)); // Продемонстрировали работу calloc
	for (int i = 0; i < num; i++)
		badItem[i] = Item::input(i);

	cout << "Now we are showing your last object:" << endl;
	badItem[num - 1].output(num - 1);

	free(badItem); // Продемонстрировали free 

	Item* dynamicItem1 = new Item[5];  // Продемонстрировали работу delete[]
	delete[] dynamicItem1;

	Item* badItem2 = (Item*)malloc(10 * sizeof(Item)); // Продемонстрировали работу maloc
	badItem2 = (Item*)realloc(badItem2, 20 * sizeof(Item));
	free(badItem2); 
;*/
	_getch();
	return 0;
}
