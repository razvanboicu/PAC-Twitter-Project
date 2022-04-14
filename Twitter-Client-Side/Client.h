#pragma once
#include <array>
#include <iostream>
#include "..\Network\TcpSocket.h"


class Client
{
	using SocketHandle = UINT_PTR;
public:
	Client();

	void Initialize(char* IPAdress);
	static void SendMsg(int connection, std::string toSend);
	static void RecieveMessage(int connection, std::string& toRecieve);
	UINT_PTR GetHandle();
private:
	TcpSocket m_clientSocket;
};

