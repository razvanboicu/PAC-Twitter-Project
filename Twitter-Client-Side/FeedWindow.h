#pragma once
#include "IWindow.h"
#include "Menu.h"
#include "SearchLogic.h"
#include "PostLogic.h"

class FeedWindow : public IWindow
{
public:
	FeedWindow(int ClientHandle, const std::string& username);
	virtual void ShowWindow() override;
	virtual bool IsShowing() override;

	void GeneratePosts();
	void HandlePostPressed();
	int GetPressedPostID();
	std::string GetPressedPostString();

	virtual Windows getNextWindowEnum() override;
private:
	int m_focusedPost;
	int m_pressedPostID;
	PostLogic m_postLogic;
	PostWidget* m_postGUI;
	std::string m_word;
	bool m_backPressed;
	bool m_postProfilePressed;
	bool m_retweetedPostPressed;
	bool m_postOthersPressed;
	bool m_retweetPressed;

	std::vector<std::pair<Post, int>> m_posts;
	std::string m_username;

	Menu m_feedWindowMenu;
	Menu m_interactions;
	Menu m_comments;
	Menu m_nextPreviousPostMenu;
	sf::Font m_font;

	sf::Texture m_lowerPostTexture;
	sf::Sprite m_lowerPostSprite;
	sf::Texture m_upperPostTexture;
	sf::Sprite m_upperPostSprite;
	sf::Texture m_nextPostButtonTexture;
	sf::Sprite m_nextPostButtonSprite;
	sf::Texture m_previousPostButtonTexture;
	sf::Sprite m_previousPostButtonSprite;
	sf::Sprite m_spriteBackground;
	sf::Texture m_textureBackground;
	sf::Sprite m_backButtonSprite;
	sf::Texture m_backButtonTexture;
};

