#pragma once
#include <optional>
#include "Textbox.h"
#include "Post.h"
#include "PostBase.h"
#include "PostLogic.h"
#include "Menu.h"
#include "Button.h"

class PostWidget 
{
public:
	void Draw(sf::RenderWindow& window);
	PostWidget(sf::Vector2f position, sf::Font& font,bool isARetweet,int ClientHandle, sf::Sprite& lowerSprite, sf::Sprite& upperSprite, sf::Vector2f size=sf::Vector2f(1450.f,250.f));

	Menu& GetInteractionMenu();
	Menu& GetCommentsMenu();
	Menu& GetNewCommentMenu();
	Menu& GetBaseMenu();
	Menu& GetWidgetMenu();

	bool IsCommentsPressed() const;
	bool IsNewCommentPressed() const;
	void ChangeNewCommentValue();

	bool IsARetweetedPost();

	void SetInteractionInfo(const int& likes, const int& dislikes, const int& retweet, const int& comments);
	void SetComment();
	void SetPostInfo(Post post);
	

private:
	PostLogic m_PostLogic;
	size_t m_CommentFocus;
	bool m_IsCommentsPressed;
	bool m_IsNewCommentPressed;
	bool m_HasARetweet;
	std::vector<std::pair<std::string, std::string>> m_Comments;
	sf::RectangleShape m_InteractionBarBackground;
	sf::Font m_Font;
	PostBase m_BasePost;
	Menu m_InteractionBar;
	Menu m_CommentsBar;
	Menu m_NewCommentBar;
	std::optional<PostBase> m_RetweetedPost;
	sf::Texture m_heartTexture;
	sf::Sprite m_heartSprite;
	sf::Texture m_interactionBarTexture;
	sf::Sprite m_interactionBarSprite;
	sf::Texture m_brokenHeartTexture;
	sf::Sprite m_brokenHeartSprite;
	sf::Texture m_retweetTexture;
	sf::Sprite m_retweetSprite;
	sf::Texture m_newCommentTexture;
	sf::Sprite m_newCommentSprite;
	sf::Texture m_addNewCommentTexture;
	sf::Sprite m_addNewCommentSprite;
	sf::Texture m_cancelIconTexture;
	sf::Sprite m_cancelIconSprite;
	sf::Texture m_commentsTexture;
	sf::Sprite m_commentsSprite;
	sf::Texture m_nextPostButtonTexture;
	sf::Texture m_previousPostButtonTexture;
	sf::Sprite m_nextPostButtonSprite;
	sf::Sprite m_previousPostButtonSprite;
	sf::Texture m_commentLowerBarTexture;
	sf::Sprite m_commentLowerBarSprite;
	sf::Texture m_commentUpperBarTexture;
	sf::Sprite m_commentUpperBarSprite;
};