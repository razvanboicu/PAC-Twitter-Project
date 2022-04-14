#include "PostWidget.h"

void PostWidget::Draw(sf::RenderWindow& window)
{
	window.draw(m_interactionBarSprite);
	m_InteractionBar.Draw(window);
	m_BasePost.DrawPostBase(window);
	if(m_IsCommentsPressed)
	    m_CommentsBar.Draw(window);
	if (m_IsNewCommentPressed)
		m_NewCommentBar.Draw(window);
	if (m_HasARetweet)
		m_RetweetedPost.value().DrawPostBase(window);
}


PostWidget::PostWidget(sf::Vector2f position, sf::Font& font, bool isARetweet, int ClientHandle, sf::Sprite& lowerSprite, sf::Sprite& upperSprite, sf::Vector2f size):
	m_BasePost(position,font,size,lowerSprite,upperSprite),
	m_IsCommentsPressed(false),
	m_IsNewCommentPressed(false),
	m_CommentFocus(0),
	m_PostLogic(ClientHandle)
{
	m_Font.loadFromFile("arial.ttf");
	m_heartTexture.loadFromFile("heart30x30.png");
	m_heartSprite.setTexture(m_heartTexture);
	m_brokenHeartTexture.loadFromFile("dislike30x30.png");
	m_brokenHeartSprite.setTexture(m_brokenHeartTexture);
	m_retweetTexture.loadFromFile("retweet30x30.png");
	m_retweetSprite.setTexture(m_retweetTexture);
	m_commentsTexture.loadFromFile("comments30x30.png");
	m_commentsSprite.setTexture(m_commentsTexture);
	m_newCommentTexture.loadFromFile("comment30x30.png");
	m_newCommentSprite.setTexture(m_newCommentTexture);
	m_nextPostButtonTexture.loadFromFile("sageataDreapta.png");
	m_nextPostButtonSprite.setTexture(m_nextPostButtonTexture);
	m_previousPostButtonTexture.loadFromFile("sageataStanga.png");
	m_previousPostButtonSprite.setTexture(m_previousPostButtonTexture);
	m_interactionBarTexture.loadFromFile("baraJos.png");
	m_interactionBarSprite.setTexture(m_interactionBarTexture);
	m_addNewCommentTexture.loadFromFile("add50x50.png");
	m_addNewCommentSprite.setTexture(m_addNewCommentTexture);
	m_commentUpperBarTexture.loadFromFile("baraMicaComment.png");
	m_commentUpperBarSprite.setTexture(m_commentLowerBarTexture);
	m_commentLowerBarTexture.loadFromFile("baraMareComment.png");
	m_commentLowerBarSprite.setTexture(m_commentUpperBarTexture);

	m_InteractionBarBackground.setSize(sf::Vector2f(size.x, 35.f));
	m_InteractionBarBackground.setPosition(sf::Vector2f(position.x, position.y+size.y ));
	m_InteractionBarBackground.setFillColor(sf::Color::White);
	m_InteractionBarBackground.setOutlineColor(sf::Color::Black);
	m_InteractionBarBackground.setOutlineThickness(0.1f);

	m_interactionBarSprite.setPosition(m_InteractionBarBackground.getPosition());
	m_interactionBarSprite.setTextureRect(sf::IntRect(m_InteractionBarBackground.getLocalBounds()));

	float buttonX = position.x + 490;
	float buttonY = position.y + size.y + 3;
	float textboxX = buttonX + 30;
	Button* likes = new Button(sf::Vector2f(30, 30), sf::Vector2f(buttonX ,buttonY), sf::Color::Green, "likes", m_Font, m_heartSprite);
	m_InteractionBar.AddWidget(std::move(likes));
	buttonX += 100;
	m_InteractionBar.getElement(0)->AddEventListener([this]() {});
	m_InteractionBar.AddWidget(new Button(sf::Vector2f(30, 30), sf::Vector2f(buttonX, buttonY), sf::Color::Green, "dislikes", m_Font, m_brokenHeartSprite));
	m_InteractionBar.getElement(1)->AddEventListener([this]() {});
	buttonX += 100;
	m_InteractionBar.AddWidget(new Button(sf::Vector2f(30, 30), sf::Vector2f(buttonX, buttonY), sf::Color::Green, "retweets", m_Font, m_retweetSprite));
	m_InteractionBar.getElement(2)->AddEventListener([this]() {});
	buttonX += 100;
	m_InteractionBar.AddWidget(new Button(sf::Vector2f(30, 30), sf::Vector2f(buttonX, buttonY), sf::Color::Green, "comments", m_Font, m_commentsSprite));
	m_InteractionBar.getElement(3)->AddEventListener([this]() {m_IsCommentsPressed = !m_IsCommentsPressed; m_IsNewCommentPressed = false; });
	buttonX += 100;
	m_InteractionBar.AddWidget(new Button(sf::Vector2f(30, 30), sf::Vector2f(buttonX, buttonY), sf::Color::Green, "add comments", m_Font, m_newCommentSprite));
	m_InteractionBar.getElement(4)->AddEventListener([this]() {m_IsNewCommentPressed = !m_IsNewCommentPressed; m_IsCommentsPressed = false; });


	m_InteractionBar.AddWidget(new Textbox(sf::Vector2f(30.f, 30.f), sf::Vector2f(textboxX,buttonY), sf::Color::Transparent, 0, m_Font, true, 20));
	dynamic_cast<Textbox*>(m_InteractionBar.getElement(5))->SetText("0");
	textboxX += 100;
	m_InteractionBar.AddWidget(new Textbox(sf::Vector2f(30.f, 30.f), sf::Vector2f(textboxX, buttonY), sf::Color::Transparent, 0, m_Font, true, 20));
	dynamic_cast<Textbox*>(m_InteractionBar.getElement(6))->SetText("0");
	textboxX += 100;
	textboxX += 100;
	m_InteractionBar.AddWidget(new Textbox(sf::Vector2f(30.f, 30.f), sf::Vector2f(textboxX, buttonY), sf::Color::Transparent, 0, m_Font, true, 20));
	dynamic_cast<Textbox*>(m_InteractionBar.getElement(7))->SetText("0");
	textboxX += 100;

	m_HasARetweet = isARetweet;
    m_RetweetedPost.emplace(PostBase(sf::Vector2f(position.x+ size.x / 2, position.y+size.y / 2), m_Font, sf::Vector2f(size.x / 2, size.y / 2),lowerSprite,upperSprite));


	Textbox* upperComment = new Textbox(sf::Vector2f(size.x / 4, 25.f), sf::Vector2f((position.x + size.x) / 2 - (size.x / 4) / 2 + 93, position.y + size.y + 37), sf::Color::White, 0, m_Font, m_commentLowerBarSprite, false, 15);
	upperComment->SetOutlineColorAndThickness(sf::Color::Black, 2);
	Textbox* lowerComment = new Textbox(sf::Vector2f(size.x / 4, size.y / 2), sf::Vector2f((position.x + size.x) / 2 - (size.x / 4) / 2 + 93, position.y + size.y + 62), sf::Color::White, 0, m_Font, m_commentUpperBarSprite, false, 15);
	lowerComment->SetOutlineColorAndThickness(sf::Color::Black, 2);
	Button* previousComment = new Button(sf::Vector2f(50.f, 50.f), sf::Vector2f((position.x + size.x) / 2 - (size.x / 4) / 2 + 93, position.y + size.y + 67 + size.y / 2), sf::Color::White,"previous", m_Font, m_previousPostButtonSprite);
	previousComment->AddEventListener([this]() { 
		if (m_CommentFocus > 0)
		{ m_CommentFocus--; 
		SetComment(); 
		} 
	});
	Button* nextComment = new Button(sf::Vector2f(50.f, 50.f), sf::Vector2f((position.x + size.x) / 2 - (size.x / 4) / 2 + size.x / 4 + 65, position.y + size.y + 67 +size.y/2), sf::Color::White, "next", m_Font, m_nextPostButtonSprite);
	nextComment->AddEventListener([this]() {m_CommentFocus++; if (m_CommentFocus < m_Comments.size()) SetComment(); else m_CommentFocus--;  });
	m_CommentsBar.AddWidget(std::move(upperComment));
	m_CommentsBar.AddWidget(std::move(lowerComment));
	m_CommentsBar.AddWidget(std::move(nextComment));
	m_CommentsBar.AddWidget(std::move(previousComment));

	m_NewCommentBar.AddWidget(new Textbox(sf::Vector2f(size.x / 4, 25.f), sf::Vector2f((position.x + size.x) / 2 - (size.x / 4) / 2 + 93, position.y + size.y + 37), sf::Color::White, 0, m_Font, m_commentLowerBarSprite, false, 15));
	dynamic_cast<Textbox*>(m_NewCommentBar.getElement(0))->SetOutlineColorAndThickness(sf::Color::Black, 2);
	m_NewCommentBar.AddWidget(new Textbox(sf::Vector2f(size.x / 4, size.y / 2), sf::Vector2f((position.x + size.x) / 2 - (size.x / 4) / 2 + 93, position.y + size.y + 62), sf::Color::White, 20, m_Font, m_commentUpperBarSprite));
	dynamic_cast<Textbox*>(m_NewCommentBar.getElement(1))->SetOutlineColorAndThickness(sf::Color::Black, 2);
	dynamic_cast<Textbox*>(m_NewCommentBar.getElement(1))->AddEventListener([this]() {return; });
	
	m_NewCommentBar.AddWidget(new Button(sf::Vector2f(50.f, 50.f), sf::Vector2f((position.x + size.x) / 2 - (size.x / 4) / 2 + ((position.x + size.x) / 2 - (size.x / 4) / 2) / 2 -80, position.y + size.y + 67 + size.y / 2), sf::Color::White, "add a new comment", m_Font, m_addNewCommentSprite));
	dynamic_cast<Button*>(m_NewCommentBar.getElement(2))->AddEventListener([this]() {return; });
}

