#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <optional>
#include <functional>

class Widget
{
public:
	enum class State
	{
		eDefault,
		ePressed,
		eFocused
	};
public:

	Widget();
	Widget(sf::Vector2f size, sf::Vector2f position, sf::Color color);
	//events
	virtual void OnStateChanged(State state) = 0;
	virtual void OnMousePressed() = 0;
	virtual void OnKeyPressed(const sf::Event& key) = 0;
	virtual void OnMouseReleased(std::function<void()>) = 0;
	virtual void OnSelected() = 0;
	virtual void AddEventListener(std::function<void(void)> listener) = 0;
	std::function<void()> Listener;

	virtual void Draw(sf::RenderWindow& window) = 0;

	bool ContainsCoords(const sf::Vector2f& point) const;

	void SetColor(const sf::Color& color);
	void SetSize(const sf::Vector2f& size);
	void SetSize(const float& x, const float& y);
	void SetPosition(const sf::Vector2f& position);
	void SetPosition(const float& x, const float& y);
	void SetOutlineColorAndThickness(const sf::Color& color, const float& thickness);

	sf::Vector2f GetSize() const;
	sf::Vector2f GetPosition() const;
	const sf::Vector2f& GetPosition();
	const sf::RectangleShape& getBackground() const;

	void setSelected(State state);
	bool IsFocused() const;
	bool IsPressed() const;
	sf::RectangleShape m_widgetBackground;

private:
	State m_state;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	bool m_selected;
};