#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Widget.h"

class Textbox : public Widget
{
public:
	Textbox(sf::Vector2f size, sf::Vector2f position, sf::Color color, uint32_t limit, sf::Font& font, sf::Sprite& textboxImage ,bool writable = false, float textSize = 30);
	Textbox(sf::Vector2f size, sf::Vector2f position, sf::Color color, uint32_t limit, sf::Font& font, bool writable = false, float textSize = 30);

	void SetOutline(float outline);
	void SetText(const std::string& text);
	void SetTextWithNewLine(const std::string& text);
	void SetCharColor(const sf::Color& color);
	const std::string& getText(); 
	void SetFont(const sf::Font& font);
	void SetSprite(const sf::Sprite& textboxImage);

	std::string getText() const;
	int GetStringSize() const;
	sf::Text GetBox() const;

	void Draw(sf::RenderWindow& window) override;
	void OnStateChanged(State state) override;
	void OnMousePressed() override;
	void OnKeyPressed(const sf::Event& key) override;
	void OnMouseReleased(std::function<void()>) override;
	void AddEventListener(std::function<void(void)> listener) override;
	void OnSelected() override;
	void GetLineSpacingRight();
	void GetLineSpacingForPresetText();

private:
	bool m_unwritable;
	bool m_imageAdded;
	sf::Text m_textBox;
	std::string m_text;
	uint32_t m_limit;
	sf::Sprite m_textboxSprite;
};

