#include "TextButton.h"


TextButton::TextButton(sf::Vector2f position,  std::string label, sf::Font& font, unsigned int labelSize, sf::Color textColor):
	Button(sf::Vector2f(0.f, 0.f), position, sf::Color::Transparent, label, font, labelSize, textColor)
{
	SetSize(sf::Vector2f(GetLabel().getLocalBounds().width, GetLabel().getLocalBounds().height));
	SetLabelPosition(position);
}

TextButton::TextButton(sf::Vector2f size, sf::Vector2f position, std::string label, sf::Font& font, unsigned int labelSize, sf::Color textColor, float borderSize):
	Button(size, position, sf::Color::Transparent, label, font, labelSize, textColor)
{
	SetLabelPosition(position);
	SetOutlineColorAndThickness(sf::Color::Black,borderSize);
}
