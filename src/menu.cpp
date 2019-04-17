#include "Game.hpp"

int 	menu(std::string *menu_items, int size)
{
	int			menu_i = 1;
	bool		menu_lable = false;

	while (true)
	{
		clear();
		for (int i = 0; i < size; i++)
		{
//			move((HEIGHT + i) / 2, (WIDTH - 1) / 2);
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

int 	client_pause_menu(std::string *menu_items, int size, int &client_getch_ref, int socket)
{
	int			menu_i = 1;
	bool		menu_lable = false;
	char 		client_menu[1024];

	while (true)
	{
		for (int i = 0; i < size; i++)
		{
//			move((HEIGHT + i) / 2, (WIDTH - 1) / 2);
			if (menu_i == i + 1)
				sprintf(&client_menu[strlen(client_menu)], "-> %s\n", menu_items[i].c_str());
			else
				sprintf(&client_menu[strlen(client_menu)], "   %s\n", menu_items[i].c_str());
		}
		clear();
		printw("%s", client_menu);
		refresh();
		send(socket, client_menu, 1024, 0);
		bzero(client_menu, 1024);
		while (client_getch_ref == 0)
			;
		switch (client_getch_ref)
		{
			case KEY_UP:
				menu_i--;
				client_getch_ref = 0;
				break;
			case KEY_DOWN:
				menu_i++;
				client_getch_ref = 0;
				break ;
			case '\n':
				menu_lable = true;
				client_getch_ref = 0;
				break;
			default:
				client_getch_ref = 0;
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
