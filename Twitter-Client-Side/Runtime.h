#pragma once
#include <utility>
#include "UserLogin.h"
#include "RegisterWindow.h"
#include "MainMenuWindow.h"
#include "PostWindow.h"
#include "ProfileWindow.h"
#include "FeedWindow.h"
#include "OtherProfilesWindow.h"
#include "Client.h"
#include "SearchKeywordWindow.h"

class Runtime
{
public:
	Runtime(char* IPAdress);
	void Begin();
	void ChangeWindow(Windows window);

private:
	//unique ptr because it should point to only 1 window at a time
	std::unique_ptr<IWindow> m_focus;
	std::string m_username; //sets user when someone logs in(window changes to Main Menu) 
	Client m_client;
	int m_handle;
};

