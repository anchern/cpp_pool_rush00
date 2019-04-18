#include "classes/Game.hpp"
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include "ncurses.h"
#include <unistd.h>

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <thread>
#include <mutex>
#include <chrono>

#include <unistd.h>
#include <iostream>

#define MENU_ITEM 3
#define PAUSE_ITEM 2

int numberOfPlayers;
//
//void print_bull_coords(t_bullet *bullets)
//{
//	if (bullets == 0)
//	{
//		file << "NULL\n";
//		return;
//	}
//	file << "x: " << bullets->bullet->get_location().x << "| y: " <<
//						bullets->bullet->get_location().y << std::endl;
//	print_bull_coords(bullets->next);
//}

void	getch_ret(int &getch_ref, bool &mut_flag)
{
	while (true)
	{
		while (mut_flag)
			;
		getch_ref = getch();
		if (getch_ref == 27)
			mut_flag = true;

	}
}


void takeClientMove(int &client_getch_ref, int socket, bool &mut_flag)
{
	while (true)
	{
		read(socket, &client_getch_ref, 4);
		if (client_getch_ref == 27)
			mut_flag = true;

	}
}

void	delete_and_move_bullets(Game &game, bool &mute_flag)
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
					game.getPlayers()[0].move(game.getPlayers()[0].get_degrees());
					setPlayersOnField(game);
				}
				break;
			case KEY_DOWN:
				game.getPlayers()[0].set_degrees(270);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					game.getPlayers()[0].move(game.getPlayers()[0].get_degrees());
					setPlayersOnField(game);
				}
				break;
			case KEY_RIGHT:
				game.getPlayers()[0].set_degrees(180);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					game.getPlayers()[0].move(game.getPlayers()[0].get_degrees());
					setPlayersOnField(game);
				}
				break;
			case KEY_LEFT:
				game.getPlayers()[0].set_degrees(0);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					game.getPlayers()[0].move(game.getPlayers()[0].get_degrees());
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
				break;
		}
		getch_ref = 0;
		usleep(70000);
	}
}

void	player2Action(std::function<int(std::string *menu_items, int size,
		int &client_getch_ref, int socket)> &menu,int &client_getch_ref,
				Game &game, std::thread &thr1, bool &mut_flag, int socket)
{
	int saveDegrees;
	std::string pause_items[PAUSE_ITEM] = {	"RESUME GAME",
											   "EXIT"};

	while (true)
	{
		switch (client_getch_ref)
		{
			case 27:
				switch (menu(pause_items, PAUSE_ITEM, client_getch_ref, socket))
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
				game.getPlayers()[1].set_degrees(90);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					game.getPlayers()[1].move(game.getPlayers()[1].get_degrees());
					setPlayersOnField(game);
				}
				break;
			case KEY_DOWN:
				game.getPlayers()[1].set_degrees(270);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					game.getPlayers()[1].move(game.getPlayers()[1].get_degrees());
					setPlayersOnField(game);
				}
				break;
			case KEY_RIGHT:
				game.getPlayers()[1].set_degrees(180);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					game.getPlayers()[1].move(game.getPlayers()[1].get_degrees());
					setPlayersOnField(game);
				}
				break;
			case KEY_LEFT:
				game.getPlayers()[1].set_degrees(0);
				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
				{
					game.getPlayers()[1].move(game.getPlayers()[1].get_degrees());
					setPlayersOnField(game);
				}
				break;
			case ' ':
				setPlayersOnField(game);
				saveDegrees = game.getPlayers()[1].get_degrees();
				game.getPlayers()[1].set_degrees(90);
				game.setBullets(game.getPlayers()[1].shot(game.getBullets()));
				game.getPlayers()[1].set_degrees(saveDegrees);
				break;
			default:
				setPlayersOnField(game);
		}
		client_getch_ref = 0;
		usleep(70000);

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
	for (int i = 0; i < numberOfPlayers; i++)
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

