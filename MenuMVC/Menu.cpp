#include "pch.h"
#include "Menu.h"

#pragma region MenuItemModel
wstring & MenuItemModel::getTitle()
{
	return title;
}

void MenuItemModel::setTitle(wstring title)
{
	this->title = title;
}

SubMenuModel * MenuItemModel::getSubMenu()
{
	return subMenu;
}

void MenuItemModel::setSubmenu(SubMenuModel * subMenu)
{
	this->subMenu = subMenu;
}

inline Task* MenuItemModel::getTask()
{
	return task;
}

void MenuItemModel::setTask(Task* task)
{
	this->task = task;
}
#pragma endregion

#pragma region MenuModel
MenuModel::MenuModel(wstring title, vector<MenuItemModel*> menuItems)
	: title(title), menuItems(menuItems)
{
	addExitItem();
}

MenuModel::~MenuModel()
{
	menuItems.clear();
	delete exitMenuItem;
}

wstring & MenuModel::getTitle()
{
	return title;
}

void MenuModel::setTitle(wstring title)
{
	this->title = title;
}

vector<MenuItemModel*>& MenuModel::getMenuItems()
{
	return menuItems;
}

void MenuModel::setMenuItems(vector<MenuItemModel*> menuItems)
{
	this->menuItems = menuItems;
}

MenuItemModel* MenuModel::getMenuItem(unsigned short index)
{
	return menuItems[index];
}

void MenuModel::addMenuItem(MenuItemModel * menuItem)
{
	menuItems.push_back(menuItem);
}

inline unsigned short MenuModel::getExitItemIndex()
{
	return exitIndex;
}


inline void MenuModel::addExitItem()
{
	exitIndex = (unsigned short) menuItems.size();
	std::wstringstream exitTitle;
	exitTitle << exitIndex + 1 << L". Выход";
	exitMenuItem = new MenuItemModel(exitTitle.str());
	menuItems.push_back(exitMenuItem);
}
#pragma endregion

#pragma region MenuItemView
MenuItemModel* MenuItemView::getMenuItemModel()
{
	return menuItemModel;
}

void MenuItemView::setMenuModel(MenuItemModel * menuItemModel)
{
	this->menuItemModel = menuItemModel;
}
#pragma endregion

#pragma region MenuItemConsoleView
// Унаследовано через MenuView
void MenuItemConsoleView::view()
{
	wcout << menuItemModel->getTitle() << endl;
}
#pragma endregion

#pragma region MenuView
MenuModel* MenuView::getMenuModel()
{
	return menuModel;
}

void MenuView::setMenuModel(MenuModel * menuModel)
{
	this->menuModel = menuModel;
}
#pragma endregion

#pragma region MenuConsoleView
// Унаследовано через MenuView
void MenuConsoleView::view()
{
	wcout << placeholder << menuModel->getTitle() << placeholder << endl;

	for (MenuItemModel* menuItem : menuModel->getMenuItems())
	{
		MenuItemConsoleView menuItemView(menuItem);
		menuItemView.view();
	}
}
#pragma endregion

void MenuItemConsoleController::start()
{
	SubMenuModel* subMenu = menuItem->getSubMenu();
	if (subMenu != nullptr)
	{
		MenuConsoleView subMenuView(subMenu);
		MenuConsoleController subMenuController((MenuModel*)subMenu, &subMenuView);
		subMenuController.start();
	}
	else
	{
		Task* task = menuItem->getTask();
		if (task != nullptr)
		{
			task->Run();
			wait();
		}
	}
}

unsigned short MenuItemConsoleController::wait()
{
	system("pause");
	return 0;
}

void MenuConsoleController::start()
{
	bool isExit = false;
	while (!isExit)
	{
		menuView->view();
		unsigned short waitResult = wait();
		if (waitResult == menuModel->getExitItemIndex())
			isExit = true;
		else
		{
			try
			{
				if (menuItemExits(waitResult))
				{
					MenuItemModel* menuItem = menuModel->getMenuItem(waitResult);
					MenuItemConsoleView menuItemView(menuItem);
					MenuItemConsoleController itemController(menuItem, &menuItemView);
					itemController.start();
				}
			}
			catch (...)
			{
				wcout << L"Такого пункта меню не существует." << endl;
			}
		}
	}
}

unsigned short MenuConsoleController::wait()
{
	wcout << L"Выберите пункт меню > ";
	unsigned short result = 0;
	wcin >> result;
	return result - 1;
}

inline bool MenuConsoleController::menuItemExits(unsigned short menuItemIndex)
{
	return menuModel->getMenuItem(menuItemIndex) != nullptr;
}
