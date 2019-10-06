//
// Created by Denis LEWANDOWSKI on 2019-04-18.
//

#include "classes/Game.hpp"
#include "../includes/includes.h"

void	soloGameMod(Game &game, char *my_name, int &getch_ref, bool &mut_flag)
{
	int j = 0;
	numberOfPlayers = 1;
	initSingleGame(game, my_name);
	time_t sTime;

	std::thread tKeyInput(getch_ret, std::ref(getch_ref),
						  std::ref(mut_flag)); //thread for read from keyboard
	std::thread tPlayer1Action(player1Action, std::ref(getch_ref),
							   std::ref(game),
							   std::ref(tKeyInput), std::ref(mut_flag));
	std::time(&sTime);
	while (true)
	{
		while (mut_flag);
		if (game.getPlayers()[0].get_hp() <= 0)
		{
			tKeyInput.detach();
			tPlayer1Action.detach();
			print_game_over();
			return ;
		}
		if (j % 18 == 0)
			standardUnitGeneration(game);
		mut_flag = true;
		score_calculation(game);
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


void	serverMod(Game &game, char *my_name, int &getch_ref, int &client_getch_ref, bool &mut_flag, int serverOrClient)
{
	int		socket = 0;
	char	player2Name[64];
	int		j = 0;
	time_t	sTime;

	numberOfPlayers = 2;

	ClientServer server(serverOrClient);
	server.createSocket();
	server.setFlagsAndBindNameSocket();
	server.listenForConnections();
	server.acceptConnectionOnSocket();
	socket = server.getSocket();
	read(socket, player2Name, 64);


	initMultiGame(game, my_name, player2Name);
	std::thread tKeyInput(getch_ret, std::ref(getch_ref),
						  std::ref(
								  mut_flag)); //thread for read from keyboard
	std::thread tPlayer1Action(player1Action, std::ref(getch_ref),
							   std::ref(game),
							   std::ref(tKeyInput), std::ref(mut_flag));
	std::function<int(std::string *menu_items, int size,
			int &client_getch_ref,
			int socket)> menu_func = client_pause_menu;
	std::thread tClientMove(takeClientMove, std::ref(client_getch_ref),
							socket,
							std::ref(mut_flag));
	std::thread tPlayer2Action(player2Action, std::ref(menu_func),
							   std::ref(client_getch_ref),
							   std::ref(game),
							   std::ref(tClientMove),
							   std::ref(mut_flag),
							   socket);
	std::time(&sTime);
	while (true)
	{
		while (mut_flag)
			;
		if (game.getPlayers()[0].get_hp() <= 0 &&
			game.getPlayers()[1].get_hp() <= 0)
		{
			tKeyInput.detach();
			tPlayer1Action.detach();
			tPlayer2Action.detach();
			tClientMove.detach();
			close(socket);
			close(server.getServerFd());
			print_game_over();
			return ;
		}
		mut_flag = true;
		if (j % 18 == 0)
			standardUnitGeneration(game);
		score_calculation(game);
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

void	clientMod(Game &game, char *my_name, int &getch_ref, int &client_getch_ref, bool &mut_flag, int serverOrClient)
{
	numberOfPlayers = 2;
	char buffer[HEIGHT * WIDTH] = {0};
	ClientServer client(serverOrClient);
	int sock = 0;

	client.createSocket();
	client.setIP("10.111.5.11");
	client.convertIPFromTextToBinary();
	client.connectToServer();
	sock = client.getServerFd();
	std::thread tReadFromServer(readFromServer, std::ref(sock),
								std::ref(mut_flag));
	send(sock, my_name, 64, 0);
	char key;
	while (true)
	{
		while (mut_flag)
		{
			read(sock, buffer, 1024);
			clear();
			printw("%s\n", buffer);
			refresh();
			bzero(buffer, sizeof(buffer));
		}
		while ((read(sock, &key, 1)) > 0)
		{
			if (key == 'y')
				break;
		}
		key = 0;
		usleep(1000);
		clear();
		if ((read(sock, buffer, 1024)) <= 0)
		{
			print_game_over();
			tReadFromServer.detach();
			return;
		}
		printw("%s", buffer);
		for (int k = 0; k < WIDTH; k++)
			printw("-");
		printw("\n");
		usleep(1000);
		bzero(buffer, sizeof(buffer));
		if ((read(sock, buffer, HEIGHT * (WIDTH + 1))) <= 0)
		{
			print_game_over();
			tReadFromServer.detach();
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
