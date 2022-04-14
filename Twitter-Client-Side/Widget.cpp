#include "Widget.h"

Widget::Widget() :
	m_state(State::eDefault),
	m_selected(true)
{
}

Widget::Widget(sf::Vector2f size, sf::Vector2f position, sf::Color color)
	:m_size(size),
	m_position(position),
	m_selected(true),
	m_state(State::eDefault)
{
	m_widgetBackground.setSize(size);
	m_widgetBackground.setPosition(position);
	m_widgetBackground.setFillColor(color);
}

bool Widget::ContainsCoords(const sf::Vector2f& point) const
{
	return getBackground().getGlobalBounds().contains(point);
}

void Widget::SetColor(const sf::Color& color)
{
	m_widgetBackground.setFillColor(color);
}

void Widget::SetSize(const sf::Vector2f& size)
{
	m_size = size;
	m_widgetBackground.setSize(size);
}

void Widget::SetSize(const float& x, const float& y)
{
	m_size.x = x;
	m_size.y = y;
	m_widgetBackground.setSize(sf::Vector2f(x,y));
}

void Widget::SetPosition(const sf::Vector2f& position)
{
	m_position = position;
	m_widgetBackground.setPosition(position);
}

void Widget::SetPosition(const float& x, const float& y)
{
	m_position.x = x;
	m_position.y = y;
	m_widgetBackground.setPosition(sf::Vector2f(x, y));
}

void Widget::SetOutlineColorAndThickness(const sf::Color& color, const float& thickness)
{
	m_widgetBackground.setOutlineColor(color);
	m_widgetBackground.setOutlineThickness(thickness);
}

sf::Vector2f Widget::GetSize() const
{
	return m_size;
}

sf::Vector2f Widget::GetPosition() const
{
	return m_position;
}

const sf::Vector2f& Widget::GetPosition()
{
	return m_position;
}

const sf::RectangleShape& Widget::getBackground() const
{
	return m_widgetBackground;
}

void Widget::setSelected(State state)
{
	m_state = state;
}

bool Widget::IsFocused() const
{
	if (m_state == State::eFocused) {
		return true;
	}
	return false;
}

bool Widget::IsPressed() const
{
	if (m_state == State::ePressed)
		return true;
	return false;
}
