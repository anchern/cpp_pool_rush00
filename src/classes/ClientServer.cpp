//
// Created by Anton CHERNYSH on 2019-04-18.
//

#include "ClientServer.hpp"

void ClientServer::createSocket()
{
	if ((_serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
}

ClientServer::ClientServer(int serverORclient)
{
	if (serverORclient == 2)
	{
		memset(&_address, '0', sizeof(_address));
		_IP = "127.0.0.1";
	}

	_address.sin_family = AF_INET;
	if (serverORclient == 1)
		_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(PORT);
}

void ClientServer::setFlagsAndBindNameSocket()
{
	int	opt = 1;

	if (setsockopt(_serverFd, SOL_SOCKET,  SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	// Forcefully attaching socket to the port 4242
	if (bind(_serverFd, (struct sockaddr *)&_address,
			 sizeof(_address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
}

void ClientServer::listenForConnections()
{
	if (listen(_serverFd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
}

void ClientServer::acceptConnectionOnSocket()
{
	int addrlen = sizeof(_address);

	clear();
	printw("Wait to connect...\n");
	refresh();
	if ((_socket = accept(_serverFd, (struct sockaddr *)&_address,
							 (socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	clear();
	printw("Socket %d connected.\n", _socket);
	refresh();
}

void ClientServer::convertIPFromTextToBinary()
{
	if (inet_pton(AF_INET, _IP.c_str(), &_address.sin_addr) <= 0)
	{
		clear();
		printw("Invalid address/ Address not supported \n");
		refresh();
		exit(1);
	}
}

void ClientServer::connectToServer()
{
	if (connect(_serverFd, (struct sockaddr *) &_address, sizeof(_address)) <
		0)
	{
		clear();
		printw("Connection Failed \n");
		refresh();
		exit(1);
	}
}

int ClientServer::getSocket() const
{
	return _socket;
}

void ClientServer::setIP(const std::string &_IP)
{
	ClientServer::_IP = _IP;
}

int ClientServer::getServerFd() const
{
	return _serverFd;
}
