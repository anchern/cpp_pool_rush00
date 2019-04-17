#include "classes/Game.hpp"
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

#define PORT 4242



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
		usleep (100);
	}
}




void	readFromServer(int &sock, bool &mut_flag)
{
	int getch_client;

	usleep(10000);
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

	int			j = 0;
	time_t		sTime;
	int			getch_ref;
	Game		&game = Game::instance();
	bool		mut_flag = false;
	int			serverORclient = 0;
	char name[64];
	std::string menu_items[MENU_ITEM] = {	"SINGLE PLAYER",
									   		"MULTI PLAYER",
											 "EXIT"};
	std::string multiPlayerMenu_items[MULTIPLAYERMENU_ITEM] = {"Server", "Client"};
	std::chrono::system_clock::time_point tp;
	std::chrono::system_clock::duration start_program;





	setlocale(LC_ALL, "");
	WINDOW *window = initscr();
	noecho();
	keypad(stdscr, TRUE);
	initGame(game, "Player1");

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


	if (serverORclient == 2) // CLIENT MOD
	{
		struct sockaddr_in address;
		int sock = 0, valread;
		struct sockaddr_in serv_addr;
		char buffer[HEIGHT * WIDTH] = {0};

		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			printf("\n Socket creation error \n");
			return -1;
		}
		memset(&serv_addr, '0', sizeof(serv_addr));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);

		// Convert IPv4 and IPv6 addresses from text to binary form
		if(inet_pton(AF_INET, "10.111.5.7", &serv_addr.sin_addr)<=0)
		{
			clear();
			printw("\nInvalid address/ Address not supported \n");
			refresh();
			return -1;
		}
		if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		{
			clear();
			printw("\nConnection Failed \n");
			refresh();
			return -1;
		}
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



