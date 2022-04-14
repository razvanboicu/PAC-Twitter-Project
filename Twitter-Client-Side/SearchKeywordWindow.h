#pragma once
#include "IWindow.h"
#include "Menu.h"
#include "SearchLogic.h"
#include "PostBase.h"


class SearchKeywordWindow : public IWindow
{
public:
	SearchKeywordWindow(int ClientHandle, std::string word,std::string username);

	void GeneratePosts();
	void HandlePostPressed();
	int GetPressedPostID();
	std::string GetPressedPostString();

	virtual void ShowWindow() override;
	virtual bool IsShowing() override;
	virtual Windows getNextWindowEnum() override;
private:
	int m_focusedPost;
	int m_pressedPostID;
	SearchLogic m_searchLogic;
	PostBase* m_postBase;
	std::string m_word;
	bool m_backPressed;
	bool m_postPressed;
	bool m_otherPostPressed;
	bool m_hasPosts;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Font m_font;
	Menu m_searchKeywordWindow;

	std::vector<std::pair<std::vector<std::string>, int>> m_posts;
	std::string m_username;

	sf::Texture m_lowerPostTexture;
	sf::Sprite m_lowerPostSprite;
	sf::Texture m_upperPostTexture;
	sf::Sprite m_upperPostSprite;
	sf::Texture m_nextPostButtonTexture;
	sf::Sprite m_nextPostButtonSprite;
	sf::Texture m_previousPostButtonTexture;
	sf::Sprite m_previousPostButtonSprite;
	sf::Texture m_textureBackground;
	sf::Sprite m_SpriteBackground;
	sf::Texture m_backButtonTexture;
	sf::Sprite m_backButtonSprite;
};