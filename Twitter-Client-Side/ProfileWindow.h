#pragma once
#include "IWindow.h"
#include "Menu.h"
#include "PostLogic.h"

class ProfileWindow : public IWindow
{
public:
	ProfileWindow(int ClientHandle,std::string username, int focus = 0);

	virtual void ShowWindow() override;
	virtual bool IsShowing() override;

	void setUser(const std::string& username);

	void GeneratePosts();

	int GetFocusedPostID() const;
	int GetRetweetedPostID();
	std::string GetPostAuthor();
	bool WasRetweetPressed();

	void HandleRetweetPostPressed();

	virtual Windows getNextWindowEnum() override;
private:
	PostWidget* m_postGUI;
	std::vector<std::pair<Post,int>> m_posts;
	size_t m_focusedPost;
	PostLogic m_postLogic;

	sf::View m_scroll;
	float m_positionY;
	bool m_backPressed;
	bool m_commentPressed;
	bool m_addNewCommentPressed;
	bool m_retweetedPostPressed;
	bool m_retweetPressed;
	bool m_refrencedWindow;
	sf::Font m_font;
	sf::Font m_colibriFont;
	Menu m_menuProfileWindow;
	Menu m_interactions;
	Menu m_nextPreviousPostMenu;

	sf::CircleShape m_profilePic;
	sf::Texture m_textureBackground;
	sf::RectangleShape m_yourPosts;
	sf::Texture m_profilePicTexture;
	sf::Texture m_nextPostButtonTexture;
	sf::Sprite m_nextPostButtonSprite;
	sf::Texture m_previousPostButtonTexture;
	sf::Sprite m_yourPostsSprite;
	sf::Texture m_yourPostsTexture;
	sf::Sprite m_previousPostButtonSprite;
	sf::Texture m_backButtonTexture;
	sf::Sprite m_backButtonSprite;
	sf::Texture m_texturePostComment;
	sf::Sprite m_spritePostComment;
	sf::Sprite m_spriteCloseButton;
	sf::Texture m_textureCloseButton;
	sf::Sprite m_spriteBackground;
	sf::Texture m_lowerPostTexture;
	sf::Sprite m_lowerPostSprite;
	sf::Texture m_upperPostTexture;
	sf::Sprite m_upperPostSprite;
	std::string m_username;
	std::string m_firstName;
	std::string m_lastName;
	
};

