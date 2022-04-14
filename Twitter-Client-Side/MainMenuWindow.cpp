#include "MainMenuWindow.h"
#include "Client.h"
#include <sstream>


MainMenuWindow::MainMenuWindow(int clientHandle, std::string username) :
	m_logoutPressed(false),
	m_postPressed(false),
	m_profilePressed(false),
	m_settingsPressed(false),
	m_searchKeyboardPressed(false),
	m_searchUserPressed(false),
	m_feedPressed(false),
	m_otherProfilesPressed(false),
	m_username(username),
	m_friendUsername(username),
	m_searchLogic(clientHandle),
	m_userLogic(clientHandle)
{

	m_window.create(sf::VideoMode(1920, 1080), "Colibri - Main Menu", sf::Style::Default);
	m_textureBackground.loadFromFile("backgroundWithBorder.png");
	m_spriteBackground.setTexture(m_textureBackground);
	m_spriteBackground.setPosition(sf::Vector2f(0.f, 0.f));

	m_font.loadFromFile("arial.ttf");

	m_textureProfileIcon.loadFromFile("profile75x75.png");
	m_spriteProfileIcon.setTexture(m_textureProfileIcon);
	m_mainMenuWindow.AddWidget(new Button(sf::Vector2f(75, 75), sf::Vector2f(100.f, 300.f), sf::Color::White, "Profile", m_font, m_spriteProfileIcon, 15));
	m_mainMenuWindow.getElement(0)->AddEventListener([this]() {m_profilePressed = true; });

	m_textureNewPostIcon.loadFromFile("newPost75x75.png");
	m_spriteNewPostIcon.setTexture(m_textureNewPostIcon);
	m_mainMenuWindow.AddWidget(new Button(sf::Vector2f(75, 75), sf::Vector2f(100.f, 375.f), sf::Color::White, "newPost", m_font, m_spriteNewPostIcon, 15));
	m_mainMenuWindow.getElement(1)->AddEventListener([this]() {m_postPressed = true; });

	m_textureFeedIcon.loadFromFile("feed75x75.png");
	m_spriteFeedIcon.setTexture(m_textureFeedIcon);

	m_mainMenuWindow.AddWidget(new Button(sf::Vector2f(75, 75), sf::Vector2f(100.f, 450.f), sf::Color::White, "feed", m_font, m_spriteFeedIcon, 15));
	m_mainMenuWindow.getElement(2)->AddEventListener([this]() {m_feedPressed = true; });

	m_textureSearchIcon.loadFromFile("search50x50.png");
	m_spriteSearchIcon.setTexture(m_textureSearchIcon);
	m_mainMenuWindow.AddWidget(new Textbox(sf::Vector2f(300.f, 45.f), sf::Vector2f(930.f, 23.f), sf::Color::White, 15, m_font));
	m_mainMenuWindow.getElement(3)->AddEventListener([this]() {});

	m_mainMenuWindow.AddWidget(new Button(sf::Vector2f(50, 50), sf::Vector2f(765.f, 20.f), sf::Color::White, "search keyword", m_font, m_spriteSearchIcon, 15));
	m_mainMenuWindow.getElement(4)->AddEventListener([this]() {HandleSearchKeyWord(); });

	Textbox* searchKeyboardTextbox = new Textbox(sf::Vector2f(300.f, 45.f), sf::Vector2f(450.f, 23.f), sf::Color::White, 15, m_font);
	searchKeyboardTextbox->AddEventListener([]() {return; });

	m_textureSearchUserIcon.loadFromFile("searchUser50x50.png");
	m_spriteSearchUserIcon.setTexture(m_textureSearchUserIcon);
	m_mainMenuWindow.AddWidget(new Button(sf::Vector2f(50, 50), sf::Vector2f(865.f, 20.f), sf::Color::White, "search user", m_font, m_spriteSearchUserIcon, 15));
	m_mainMenuWindow.getElement(5)->AddEventListener(
		[this]() {m_searchUserPressed = true;
	m_userSearchMenu.EraseAllWidgets();
	ShowUserSearch(dynamic_cast<Textbox*>(m_mainMenuWindow.getElement(3))->getText()); });

	m_mainMenuWindow.AddWidget(new Textbox(sf::Vector2f(300.f, 45.f), sf::Vector2f(100.f, 200.f), sf::Color::Transparent, 0, m_font, true));
	m_mainMenuWindow.getElement(6)->AddEventListener([this]() {});

	m_textureLogoutIcon.loadFromFile("logout75x75.png");
	m_spriteLogoutIcon.setTexture(m_textureLogoutIcon);
	m_mainMenuWindow.AddWidget(new Button(sf::Vector2f(75, 75), sf::Vector2f(100.f, 600.f), sf::Color::White, "Log Out", m_font, m_spriteLogoutIcon, 15));
	m_mainMenuWindow.getElement(7)->AddEventListener([this]() {m_logoutPressed = true; });

	m_textureSettingsIcon.loadFromFile("settings75x75.png");
	m_spriteSettingsIcon.setTexture(m_textureSettingsIcon);

	m_textureSettingsButton.loadFromFile("delete50x50.png");
	m_spriteSettingsButton.setTexture(m_textureSettingsButton);

	Button* deleteButton = new Button(sf::Vector2f(75, 75), sf::Vector2f(180, 525), sf::Color::White, "", m_font, m_spriteSettingsButton, 15);
	deleteButton->AddEventListener([this]() {
		m_userLogic.DeleteAccount(m_username);
		m_logoutPressed = true;
		});
	m_settingsMenu.AddWidget(deleteButton);

	m_mainMenuWindow.AddWidget(new Button(sf::Vector2f(75, 75), sf::Vector2f(100.f, 525.f), sf::Color::White, "settings", m_font, m_spriteSettingsIcon, 15));
	m_mainMenuWindow.getElement(8)->AddEventListener([this]()
		{
			m_settingsPressed = !m_settingsPressed;
		});

	m_mainMenuWindow.AddWidget(searchKeyboardTextbox);

	GenerateFriendList();
}

