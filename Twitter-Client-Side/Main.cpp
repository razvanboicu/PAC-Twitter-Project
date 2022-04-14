#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"
#include "TextButton.h"
#include "Menu.h"
#include "UserLogin.h"
#include "User.h"
#include "Runtime.h"
#include <ctime>
#include "FriendRequest.h"
#include "Notifications.h"
#include <array>
#include "..\Network\TcpSocket.h"
#include <SFML/Network.hpp>
#include "Client.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")	//  links to Ws2_32.lib


int main(int argc, char* argv[])
{
	// Validate the parameters
	if (argc != 2) {
		std::cerr << "usage: " << argv[0] << " server-name" << std::endl;
		return 1;
	}

	Runtime r(argv[1]);
	r.Begin();

	system("pause");
	return 0;
}


