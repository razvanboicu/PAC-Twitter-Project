#pragma once
#include "Widget.h"
#include "Textbox.h"
#include "Button.h"

class Menu
{
public:
	//constructor
	Menu();
	Menu(const Menu& other);
	//move constructor
	Menu(Menu&& other) noexcept;

	void OnEvent(const sf::Event& event, const sf::Vector2f& point);
	void AddWidget(Widget* widget);
	void RemoveWidget(const unsigned int& index);
	void EraseAllWidgets();
	Widget* getLastElement() const;
	Widget* getElement(int index) const;
	void Draw(sf::RenderWindow& window);

	//copy assignment operator
	Menu& operator=(const Menu& other);
	//move assignment operator
	Menu& operator=(Menu&& other);
	//destructor
	~Menu();

private:
	std::vector<Widget*> m_widgets;
	Widget* m_selected;
};
