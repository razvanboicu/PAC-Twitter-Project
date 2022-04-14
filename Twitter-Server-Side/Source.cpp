#include <iostream>
#include <fstream>
#include "../Logger/Logger.h"

#include <array>
#include <sstream>
#include "../Network/TcpSocket.h"
#include "ThreadPool.h"
#include "Processor.h"

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")	//  links to Ws2_32.lib

int main()
{
	std::ofstream out("logs.txt", std::ios::app);
	Logger logger(out);

	logger.Log(Logger::Level::Info, "Starting server");

	std::shared_ptr<Processor> p = std::make_shared<Processor>();
	std::cout << "Starting server" << std::endl;


	TcpSocket listener;
	listener.Listen(27015);
	ThreadPool tp;
	while (1)
	{
		logger.Log(Logger::Level::Info, "Waiting for client to connect");
		int client = accept(listener.getHandle(), NULL, NULL);
		logger.Log(Logger::Level::Info, "Client connected");
		std::cout << "Client connected\n";
		tp.AddWork(client,std::ref(p));
	}
	return 0;
}