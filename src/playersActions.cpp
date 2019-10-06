//
// Created by Denis LEWANDOWSKI on 2019-04-18.
//

#include <../includes/includes.h>
#include "classes/Game.hpp"
#define PAUSE_ITEM 2

void	player1Action(int &getch_ref, Game &game)
{
	int saveDegrees;
	std::string pause_items[PAUSE_ITEM] = {	"RESUME GAME",
											   "EXIT"};

	nodelay(stdscr, 1);
    switch (wgetch(stdscr))
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
                    exit(0);
                default:
                    break;
            }
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
            if (game.getPlayers()[0].get_hp() <= 0)
                break;
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
//    usleep(100);
}

//void	player2Action(std::function<int(std::string *menu_items, int size,
//										int &client_getch_ref, int socket)> &menu,int &client_getch_ref,
//					  Game &game, std::thread &thr1, bool &mut_flag, int socket)
//{
//	int saveDegrees;
//	std::string pause_items[PAUSE_ITEM] = {	"RESUME GAME",
//											   "EXIT"};
//
//	while (true)
//	{
//		switch (client_getch_ref)
//		{
//			case 27:
//				switch (menu(pause_items, PAUSE_ITEM, client_getch_ref, socket))
//				{
//					case 1:
//						break;
//					case 2:
//						clear();
//						printw("BYE!");
//						refresh();
//						usleep(100000);
//						endwin();
//						thr1.detach();
//						exit(0);
//					default:
//						break;
//				}
//				mut_flag = false;
//				break;
//			case KEY_UP:
//				game.getPlayers()[1].set_degrees(90);
//				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
//				{
//					game.getPlayers()[1].move(game.getPlayers()[1].get_degrees());
//					setPlayersOnField(game);
//				}
//				break;
//			case KEY_DOWN:
//				game.getPlayers()[1].set_degrees(270);
//				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
//				{
//					game.getPlayers()[1].move(game.getPlayers()[1].get_degrees());
//					setPlayersOnField(game);
//				}
//				break;
//			case KEY_RIGHT:
//				game.getPlayers()[1].set_degrees(180);
//				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
//				{
//					game.getPlayers()[1].move(game.getPlayers()[1].get_degrees());
//					setPlayersOnField(game);
//				}
//				break;
//			case KEY_LEFT:
//				game.getPlayers()[1].set_degrees(0);
//				for (int i = 0; i < game.getPlayers()->get_speed(); i++)
//				{
//					game.getPlayers()[1].move(game.getPlayers()[1].get_degrees());
//					setPlayersOnField(game);
//				}
//				break;
//			case ' ':
//				if (game.getPlayers()[1].get_hp() <= 0)
//					break;
//				setPlayersOnField(game);
//				saveDegrees = game.getPlayers()[1].get_degrees();
//				game.getPlayers()[1].set_degrees(90);
//				game.setBullets(game.getPlayers()[1].shot(game.getBullets()));
//				game.getPlayers()[1].set_degrees(saveDegrees);
//				break;
//			default:
//				setPlayersOnField(game);
//		}
//		client_getch_ref = 0;
//		usleep(70000);
//
//	}
//}

