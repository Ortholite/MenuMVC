#pragma once

#include <string>
#include <vector>
#include <iostream>
//
using std::vector;
using std::wstring;
using std::wcout;

class SubMenuModel;

class MenuItemModel
{
private:
	wstring title;
	SubMenuModel* subMenu;
public:
	MenuItemModel()
		: MenuItemModel(wstring(), nullptr)
	{
	}
	MenuItemModel(wstring title)
		: MenuItemModel(title, nullptr)
	{

	}
	MenuItemModel(wstring title, SubMenuModel* subMenu)
		: title(title), subMenu(subMenu)
	{

	}

	wstring& getTitle()
	{
		return title;
	}
	void setTitle(wstring title)
	{
		this->title = title;
	}

	SubMenuModel* getSubMenu()
	{
		return subMenu;
	}

	void setSubmenu(SubMenuModel* subMenu)
	{
		this->subMenu = subMenu;

	}
};

class MenuModel
{
protected:
	wstring title;
	vector<MenuItemModel*>  menuItems;

	MenuModel(wstring title, vector<MenuItemModel*> menuItems)
	{

	}
	~MenuModel() {}
public:
	vector<MenuItemModel*>& getMenuItems()
	{
		return menuItems;
	}

	void setMenuItems(vector<MenuItemModel*> menuItems)
	{
		this->menuItems = menuItems;
	}

	void addMenuItem(MenuItemModel* menuItem)
	{
		menuItems.push_back(menuItem);
	}
};

class SubMenuModel : public MenuModel
{
public:
	SubMenuModel() : SubMenuModel(wstring(), vector<MenuItemModel*>())
	{

	}
	SubMenuModel(wstring title) : SubMenuModel(title, vector<MenuItemModel*>())
	{

	}
	SubMenuModel(vector<MenuItemModel*> menuItems) : SubMenuModel(wstring(), menuItems)
	{

	}
	SubMenuModel(wstring title, vector<MenuItemModel*> menuItems) : MenuModel(title, menuItems)
	{

	}
};

class MenuViewer
{
public:
	virtual void view() = 0;
};

class MenuView : public MenuViewer
{
protected:
	MenuModel* menuModel;

	MenuView(MenuModel* menuModel)
		: menuModel(menuModel)
	{

	}
public:
	MenuModel* getMenuModel()
	{
		return menuModel;
	}

	void setMenuModel(MenuModel* menuModel)
	{
		this->menuModel = menuModel;
	}

	// Унаследовано через MenuViewer
	virtual void view() override = 0;
};

class MenuConsoleView : public MenuView
{
private:
	const wstring placeholder = L"*****";
public:
	MenuConsoleView() : MenuConsoleView(nullptr)
	{

	}
	MenuConsoleView(MenuModel* menuModel) : MenuView(menuModel)
	{

	}
	~MenuConsoleView() {}

private:
	// Унаследовано через MenuView
	virtual void view() override
	{
		for (MenuItemModel* menuItem : menuModel->getMenuItems())
		{
			wcout << placeholder << menuItem->getTitle() << placeholder << std::endl;
		}
	}
};