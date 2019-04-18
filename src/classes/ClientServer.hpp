//
// Created by Anton CHERNYSH on 2019-04-18.
//

#ifndef RUSH00_CLIENTSERVER_HPP
#define RUSH00_CLIENTSERVER_HPP

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <ncurses.h>
#include <arpa/inet.h>
#include <string>

#define PORT 4242



class ClientServer
{
public:
	explicit	ClientServer(int serverORclient);
	~ClientServer() = default;
	void		createSocket();

	// Server functions
	void		setFlagsAndBindNameSocket();
	void		listenForConnections();
	void		acceptConnectionOnSocket();

	// Client functions
	void		convertIPFromTextToBinary();
	void		connectToServer();

	int getSocket() const;

	int getServerFd() const;

	void setIP(const std::string &_IP);


private:
	int 				_socket;
	struct  sockaddr_in _address;
	int					_serverFd;
	std::string			_IP;
};


#endif //RUSH00_CLIENTSERVER_HPP
