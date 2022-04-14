#pragma once
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "UserLogic.h"
#include "Widget.h"
#include "Button.h"
#include "Textbox.h"
#include "TextButton.h"
#include "User.h"
#include "IWindow.h"
#include <stdio.h>

class UserLogin:public IWindow {

public:
	using Credentials = std::pair<std::string, std::string>;
public:

	UserLogin(int ClientHandle);

	virtual void ShowWindow() override;
	virtual bool IsShowing() override;

	virtual Windows getNextWindowEnum() override;

	void GetUserAndPass();
	std::string GetUsername() const;

	void Login(const Credentials& credentials);

	~UserLogin() = default;

private:
	bool m_registerPressed;
	bool m_loginPressed;
	User m_user;
	UserLogic m_userLogic;
	sf::Text m_errorText;
	sf::Font m_font;
	sf::Texture m_image;
	sf::Texture m_image2;
	sf::Sprite m_imageSprite2;
	sf::Sprite m_imageSprite;
	Menu m_menuUserLogin;
};

