#include "classes/Game.hpp"
#include <stdlib.h>
#include <sstream>

#define MENU_ITEM 3
#define PAUSE_ITEM 2

#define PORT 4242

//FILE *file = std::fopen("/Users/achernys/cpp_pool_rush00/logs", "rwa");

void print_bull_coords(t_bullet *bullets)
{
	if (bullets == 0)
	{
		file << "NULL\n";
		return;
	}
	file << "x: " << bullets->bullet->get_location().x << "| y: " <<
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
	send(socket, outData, strlen(outData) + 1, 0);
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
	printw("%s | HP: %d | %s | HP: %d |\nTime: %.2ld:%.2ld | Score: %u\n",
			game.getPlayers()[0].get_name().c_str(),game.getPlayers()[0].get_hp(),
			game.getPlayers()[1].get_name().c_str(),game.getPlayers()[1].get_hp(),
			mCurTime,sCurTime, game.getScore());
	for (int k = 0; k < WIDTH; k++)
		printw("-");
	printw("\n");
	game.printField();
//	printw("%s\n", game.getOneLineField());
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



struct sockaddr_in	create_server(int *server_fd)
{
	int valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	std::string hello = "";

	// Creating socket file descriptor
	if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(*server_fd, SOL_SOCKET,  SO_REUSEPORT,
				   &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(*server_fd, (struct sockaddr *)&address,
			 sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(*server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}


	return (address);
}

int new_socket(int server_fd, struct sockaddr_in &address)
{
	int  new_socket;
	int addrlen = sizeof(address);

	clear();
	printw("Wait to connect...\n");
	refresh();
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
							 (socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	clear();
	printw("Socket %d connected.\n", new_socket);
	refresh();
	return (new_socket);
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
//	long long jjjjj;
	std::string my_name;
	int socket = 0;
	struct sockaddr_in address;
	int server_fd = 0;

	file.open("/Users/achernys/cpp_pool_rush00/logs", std::ios::out | std::ios::app);
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	initMultiGame(game, "Player1", "Player2");

//	std::thread tMusic([](){
//		while (true)
//			system("afplay Sound1.mp3");
//	});
	switch (menu(menu_items, MENU_ITEM))
	{
		case 1:
			break;
		case 2:
			address = create_server(&server_fd);
			socket = new_socket(server_fd, address);
			break;
		case 3:
			printw("Bye!\n");
			return (0);
		default:
			break;
	}
//	if (socket != 0)
//	{
//		char mess[] = "Bye!";
//		send(socket, mess, 5, 0);
//		printw("Socket %d kicked\n", socket);
//		close(socket);
//		getch();
//		socket = new_socket(server_fd, address);
//
//		exit(1);
//	}
//	std::chrono::system_clock::time_point tp;
//	std::chrono::system_clock::duration start_program;
	std::function<int(std::string *menu_items, int size, int &client_getch_ref,
					  int socket)> menu_func = client_pause_menu;
	std::thread tKeyInput(getch_ret, std::ref(getch_ref),
						  std::ref(mut_flag)); //thread for read from keyboard
	std::thread tPlayer1Action(player1Action, std::ref(getch_ref),
							   std::ref(game),
							   std::ref(tKeyInput), std::ref(mut_flag));
	std::thread tClientMove(takeClientMove, std::ref(client_getch_ref), socket,
							std::ref(mut_flag));
	std::thread tPlayer2Action(player2Action, std::ref(menu_func),
							   std::ref(client_getch_ref), std::ref(game),
							   std::ref(tClientMove), std::ref(mut_flag),
							   socket);

	std::time(&sTime);
//	std::string kkkk;
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
			return (0);
		}
		if (j % 18 == 0)
			standardUnitGeneration(game);
		mut_flag = true;
		score_calc(game);
		setEntitiesOnPrintField(game);
		printField(game, sTime, socket);
		game.clsField();
		game.clsGameEntities();
//		tp = std::chrono::system_clock::now();
//		start_program = tp.time_since_epoch();
//		jjjjj = start_program.count();
//		kkkk = std::to_string(jjjjj);
//		refresh();
//		send(socket, kkkk.c_str(), kkkk.length(), 0);

		standardUnitActions(j, game);
		delete_and_move_bullets(game, mut_flag);
		mut_flag = false;
		usleep(70000);
		j++;
	}
}