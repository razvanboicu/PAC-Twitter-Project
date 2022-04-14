#include "SearchKeywordWindow.h"

SearchKeywordWindow::SearchKeywordWindow(int ClientHandle, std::string word, std::string username):
	m_searchLogic(ClientHandle),
	m_word(word),
	m_username(username),
	m_postPressed(false),
	m_otherPostPressed(false),
	m_hasPosts(true)
{
	m_font.loadFromFile("arial.ttf");
	m_lowerPostTexture.loadFromFile("baraMicaMica.png");
	m_lowerPostSprite.setTexture(m_lowerPostTexture);
	m_upperPostTexture.loadFromFile("baraMare.png");
	m_upperPostSprite.setTexture(m_upperPostTexture);
	m_nextPostButtonTexture.loadFromFile("sageataDreapta.png");
	m_nextPostButtonSprite.setTexture(m_nextPostButtonTexture);
	m_textureBackground.loadFromFile("background1280x720.png");
	m_SpriteBackground.setTexture(m_textureBackground);
	m_previousPostButtonTexture.loadFromFile("sageataStanga.png");
	m_previousPostButtonSprite.setTexture(m_previousPostButtonTexture);
	m_backButtonTexture.loadFromFile("backButtonImage.png");
	m_backButtonSprite.setTexture(m_backButtonTexture);

	m_backPressed = false;
	m_postBase = new PostBase(sf::Vector2f(140.f, 235.f), m_font, sf::Vector2f(1000.f, 250.f), m_lowerPostSprite, m_upperPostSprite);

	m_window.create(sf::VideoMode(1280, 720), "Colibri - SearchKeywordWindow", sf::Style::Default);
	m_font.loadFromFile("arial.ttf");
	m_searchKeywordWindow.AddWidget(new Button(sf::Vector2f(50, 50), sf::Vector2f(10.f, 10.f), sf::Color::White, "Back", m_font,m_backButtonSprite, 15));
	m_searchKeywordWindow.getElement(0)->AddEventListener([this]() {m_backPressed = true; });
	m_searchKeywordWindow.AddWidget(new Button(sf::Vector2f(30, 30), sf::Vector2f(1100.f, 520.f), sf::Color::White, "Next", m_font, m_nextPostButtonSprite, 15));
	m_searchKeywordWindow.getElement(1)->AddEventListener([this]()
		{   m_focusedPost++;
	if (m_focusedPost < m_posts.size())
		m_postBase->SetPostBaseInfo(m_posts[m_focusedPost].first[0], m_posts[m_focusedPost].first[1], m_posts[m_focusedPost].first[2]);
	else m_focusedPost--;
		});

	m_searchKeywordWindow.AddWidget(new Button(sf::Vector2f(30, 30), sf::Vector2f(140.f, 520.f), sf::Color::White, "Previous", m_font, m_previousPostButtonSprite, 15));
	m_searchKeywordWindow.getElement(2)->AddEventListener([this]()
		{
			if (m_focusedPost != 0)
			{
				m_focusedPost--;
				m_postBase->SetPostBaseInfo(m_posts[m_focusedPost].first[0], m_posts[m_focusedPost].first[1], m_posts[m_focusedPost].first[2]);
			}});

	m_postBase->GetPostBaseMenu().getElement(0)->AddEventListener([this]() {
		HandlePostPressed();
		});

	m_postBase->GetPostBaseMenu().getElement(1)->AddEventListener([this]() {
		HandlePostPressed();
		});

	GeneratePosts();
}

void SearchKeywordWindow::GeneratePosts()
{
	m_posts = m_searchLogic.HandleKeyWordSearch(m_word);
	if (m_posts.empty())
		m_hasPosts = false;
	else
	m_postBase->SetPostBaseInfo(m_posts[m_focusedPost].first[0], m_posts[m_focusedPost].first[1], m_posts[m_focusedPost].first[2]);
}

void SearchKeywordWindow::HandlePostPressed()
{
	m_pressedPostID = m_posts[m_focusedPost].second;
	if (m_username == m_posts[m_focusedPost].first[0])
		m_postPressed = true;
	else m_otherPostPressed = true;
}

int SearchKeywordWindow::GetPressedPostID()
{
	return m_pressedPostID;
}

std::string SearchKeywordWindow::GetPressedPostString()
{
	return m_posts[m_focusedPost].first[0];
}

void SearchKeywordWindow::ShowWindow()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		sf::Vector2f point = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		m_searchKeywordWindow.OnEvent(event, point);
		if(m_hasPosts)
		m_postBase->GetPostBaseMenu().OnEvent(event, point);
		if (event.type == event.Closed)
			m_window.close();
	}
	m_window.draw(m_SpriteBackground);
	if(m_hasPosts)
	m_postBase->DrawPostBase(m_window);
	m_searchKeywordWindow.Draw(m_window);
	m_window.display();
}

bool SearchKeywordWindow::IsShowing()
{
	return !m_backPressed && !m_postPressed && !m_otherPostPressed;
}

Windows SearchKeywordWindow::getNextWindowEnum()
{
	if (m_backPressed)
		return Windows::eMainMenuWindow;
	if (m_postPressed)
		return Windows::eProfileWindow;
	if (m_otherPostPressed)
		return Windows::eOtherProfilesWindow;
}
