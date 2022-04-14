#include "Client.h"
#include <sstream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")	//  links to Ws2_32.lib


Client::Client():m_clientSocket()
{

}

void Client::Initialize(char* IPAdress)
{
	std::cout << "Connecting to server at: " << IPAdress << std::endl;
	m_clientSocket.Connect(IPAdress, 27015);
}

void Client::SendMsg(int connection, std::string toSend)
{
	TcpSocket::SendUsingHandle(connection, toSend.c_str(), toSend.size());
}

void Client::RecieveMessage(int connection, std::string& toRecieve)
{
	std::array<char, 512> receiveBuffer;
	int revieved;
	TcpSocket::RecieveUsingHandle(connection,receiveBuffer.data(), receiveBuffer.size(), revieved);
	std::ostringstream stream;
	for (int i = 0; i < revieved; i++)
		stream << receiveBuffer[i];
	toRecieve = stream.str();
}

UINT_PTR Client::GetHandle()
{
	return m_clientSocket.getHandle();
}
