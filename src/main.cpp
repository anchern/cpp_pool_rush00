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
	if (numberOfPlayers == 2)
		sendData(socket, game, sCurTime, mCurTime);
	clear();
	if (numberOfPlayers == 2)
		printw("%s | HP: %d | %s | HP: %d |\nTime: %.2ld:%.2ld | Score: %u\n",
			game.getPlayers()[0].get_name().c_str(),game.getPlayers()[0].get_hp(),
			game.getPlayers()[1].get_name().c_str(),game.getPlayers()[1].get_hp(),
			mCurTime,sCurTime, game.getScore());
	else if (numberOfPlayers == 1)
		printw("%s | HP: %d |\nTime: %.2ld:%.2ld | Score: %u\n",
			   game.getPlayers()[0].get_name().c_str(),game.getPlayers()[0].get_hp(),
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

int		startMenu()
{
	int serverOrClient = 0;
	std::string menu_items[MENU_ITEM] = {"SINGLE PLAYER",
										 "MULTI PLAYER",
										 "EXIT"};
	std::string multiPlayerMenu_items[MULTIPLAYERMENU_ITEM] = {"CREATE GAME", "JOIN THE GAME"};


	switch (menu(menu_items, MENU_ITEM))
	{
		case 1:
			serverOrClient = 0;
			break;
		case 2:
			switch (menu(multiPlayerMenu_items, MULTIPLAYERMENU_ITEM))
			{
				case 1:
					serverOrClient = 1;
					break;
				case 2:
					serverOrClient = 2;
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
	return (serverOrClient);
}

int main()
{
	int getch_ref;
	int client_getch_ref;
	Game &game = Game::instance();
	bool mut_flag = false;

	int serverOrClient = 0;

	char my_name[64];




	setlocale(LC_ALL, "");
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	numberOfPlayers = 0;

	serverOrClient = startMenu();
	clear();
	printw("ENTER YOUR NAME: ");
	echo();
	refresh();
	scanw("%s\n", my_name);
	noecho();
	if (serverOrClient == 0)
		soloGameMod(game, my_name, getch_ref, mut_flag);
	else if (serverOrClient == 1)
		serverMod(game, my_name, getch_ref, client_getch_ref, mut_flag, serverOrClient);
	else if (serverOrClient == 2) // CLIENT MOD
		clientMod(game, my_name, getch_ref, client_getch_ref, mut_flag, serverOrClient);
	return (0);
}
