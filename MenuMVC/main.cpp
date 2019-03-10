// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include "Menu.h"

using namespace std;

class MyClass : public Task
{
public:

	int add(int a, int b)
	{
		return a + b;
	}

	// Унаследовано через Task
	virtual void Run() override
	{
		int a = 0;
		int b = 0;
		wcout << L"Введите 1 число > ";
		wcin >> a;
		wcout << L"Введите 2 число > ";
		wcin >> b;
		wcout << L"Результат: " << add(a, b) << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");

	MyClass* obj = new MyClass();

	MenuItemModel* menuItem1 = new MenuItemModel(L"1. Сложить 2 целых числа.", obj);

	MenuItemModel* smenuItem1 = new MenuItemModel(L"1. Рофел");
	MenuItemModel* smenuItem2 = new MenuItemModel(L"2. Тест");
	SubMenuModel* subMenu = new SubMenuModel(L"Рофломеню", { smenuItem1, smenuItem2 });

	MenuItemModel* menuItem2 = new MenuItemModel(L"2. Сложить 3 вещественных числа.", subMenu);

	MenuModel*     menuModel = new MenuModel(L"Главное меню", { menuItem1, menuItem2 });

	MenuConsoleView menuView(menuModel);
	MenuConsoleController controller(menuModel, &menuView);
	controller.start();


	delete smenuItem1;
	delete smenuItem2;
	delete subMenu;
	delete menuItem1;
	delete menuItem2;
	delete menuModel;
}