//			if ((valread = read(sock, buffer, 1024)) <= 0)
//			{
//				clear();
//				::move(100, 100);
//				refresh();
//				printw("                                                                                                                                                                              \n"
//					   "                                                                                                                                                                                       \n"
//					   "                                                                                                                                                                                       \n"
//					   "                                                                                 `:                                                                                                    \n"
//					   "                                                               `+@@@'            @+@            .;           +,           `...,,,                                                      \n"
//					   "                                                              +#;;;;'@`         +;;;'          .#'#         @;+.       ;@@#+++++'@                                                     \n"
//					   "                                                            `@';;;;;;;@         #;;;#          #;;'`       .';;@      #';;;;;;;;;'.                                                    \n"
//					   "                                                           `#;;;;;;;;;'        `';;;;+         #;;;+       #;;;#     ,';;;;;;;;;;;+                                                    \n"
//					   "                                                           #;;;;;;;;;;;.       +;;;;;#         +;;;#       @;;;'     +;;;;;;;;;;;;+                                                    \n"
//					   "                                                          @;;;;;;;;;;;'`       @;;;;;;;        +;;;'`      +;;;;.    +;;;;;;;;;;;'.                                                    \n"
//					   "                                                         .';;;;;'@+@';@        ';;;;;;@        ';;;;#     .;;;;;'    .';;;'''++'+#                                                     \n"
//					   "                                                         @;;;;;@;   '#        :;;;;;;;'        ';;;;#     +;;;;;#     #;;;#;:,,:.                                                      \n"
//					   "                                                         +;;;;@               #;;;#;;;;;      `;;;;;'`    @;;;;;@     #;;;;                                                            \n"
//					   "                                                        ,;;;;@                #;;;#+;;;@      `;;;;;;+    +;;;;;+     #;;;;                                                            \n"
//					   "                                                        +;;;',               `';;;:#;;;+      .;;;;;;#   .;;;;;;'     #;;;;                                                            \n"
//					   "                                                        @;;;@   ```````      ;;;;' .;;;;,     :;;;;;;'`  +;;;;;;;.    #;;;; ``.:                                                       \n"
//					   "                                                        #;;;'  @#######+     #;;;#  +;;;#     ;;;;';;;'  @;;;#;;;:    #;;;@@##+'@                                                      \n"
//					   "                                                        +;;;. +;;;;;;;;+`    #;;;#  @;;;#     +;;;@;;;@  +;;;@;;;+    #;;;;;;;;;;.                                                     \n"
//					   "                                                        +;;;. @;;;;;;;;;'    ';;;@@@@;;;'@+   +;;;@;;;' `;;;'@;;;#    #;;;;;;;;;;'                                                     \n"
//					   "                                                        +;;;` #;;;;;;;;;+   ,;;;;;;;;;;;;;':  #;;;#';;;'+;;;#';;;@    #;;;;;;;;;;'                                                     \n"
//					   "                                                        +;;;. @;;;;;;;;;,   +;;;;;;;;;;;;;;@  #;;;+@;;;@@;;;@,;;;#    #;;;;;;;;;'`                                                     \n"
//					   "                                                        #;;;: .#;;;;;;;@    @;;;;;;;;;;;;;;#  @;;;+';;;'+;;;;`;;;+    #;;;;;;;'##                                                      \n"
//					   "                                                        @;;;#  .#@#@;;;#    #;;;;;;;;;;;;;;@  #;;;' ';;;;;;'` ';;'    #;;;@##+;`                                                       \n"
//					   "                                                        #;;;#      #;;;#    ';;;;;;;;;;;;;+,  #;;;: @;;;;;;+  +;;;`   #;;;;                                                            \n"
//					   "                                                        ,;;;;,     #;;;@   .;;;'@@@@@##;;;#   #;;;, ';;;;;;@  #;;;,   #;;;;                                                            \n"
//					   "                                                         ';;;@     #;;;@   ;;;;#      @;;;@   +;;;.  ';;;;;'  #;;;;   #;;;;    .,                                                      \n"
//					   "                                                         @;;;;@   `#;;;#   @;;;@      +;;;#   ';;;`  @;;;;;.  @;;;+   #;;;#''#@++#                                                     \n"
//					   "                                                         ;;;;;;@###;;;;#   @;;;#      :;;;+   ';;;`  ';;;;+   #;;;@   #;;;;'';;;;'`                                                    \n"
//					   "                                                          #;;;;;;;;;;;;'   #;;;;      `;;;'  `';;;`   ';;;@   +;;;@   #;;;;;;;;;;;:                                                    \n"
//					   "                                                          ';;;;;;;;;;;+`   ';;;.       ';;'  .;;;'    @;;;'   ';;;@   @;;;;;;;;;;;:                                                    \n"
//					   "                                                           @;;;;;;;;;;#    ';;'        +;;;` .;;;+    ;;;+    :;;;#   #;;;;;;;;;;'`                                                    \n"
//					   "                                                           `@;;;;;;;;@     #;;#        #;;+  `;;;#     @@'    `;;;@   `+;;;;;;;'+#                                                     \n"
//					   "                                                            `@';;;;+#      ''''        '';#   #;;+             #;',    ,@@@##@@+.                                                      \n"
//					   "                                                              ;@@@@:        +;          +#    ,@#              .@'                                                                     \n"
//					   "                                                                                                                      `:;,                                                             \n"
//					   "                                                                 :##'`                      `                       ,@#''+@'                                                           \n"
//					   "                                                               ,@';;'##        @##         ##@      `;#####@@;     #+;;;;;;'@                                                          \n"
//					   "                                                              ;+;;;;;;'@      #;;+        .';;,   .@#';;;;;;;+`   @;;;;;;;;;;#                                                         \n"
//					   "                                                             .+;;;;;;;;;@     #;;;;       @;;;#   #;;;;;;;;;;;'  .';;;;;;;;;;';                                                        \n"
//					   "                                                             @;;;;;;;;;;':    @;;;@       +;;;#  ;;;;;;;;;;;;;#  +;;;;;;;;;;;;#                                                        \n"
//					   "                                                            ';;;;;;;;;;;;@    #;;;#      :;;;;;  ';;;;;;;;;;;;'  #;;;;;++';;;;;.                                                       \n"
//					   "                                                            #;;;;#@@#;;;;'`   ;;;;'`     @;;;'   :;;;;;;;;;;;#`  ';;;;@,.;#;;;;#                                                       \n"
//					   "                                                           :;;;;#.  .@;;;;#   `';;;;     +;;;@    #;;;#@@@@@@,    #;;;#   `#;;;@                                                       \n"
//					   "                                                           @;;;;;     #;;;@    #;;;@    ,;;;;:    @;;;'           @;;;#    +;;;#                                                       \n"
//					   "                                                           +;;;@      +;;;+    @;;;#    #;;;+     @;;;'           @;;;#    :;;;#                                                       \n"
//					   "                                                          .;;;;:      `';;'    ;;;;'`   #;;;@     @;;;'           @;;;#    ';;;#                                                       \n"
//					   "                                                          +;;;+        +;;;`   `';;;;  `';;;;     @;;;'           @;;;#    @;;;@                                                       \n"
//					   "                                                          @;;;@        +;;;`    #;;;@  ';;;'      @;;;#;+#@@;     @;;;#   .';;;#                                                       \n"
//					   "                                                          #;;;+        +;;;`    @;;;#  @;;;@      @;;;''';;;+`    @;;;#  .#;;;;,                                                       \n"
//					   "                                                          +;;;,        +;;;`    ;;;;'  ';;;+      @;;;;;;;;;;'    @;;;#:##;;;;+                                                        \n"
//					   "                                                          ';;;`        ';;;`    `';;;::;;;;`      @;;;;;;;;;;+    @;;;+';;;;;;@                                                        \n"
//					   "                                                          ';;'        `';;'      #;;;##;;;#       @;;;;;;;;;;;    @;;;;;;;;;;+`                                                        \n"
//					   "                                                          ';;'        :;;;+      @;;;##;;;@       @;;;;;;;;;#     @;;;;;;;;;'+                                                         \n"
//					   "                                                          ';;'        #;;;#      ';;;'';;;:       @;;;#+##@@.     @;;;;;;;;;@                                                          \n"
//					   "                                                          +;;;.       #;;;#      `';;;;;;'        @;;;'``         @;;;;;;;;;@                                                          \n"
//					   "                                                          #;;;'      ,;;;;,       #;;;;;;#        @;;;'           @;;;'+';;;;;                                                         \n"
//					   "                                                          @;;;@      @;;;+        @;;;;;;#        @;;;'           @;;;#,#;;;;#                                                         \n"
//					   "                                                          +;;;':    :';;;@        ;;;;;;;:        @;;;'  `:#@,    @;;;#  #;;;;@                                                        \n"
//					   "                                                          .;;;;#,  ,#;;;;,        `';;;;'         @;;;@@@#';;@    @;;;#  ';;;;':                                                       \n"
//					   "                                                           #;;;;+@@+;;;;#          #;;;;#         @;;;;;;;;;;;,   @;;;#   @;;;;#                                                       \n"
//					   "                                                           #;;;;;;;;;;;;'          @;;;;#         @;;;;;;;;;;;'   @;;;#   ,';;;;:                                                      \n"
//					   "                                                           `+;;;;;;;;;;@           ';;;;:         @;;;;;;;;;;;:   #;;;#    @;;;;#                                                      \n"
//					   "                                                            +;;;;;;;;;+.           `';;'`         ;;;;;;;;;;;#    #;;;'    `+;;;#                                                      \n"
//					   "                                                             @';;;;;;+;             #;;@           @+';;;;'#@,    +;;'.     #;;;'                                                      \n"
//					   "                                                              +#';;'#'              ;++;            .;###+:`      .+'#       @;#                                                       \n"
//					   "                                                               `;##+`                ..                            .;        `+`                                                       \n"
//					   "                                                                                                                                                                                       \n"
//					   "                                                                                                                                                                                       \n"
//					   "                                                                                                         "
//					   "                                                                                               \n\n"
//					   "                                                                                                                                                                                         ");
//				refresh();
//				exit(0);
//			}
//			printw("%s\n", buffer);

