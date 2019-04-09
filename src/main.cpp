#include "classes/Game.hpp"
#include <iostream>
#include "ncurses.h"
#include <unistd.h>
#include <thread>

#define MENU_ITEM 3
#define PAUSE_ITEM 2

std::mutex mutex;

int 	menu(std::string *menu_items, int size);

void print_bull_coords(t_bullet *bullets)
{
	if (bullets == 0)
		return;
	std::cout << "x: " << bullets->bullet->get_location().x << " | y: " <<
	bullets->bullet->get_location().y << std::endl;
	print_bull_coords(bullets->next);
}

void	getch_ret(int &getch_ref, bool &mut_flag)
{
	while (true)
	{
		while (mut_flag)
			;
		getch_ref = getch();
		if (getch_ref == 27)
			mut_flag = true;
		usleep(500);
	}
}


void	delete_and_move_death_bullets(Game &game)
{
	t_bullet *bulletTmp;
	t_bullet *bulletTmp1;

	bulletTmp = game.getBullets();
	bulletTmp1 = bulletTmp;
	while (bulletTmp != nullptr)
	{
		if (bulletTmp->bullet->get_location().x == -1)
		{
			bulletTmp1 = delete_bullet(bulletTmp1, bulletTmp->bullet);
			bulletTmp = bulletTmp1;
			continue ;
		}
		bulletTmp = bulletTmp->next;
	}
	game.setBullets(bulletTmp1);
	if (game.getBullets() != nullptr)
	{
		for (int i = 0; i < game.getBullets()->bullet->get_speed(); i++)
		{
			moveBullets(game);
			setBulletsOnField(game);
			if (game.getBullets() == nullptr)
				break ;
		}
	}
}

void	player1Action(int &getch_ref, Game &game, std::thread &thr1, bool &mut_flag)
{
	int saveDegrees;
	std::string pause_items[PAUSE_ITEM] = {	"RESUME GAME",
											  "EXIT"};

	while (true)
	{
		switch (getch_ref)
		{
			case 27:
				switch (menu(pause_items, PAUSE_ITEM))
				{
					case 1:
						break;
					case 2:
						clear();
						printw("BYE!");
						refresh();
						usleep(100000);
						endwin();
						thr1.detach();
						exit(0);
					default:
						break;
				}
				mut_flag = false;
				break;
			case KEY_UP:
				game.getPlayers()[0].set_degrees(90);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					movePlayer(game);
					setPlayersOnField(game);
				}
				break;
			case KEY_DOWN:
				game.getPlayers()[0].set_degrees(270);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					movePlayer(game);
					setPlayersOnField(game);
				}
				break;
			case KEY_RIGHT:
				game.getPlayers()[0].set_degrees(180);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					movePlayer(game);
					setPlayersOnField(game);
				}
				break;
			case KEY_LEFT:
				game.getPlayers()[0].set_degrees(0);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					movePlayer(game);
					setPlayersOnField(game);
				}
				break;
			case ' ':
				setPlayersOnField(game);
				saveDegrees = game.getPlayers()[0].get_degrees();
				game.getPlayers()[0].set_degrees(90);
				game.setBullets(game.getPlayers()[0].shot(game.getBullets()));
				game.getPlayers()[0].set_degrees(saveDegrees);
				break;
			default:
				setPlayersOnField(game);
		}
		getch_ref = 0;
		usleep(500);
	}
}

void score_calc(Game &game)
{
	int number_of_units = 0;
	int number_of_units_tmp = 0;
	for (int i = 0; i < STANDART_UNITS_NUMBER; i++)
	{
		if (game.getStandartUnits()[i].get_location().x != -1)
			number_of_units++;
	}
	for (int i = 0; i < NUMBEROFPLAYERS; i++)
		if (game.getPlayers()[i].get_hp() == 0)
			game.getPlayers()[i].death();
	for (int i = 0; i < STANDART_UNITS_NUMBER; i++)
		if (game.getStandartUnits()[i].get_hp() == 0)
			game.getStandartUnits()[i].death();
	for (int i = 0; i < STANDART_UNITS_NUMBER; i++)
	{
		if (game.getStandartUnits()[i].get_location().x != -1)
			number_of_units_tmp++;
	}
	if (number_of_units - number_of_units_tmp > 0)
		game.setScore(number_of_units - number_of_units_tmp);
}

void	printField(Game &game, time_t sTime)
{
	time_t time;

	std::time(&time);
	clear();
	printw("Player: %s | HP: %d | Time: %.2d:%.2d | Score: %u\n",game.getPlayers()[0].get_name().c_str(),
		   game.getPlayers()[0].get_hp(), (time - sTime) /60,(time - sTime) % 60, game.getScore());
	for (int k = 0; k < WIDTH; k++)
		printw("-");
	printw("\n");
	game.printField();
	for (int k = 0; k < WIDTH; k++)
		printw("-");
	printw("\n");
	refresh();
}

void	standardUnitActions(int j, Game &game)
{
	if (j % 23 == 0)
	{
		for (int i = 0; i < STANDART_UNITS_NUMBER; i++)
			if (game.getStandartUnits()[i].get_location().x != -1)
				game.setBullets(game.getStandartUnits()[i].shot(game.getBullets()));
	}
	else
	{
		for (int i = 0; i < game.getStandartUnits()->get_speed(); i++)
		{
			moveStantardUnits(game);
			setStandardUnitsOnField(game);
		}
	}
}

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

int main()
{

	int			j = 0;
	time_t		sTime;
	int			getch_ref;
	Game		&game = Game::instance();
	bool		mut_flag = false;
	std::string menu_items[MENU_ITEM] = {	"SINGLE PLAYER",
									   		"MULTI PLAYER",
											 "EXIT"};


	setlocale(LC_ALL, "");
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	initGame(game, "Player1");
	std::time(&sTime);


	switch (menu(menu_items, MENU_ITEM))
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			printw("Bye!\n");
			return (0);
		default:
			break;
	}

	std::thread	tKeyInput(getch_ret, std::ref(getch_ref), std::ref(mut_flag)); //thread for read from keyboard
	std::thread tPlayer1Action(player1Action, std::ref(getch_ref), std::ref(game),
			std::ref(tKeyInput), std::ref(mut_flag));


	while (true)
	{
		while (mut_flag)
			;
		if (j % 18 == 0)
			standardUnitGeneration(game);
		score_calc(game);
		setEntitiesOnPrintField(game);
		printField(game, sTime);
		game.clsField();
		game.clsGameEntities();
		usleep(100000);
		standardUnitActions(j, game);
		delete_and_move_death_bullets(game);
		j++;
	}
}