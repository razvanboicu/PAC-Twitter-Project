#pragma once
#include "Menu.h"
#include "Widget.h"

class PostBase
{
public:
    PostBase(sf::Vector2f position, sf::Font& font, sf::Vector2f size, sf::Sprite& lowerSprite, sf::Sprite& upperSprite);
	void SetPostBaseInfo(std::string author, std::string time, std::string text);
	Menu& GetPostBaseMenu();
	void SetSprites(sf::Sprite& lowerSprite, sf::Sprite& upperSprite);
	void DrawPostBase(sf::RenderWindow& window);
private:
	Menu m_PostBaseMenu;
	sf::Sprite m_lowerSprite;
	sf::Sprite m_upperSprite;
};