//			bzero(buffer, sizeof(buffer));
			while ((valread = read(sock, &key, 1)) > 0)
			{
				if (key == 'y')
					break;
			}
			clear();
			for (int k = 0; k < WIDTH; k++)
				printw("-");
			printw("\n");
			key = 0;
			usleep(1000);
			bzero(buffer, sizeof(buffer));
			if ((valread = read(sock, buffer, HEIGHT * (WIDTH + 1) + 1024)) <= 0)
			{
				clear();
				::move(100, 100);
				refresh();
				printw("                                                                                                                                                                              \n"
					   "                                                                                                                                                                                       \n"
					   "                                                                                                                                                                                       \n"
					   "                                                                                 `:                                                                                                    \n"
					   "                                                               `+@@@'            @+@            .;           +,           `...,,,                                                      \n"
					   "                                                              +#;;;;'@`         +;;;'          .#'#         @;+.       ;@@#+++++'@                                                     \n"
					   "                                                            `@';;;;;;;@         #;;;#          #;;'`       .';;@      #';;;;;;;;;'.                                                    \n"
					   "                                                           `#;;;;;;;;;'        `';;;;+         #;;;+       #;;;#     ,';;;;;;;;;;;+                                                    \n"
					   "                                                           #;;;;;;;;;;;.       +;;;;;#         +;;;#       @;;;'     +;;;;;;;;;;;;+                                                    \n"
					   "                                                          @;;;;;;;;;;;'`       @;;;;;;;        +;;;'`      +;;;;.    +;;;;;;;;;;;'.                                                    \n"
					   "                                                         .';;;;;'@+@';@        ';;;;;;@        ';;;;#     .;;;;;'    .';;;'''++'+#                                                     \n"
					   "                                                         @;;;;;@;   '#        :;;;;;;;'        ';;;;#     +;;;;;#     #;;;#;:,,:.                                                      \n"
					   "                                                         +;;;;@               #;;;#;;;;;      `;;;;;'`    @;;;;;@     #;;;;                                                            \n"
					   "                                                        ,;;;;@                #;;;#+;;;@      `;;;;;;+    +;;;;;+     #;;;;                                                            \n"
					   "                                                        +;;;',               `';;;:#;;;+      .;;;;;;#   .;;;;;;'     #;;;;                                                            \n"
					   "                                                        @;;;@   ```````      ;;;;' .;;;;,     :;;;;;;'`  +;;;;;;;.    #;;;; ``.:                                                       \n"
					   "                                                        #;;;'  @#######+     #;;;#  +;;;#     ;;;;';;;'  @;;;#;;;:    #;;;@@##+'@                                                      \n"
					   "                                                        +;;;. +;;;;;;;;+`    #;;;#  @;;;#     +;;;@;;;@  +;;;@;;;+    #;;;;;;;;;;.                                                     \n"
					   "                                                        +;;;. @;;;;;;;;;'    ';;;@@@@;;;'@+   +;;;@;;;' `;;;'@;;;#    #;;;;;;;;;;'                                                     \n"
					   "                                                        +;;;` #;;;;;;;;;+   ,;;;;;;;;;;;;;':  #;;;#';;;'+;;;#';;;@    #;;;;;;;;;;'                                                     \n"
					   "                                                        +;;;. @;;;;;;;;;,   +;;;;;;;;;;;;;;@  #;;;+@;;;@@;;;@,;;;#    #;;;;;;;;;'`                                                     \n"
					   "                                                        #;;;: .#;;;;;;;@    @;;;;;;;;;;;;;;#  @;;;+';;;'+;;;;`;;;+    #;;;;;;;'##                                                      \n"
					   "                                                        @;;;#  .#@#@;;;#    #;;;;;;;;;;;;;;@  #;;;' ';;;;;;'` ';;'    #;;;@##+;`                                                       \n"
					   "                                                        #;;;#      #;;;#    ';;;;;;;;;;;;;+,  #;;;: @;;;;;;+  +;;;`   #;;;;                                                            \n"
					   "                                                        ,;;;;,     #;;;@   .;;;'@@@@@##;;;#   #;;;, ';;;;;;@  #;;;,   #;;;;                                                            \n"
					   "                                                         ';;;@     #;;;@   ;;;;#      @;;;@   +;;;.  ';;;;;'  #;;;;   #;;;;    .,                                                      \n"
					   "                                                         @;;;;@   `#;;;#   @;;;@      +;;;#   ';;;`  @;;;;;.  @;;;+   #;;;#''#@++#                                                     \n"
					   "                                                         ;;;;;;@###;;;;#   @;;;#      :;;;+   ';;;`  ';;;;+   #;;;@   #;;;;'';;;;'`                                                    \n"
					   "                                                          #;;;;;;;;;;;;'   #;;;;      `;;;'  `';;;`   ';;;@   +;;;@   #;;;;;;;;;;;:                                                    \n"
					   "                                                          ';;;;;;;;;;;+`   ';;;.       ';;'  .;;;'    @;;;'   ';;;@   @;;;;;;;;;;;:                                                    \n"
					   "                                                           @;;;;;;;;;;#    ';;'        +;;;` .;;;+    ;;;+    :;;;#   #;;;;;;;;;;'`                                                    \n"
					   "                                                           `@;;;;;;;;@     #;;#        #;;+  `;;;#     @@'    `;;;@   `+;;;;;;;'+#                                                     \n"
					   "                                                            `@';;;;+#      ''''        '';#   #;;+             #;',    ,@@@##@@+.                                                      \n"
					   "                                                              ;@@@@:        +;          +#    ,@#              .@'                                                                     \n"
					   "                                                                                                                      `:;,                                                             \n"
					   "                                                                 :##'`                      `                       ,@#''+@'                                                           \n"
					   "                                                               ,@';;'##        @##         ##@      `;#####@@;     #+;;;;;;'@                                                          \n"
					   "                                                              ;+;;;;;;'@      #;;+        .';;,   .@#';;;;;;;+`   @;;;;;;;;;;#                                                         \n"
					   "                                                             .+;;;;;;;;;@     #;;;;       @;;;#   #;;;;;;;;;;;'  .';;;;;;;;;;';                                                        \n"
					   "                                                             @;;;;;;;;;;':    @;;;@       +;;;#  ;;;;;;;;;;;;;#  +;;;;;;;;;;;;#                                                        \n"
					   "                                                            ';;;;;;;;;;;;@    #;;;#      :;;;;;  ';;;;;;;;;;;;'  #;;;;;++';;;;;.                                                       \n"
					   "                                                            #;;;;#@@#;;;;'`   ;;;;'`     @;;;'   :;;;;;;;;;;;#`  ';;;;@,.;#;;;;#                                                       \n"
					   "                                                           :;;;;#.  .@;;;;#   `';;;;     +;;;@    #;;;#@@@@@@,    #;;;#   `#;;;@                                                       \n"
					   "                                                           @;;;;;     #;;;@    #;;;@    ,;;;;:    @;;;'           @;;;#    +;;;#                                                       \n"
					   "                                                           +;;;@      +;;;+    @;;;#    #;;;+     @;;;'           @;;;#    :;;;#                                                       \n"
					   "                                                          .;;;;:      `';;'    ;;;;'`   #;;;@     @;;;'           @;;;#    ';;;#                                                       \n"
					   "                                                          +;;;+        +;;;`   `';;;;  `';;;;     @;;;'           @;;;#    @;;;@                                                       \n"
					   "                                                          @;;;@        +;;;`    #;;;@  ';;;'      @;;;#;+#@@;     @;;;#   .';;;#                                                       \n"
					   "                                                          #;;;+        +;;;`    @;;;#  @;;;@      @;;;''';;;+`    @;;;#  .#;;;;,                                                       \n"
					   "                                                          +;;;,        +;;;`    ;;;;'  ';;;+      @;;;;;;;;;;'    @;;;#:##;;;;+                                                        \n"
					   "                                                          ';;;`        ';;;`    `';;;::;;;;`      @;;;;;;;;;;+    @;;;+';;;;;;@                                                        \n"
					   "                                                          ';;'        `';;'      #;;;##;;;#       @;;;;;;;;;;;    @;;;;;;;;;;+`                                                        \n"
					   "                                                          ';;'        :;;;+      @;;;##;;;@       @;;;;;;;;;#     @;;;;;;;;;'+                                                         \n"
					   "                                                          ';;'        #;;;#      ';;;'';;;:       @;;;#+##@@.     @;;;;;;;;;@                                                          \n"
					   "                                                          +;;;.       #;;;#      `';;;;;;'        @;;;'``         @;;;;;;;;;@                                                          \n"
					   "                                                          #;;;'      ,;;;;,       #;;;;;;#        @;;;'           @;;;'+';;;;;                                                         \n"
					   "                                                          @;;;@      @;;;+        @;;;;;;#        @;;;'           @;;;#,#;;;;#                                                         \n"
					   "                                                          +;;;':    :';;;@        ;;;;;;;:        @;;;'  `:#@,    @;;;#  #;;;;@                                                        \n"
					   "                                                          .;;;;#,  ,#;;;;,        `';;;;'         @;;;@@@#';;@    @;;;#  ';;;;':                                                       \n"
					   "                                                           #;;;;+@@+;;;;#          #;;;;#         @;;;;;;;;;;;,   @;;;#   @;;;;#                                                       \n"
					   "                                                           #;;;;;;;;;;;;'          @;;;;#         @;;;;;;;;;;;'   @;;;#   ,';;;;:                                                      \n"
					   "                                                           `+;;;;;;;;;;@           ';;;;:         @;;;;;;;;;;;:   #;;;#    @;;;;#                                                      \n"
					   "                                                            +;;;;;;;;;+.           `';;'`         ;;;;;;;;;;;#    #;;;'    `+;;;#                                                      \n"
					   "                                                             @';;;;;;+;             #;;@           @+';;;;'#@,    +;;'.     #;;;'                                                      \n"
					   "                                                              +#';;'#'              ;++;            .;###+:`      .+'#       @;#                                                       \n"
					   "                                                               `;##+`                ..                            .;        `+`                                                       \n"
					   "                                                                                                                                                                                       \n"
					   "                                                                                                                                                                                       \n"
					   "                                                                                                         "
					   "                                                                                               \n\n"
					   "                                                                                                                                                                                         ");
				refresh();
				exit(0);
			}
			printw("%s\n", buffer);
			for (int k = 0; k < WIDTH; k++)
				printw("-");
			printw("\n");
//			bzero(buffer, sizeof(buffer));
//			read(sock, buffer, sizeof(buffer));
//			tp = std::chrono::system_clock::now();
//			start_program = tp.time_since_epoch();
//			printw("|||ANTON = %lld||||\n", strtoll(buffer, nullptr, 10));
//			printw("DENIS = %lld\n", start_program.count());
//			printw("RAZNICA = %lld", start_program.count() - strtoll(buffer, nullptr, 10));
//			printw("\n");
			refresh();
		}
	}









	if (serverORclient == 0)
	{
		echo();
		clear();
		bzero(name, sizeof(name));
		printw("Enter your name : ");
		scanw("%s\n", name);
		refresh();
		game.getPlayers()[0].setName(name);
		noecho();
		std::thread tKeyInput(getch_ret, std::ref(getch_ref), std::ref(mut_flag)); //thread for read from keyboard
		std::thread tPlayer1Action(player1Action, std::ref(getch_ref), std::ref(game),
								   std::ref(tKeyInput), std::ref(mut_flag));
		std::time(&sTime);
		while (true)
		{
			while (mut_flag);
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
}