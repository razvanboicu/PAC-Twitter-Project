#pragma once
#include "Button.h"
#include <SFML/Graphics.hpp>

class TextButton : public Button
{
public:

	TextButton(sf::Vector2f position,  std::string label, sf::Font& font, unsigned int labelSize=0, sf::Color textColor= sf::Color::Black);
	TextButton(sf::Vector2f size,sf::Vector2f position, std::string label, sf::Font& font, unsigned int labelSize = 0, sf::Color textColor = sf::Color::Black, float borderSize = 0);

private:

};

