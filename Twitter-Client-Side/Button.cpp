#include "Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Color color, const std::string& label, sf::Font& font, unsigned int labelSize, sf::Color textColor) :
	Widget(size, position, color)
{
	m_label.setFillColor(textColor);
	if (labelSize != 0)
		m_label.setCharacterSize(labelSize);
	m_label.setString(label);
	m_label.setFont(font);
	m_label.setPosition((position.x + size.x / 2) - (m_label.getLocalBounds().width / 2), (position.y + size.y / 2) - (m_label.getLocalBounds().height / 2));
	m_imageAdded = false;
}

Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Color color, const std::string& label, sf::Font& font, sf::Sprite buttonImage, unsigned int labelSize, sf::Color textColor) :
	Widget(size, position, color)
{
	m_label.setFillColor(textColor);
	if (labelSize != 0)
		m_label.setCharacterSize(labelSize);
	m_label.setString(label);
	m_label.setFont(font);
	m_label.setPosition((position.x + size.x / 2) - (m_label.getLocalBounds().width / 2), (position.y + size.y / 2) - (m_label.getLocalBounds().height / 2));
	m_buttonImageSprite = buttonImage;
	m_buttonImageSprite.setPosition(position);
	m_buttonImageSprite.setTextureRect(sf::IntRect(m_widgetBackground.getLocalBounds()));
	m_imageAdded = true;
}

void Button::Draw(sf::RenderWindow& window)
{
	if (m_imageAdded) {
		OnSelected();
		window.draw(m_buttonImageSprite);
		window.draw(m_selectedBorder);
	}
	else {
		OnSelected();
		window.draw(getBackground());
		window.draw(m_selectedBorder);
		window.draw(m_label);
	}
}

sf::Text Button::GetLabel() const
{
	return m_label;
}

void Button::SetLabelPosition(const sf::Vector2f& position)
{
	m_label.setPosition((position.x + GetSize().x / 2) - (m_label.getLocalBounds().width / 2), (position.y + GetSize().y / 2) - (m_label.getLocalBounds().height / 2));
}

void Button::SetSprite(const sf::Texture image)
{
	m_buttonImageSprite.setTexture(image);
}

void Button::OnStateChanged(State state)
{
	setSelected(state);
}

void Button::OnMousePressed()
{
	setSelected(State::ePressed);
	SetPosition(GetPosition().x + 3, GetPosition().y + 3);
	SetSize(GetSize().x - 7, GetSize().y - 7);
	m_label.setPosition((GetPosition().x + GetSize().x / 2) - (m_label.getLocalBounds().width / 2), (GetPosition().y + GetSize().y / 2) - (m_label.getLocalBounds().height / 2));
	m_buttonImageSprite.setPosition(GetPosition().x, GetPosition().y);
	m_buttonImageSprite.setScale(0.95f, 0.95f);
}

void Button::OnKeyPressed(const sf::Event& key)
{
	if (IsFocused()) {
		if (key.text.unicode == 9) {
			OnSelected();
		}
		if (key.text.unicode == 13) {
			OnMousePressed();
			OnMouseReleased(Listener);
		}
	}
}

void Button::OnMouseReleased(std::function<void()>)
{
	Listener();
	setSelected(State::eDefault);
	SetSize(GetSize().x + 7, GetSize().y + 7);
	SetPosition(GetPosition().x - 3, GetPosition().y - 3);
	m_label.setPosition((GetPosition().x + GetSize().x / 2) - (m_label.getLocalBounds().width / 2), (GetPosition().y + GetSize().y / 2) - (m_label.getLocalBounds().height / 2));
	m_buttonImageSprite.setPosition(GetPosition().x, GetPosition().y);
	m_buttonImageSprite.setScale(1.0f, 1.0f);
}

void Button::AddEventListener(std::function<void(void)> listener)
{
	if (listener != NULL) {
		Listener = listener;
	}
}

void Button::OnSelected()
{
	if (IsFocused()) {
		m_selectedBorder.setPosition(GetPosition().x,GetPosition().y);
		m_selectedBorder.setSize(sf::Vector2f(GetSize().x, GetSize().y));
		m_selectedBorder.setFillColor(sf::Color::Transparent);
		m_selectedBorder.setOutlineColor(sf::Color::Black);
		m_selectedBorder.setOutlineThickness(2);
	}
	else {
		m_selectedBorder.setOutlineColor(sf::Color::Transparent);
	}
}

void Button::SetBackgroundColor(const sf::Color& color)
{
	m_widgetBackground.setFillColor(color);
}

void Button::SetButtonImage(sf::Sprite buttonImage)
{
	m_buttonImageSprite = buttonImage;
	m_buttonImageSprite.setPosition(m_widgetBackground.getPosition());
	m_buttonImageSprite.setTextureRect(sf::IntRect(m_widgetBackground.getLocalBounds()));
	m_imageAdded = true;
}
