#pragma once
#include "IWindow.h"
#include "Menu.h"
#include "Client.h"
#include "UserLogic.h"
#include "PostLogic.h"
#include <sstream>

class OtherProfilesWindow : public IWindow
{
public:
	OtherProfilesWindow(std::string usernameOther, std::string usernameCurrent,int ClientHandle, int FocusedPost = 0);

	virtual void ShowWindow() override;
	virtual bool IsShowing() override;
	virtual Windows getNextWindowEnum() override;

	bool WasRetweetPressed();
	int GetFocusedPostID();
	std::string GetPostAuthor();

	int GetRetweetedPostID();
	void HandleRetweetPostPressed();

	void GeneratePosts();

private:
	PostWidget* m_postGUI;
	std::vector<std::pair<Post, int>> m_posts;
	PostLogic m_postLogic;
	UserLogic m_userLogic;
	size_t m_focusedPost;

	bool m_backPressed;
	Menu m_otherProfilesMenu;
	Menu m_interactions;
	Menu m_nextPreviousPostMenu;
	sf::Font m_font;
	std::string m_username;
	std::string m_currentUsername;
	bool m_commentPressed;
	bool m_retweetedPostPressed;
	bool m_retweetOtherPostPressed;
	bool m_refrencedWindow;
	bool m_addNewCommentPressed;
	bool m_retweetPressed;
	sf::Font m_colibriFont;
	sf::CircleShape m_profilePic;
	sf::Texture m_texturePostComment;
	sf::Sprite m_spritePostComment;
	sf::Texture m_textureBackground;
	sf::Sprite m_spriteCloseButton;
	sf::Texture m_textureCloseButton;
	sf::Texture m_profilePicTexture;
	sf::Texture m_heartTexture;
	sf::Sprite m_heartSprite;
	sf::Texture m_brokenHeartTexture;
	sf::Sprite m_brokenHeartSprite;
	sf::Texture m_retweetTexture;
	sf::Sprite m_retweetSprite;
	sf::Texture m_newCommentTexture;
	sf::Sprite m_newCommentSprite;
	sf::Texture m_commentsTexture;
	sf::Sprite m_commentsSprite;
	sf::Texture m_nextPostButtonTexture;
	sf::Sprite m_nextPostButtonSprite;
	sf::Texture m_previousPostButtonTexture;
	sf::Sprite m_previousPostButtonSprite;
	sf::Texture m_backButtonTexture;
	sf::Sprite m_backButtonSprite;
	sf::Texture m_followButtonTexture;
	sf::Sprite m_followButtonSprite;
	sf::Texture m_unfollowButtonTexture;
	sf::Sprite m_unfollowButtonSprite;
	sf::Sprite m_spriteBackground;
	sf::Sprite m_followUnfollowButtonSprite;
	sf::Texture m_lowerPostTexture;
	sf::Sprite m_lowerPostSprite;
	sf::Texture m_upperPostTexture;
	sf::Sprite m_upperPostSprite;	
	sf::Sprite m_yourPostsSprite;
	sf::Texture m_yourPostsTexture;
	sf::RectangleShape m_yourPosts;
};

