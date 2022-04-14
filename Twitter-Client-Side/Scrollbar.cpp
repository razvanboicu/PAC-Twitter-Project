#include "Scrollbar.h"

Scrollbar::Scrollbar(sf::Vector2f size, sf::Vector2f position, sf::Color color) :
	Widget(size, position, color)
{
	m_scrollbarButtonShape.setFillColor(sf::Color::Black);
	m_scrollbarButtonShape.setPosition(position);
	m_scrollbarButtonShape.setSize(sf::Vector2f(size.x, size.y/10));
	m_widgetBackground.setOutlineColor(sf::Color::Black);
	m_widgetBackground.setOutlineThickness(2.f);
}

void Scrollbar::Draw(sf::RenderWindow& window)
{
	window.draw(getBackground());
	window.draw(m_scrollbarButtonShape);
}

void Scrollbar::OnStateChanged(State state)
{
	setSelected(state);
}

void Scrollbar::OnMousePressed()
{

	setSelected(State::ePressed);
	m_scrollbarButtonShape.setPosition(sf::Vector2f(m_scrollbarButtonShape.getPosition().x, sf::Mouse::getPosition().y - 40));
	Listener();
}

void Scrollbar::OnKeyPressed(const sf::Event& key)
{
}

void Scrollbar::OnMouseReleased(std::function<void()>)
{
}

void Scrollbar::AddEventListener(std::function<void(void)> listener)
{
	if (listener != NULL) {
		Listener = listener;
	}
}

void Scrollbar::OnSelected()
{
}

void Scrollbar::SetScrolling(const std::vector<std::string>& initialList, std::function<void(const std::vector<std::string>& friendList)> function, const unsigned int& maximumElements)
{
	std::vector<std::string> showingList;
	showingList.resize(maximumElements);
	m_sensitivity = (float)1 / ((initialList.size() - maximumElements + 1));
	std::vector<float> changingPoints;
	changingPoints.push_back(0);
	for (int i = 0; i < (initialList.size() - maximumElements) + 1; i++) {
		changingPoints.push_back(((float)i / (initialList.size() - maximumElements + 1) + m_sensitivity) * m_widgetBackground.getSize().y);
	}
	/*if (m_scrollbarButtonShape.getPosition().y < changingPoints[0]) {
		std::copy(initialList.begin(), initialList.begin() + maximumElements, showingList.begin());
	}*/

	for (int i = 0; i < changingPoints.size() - 1; i++) {
		if (m_scrollbarButtonShape.getPosition().y > changingPoints[i]) {
			if (m_scrollbarButtonShape.getPosition().y < changingPoints[i + 1]) {
				std::copy(initialList.begin() + i , initialList.begin() + maximumElements + i , showingList.begin());
				function(showingList);
			}
		}
	}

}

sf::RectangleShape Scrollbar::GetScrollButton() const
{
	return m_scrollbarButtonShape;
}
