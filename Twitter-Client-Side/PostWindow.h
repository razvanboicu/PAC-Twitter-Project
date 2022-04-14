#pragma once
#include "IWindow.h"
#include "Menu.h"
#include "PostLogic.h"
#include "PostBase.h"
#include <SFML\Graphics.hpp>

class PostWindow: public IWindow
{
public:
    PostWindow(int ClientHandle, int PostID);

    virtual void ShowWindow() override;
    virtual bool IsShowing() override;

    virtual Windows getNextWindowEnum() override;

    void SendPost();
    void setUsername(const std::string& user);

   

private:
    int m_postID;
    PostBase* m_postBaseRetweet;
    bool m_backPressed;
    bool m_postPressed;
    bool m_hasARetweetedPost;
    sf::Texture m_texture;
    sf::Texture m_textureBackground;
    sf::Texture m_textureBackButton;
    sf::Texture m_texturePostButton;
    sf::Sprite m_sprite;
    sf::Sprite m_spriteBackground;
    sf::Sprite m_spriteBackButton;
    sf::Sprite m_spritePostButton;
    sf::Texture m_lowerPostTexture;
    sf::Sprite m_lowerPostSprite;
    sf::Texture m_upperPostTexture;
    sf::Sprite m_upperPostSprite; 
    sf::Texture m_retweetUpperPostTexture;
    sf::Sprite m_retweetUpperPostSprite;
    sf::Texture m_retweetLowerPostTexture;
    sf::Sprite m_retweetLowerPostSprite;
    sf::Font m_font1;
    std::string m_username;
    Menu m_postMenuWindow;
    PostLogic m_postLogic;
};

