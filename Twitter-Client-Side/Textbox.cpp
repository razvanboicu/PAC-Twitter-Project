#include "Textbox.h"

Textbox::Textbox(sf::Vector2f size, sf::Vector2f position, sf::Color color, uint32_t limit, sf::Font& font, bool writable, float textSize) :
	Widget(size, position, color),
	m_limit(limit),
	m_unwritable(writable),
	m_imageAdded(false)
{
	m_textBox.setFillColor(sf::Color::Black);
	m_textBox.setPosition(position);
	m_textBox.setFont(font);
	m_textBox.setCharacterSize(textSize);
}

Textbox::Textbox(sf::Vector2f size, sf::Vector2f position, sf::Color color, uint32_t limit, sf::Font& font, sf::Sprite& textboxImage, bool writable, float textSize):
	Widget(size, position, color),
	m_limit(limit),
	m_unwritable(writable),
	m_imageAdded(true)
{
	m_textBox.setFillColor(sf::Color::Black);
	m_textBox.setPosition(position);
	m_textBox.setFont(font);
	m_textBox.setCharacterSize(textSize);
	SetSprite(textboxImage);
	m_textboxSprite.setPosition(position);
	m_textboxSprite.setTextureRect(sf::IntRect(m_widgetBackground.getLocalBounds()));
}

void Textbox::SetOutline(float outline)
{
	m_textBox.setOutlineThickness(outline);
	m_textBox.setOutlineColor(sf::Color::White);
}

void Textbox::SetText(const std::string& text)
{
	m_text = text;
	m_textBox.setString(text);
}

void Textbox::SetTextWithNewLine(const std::string& text)
{
	m_text.clear();
	for (int i = 0; i < text.size(); i++)
	{
		m_text.push_back(text[i]);
		m_textBox.setString(m_text);
		GetLineSpacingForPresetText();
	}
}


void Textbox::SetCharColor(const sf::Color& color)
{
	m_textBox.setFillColor(color);
}

const std::string& Textbox::getText()
{
	return m_text;
}

void Textbox::SetFont(const sf::Font& font)
{
	m_textBox.setFont(font);
}

void Textbox::SetSprite(const sf::Sprite& textboxImage)
{
	m_textboxSprite = textboxImage;
}

std::string Textbox::getText() const
{
	return m_text;
}

int Textbox::GetStringSize() const
{
	return m_text.size();
}

sf::Text Textbox::GetBox() const
{
	return m_textBox;
}

void Textbox::Draw(sf::RenderWindow& window)
{
	if (m_imageAdded) {
		window.draw(m_textboxSprite);
		window.draw(m_textBox);
	}
	else {
		window.draw(getBackground());
		window.draw(m_textBox);
	}
}

void Textbox::OnStateChanged(State state)
{
	if (IsFocused() && state == State::eDefault && !m_unwritable)
	{
		setSelected(state);
		m_textBox.setString(m_text);
	}
}

void Textbox::OnMousePressed(){
	if(Listener)
	Listener();
	if (m_limit != 0 && !m_unwritable)
	{
		setSelected(State::eFocused);
		OnSelected();
	}
}

void Textbox::OnKeyPressed(const sf::Event& key)
{
	if (IsFocused() && !m_unwritable)
	{
		if (key.text.unicode == 8) //if key is backspace
		{
			if (m_text.size() > 0)
				m_text.pop_back();;
		}
		else if (key.text.unicode == 9) {
		}
		else if (key.text.unicode == 32)
		{
			m_text.push_back(' ');
			GetLineSpacingRight();
		}
		else if (m_text.size() < m_limit && key.text.unicode > 32 && key.text.unicode < 127)
		{
			m_text.push_back(key.text.unicode);
			GetLineSpacingRight();
		}
		OnSelected();
	}

	Listener();
}

void Textbox::OnMouseReleased(std::function<void()>)
{
}

void Textbox::AddEventListener(std::function<void(void)> listener)
{
	if (listener != NULL) {
		Listener = listener;
	}
}

void Textbox::OnSelected()
{
	if (IsFocused() && !m_unwritable) {
		m_textBox.setString(m_text);
		m_textBox.setString(m_text + '_');
	}
}

void Textbox::GetLineSpacingRight()
{
	if (m_widgetBackground.getPosition().x + m_widgetBackground.getSize().x - 25 < m_textBox.findCharacterPos(m_textBox.getString().getSize() - 1).x) {
		char temp = m_text[m_text.size() - 1];
		m_text.erase(m_text.size() - 1);
		m_text.push_back('\n');
		m_text.push_back(temp);
	}
}

void Textbox::GetLineSpacingForPresetText()
{
	if (m_widgetBackground.getPosition().x + m_widgetBackground.getSize().x - 25 < m_textBox.findCharacterPos(m_textBox.getString().getSize() - 1).x) {
		char temp = m_text[m_text.size() - 1];
		m_text.erase(m_text.size() - 1);
		m_text.push_back('\n');
		m_text.push_back(temp);
	}
}

