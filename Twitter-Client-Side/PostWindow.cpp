#include "PostWindow.h"
#include "Client.h"
#include "ErrorWindow.h"
#include <iomanip>      
#include <ctime>        
#include <chrono>
#include <sstream>

PostWindow::PostWindow(int ClientHandle, int PostID) :
	m_postPressed(false),
	m_backPressed(false),
	m_postLogic(ClientHandle),
	m_postID(PostID)
{
	m_window.create(sf::VideoMode(1280, 720), "Colibri - Post");
	m_textureBackground.loadFromFile("background1280x720.png");
	m_spriteBackground.setTexture(m_textureBackground);
	m_spriteBackground.setPosition(sf::Vector2f(0.f, 0.f));

	m_font1.loadFromFile("arial.ttf");

	m_postMenuWindow.AddWidget(new Textbox(sf::Vector2f(500, 500), sf::Vector2f(190.f, 35.f), sf::Color::White, 120, m_font1));
	m_postMenuWindow.getElement(0)->AddEventListener([this]() {dynamic_cast<Textbox*>(m_postMenuWindow.getElement(3))->SetText(std::to_string(dynamic_cast<Textbox*>(m_postMenuWindow.getElement(0))->GetStringSize()) + "/120"); });


	m_texturePostButton.loadFromFile("post120x50.png");
	m_spritePostButton.setTexture(m_texturePostButton);
	m_postMenuWindow.AddWidget(new Button(sf::Vector2f(120, 50), sf::Vector2f(250.f, 550.f), sf::Color::White, "Post", m_font1, m_spritePostButton, 15));
	m_postMenuWindow.getElement(1)->AddEventListener([this]() {SendPost(); });

	m_textureBackButton.loadFromFile("back120x50.png");
	m_spriteBackButton.setTexture(m_textureBackButton);
	m_postMenuWindow.AddWidget(new Button(sf::Vector2f(120, 50), sf::Vector2f(500.f, 550.f), sf::Color::White, "Back", m_font1, m_spriteBackButton, 15));
	m_postMenuWindow.getElement(2)->AddEventListener([this]() {m_backPressed = true; });

	m_postMenuWindow.AddWidget(new Textbox(sf::Vector2f(0, 0), sf::Vector2f(395.f, 540.f), sf::Color::Transparent, 0, m_font1));
    m_postMenuWindow.getElement(3)->AddEventListener([this]() {});
	dynamic_cast<Textbox*>(m_postMenuWindow.getElement(3))->SetText("0/120");

	m_lowerPostTexture.loadFromFile("baraMicaMica.png");
	m_lowerPostSprite.setTexture(m_lowerPostTexture);
	m_upperPostTexture.loadFromFile("baraMare.png");
	m_upperPostSprite.setTexture(m_upperPostTexture);

	
	m_retweetUpperPostTexture.loadFromFile("retweetMare.png");
	m_retweetUpperPostSprite.setTexture(m_retweetUpperPostTexture);
	m_retweetLowerPostTexture.loadFromFile("retweetMic.png");
	m_retweetLowerPostSprite.setTexture(m_retweetLowerPostTexture);

	m_postBaseRetweet = new PostBase(sf::Vector2f(790.f, 235.f), m_font1, sf::Vector2f(300.f, 200.f), m_retweetLowerPostSprite, m_retweetUpperPostSprite);

	if (PostID == 0)
		m_hasARetweetedPost = false;
	else
	{
		m_postID = PostID;
		std::vector<std::string> tokens;
		tokens = m_postLogic.GetPostViaID(PostID);
		m_postBaseRetweet->SetPostBaseInfo(tokens[0],tokens[1],tokens[2]);
		m_hasARetweetedPost = true;
	}
}

void PostWindow::ShowWindow()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		sf::Vector2f point = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		m_postMenuWindow.OnEvent(event, point);
		if (event.type == event.Closed)
			m_window.close();
	}
	//m_window.clear(sf::Color(176, 148, 246));
	m_window.draw(m_spriteBackground);
	if (m_hasARetweetedPost)
	{
		Textbox text(sf::Vector2f(100.f, 35.f), sf::Vector2f(790.f, 150.f), sf::Color::Transparent, 120, m_font1);
		text.SetText("The post you're retweeting:");
		m_postBaseRetweet->DrawPostBase(m_window);
		text.Draw(m_window);
	}
	m_postMenuWindow.Draw(m_window);
	m_window.display();
}

bool PostWindow::IsShowing()
{
	return !m_backPressed && !m_postPressed;
}

Windows PostWindow::getNextWindowEnum()
{
	if (m_backPressed)
		return Windows::eMainMenuWindow;
}

void PostWindow::SendPost()
{
	std::string Text = dynamic_cast<Textbox*>(m_postMenuWindow.getElement(0))->getText();
	if (Text!="")
	{
		if (!m_postLogic.SendPostToServer(m_username,Text,m_postID))
		{
			ErrorWindow err("Post failed to send", "ERROR-Post failed to send properly");
			err.ShowError();
		}
		else m_backPressed = true;
	}
}

void PostWindow::setUsername(const std::string& user)
{
	m_username = user;
}

