#include "TcpSocket.h"

#include <iostream>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")	//  links to Ws2_32.lib

const TcpSocket::SocketHandle TcpSocket::InvalidSocketHandle = INVALID_SOCKET;

TcpSocket::TcpSocket() : m_socket(InvalidSocketHandle)
{
	// *** Create a socket ***
	// Create a SOCKET for connecting to server: IPv4, stream socket, TCP
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_socket == InvalidSocketHandle)
	{
		//throw std::string("Error at socket(): ") + std::to_string(WSAGetLastError());
	}
}

TcpSocket::TcpSocket(SocketHandle socketHandle) : m_socket(socketHandle)
{
	// empty
}

TcpSocket::~TcpSocket()
{
	if (m_socket != InvalidSocketHandle)
	{
		closesocket(m_socket);
	}
}

bool TcpSocket::Listen(uint16_t remotePort)
{
	addrinfo* result = nullptr, hints;
	ZeroMemory(&hints, sizeof(hints));	// memset to 0
	hints.ai_family = AF_INET;			// IPv4

	// *** Resolve the server address and port (can be also names like "localhost") ***
	int iResult = getaddrinfo(nullptr, std::to_string(remotePort).c_str(), &hints, &result);
	if (iResult != 0)
	{
		freeaddrinfo(result);
		std::cerr << "getaddrinfo failed: " << iResult << std::endl;
		return false;
	}

	// *** Binding the socket ***
	// Setup the TCP listening socket
	iResult = bind(m_socket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		std::cerr << "bind failed with error: " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		return false;
	}

	// 'result' not needed anymore so free it
	freeaddrinfo(result);

	// *** Listening on the socket ***
	if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		return false;
	}

	return true;
}

TcpSocket TcpSocket::Accept()
{
	// *** Accept a connection ***
	// There are multiple techniques to accept client connections,
	// and multiple techniques to accept multiple client connections.
	// In this example however a single connection is accepted.

	// Accept a client socket
	SocketHandle clientSocket = accept(m_socket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET)
	{
		throw std::string("accept failed") + std::to_string(WSAGetLastError());
	}

	return TcpSocket(clientSocket);
}

bool TcpSocket::Connect(const std::string& remoteAddress, uint16_t remotePort)
{
	// *** Connect to server ***
	addrinfo* result = nullptr, hints;
	ZeroMemory(&hints, sizeof(hints));	// memset to 0
	hints.ai_family = AF_INET;			// IPv4

	// *** Resolve the server address and port (can be also names like "localhost") ***
	int iResult = getaddrinfo(remoteAddress.c_str(), std::to_string(remotePort).c_str(), &hints, &result);
	if (iResult != 0)
	{
		freeaddrinfo(result);
		std::cerr << "getaddrinfo failed: " << iResult << std::endl;
		return false;
	}

	// Attempt to connect to the first address returned by the call to getaddrinfo
	iResult = connect(m_socket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		std::cerr << "Unable to connect to server: " << WSAGetLastError() << std::endl;
		return false;
	}

	freeaddrinfo(result);

	return true;
}

bool TcpSocket::Send(const void* data, int size)
{
	for (int sent = 0, result = 0; sent < size; sent += result)
	{
		result = send(m_socket, static_cast<const char*>(data), size, 0);
		if (result < 0)
		{
			std::cerr << "send failed: " << WSAGetLastError() << std::endl;
			return false;
		}
	}

	return true;
}

bool TcpSocket::Receive(void* data, int size, int& recieved)
{
	recieved = recv(m_socket, static_cast<char*>(data), size, 0);
	if (recieved < 0)
	{
		std::cerr << "receive failed: " << WSAGetLastError() << std::endl;
		return false;
	}

	return true;
}

void TcpSocket::coutHandle()
{
	std::cout << m_socket;
}

UINT_PTR TcpSocket::getHandle()
{
	return m_socket;
}

bool TcpSocket::SendUsingHandle(int connection, const void* data, int size)
{
	for (int sent = 0, result = 0; sent < size; sent += result)
	{

		if (data != "STANDBY") {
			if (result < 0) {
				std::cerr << "send failed: " << WSAGetLastError() << std::endl;
				return false;
			}
		}
		else
			result = send(connection, static_cast<const char*>(data), size, 0);
		
	}
	return true;
	
}

bool TcpSocket::RecieveUsingHandle(int connection, void* data, int size, int& recieved)
{
	if (data != "STANDBY") {
		if (recieved < 0)
		{
			std::cerr << "receive failed: " << WSAGetLastError() << std::endl;
			return false;
		}
		else 
			recieved = recv(connection, static_cast<char*>(data), size, 0);
		
	}
	return true;
}

//// this class should not be exposed to a header
struct WinsocketInitializer
{
	WinsocketInitializer()
	{
		// *** initialize Winsock ***
		// initialize Winsock before making other Winsock functions calls (only once per application/dll)
		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);		// initiate use of WS2_32.dll, with version 2.2
		if (iResult != 0)
		{
			throw std::string("WSAStartup failed: ") + std::to_string(iResult);
		}
	}

	~WinsocketInitializer()
	{
		WSACleanup();
	}
};

WinsocketInitializer globalInitializer;