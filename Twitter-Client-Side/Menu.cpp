#include "Menu.h"
#include <iostream>

Menu::Menu() :
	m_widgets(0),
	m_selected(nullptr)
{
}

Menu::Menu(const Menu& other)
	:m_selected(other.m_selected),
	m_widgets(other.m_widgets)
{
}

Menu::Menu(Menu&& other) noexcept
{
	m_selected = other.m_selected;
	m_widgets = other.m_widgets;
	other.m_selected = nullptr;
	for (size_t i = 0; i < other.m_widgets.size(); i++)
		other.m_widgets[i] = nullptr;
}

void Menu::OnEvent(const sf::Event& event, const sf::Vector2f& point)
{
	switch (event.type)
	{
	case sf::Event::TextEntered:
		if (m_selected != nullptr) {
			if (event.text.unicode == 9) {
				if (m_selected->IsPressed()) {
					break;
				}
				m_selected->OnStateChanged(Widget::State::eDefault);
				bool gasitSelectat = false;
				for (int it = 0; it < m_widgets.size(); it++) {
					if (gasitSelectat) {
						m_selected = m_widgets[it];
						break;
					}
					if (m_selected == m_widgets[it]) {
						gasitSelectat = true;
					}
					if (it == m_widgets.size() - 1)
						it = -1;
				}
				m_selected->setSelected(Widget::State::eFocused);
				m_selected->OnKeyPressed(event);
			}
			else {
				m_selected->OnKeyPressed(event);
			}
		}
		else {
			if (event.text.unicode == 9) {
				m_selected = m_widgets.front();
				m_selected->setSelected(Widget::State::eFocused);
				m_selected->OnSelected();
			}
		}
		break;
	case sf::Event::MouseButtonPressed:
	{
		if (m_selected != nullptr)
		{
			if (m_selected->ContainsCoords(point))
				m_selected->OnStateChanged(Widget::State::eFocused);
			else
			{
				m_selected->OnStateChanged(Widget::State::eDefault);
				m_selected = nullptr;
			}
		}

		for (auto it : m_widgets)
		{
			if (it->ContainsCoords(point))
			{
				m_selected = it;
			}
		}
		if (m_selected != nullptr)
			m_selected->OnMousePressed();
		break;
	}
	case sf::Event::MouseButtonReleased:
		if (m_selected != nullptr)
			m_selected->OnMouseReleased(m_selected->Listener);
		break;
	}
}

void Menu::AddWidget(Widget* widget)
{
	m_widgets.push_back(widget);
}

void Menu::RemoveWidget(const unsigned int& index)
{
	m_widgets.erase(m_widgets.begin()+index);
}

void Menu::EraseAllWidgets()
{
	m_widgets.clear();
	m_selected = nullptr;
}

Widget* Menu::getLastElement() const
{
	return m_widgets[m_widgets.size() - 1];
}

Widget* Menu::getElement(int index) const
{
	return m_widgets[index];
}

void Menu::Draw(sf::RenderWindow& window)
{
	for (const auto& it : m_widgets)
		it->Draw(window);
}

Menu& Menu::operator=(const Menu& other)
{
	if (this != &other)
	{
		m_selected = other.m_selected;
		m_widgets = other.m_widgets;
	}
	return *this;
}

Menu& Menu::operator=(Menu&& other)
{
	if (this == &other)
	{
		return *this;
	}
	for (auto it : m_widgets)
		delete it;
	m_widgets = other.m_widgets;
	delete m_selected;
	m_selected = other.m_selected;
	other.m_selected = nullptr;
	for (auto it : other.m_widgets)
		it = nullptr;

	return *this;
}

Menu::~Menu()
{
	delete m_selected;
	//for (auto it : m_Widgets)
		//delete it;
}
