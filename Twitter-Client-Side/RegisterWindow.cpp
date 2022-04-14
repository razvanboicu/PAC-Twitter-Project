#include "RegisterWindow.h"
#include "ErrorWindow.h"
#include "Client.h"
#include "User.h"

RegisterWindow::RegisterWindow(int ClientHandle):
	m_UserLogic(ClientHandle)
{
	m_backPressed = false;
	m_registerPressed = false;

	m_window.create(sf::VideoMode(1280, 720), "Colibri - Register");
	m_font.loadFromFile("arial.ttf");
	m_texture.loadFromFile("backgroundRegister.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(sf::Vector2f(0.f, 0.f));

	m_textureBackButton.loadFromFile("back120x50.png");
	m_spriteBackButton.setTexture(m_textureBackButton);

	m_textureRegisterButton.loadFromFile("register120x50.png");
	m_spriteRegisterButton.setTexture(m_textureRegisterButton);

	Textbox* t1 = new Textbox(sf::Vector2f(400.f, 45.f), sf::Vector2f(775.f, 200.f), sf::Color::White, 15, m_font);
	t1->AddEventListener([this]() {});
	m_menuRegisterWindow.AddWidget(t1);
	Textbox* t2 = new Textbox(sf::Vector2f(400.f, 45.f), sf::Vector2f(775.f, 270.f), sf::Color::White, 15, m_font);
	t2->AddEventListener([this]() {});
	m_menuRegisterWindow.AddWidget(t2);
	Textbox* t3 = new Textbox(sf::Vector2f(400.f, 45.f), sf::Vector2f(775.f, 340.f), sf::Color::White, 25, m_font);
	t3->AddEventListener([this]() {});
	m_menuRegisterWindow.AddWidget(t3);
	Textbox* t4 = new Textbox(sf::Vector2f(400.f, 45.f), sf::Vector2f(775.f, 410.f), sf::Color::White, 15, m_font);
	t4->AddEventListener([this]() {});
	m_menuRegisterWindow.AddWidget(t4);
	Textbox* t5 = new Textbox(sf::Vector2f(400.f, 45.f), sf::Vector2f(775.f, 480.f), sf::Color::White, 15, m_font);
	t5->AddEventListener([this]() {});
	m_menuRegisterWindow.AddWidget(t5);
	Button* b1 = new Button(sf::Vector2f(120.f, 50.f), sf::Vector2f(400.f, 600.f), sf::Color::White, "Register", m_font, m_spriteRegisterButton, 25);
	b1->AddEventListener([this]() {GatherInfo(); });
	m_menuRegisterWindow.AddWidget(b1);
	Button* b2 = new Button(sf::Vector2f(120.f, 50.f), sf::Vector2f(200.f, 600.f), sf::Color::White, "Back", m_font, m_spriteBackButton, 25);
	b2->AddEventListener([this]() {m_backPressed = true; });
	m_menuRegisterWindow.AddWidget(b2);
	Textbox* t8 = new Textbox(sf::Vector2f(300.f, 45.f), sf::Vector2f(400.f, 550.f), sf::Color::Transparent, 0, m_font);
	t8->SetCharColor(sf::Color::Red);
	t8->AddEventListener([]() {return; });
	m_menuRegisterWindow.AddWidget(t8);
}

bool RegisterWindow::IsShowing()
{
	return !m_backPressed && !m_registerPressed;
}

void RegisterWindow::ShowWindow(){
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		sf::Vector2f point = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		m_menuRegisterWindow.OnEvent(event, point);
		if (event.type == event.Closed)
			m_window.close();
	}
	m_window.clear(sf::Color(176, 148, 246));
	m_window.draw(m_sprite);
	m_menuRegisterWindow.Draw(m_window);
	m_window.display();
}

Windows RegisterWindow::getNextWindowEnum()
{
	if (m_registerPressed)
		return Windows::eLoginWindow;
	if (m_backPressed)
		return Windows::eLoginWindow;
}

void RegisterWindow::GatherInfo()
{
	//email, username and password must be completed
	RegisterCredentials Register = std::make_tuple(dynamic_cast<Textbox*>(m_menuRegisterWindow.getElement(0))->getText()
		, dynamic_cast<Textbox*>(m_menuRegisterWindow.getElement(1))->getText()
		, dynamic_cast<Textbox*>(m_menuRegisterWindow.getElement(2))->getText()
		, dynamic_cast<Textbox*>(m_menuRegisterWindow.getElement(3))->getText()
		, dynamic_cast<Textbox*>(m_menuRegisterWindow.getElement(4))->getText());
	SendInfo(Register);
}

void RegisterWindow::SendInfo(const RegisterCredentials& Register)
{
	const auto& [username, pass, email, firstname, lastname] = Register;
	if (User::CheckValidId(username) && User::CheckValidEmail(email) && User::CheckValidPassword(pass) && User::CheckValidFirstName(firstname) && User::CheckValidSecondName(lastname))
	{
		if (m_UserLogic.HandleRegister(Register))
		{
			m_registerPressed = true;
		}
		else
		{
			ErrorWindow error("ERROR-Username already exists", "ERROR-REGISTER");
			error.ShowError();
		}
	}
}