Menu& PostWidget::GetInteractionMenu()
{
	return m_InteractionBar;
}

Menu& PostWidget::GetCommentsMenu()
{
	return m_CommentsBar;
}

Menu& PostWidget::GetNewCommentMenu()
{
	return m_NewCommentBar;
}

Menu& PostWidget::GetBaseMenu()
{
	return m_RetweetedPost.value().GetPostBaseMenu();
}

bool PostWidget::IsCommentsPressed() const
{
	return m_IsCommentsPressed;
}

bool PostWidget::IsNewCommentPressed() const
{
	return m_IsNewCommentPressed;
}

Menu& PostWidget::GetWidgetMenu()
{
	return m_BasePost.GetPostBaseMenu();
}

void PostWidget::ChangeNewCommentValue()
{
	m_IsNewCommentPressed = !m_IsNewCommentPressed;
	dynamic_cast<Textbox*>(m_NewCommentBar.getElement(1))->SetText("");
}

void PostWidget::SetPostInfo(Post post)
{
	m_HasARetweet = false;
	m_CommentFocus = 0;
	m_Comments = post.GetComments();
	m_BasePost.SetPostBaseInfo(post.GetAuthor(), post.GetTime(), post.GetPost());
	if (post.HasARetweet())
	{
		m_HasARetweet = true;
		m_RetweetedPost.value().SetPostBaseInfo(post.GetRetweetedPostInfo().first, " ", post.GetRetweetedPostInfo().second);
	}
	SetInteractionInfo(post.GetLikes(), post.GetDislikes(), post.GetRetweets(), post.GetNumberOfComments());
	SetComment();
	dynamic_cast<Textbox*>(m_NewCommentBar.getElement(1))->SetText("");
}

void PostWidget::SetInteractionInfo(const int& likes, const int& dislikes, const int& retweets, const int& comments)
{
	dynamic_cast<Textbox*>(m_InteractionBar.getElement(5))->SetText(std::to_string(likes));
	dynamic_cast<Textbox*>(m_InteractionBar.getElement(6))->SetText(std::to_string(dislikes));
	dynamic_cast<Textbox*>(m_InteractionBar.getElement(7))->SetText(std::to_string(comments));
}

void PostWidget::SetComment()
{
	if (!m_Comments.empty())
	{
		dynamic_cast<Textbox*>(m_CommentsBar.getElement(1))->SetText(m_Comments[m_CommentFocus].first);
		dynamic_cast<Textbox*>(m_CommentsBar.getElement(0))->SetText(m_Comments[m_CommentFocus].second);
	}
	else
	{
		dynamic_cast<Textbox*>(m_CommentsBar.getElement(0))->SetText("");
		dynamic_cast<Textbox*>(m_CommentsBar.getElement(1))->SetText("");
	}

}

bool PostWidget::IsARetweetedPost()
{
	return m_RetweetedPost.has_value();
}
