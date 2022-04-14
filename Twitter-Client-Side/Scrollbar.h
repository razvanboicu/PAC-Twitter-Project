#pragma once
#include "Widget.h"
#include <algorithm>

class Scrollbar : public Widget
{
public:
	Scrollbar(sf::Vector2f size, sf::Vector2f position, sf::Color color);
	void Draw(sf::RenderWindow& window) override;
	void OnStateChanged(State state) override;
	void OnMousePressed() override;
	void OnKeyPressed(const sf::Event& key) override;
	void OnMouseReleased(std::function<void()>) override;
	void AddEventListener(std::function<void(void)> listener) override;
	void OnSelected() override;

	void SetScrolling(const std::vector<std::string>& initialList,std::function<void(const std::vector<std::string>& friendList)> function,const unsigned int& maximumElements);

	sf::RectangleShape GetScrollButton() const;
private:
	float m_sensitivity;
	sf::Sprite m_scrollbarButtonSprite;
	sf::RectangleShape m_scrollbarButtonShape;
};

