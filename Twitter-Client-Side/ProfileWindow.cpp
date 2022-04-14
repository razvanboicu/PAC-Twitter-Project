#include "ProfileWindow.h"
#include "ErrorWindow.h"

ProfileWindow::ProfileWindow(int ClientHandle, std::string username, int focus) :
	m_backPressed(false),
	m_commentPressed(false),
	m_addNewCommentPressed(false),
	m_positionY(1080),
	m_postLogic(ClientHandle),
	m_focusedPost(0),
	m_username(username),
	m_retweetPressed(false),
	m_retweetedPostPressed(false),
	m_refrencedWindow(false)
{
	m_profilePicTexture.loadFromFile("profilepic.png");
	m_backButtonTexture.loadFromFile("backButtonImage.png");
	m_backButtonSprite.setTexture(m_backButtonTexture);
	m_nextPostButtonTexture.loadFromFile("sageataDreapta.png");
	m_nextPostButtonSprite.setTexture(m_nextPostButtonTexture);
	m_previousPostButtonTexture.loadFromFile("sageataStanga.png");
	m_previousPostButtonSprite.setTexture(m_previousPostButtonTexture);
	m_texturePostComment.loadFromFile("addComment.png");
	m_spritePostComment.setTexture(m_texturePostComment);
	m_textureCloseButton.loadFromFile("cancelIcon.png");
	m_spriteCloseButton.setTexture(m_textureCloseButton);
	m_lowerPostTexture.loadFromFile("baraMicaMica.png");
	m_lowerPostSprite.setTexture(m_lowerPostTexture);
	m_upperPostTexture.loadFromFile("baraMare.png");
	m_upperPostSprite.setTexture(m_upperPostTexture);
	m_yourPostsTexture.loadFromFile("yourPosts.png");
	m_yourPostsSprite.setTexture(m_yourPostsTexture);

	m_postGUI = new PostWidget(sf::Vector2f(225.f, 475.f), m_font, 0, ClientHandle, m_lowerPostSprite, m_upperPostSprite);

	m_profilePic.setRadius(100.f);
	m_profilePic.setPosition(sf::Vector2f(850.f, 50.f));
	m_profilePic.setTexture(&m_profilePicTexture);
	m_profilePic.setOutlineColor(sf::Color::Black);
	m_profilePic.setOutlineThickness(0);

	m_yourPosts.setSize(sf::Vector2f(300.f, 75.f));
	m_yourPosts.setPosition(sf::Vector2f(215.f, 365.f));
	m_yourPosts.setFillColor(sf::Color::Black);
	m_yourPosts.setTexture(&m_yourPostsTexture);

	m_window.create(sf::VideoMode(1920, 1080), "Colibri - Profile", sf::Style::Default);
	m_textureBackground.loadFromFile("background1920x1080.png");
	m_spriteBackground.setTexture(m_textureBackground);
	m_spriteBackground.setPosition(sf::Vector2f(0.f, 0.f));
	m_font.loadFromFile("arial.ttf");
	m_colibriFont.loadFromFile("Ruach LET.ttf");
	m_scroll.reset(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
	m_window.setView(m_scroll);


	m_menuProfileWindow.AddWidget(new Button(sf::Vector2f(50, 50), sf::Vector2f(10.f, 10.f), sf::Color::White, "Back", m_font, m_backButtonSprite, 15));
	m_menuProfileWindow.getElement(0)->AddEventListener([this]() {m_backPressed = true; });
	m_menuProfileWindow.AddWidget(new Textbox(sf::Vector2f(300.f, 75.f), sf::Vector2f(810.f, 250.f), sf::Color::Transparent, 0, m_colibriFont, true, 60));
	m_menuProfileWindow.getElement(1)->AddEventListener([this]() {});
	m_nextPreviousPostMenu.AddWidget(new Button(sf::Vector2f(30, 30), sf::Vector2f(1650.f, 770.f), sf::Color::White, "Next", m_font, m_nextPostButtonSprite, 15));
	m_nextPreviousPostMenu.getElement(0)->AddEventListener([this]()
		{   m_focusedPost++;
	if (m_focusedPost < m_posts.size())
		m_postGUI->SetPostInfo(m_posts[m_focusedPost].first);
	else m_focusedPost--;
		});

	/* m_profilePic.getPosition().x + 50 - dynamic_cast<Textbox*>(m_menuProfileWindow.getElement(1))->getBox().getGlobalBounds().width / 2; */

	m_nextPreviousPostMenu.AddWidget(new Button(sf::Vector2f(30, 30), sf::Vector2f(225.f, 770.f), sf::Color::White, "Previous", m_font, m_previousPostButtonSprite, 15));
	m_nextPreviousPostMenu.getElement(1)->AddEventListener([this]()
		{   
	if (m_focusedPost != 0)
		m_postGUI->SetPostInfo(m_posts[--m_focusedPost].first); });

	m_menuProfileWindow.AddWidget(new Textbox(sf::Vector2f(300.f, 75.f), sf::Vector2f(810.f, 250.f), sf::Color::Transparent, 0, m_colibriFont, true, 60));
	m_menuProfileWindow.getElement(2)->AddEventListener([this]() {});
	dynamic_cast<Textbox*>(m_menuProfileWindow.getElement(2))->SetText(std::string(m_username));

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
		HandleRetweetPostPressed();
		});

	m_postGUI->GetBaseMenu().getElement(1)->AddEventListener([this]() {
		HandleRetweetPostPressed();
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

	if (focus != 0)
	{
		m_refrencedWindow = true;
		m_focusedPost = focus;
	}

	GeneratePosts();
}

void ProfileWindow::ShowWindow()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		sf::Vector2f point = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		m_menuProfileWindow.OnEvent(event, point);
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
			if (event.type == event.Closed)
				m_window.close();
		}
	}
	m_window.draw(m_spriteBackground);
	m_window.draw(m_yourPosts);
	m_window.draw(m_profilePic);
	m_menuProfileWindow.Draw(m_window);
	if (!m_posts.empty())
	{
		m_postGUI->Draw(m_window);
		m_nextPreviousPostMenu.Draw(m_window);
	}
	m_window.display();
}

