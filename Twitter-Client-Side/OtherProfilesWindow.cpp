#include "OtherProfilesWindow.h"

OtherProfilesWindow::OtherProfilesWindow(std::string usernameOther, std::string usernameCurrent, int ClientHandle, int FocusedPost) :
	m_backPressed(false),
	m_username(usernameOther),
	m_commentPressed(false),
	m_addNewCommentPressed(false),
	m_currentUsername(usernameCurrent),
	m_focusedPost(0),
	m_postLogic(ClientHandle),
	m_userLogic(ClientHandle),
	m_retweetPressed(false),
	m_refrencedWindow(false)
{
	m_profilePicTexture.loadFromFile("profilepic.png");
	m_backButtonTexture.loadFromFile("backButtonImage.png");
	m_backButtonSprite.setTexture(m_backButtonTexture);
	m_nextPostButtonTexture.loadFromFile("sageataDreapta.png");
	m_nextPostButtonSprite.setTexture(m_nextPostButtonTexture);
	m_previousPostButtonTexture.loadFromFile("sageataStanga.png");
	m_previousPostButtonSprite.setTexture(m_previousPostButtonTexture);
	m_heartTexture.loadFromFile("heart30x30.png");
	m_heartSprite.setTexture(m_heartTexture);
	m_brokenHeartTexture.loadFromFile("dislike30x30.png");
	m_brokenHeartSprite.setTexture(m_brokenHeartTexture);
	m_retweetTexture.loadFromFile("retweet30x30.png");
	m_retweetSprite.setTexture(m_retweetTexture);
	m_commentsTexture.loadFromFile("comments30x30.png");
	m_commentsSprite.setTexture(m_commentsTexture);
	m_newCommentTexture.loadFromFile("comment30x30.png");
	m_newCommentSprite.setTexture(m_newCommentTexture);
	m_texturePostComment.loadFromFile("addComment.png");
	m_spritePostComment.setTexture(m_texturePostComment);
	m_textureCloseButton.loadFromFile("cancelIcon.png");
	m_spriteCloseButton.setTexture(m_textureCloseButton);
	m_followButtonTexture.loadFromFile("follow35x35.png");
	m_followButtonSprite.setTexture(m_followButtonTexture);
	m_unfollowButtonTexture.loadFromFile("followed35x35.png");
	m_unfollowButtonSprite.setTexture(m_unfollowButtonTexture);
	m_lowerPostTexture.loadFromFile("baraMicaMica.png");
	m_lowerPostSprite.setTexture(m_lowerPostTexture);
	m_upperPostTexture.loadFromFile("baraMare.png");
	m_upperPostSprite.setTexture(m_upperPostTexture);
	m_yourPostsTexture.loadFromFile("yourPosts.png");
	m_yourPostsSprite.setTexture(m_yourPostsTexture);

	m_yourPosts.setSize(sf::Vector2f(300.f, 75.f));
	m_yourPosts.setPosition(sf::Vector2f(215.f, 365.f));
	m_yourPosts.setFillColor(sf::Color::Black);
	m_yourPosts.setTexture(&m_yourPostsTexture);

	m_postGUI = new PostWidget(sf::Vector2f(225.f, 475.f), m_font, 0, ClientHandle, m_lowerPostSprite, m_upperPostSprite);

	m_profilePic.setRadius(100.f);
	m_profilePic.setPosition(sf::Vector2f(850.f, 50.f));
	m_profilePic.setTexture(&m_profilePicTexture);
	m_profilePic.setOutlineColor(sf::Color::Black);
	m_profilePic.setOutlineThickness(1);

	m_window.create(sf::VideoMode(1920, 1080), usernameOther + "'s Profile", sf::Style::Default);
	m_font.loadFromFile("arial.ttf");
	m_colibriFont.loadFromFile("Ruach LET.ttf");
	m_textureBackground.loadFromFile("background1920x1080.png");
	m_spriteBackground.setTexture(m_textureBackground);
	m_spriteBackground.setPosition(sf::Vector2f(0.f, 0.f));

	m_otherProfilesMenu.AddWidget(new Button(sf::Vector2f(50, 50), sf::Vector2f(10.f, 10.f), sf::Color::White, "Back", m_font, m_backButtonSprite, 15));
	m_otherProfilesMenu.getElement(0)->AddEventListener([this]() {m_backPressed = true; });
	m_otherProfilesMenu.AddWidget(new Textbox(sf::Vector2f(300.f, 75.f), sf::Vector2f(810.f, 250.f), sf::Color::Transparent, 0, m_colibriFont, true, 60));
	m_otherProfilesMenu.getElement(1)->AddEventListener([this]() {});
	m_nextPreviousPostMenu.AddWidget(new Button(sf::Vector2f(50, 50), sf::Vector2f(1650.f, 770.f), sf::Color::White, "Next", m_font, m_nextPostButtonSprite, 15));
	m_nextPreviousPostMenu.getElement(0)->AddEventListener([this]() {m_focusedPost++;
	if (m_focusedPost < m_posts.size())
		m_postGUI->SetPostInfo(m_posts[m_focusedPost].first);
	else m_focusedPost--; });
	m_nextPreviousPostMenu.AddWidget(new Button(sf::Vector2f(50, 50), sf::Vector2f(225.f, 770.f), sf::Color::White, "Previous", m_font, m_previousPostButtonSprite, 15));
	m_nextPreviousPostMenu.getElement(1)->AddEventListener([this]() {if (m_focusedPost != 0)
		m_postGUI->SetPostInfo(m_posts[--m_focusedPost].first); });
	dynamic_cast<Textbox*>(m_otherProfilesMenu.getElement(1))->SetText(std::string(m_username));
	if (!m_userLogic.CheckIfFollowing(m_currentUsername, m_username))
		m_followUnfollowButtonSprite = m_followButtonSprite;
	else m_followUnfollowButtonSprite = m_unfollowButtonSprite;
	m_otherProfilesMenu.AddWidget(new Button(sf::Vector2f(50.f, 50.f), sf::Vector2f(825.f + dynamic_cast<Textbox*>(m_otherProfilesMenu.getElement(1))->GetBox().getLocalBounds().width, 277.f), sf::Color::White, "follow", m_font, m_followUnfollowButtonSprite));
	m_otherProfilesMenu.getElement(2)->AddEventListener([this]()
		{
			if (!m_userLogic.UpdateFollowStatus(m_currentUsername, m_username))
				m_followUnfollowButtonSprite = m_followButtonSprite;
			else m_followUnfollowButtonSprite = m_unfollowButtonSprite;
			dynamic_cast<Button*>(m_otherProfilesMenu.getElement(2))->SetButtonImage(m_followUnfollowButtonSprite);
		});

	m_interactions = m_postGUI->GetInteractionMenu();
	m_interactions.getElement(0)->AddEventListener([this]()
		{
			m_postLogic.SendLikeToServer(m_currentUsername, m_posts[m_focusedPost].second);
			GeneratePosts(); });
	m_interactions.getElement(1)->AddEventListener([this]()
		{m_postLogic.SendDislikeToServer(m_currentUsername, m_posts[m_focusedPost].second);

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
				m_postLogic.SendCommentToServer(m_currentUsername, comment, m_posts[m_focusedPost].second);
				m_postGUI->ChangeNewCommentValue();
				GeneratePosts();
			}
		}
		});

	if (FocusedPost != 0)
	{
		m_focusedPost = FocusedPost;
		m_refrencedWindow = true;
	}

	GeneratePosts();
}

