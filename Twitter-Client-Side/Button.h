#pragma once
#include "Widget.h"
#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>


class Button : public Widget
{
public:

	Button(sf::Vector2f size, sf::Vector2f position, sf::Color color, const std::string& label, sf::Font& font, unsigned int labelSize= 0, sf::Color textColor = sf::Color::Black);
	Button(sf::Vector2f size, sf::Vector2f position, sf::Color color, const std::string& label, sf::Font& font,sf::Sprite buttonImage, unsigned int labelSize = 0, sf::Color textColor = sf::Color::Black);

	void Draw(sf::RenderWindow& window) override;
	sf::Text GetLabel() const;
	void SetLabelPosition(const sf::Vector2f& label);
	void SetSprite(sf::Texture image);
	void SetBackgroundColor(const sf::Color& color);
	void SetButtonImage(sf::Sprite buttonImage);

	void OnMousePressed() override;
	void OnMouseReleased(std::function<void()>) override;
	void OnKeyPressed(const sf::Event& key) override;
	void AddEventListener(std::function<void(void)> listener) override;
	void OnStateChanged(State state) override;
	void OnSelected() override;
	
private:
	sf::RectangleShape m_selectedBorder;
	sf::Text m_label;
	bool m_imageAdded;
	sf::Sprite m_buttonImageSprite;
};

