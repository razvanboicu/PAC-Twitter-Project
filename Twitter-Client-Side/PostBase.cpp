#include "PostBase.h"

PostBase::PostBase(sf::Vector2f position, sf::Font& font, sf::Vector2f size, sf::Sprite& lowerSprite, sf::Sprite& upperSprite)
{
	Textbox* lower = new Textbox(sf::Vector2f(size.x,25.f),sf::Vector2f(position.x,position.y-30.f),sf::Color::White,0,font,lowerSprite,false,15.f);
	Textbox* upper = new Textbox(size, position, sf::Color::White, 0, font,upperSprite);
	upper->SetOutlineColorAndThickness(sf::Color::Black, 2.f);
	lower->SetOutlineColorAndThickness(sf::Color::Black, 2.f);
	m_PostBaseMenu.AddWidget(std::move(lower));
	m_PostBaseMenu.getElement(0)->AddEventListener([this]() {return; });
	m_PostBaseMenu.AddWidget(std::move(upper));
	m_PostBaseMenu.getElement(1)->AddEventListener([this]() {return; });
}

void PostBase::SetPostBaseInfo(std::string author, std::string time, std::string text)
{
	dynamic_cast<Textbox*>(m_PostBaseMenu.getElement(0))->SetTextWithNewLine(author + " " + time);
	dynamic_cast<Textbox*>(m_PostBaseMenu.getElement(1))->SetTextWithNewLine(text);
}

Menu& PostBase::GetPostBaseMenu()
{
	return m_PostBaseMenu;
}

void PostBase::SetSprites(sf::Sprite& lowerSprite, sf::Sprite& upperSprite)
{
	m_lowerSprite = lowerSprite;
	m_upperSprite = upperSprite;
}

void PostBase::DrawPostBase(sf::RenderWindow& window)
{
	m_PostBaseMenu.Draw(window);
}