void OtherProfilesWindow::ShowWindow()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		sf::Vector2f point = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		m_otherProfilesMenu.OnEvent(event, point);
		m_postGUI->GetInteractionMenu().OnEvent(event, point);
		if (!m_posts.empty())
		{
			if (m_postGUI->IsCommentsPressed())
				m_postGUI->GetCommentsMenu().OnEvent(event, point);
			if (m_postGUI->IsNewCommentPressed())
				m_postGUI->GetNewCommentMenu().OnEvent(event, point);
			if (m_postGUI->IsARetweetedPost())
				m_postGUI->GetBaseMenu().OnEvent(event, point);
			m_nextPreviousPostMenu.OnEvent(event, point); 
		}
		if (event.type == event.Closed)
			m_window.close();
	}
	m_window.clear(sf::Color(176, 148, 246));
	m_window.draw(m_spriteBackground);
	m_window.draw(m_profilePic);
	m_window.draw(m_yourPosts);
	m_otherProfilesMenu.Draw(m_window);
	if (!m_posts.empty())
	{
		m_nextPreviousPostMenu.Draw(m_window);
		m_postGUI->Draw(m_window);
	}
	m_window.display();
}

bool OtherProfilesWindow::IsShowing()
{
	return !m_backPressed && !m_retweetPressed && !m_retweetOtherPostPressed && !m_retweetedPostPressed;
}

Windows OtherProfilesWindow::getNextWindowEnum()
{
	if (m_backPressed)
		return Windows::eMainMenuWindow;
	if (m_retweetPressed)
		return Windows::ePostWindow;
	if (m_retweetedPostPressed)
		return Windows::eProfileWindow;
	if (m_retweetOtherPostPressed)
		return Windows::eOtherProfilesWindow;
}

bool OtherProfilesWindow::WasRetweetPressed()
{
	return m_retweetPressed;
}

int OtherProfilesWindow::GetFocusedPostID()
{
	return m_posts[m_focusedPost].second;
}

std::string OtherProfilesWindow::GetPostAuthor()
{
	return m_posts[m_focusedPost].first.GetRetweetedPostAuthor();
}

int OtherProfilesWindow::GetRetweetedPostID()
{
	return m_posts[m_focusedPost].first.GetIDToRetweet();
}

void OtherProfilesWindow::HandleRetweetPostPressed()
{
	if (m_posts[m_focusedPost].first.HasARetweet())
	{
		if (m_posts[m_focusedPost].first.GetRetweetedPostAuthor() == m_username)
		{
			for (int i = 0; i < m_posts.size(); i++)
				if (m_posts[i].second == m_posts[m_focusedPost].first.GetIDToRetweet())
				{
					std::cout << m_posts[i].second;
					m_focusedPost = i;
					std::cout << m_focusedPost;
				}
			m_postGUI->SetPostInfo(m_posts[m_focusedPost].first);
			return;
		}
		if (m_posts[m_focusedPost].first.GetRetweetedPostInfo().first.find(m_username) != std::string::npos)
		{
			for (int i = 0; i < m_posts.size(); i++)
				if (m_posts[i].second == m_posts[m_focusedPost].first.GetIDToRetweet())
					m_focusedPost = i;
			m_postGUI->SetPostInfo(m_posts[m_focusedPost].first);
		}
		else if (m_posts[m_focusedPost].first.GetRetweetedPostInfo().first.find(m_currentUsername) != std::string::npos)
			m_retweetedPostPressed = true;
		else m_retweetOtherPostPressed = true;
	}
}

void OtherProfilesWindow::GeneratePosts()
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
