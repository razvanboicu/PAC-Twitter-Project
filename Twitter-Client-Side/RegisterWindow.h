#pragma once
#include "IWindow.h"
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "UserLogic.h"

#include <tuple>
#include <fstream>
#include <regex>

class RegisterWindow :
    public IWindow
{
public:
    using RegisterCredentials = std::tuple<std::string, std::string, std::string, std::string, std::string>;

public:
    RegisterWindow(int ClientHandle);
    virtual bool IsShowing() override;
    virtual void ShowWindow() override;
    virtual Windows getNextWindowEnum() override;
    void GatherInfo();
    void SendInfo(const RegisterCredentials&);

private:
    UserLogic m_UserLogic;
    bool m_backPressed;
    bool m_registerPressed;
    sf::Texture m_texture;
    sf::Texture m_textureBackButton;
    sf::Texture m_textureRegisterButton;
    sf::Sprite m_sprite;
    sf::Sprite m_spriteBackButton;
    sf::Sprite m_spriteRegisterButton;
    sf::Font m_font;
    Menu m_menuRegisterWindow;
};

