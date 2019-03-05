// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
using namespace std;

class inter
{
public:
	virtual void sos() PURE;
};

class base : public inter
{
public:
	base() {}
	~base() {}
public:


	// Унаследовано через inter
	virtual void sos() override
	{
		std::cout << "sos";
	}

};

class child : public base
{
public:
	child() {}
	~child() {}

public:
	virtual void sos() override
	{
		std::cout << "at";
	}
};

int main()
{
	base* b = new base();
	b->sos();

	child* c = new child();
	c->sos();

	std::cin.get();
	//string res;
	//ifstream fin("test.txt", ios_base::binary);
	//if (fin.is_open())
	//{
	//	while (!fin.eof())
	//	{
	//		getline(fin, res);
	//	}
	//	//TODO: Hello?
	//}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
