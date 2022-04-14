#include "UserLogin.h"
#include <stdio.h>
#include <windows.h>
#include "ErrorWindow.h"
#include <SFML\Graphics.hpp>
#include "..\Network\TcpSocket.h"
#include "Client.h"

UserLogin::UserLogin(int ClientHandle) :
	m_registerPressed(false),
	m_loginPressed(false),
	m_userLogic(ClientHandle)
{
	m_window.create(sf::VideoMode(1280, 720), "Colibri - Log In");
	m_image.loadFromFile("backgroundLogin.png");
	m_imageSprite.setTexture(m_image);
	m_imageSprite.setPosition(sf::Vector2f(0.f, 0.f));

	m_image2.loadFromFile("loginButton120x50.png");
	m_imageSprite2.setTexture(m_image2);

	m_font.loadFromFile("arial.ttf");
	Textbox* usernameTextbox = new Textbox(sf::Vector2f(300.f, 45.f), sf::Vector2f(490.f, 280.f), sf::Color::White, 15, m_font);
	usernameTextbox->AddEventListener([]() {return; });
	Textbox* passwordTextbox = new Textbox(sf::Vector2f(300.f, 45.f), sf::Vector2f(490.f, 360.f), sf::Color::White, 15, m_font);
	passwordTextbox->AddEventListener([]() {return; });
	Button* butonLogin = new Button(sf::Vector2f(120.f, 50.f), sf::Vector2f(580.f, 490.f), sf::Color::White, "Log In", m_font, m_imageSprite2, 25);
	TextButton* butonRegister = new TextButton(sf::Vector2f(515.f, 420.f), "You don't have an account? Register!", m_font, 15);
	butonLogin->AddEventListener([this]() {GetUserAndPass(); });
	butonRegister->AddEventListener([this]() {m_registerPressed = true; });
	m_menuUserLogin.AddWidget(usernameTextbox);
	m_menuUserLogin.AddWidget(passwordTextbox);
	m_menuUserLogin.AddWidget(butonRegister);
	m_menuUserLogin.AddWidget(butonLogin);
}

void UserLogin::ShowWindow()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		sf::Vector2f point = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		m_menuUserLogin.OnEvent(event, point);
		if (event.type == event.Closed)
			m_window.close();
	}
	m_window.clear(sf::Color(46, 134, 193));
	m_window.draw(m_imageSprite);
	m_menuUserLogin.Draw(m_window);
	m_window.display();
}

bool UserLogin::IsShowing()
{
	return !m_registerPressed && !m_loginPressed;
}

Windows UserLogin::getNextWindowEnum()
{
	if (m_loginPressed)
		return Windows::eMainMenuWindow;
	if (m_registerPressed)
		return Windows::eRegisterWindow;
}

void UserLogin::GetUserAndPass()
{
	Credentials credentials(std::make_pair(dynamic_cast<Textbox*>(m_menuUserLogin.getElement(0))->getText(), dynamic_cast<Textbox*>(m_menuUserLogin.getElement(1))->getText()));
	Login(credentials);
}

std::string UserLogin::GetUsername() const
{
	return m_user.GetUsername();
}

void UserLogin::Login(const Credentials& credentials)
{
	auto& [id, pass] = credentials;
	if (id != "" && pass != "")
		if (m_userLogic.HandleLogin(credentials))
		{
			m_user.SetId(id);
			m_user.SetPassword(pass);
			m_loginPressed = true;
		}
		else
		{
			ErrorWindow Error("Make sure the username and password are correct", "Error - invalid account");
			Error.ShowError();
		}
}

