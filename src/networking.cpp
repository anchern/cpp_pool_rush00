#include "Game.hpp"

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