void MainMenuWindow::ShowWindow() {
	sf::Event event;
	sf::RectangleShape friendsList;
	friendsList.setSize(sf::Vector2f(300, 900));
	friendsList.setPosition(1550, 80);
	friendsList.setFillColor(sf::Color::White);

	while (m_window.pollEvent(event))
	{
		sf::Vector2f point = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		m_mainMenuWindow.OnEvent(event, point);
		m_userSearchMenu.OnEvent(event, point);
		m_scrollbarMenu.OnEvent(event, point);
		if (m_settingsPressed)
			m_settingsMenu.OnEvent(event, point);
		if (event.type == event.Closed)
			m_window.close();
	}
	m_window.draw(m_spriteBackground);
	m_window.draw(friendsList);
	if (m_settingsPressed)
		m_settingsMenu.Draw(m_window);
	m_mainMenuWindow.Draw(m_window);
	m_userSearchMenu.Draw(m_window);
	m_scrollbarMenu.Draw(m_window);
	m_window.display();
}

bool MainMenuWindow::IsShowing()
{
	return !m_logoutPressed && !m_postPressed && !m_profilePressed && !m_feedPressed && !m_otherProfilesPressed && !m_searchKeyboardPressed;
}

Windows MainMenuWindow::getNextWindowEnum()
{
	if (m_logoutPressed)
		return Windows::eLoginWindow;
	if (m_postPressed)
		return Windows::ePostWindow;
	if (m_profilePressed)
		return Windows::eProfileWindow;
	if (m_searchKeyboardPressed)
		return Windows::eSearchKeywordWindow;
	if (m_feedPressed)
		return Windows::eFeedWindow;
	if (m_otherProfilesPressed)
		return Windows::eOtherProfilesWindow;
}

void MainMenuWindow::SetUser(std::string username)
{
	m_username = username;
	dynamic_cast<Textbox*>(m_mainMenuWindow.getElement(6))->SetText(std::string("Hello, @" + m_username + "! How are you today?"));
}

