#include "classes/Game.hpp"
#include <iostream>
#include "ncurses.h"
#include <unistd.h>
#include <thread>

void print_bull_coords(t_bullet *bullets)
{
	if (bullets == 0)
		return;
	std::cout << "x: " << bullets->bullet->get_location().x << " | y: " <<
	bullets->bullet->get_location().y << std::endl;
	print_bull_coords(bullets->next);
}

void	getch_ret(int &getch_ref)
{
	while (true)
	{
		getch_ref = getch();
		usleep(1000);
	}
}

int main()
{
	int j = 0;
	Game &game = Game::instance();
	int saveDegrees;
	initGame(game, "Kek");
	t_bullet *bulletTmp;
	t_bullet *bulletTmp1;
	int getch_ref;
	int number_of_units = 0;
	int number_of_units_tmp = 0;

	setlocale(LC_ALL, "");
	std::thread thr1(getch_ret, std::ref(getch_ref));

	initscr();
	noecho();
	keypad(stdscr, TRUE);
	setEntitiesOnPrintField(game);
//	std::cout << "----------------------------------------------------"
//			  << std::endl;
	game.printField();
	refresh();
//	std::cout << "----------------------------------------------------"
//			  << std::endl;
	time_t sTime;
	time_t time;

	std::time(&sTime);

	while (true)
	{
		if (j % 18 == 0)
			standardUnitGeneration(game);
		number_of_units = 0;
		number_of_units_tmp = 0;
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
		setEntitiesOnPrintField(game);

		std::time(&time);
		clear();
		printw("HP: %d | Time: %.2d:%.2d | Score: %u\n",game.getPlayers()[0].get_hp(), (time - sTime) / 60, (time -
		sTime) % 60, game.getScore());
		for (int k = 0; k < WIDTH; k++)
			printw("-");
		printw("\n");
		game.printField();
		for (int k = 0; k < WIDTH; k++)
			printw("-");
		printw("\n");
		refresh();
		game.clsField();
		game.clsGameEntities();
		usleep(100000);
		switch (getch_ref)
		{
			case KEY_UP:
				game.getPlayers()[0].set_degrees(90);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					movePlayer(game);
					setPlayersOnField(game);
				}
				break ;
			case KEY_DOWN:
				game.getPlayers()[0].set_degrees(270);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					movePlayer(game);
					setPlayersOnField(game);
				}
				break ;
			case KEY_RIGHT:
				game.getPlayers()[0].set_degrees(180);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					movePlayer(game);
					setPlayersOnField(game);
				}
				break ;
			case KEY_LEFT:
				game.getPlayers()[0].set_degrees(0);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					movePlayer(game);
					setPlayersOnField(game);
				}
				break ;
			case ' ':
				setPlayersOnField(game);
				saveDegrees = game.getPlayers()[0].get_degrees();
				game.getPlayers()[0].set_degrees(90);
				game.setBullets(game.getPlayers()[0].shot(game.getBullets()));
				game.getPlayers()[0].set_degrees(saveDegrees);
				break ;
			case 'q':
				clear();
				printw("Bye!\n");
				refresh();
				usleep(100000);
				endwin();
				thr1.detach();
				return (0);
			default:
				setPlayersOnField(game);
		}
		getch_ref = 0;
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
		j++;
	}
}