bool ProfileWindow::IsShowing()
{
	return !m_backPressed && !m_retweetPressed && !m_retweetedPostPressed;
}

void ProfileWindow::setUser(const std::string& username)
{
	m_username = username;
	dynamic_cast<Textbox*>(m_menuProfileWindow.getElement(1))->SetText(std::string(m_username));
}

void ProfileWindow::GeneratePosts()
{
	int NumberOfPosts = m_postLogic.GetNumberOfPostsFromUser(m_username);
	if (NumberOfPosts != 0)
	{
		m_posts = m_postLogic.GetPostsFromUser(NumberOfPosts);
		if (m_focusedPost != 0 && m_refrencedWindow)
			for (int i = 0; i < m_posts.size(); i++)
				if (m_focusedPost == m_posts[i].second)
					m_focusedPost = i;
		m_postGUI->SetPostInfo(m_posts[m_focusedPost].first);
	}
}

int ProfileWindow::GetFocusedPostID() const
{
	return m_posts[m_focusedPost].second;
}

int ProfileWindow::GetRetweetedPostID() 
{
	return m_posts[m_focusedPost].first.GetIDToRetweet();
}

std::string ProfileWindow::GetPostAuthor()
{
	return m_posts[m_focusedPost].first.GetRetweetedPostAuthor();
}

bool ProfileWindow::WasRetweetPressed()
{
	return m_retweetPressed;
}

void ProfileWindow::HandleRetweetPostPressed()
{
	if (m_posts[m_focusedPost].first.HasARetweet())
	{
		if (m_posts[m_focusedPost].first.GetRetweetedPostInfo().first.find(m_username) != std::string::npos)
		{
			for (int i = 0; i < m_posts.size(); i++)
				if (m_posts[i].second == m_posts[m_focusedPost].first.GetIDToRetweet())
					m_focusedPost = i;
			m_postGUI->SetPostInfo(m_posts[m_focusedPost].first);
		}
		else m_retweetedPostPressed = true;
	}
}

Windows ProfileWindow::getNextWindowEnum()
{
	if (m_backPressed )
		return Windows::eMainMenuWindow;
	if (m_retweetPressed)
		return Windows::ePostWindow;
	if (m_retweetedPostPressed)
		return Windows::eOtherProfilesWindow;
}