void MainMenuWindow::ShowUserSearch(std::string user)
{
	m_scrollbarMenu.EraseAllWidgets();
	if (user != "")
	{
		std::vector<std::string> userMatches = m_searchLogic.HandleUserSearch(user,m_username);
		float startingYpos = 60.f;
		if (userMatches[0] != "NONE")
		{
			if (userMatches.size() > 4) {
				std::vector<std::string> userMatchesCopy;
				userMatchesCopy.resize(4);
				std::copy(userMatches.begin(), userMatches.begin() + 4, userMatchesCopy.begin());
				Scrollbar* scroll = new Scrollbar(sf::Vector2f(30, 216), sf::Vector2f(1232.f, 25.f), sf::Color::White);
				startingYpos += 45;
				DrawUserSearch(userMatchesCopy);
				scroll->AddEventListener([this, scroll, userMatches]() {
					std::vector<std::string> userMatchesCopy;
					userMatchesCopy.resize(4);
					scroll->SetScrolling(userMatches, [this](std::vector<std::string> userMatchesCopy) { this->DrawUserSearch(userMatchesCopy); }, 4);
					});
				m_scrollbarMenu.AddWidget(scroll);
			}
			else {
				DrawUserSearch(userMatches);
			}
		}
	}
}

void MainMenuWindow::DrawUserSearch(const std::vector<std::string>& userMatches)
{
	int startingYpos = 60.f;
	for (const auto& username : userMatches)
	{
		TextButton* user = new TextButton(sf::Vector2f(300.f, 45.f), sf::Vector2f(930.f, startingYpos), username, m_font, 25, sf::Color::Black, 2.f);
		user->SetBackgroundColor(sf::Color::White);
		user->AddEventListener([this, username]() {
			m_friendUsername = username;
			m_otherProfilesPressed = true;
			});
		m_userSearchMenu.AddWidget(user);
		startingYpos += 45;
	}
}

void MainMenuWindow::ShowFriendsList(const std::vector<std::string>& friendList)
{
	float startingYpos = 80.f;
	for (const auto& friends : friendList) {
		TextButton* friendButton = new TextButton(sf::Vector2f(296.f, 97.f), sf::Vector2f(1552.f, startingYpos), friends, m_font, 25, sf::Color::Black, 2.f);
		friendButton->SetBackgroundColor(sf::Color::White);
		friendButton->AddEventListener([this, friends]() {
			m_friendUsername = friends;
			m_otherProfilesPressed = true;
			});
		m_mainMenuWindow.AddWidget(friendButton);
		startingYpos += 100;
	}
}

void MainMenuWindow::GenerateFriendList()
{
	std::vector<std::string> friendList = m_userLogic.GetFriendsListForUser(m_username);
	if (friendList[0] == "EMPTY")
		return;
	else if (friendList.size() > 9) {
		std::vector<std::string> showingFriendList;
		showingFriendList.resize(9);
		std::copy(friendList.begin(), friendList.begin() + 9, showingFriendList.begin());
		Scrollbar* scroll = new Scrollbar(sf::Vector2f(30, 900), sf::Vector2f(1851.f, 80.f), sf::Color::White);
		float startingYpos = 80.f;
		ShowFriendsList(showingFriendList);
		scroll->AddEventListener([this, scroll, friendList]() {
			std::vector<std::string> showingFriendList;
			showingFriendList.resize(9);
			scroll->SetScrolling(friendList, [this](std::vector<std::string> showingFriendList) { this->ShowFriendsList(showingFriendList); }, 9);
			});
		m_mainMenuWindow.AddWidget(scroll);
	}
	else
	{
		ShowFriendsList(friendList);
	}
}

void MainMenuWindow::HandleSearchKeyWord()
{
	if (dynamic_cast<Textbox*>(m_mainMenuWindow.getElement(9))->getText() != "")
	{
		m_searchKeyboardPressed = true;
	}
}


std::string MainMenuWindow::GetFriendUser()
{
	return m_friendUsername;
}

std::string MainMenuWindow::GetUser()
{
	return m_username;
}

std::string MainMenuWindow::GetSearchBoxID()
{
	return dynamic_cast<Textbox*>(m_mainMenuWindow.getElement(9))->getText();
}