void sendData(int socket, Game &game, time_t sTime, time_t mTime)
{
	char *oneLineField;
	char header[1024];
	char *outData;


	sprintf(header, "%s | HP: %d | %s | HP: %d |\nTime: %.2ld:%.2ld | Score: %u\n",
			game.getPlayers()[0].get_name().c_str(),game.getPlayers()[0].get_hp(),
			game.getPlayers()[1].get_name().c_str(),game.getPlayers()[1].get_hp(),
			mTime, sTime, game.getScore());
	oneLineField = game.getOneLineField();
	outData = new char [strlen(oneLineField) + sizeof(header)];
	strcpy(outData, header);
	strcat(outData, oneLineField);
	send(socket, "y", 1, 0);
	send(socket, header, 1024, 0);
	send(socket, oneLineField, strlen(oneLineField) + 1, 0);
//	send(socket, outData, strlen(outData) + 1, 0);
	delete [] oneLineField;
	delete [] outData;
}

void	printField(Game &game, time_t sTime, int socket)
{
	time_t time;
	time_t sCurTime;
	time_t mCurTime;

	std::time(&time);
	sCurTime = (time - sTime) % 60;
	mCurTime = (time - sTime) / 60;
	sendData(socket, game, sCurTime, mCurTime);
	clear();
	if (numberOfPlayers == 2)
		printw("%s | HP: %d | %s | HP: %d |\nTime: %.2ld:%.2ld | Score: %u\n",
			game.getPlayers()[0].get_name().c_str(),game.getPlayers()[0].get_hp(),
			game.getPlayers()[1].get_name().c_str(),game.getPlayers()[1].get_hp(),
			mCurTime,sCurTime, game.getScore());
	else if (numberOfPlayers == 1)
		printw("%s | HP: %d |x: %d|y: %d|\nTime: %.2ld:%.2ld | Score: %u\n",
			   game.getPlayers()[0].get_name().c_str(),game.getPlayers()[0].get_hp(),
			   game.getPlayers()[0].get_location().x, game.getPlayers()[0].get_location().y,
			   mCurTime,sCurTime, game.getScore());
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



void	readFromServer(int &sock, bool &mut_flag)
{
	int getch_client;

	while (true)
	{
		if ((getch_client = getch()) == ' ')
			beep();
		if (getch_client == 27)
			mut_flag = true;
		if (getch_client == '\n')
			mut_flag = false;
		send(sock, &getch_client, 4, 0);
	}
}


int main()
{

	int j = 0;
	time_t sTime;
	int getch_ref;
	int client_getch_ref;
	Game &game = Game::instance();
	bool mut_flag = false;
	std::string menu_items[MENU_ITEM] = {"SINGLE PLAYER",
										 "MULTI PLAYER",
										 "EXIT"};
	int serverORclient = 0;
	std::string multiPlayerMenu_items[MULTIPLAYERMENU_ITEM] = {"CREATE GAME", "JOIN THE GAME"};
	std::string my_name;
	int server_fd = 0;

	setlocale(LC_ALL, "");
	initscr();
	noecho();
	keypad(stdscr, TRUE);


	switch (menu(menu_items, MENU_ITEM))
	{
		case 1:
			break;
		case 2:
			switch (menu(multiPlayerMenu_items, MULTIPLAYERMENU_ITEM))
			{
				case 1:
					serverORclient = 1;
					break;
				case 2:
					serverORclient = 2;
					break;
				default:
					break;
			}
			break;
		case 3:
			clear();
			refresh();
			return (0);
		default:
			break;
	}



	if (serverORclient == 0)
	{
		numberOfPlayers = 1;
		initSingleGame(game, "Player1");
		std::thread tKeyInput(getch_ret, std::ref(getch_ref),
							  std::ref(mut_flag)); //thread for read from keyboard
		std::thread tPlayer1Action(player1Action, std::ref(getch_ref),
								   std::ref(game),
								   std::ref(tKeyInput), std::ref(mut_flag));
		std::time(&sTime);
		while (true)
		{
			while (mut_flag)
				;
			if (game.getPlayers()[0].get_hp() == 0)
			{
				tKeyInput.detach();
				tPlayer1Action.detach();
				return (0);
			}
			if (j % 18 == 0)
				standardUnitGeneration(game);
			mut_flag = true;
			score_calc(game);
			setEntitiesOnPrintField(game);
			printField(game, sTime, 0);
			game.clsField();
			game.clsGameEntities();
			standardUnitActions(j, game);
			delete_and_move_bullets(game, mut_flag);
			mut_flag = false;
			usleep(70000);
			j++;
		}
	}
	else if (serverORclient == 1)
	{
		numberOfPlayers = 2;
		int socket = 0;
		ClientServer server(serverORclient);
		server.createSocket();
		server.setFlagsAndBindNameSocket();
		server.listenForConnections();
		server.acceptConnectionOnSocket();
		socket = server.getSocket();
		initMultiGame(game, "Player1", "Player2");
		std::thread tKeyInput(getch_ret, std::ref(getch_ref),
							  std::ref(mut_flag)); //thread for read from keyboard
		std::thread tPlayer1Action(player1Action, std::ref(getch_ref),
								   std::ref(game),
								   std::ref(tKeyInput), std::ref(mut_flag));
		std::function<int(std::string *menu_items, int size, int &client_getch_ref,
						  int socket)> menu_func = client_pause_menu;
		std::thread tClientMove(takeClientMove, std::ref(client_getch_ref), socket,
								std::ref(mut_flag));
		std::thread tPlayer2Action(player2Action, std::ref(menu_func),
								   std::ref(client_getch_ref), std::ref(game),
								   std::ref(tClientMove), std::ref(mut_flag),
								   socket);

		std::time(&sTime);
		while (true)
		{
			while (mut_flag)
				;
			if (game.getPlayers()[0].get_hp() == 0 || game.getPlayers()[1].get_hp() == 0)
			{
				tKeyInput.detach();
				tPlayer1Action.detach();
				tPlayer2Action.detach();
				tClientMove.detach();
				close(socket);
				close(server_fd);
				return (0);
			}
			mut_flag = true;
			if (j % 18 == 0)
				standardUnitGeneration(game);
			score_calc(game);
			setEntitiesOnPrintField(game);
			printField(game, sTime, socket);
			game.clsField();
			game.clsGameEntities();
			standardUnitActions(j, game);
			delete_and_move_bullets(game, mut_flag);
			mut_flag = false;
			usleep(70000);
			j++;
		}
	}
	else if (serverORclient == 2) // CLIENT MOD
	{
		numberOfPlayers = 2;
		char buffer[HEIGHT * WIDTH] = {0};
		ClientServer client(serverORclient);
		int sock = 0, valread;

		client.createSocket();
		client.setIP("10.111.6.8");
		client.convertIPFromTextToBinary();
		client.connectToServer();
		sock = client.getServerFd();
		std::thread thr1(readFromServer, std::ref(sock), std::ref(mut_flag));
		long long epoch_server = 0;
		char key;
		while (true)
		{
			while (mut_flag)
			{
				valread = read(sock, buffer, 1024);
				clear();
				printw("%s\n", buffer);
				refresh();
				bzero(buffer, sizeof(buffer));
			}
			while ((valread = read(sock, &key, 1)) > 0)
			{
				if (key == 'y')
					break;
			}
			key = 0;
			usleep(1000);
			clear();
			if ((valread = read(sock, buffer, HEIGHT * (WIDTH + 1) + 1024)) <= 0)
			{
				print_game_over();
				thr1.detach();
				exit(0);
			}
			for (int k = 0; k < WIDTH; k++)
				printw("-");
			printw("\n");
			bzero(buffer, sizeof(buffer));
			if ((valread = read(sock, buffer, HEIGHT * (WIDTH + 1) + 1024)) <= 0)
			{
				print_game_over();
				thr1.detach();
				exit(0);
			}
			printw("%s\n", buffer);
			for (int k = 0; k < WIDTH; k++)
				printw("-");
			printw("\n");
			refresh();
			bzero(buffer, sizeof(buffer));
		}
	}
}