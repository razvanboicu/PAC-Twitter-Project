#include "FeedWindow.h"

FeedWindow::FeedWindow(int ClientHandle, const std::string& username) :
	m_backPressed(false),
	m_postLogic(ClientHandle),
	m_username(username),
	m_retweetPressed(false),
	m_retweetedPostPressed(false),
	m_focusedPost(0)
{
	m_font.loadFromFile("arial.ttf");
	m_lowerPostTexture.loadFromFile("baraMicaMica.png");
	m_lowerPostSprite.setTexture(m_lowerPostTexture);
	m_upperPostTexture.loadFromFile("baraMare.png");
	m_backButtonTexture.loadFromFile("backButtonImage.png");
	m_backButtonSprite.setTexture(m_backButtonTexture);
	m_upperPostSprite.setTexture(m_upperPostTexture);
	m_nextPostButtonTexture.loadFromFile("sageataDreapta.png");
	m_nextPostButtonSprite.setTexture(m_nextPostButtonTexture);
	m_previousPostButtonTexture.loadFromFile("sageataStanga.png");
	m_previousPostButtonSprite.setTexture(m_previousPostButtonTexture);
	m_textureBackground.loadFromFile("background1920x1080.png");
	m_spriteBackground.setTexture(m_textureBackground);

	m_backPressed = false;
	m_postGUI = new PostWidget(sf::Vector2f(200.f, 300.f), m_font, 0, ClientHandle, m_lowerPostSprite, m_upperPostSprite);

	m_window.create(sf::VideoMode(1920, 1080), "Feed", sf::Style::Default);
	m_font.loadFromFile("arial.ttf");
	m_feedWindowMenu.AddWidget(new Button(sf::Vector2f(50, 50), sf::Vector2f(10.f, 10.f), sf::Color::White, "Back", m_font, m_backButtonSprite, 15));
	m_feedWindowMenu.getElement(0)->AddEventListener([this]() {m_backPressed = true; });
	m_nextPreviousPostMenu.AddWidget(new Button(sf::Vector2f(30, 30), sf::Vector2f(200.f, 600.f), sf::Color::White, "Previous", m_font, m_previousPostButtonSprite, 15));
	m_nextPreviousPostMenu.getElement(0)->AddEventListener([this]()
		{
			if (m_focusedPost != 0)
				m_postGUI->SetPostInfo(m_posts[--m_focusedPost].first); });

	m_nextPreviousPostMenu.AddWidget(new Button(sf::Vector2f(30, 30), sf::Vector2f(1620.f, 600.f), sf::Color::White, "Next", m_font, m_nextPostButtonSprite, 15));
	m_nextPreviousPostMenu.getElement(1)->AddEventListener([this]()
		{  if (m_focusedPost < m_posts.size()-1)
	{
		m_focusedPost++;
		m_postGUI->SetPostInfo(m_posts[m_focusedPost].first);
	}
		});

	m_interactions = m_postGUI->GetInteractionMenu();
	m_interactions.getElement(0)->AddEventListener([this]()
		{
			m_postLogic.SendLikeToServer(m_username, m_posts[m_focusedPost].second);
			GeneratePosts(); });
	m_interactions.getElement(1)->AddEventListener([this]()
		{m_postLogic.SendDislikeToServer(m_username, m_posts[m_focusedPost].second);

	GeneratePosts(); });
	m_interactions.getElement(2)->AddEventListener([this]()
		{
			m_retweetPressed = !m_retweetPressed;
		});

	m_postGUI->GetBaseMenu().getElement(0)->AddEventListener([this]() {
		m_retweetedPostPressed = true;
		HandlePostPressed();
		});

	m_postGUI->GetBaseMenu().getElement(1)->AddEventListener([this]() {
		m_retweetedPostPressed = true;
		HandlePostPressed();
		});

	m_postGUI->GetWidgetMenu().getElement(0)->AddEventListener([this]() {
		HandlePostPressed();
		});

	m_postGUI->GetWidgetMenu().getElement(1)->AddEventListener([this]() {
		HandlePostPressed();
		});

	m_postGUI->GetNewCommentMenu().getElement(2)->AddEventListener([this]() {
		if (m_postGUI->IsNewCommentPressed())
		{
			std::string comment = dynamic_cast<Textbox*>(m_postGUI->GetNewCommentMenu().getElement(1))->getText();
			if (comment != "")
			{
				m_postLogic.SendCommentToServer(m_username, comment, m_posts[m_focusedPost].second);
				m_postGUI->ChangeNewCommentValue();
				GeneratePosts();
			}
		}
		});

	m_posts = m_postLogic.HandleFeed(m_username);
	if(!m_posts.empty())
	m_postGUI->SetPostInfo(m_posts[m_focusedPost].first);
}

void FeedWindow::ShowWindow()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		sf::Vector2f point = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		m_feedWindowMenu.OnEvent(event, point);
		if (!m_posts.empty())
		{
			m_nextPreviousPostMenu.OnEvent(event, point);
			m_postGUI->GetInteractionMenu().OnEvent(event, point);
			if (m_postGUI->IsCommentsPressed())
				m_postGUI->GetCommentsMenu().OnEvent(event, point);
			if (m_postGUI->IsNewCommentPressed())
				m_postGUI->GetNewCommentMenu().OnEvent(event, point);
			if (m_postGUI->IsARetweetedPost())
				m_postGUI->GetBaseMenu().OnEvent(event, point);
			m_postGUI->GetWidgetMenu().OnEvent(event, point);
		}
		if (event.type == event.Closed)
			m_window.close();
	}
	m_window.clear();
	m_window.draw(m_spriteBackground);;
	m_feedWindowMenu.Draw(m_window);
	if (!m_posts.empty())
	{
		m_nextPreviousPostMenu.Draw(m_window);
		m_postGUI->Draw(m_window);
	}
	m_window.display();
}

bool FeedWindow::IsShowing()
{
	return !m_backPressed && !m_postProfilePressed && !m_postOthersPressed && !m_retweetPressed;
}

void FeedWindow::GeneratePosts()
{
	for (int i = 0; i < m_posts.size(); i++)
		m_posts[i] = m_postLogic.GetAllPostInfoViaID(m_posts[i].second);
	m_postGUI->SetPostInfo(m_posts[m_focusedPost].first);
}

void FeedWindow::HandlePostPressed()
{

	if (m_retweetedPostPressed)
	{
		if (m_posts[m_focusedPost].first.GetRetweetedPostAuthor() == m_username)
			m_postProfilePressed = true;
		else m_postOthersPressed = true;
	}
	else m_postOthersPressed = true;
}

int FeedWindow::GetPressedPostID()
{
	if (m_retweetedPostPressed)
	{
		return m_posts[m_focusedPost].first.GetIDToRetweet();
	}
	else
	{
		return m_posts[m_focusedPost].second;
	}
}

std::string FeedWindow::GetPressedPostString()
{
	if (m_retweetedPostPressed)
		return m_posts[m_focusedPost].first.GetRetweetedPostAuthor();
	else return m_posts[m_focusedPost].first.GetAuthor();
}

Windows FeedWindow::getNextWindowEnum()
{
	if (m_backPressed)
		return Windows::eMainMenuWindow;
	if (m_postProfilePressed)
		return Windows::eProfileWindow;
	if (m_postOthersPressed)
		return Windows::eOtherProfilesWindow;
	if (m_retweetPressed)
		return Windows::ePostWindow;
}
