#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
//
using std::vector;
using std::wstring;
using std::wcin;
using std::wcout;
using std::endl;

class Task
{
public:
	virtual void Run() = 0;
};

#pragma region Models definition
class SubMenuModel;

class MenuItemModel
{
private:
	wstring title;
	SubMenuModel* subMenu;
	Task* task;

public:
	MenuItemModel()
		: title(wstring()), task(nullptr), subMenu(nullptr) { }

	MenuItemModel(wstring title)
		: title(title), task(nullptr), subMenu(nullptr) { }

	MenuItemModel(wstring title, SubMenuModel* subMenu)
		: title(title), subMenu(subMenu) { }

	MenuItemModel(wstring title, Task* task)
		: title(title), task(task) { }

	inline wstring& getTitle();
	void setTitle(wstring title);

	inline SubMenuModel* getSubMenu();
	void setSubmenu(SubMenuModel* subMenu);

	inline Task* getTask();
	void setTask(Task* task);
};

class MenuModel
{
protected:
	wstring title;
	vector<MenuItemModel*> menuItems;
	unsigned short exitIndex;
	MenuItemModel* exitMenuItem;

public:
	MenuModel(wstring title, vector<MenuItemModel*> menuItems);

	~MenuModel();

	inline wstring& getTitle();
	void setTitle(wstring title);

	inline vector<MenuItemModel*>& getMenuItems();
	void setMenuItems(vector<MenuItemModel*> menuItems);

	MenuItemModel* getMenuItem(unsigned short index);
	void addMenuItem(MenuItemModel* menuItem);

	unsigned short getExitItemIndex();
private:
	void addExitItem();
};

class SubMenuModel : public MenuModel
{
public:
	SubMenuModel()
		: SubMenuModel(wstring(), vector<MenuItemModel*>()) { }

	SubMenuModel(wstring title)
		: SubMenuModel(title, vector<MenuItemModel*>()) { }

	SubMenuModel(vector<MenuItemModel*> menuItems) 
		: SubMenuModel(wstring(), menuItems) { }

	SubMenuModel(wstring title, vector<MenuItemModel*> menuItems)
		: MenuModel(title, menuItems) { }
};
#pragma endregion

#pragma region View definition
class Viewable
{
public:
	virtual void view() = 0;
};

class MenuItemView : public	Viewable
{
protected:
	MenuItemModel* menuItemModel;

	MenuItemView(MenuItemModel * menuItemModel)
		: menuItemModel(menuItemModel) { }

public:
	inline MenuItemModel* getMenuItemModel();
	void setMenuModel(MenuItemModel* menuItemModel);

	// Унаследовано через MenuViewer
	virtual void view() override = 0;
};

class MenuItemConsoleView : public MenuItemView
{
public:
	MenuItemConsoleView()
		: MenuItemConsoleView(nullptr) { }

	MenuItemConsoleView(MenuItemModel * menuItemModel)
		: MenuItemView(menuItemModel) { }

	// Унаследовано через MenuView
	virtual void view() override;
};

class MenuView : public Viewable
{
protected:
	MenuModel* menuModel;

	MenuView(MenuModel * menuModel)
		: menuModel(menuModel) { }

public:
	inline MenuModel* getMenuModel();
	void setMenuModel(MenuModel* menuModel);

// Унаследовано через MenuViewer
virtual void view() override = 0;
};

class MenuConsoleView : public MenuView
{
private:
	const wstring placeholder = L"*****";

public:
	MenuConsoleView()
		: MenuConsoleView(nullptr) { }

	MenuConsoleView(MenuModel * menuModel)
		: MenuView(menuModel) { }

	// Унаследовано через MenuView
	virtual void view() override;
};
#pragma endregion


class Controller
{
public:
	virtual void start() = 0;
private:
	virtual unsigned short wait() = 0;
};



class MenuConsoleController;

class MenuItemConsoleController : public Controller
{
private:
	MenuItemModel* menuItem;
	MenuItemView*  menuItemView;

public:
	MenuItemConsoleController(MenuItemModel* menuItem, MenuItemView* menuItemView)
		: menuItem(menuItem), menuItemView(menuItemView) { }

	// Унаследовано через Controller
public:
	virtual void start() override;

private:
	virtual unsigned short wait() override;

};

class MenuConsoleController : public Controller
{
private:
	MenuModel* menuModel;
	MenuView*  menuView;
public:
	MenuConsoleController(MenuModel* menuModel, MenuView* menuView)
		: menuModel(menuModel), menuView(menuView) {}

	// Унаследовано через Controller
public:
	virtual void start() override;

private:
	virtual unsigned short wait() override;;

	bool menuItemExits(unsigned short menuItemIndex);
};
