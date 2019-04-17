//
// Created by Denis LEWANDOWSKI on 2019-04-15.
//

#include "../includes/includes.h"
#include "ncurses.h"

int 	menu(std::string *menu_items, int size)
{
	int			menu_i = 1;
	bool		menu_lable = false;

	while (true)
	{
		clear();
		for (int i = 0; i < size; i++)
		{

			if (menu_i == i + 1)
				printw("-> %s\n", menu_items[i].c_str());
			else
				printw("   %s\n", menu_items[i].c_str());
		}
		refresh();
		switch (getch())
		{
			case KEY_UP:
				menu_i--;
				break;
			case KEY_DOWN:
				menu_i++;
				break ;
			case '\n':
				menu_lable = true;
				break;
			default:
				break;
		}
		if (menu_i == size + 1)
			menu_i = 1;
		else if (menu_i == 0)
			menu_i = size;
		if (menu_lable)
			break ;
	}
	return (menu_i);
}
