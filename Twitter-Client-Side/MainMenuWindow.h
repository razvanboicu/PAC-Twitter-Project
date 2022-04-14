#pragma once
#include "IWindow.h"
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "TextButton.h"
#include "Scrollbar.h"
#include "SearchLogic.h"
#include "UserLogic.h"
#include <algorithm>

class MainMenuWindow : public IWindow {
public:
    MainMenuWindow(int clientHandle, std::string username);

    virtual void ShowWindow() override;
    virtual bool IsShowing() override;
         
    virtual Windows getNextWindowEnum() override;

    void SetUser(std::string username);
    void ShowUserSearch(std::string user);
    void DrawUserSearch(const std::vector<std::string>& userMatches);
    void ShowFriendsList(const std::vector<std::string>& friendList);
    void GenerateFriendList();
    void HandleSearchKeyWord();
    std::string GetFriendUser();
    std::string GetUser();
    std::string GetSearchBoxID();

private:
    bool m_logoutPressed;
    bool m_feedPressed;
    bool m_postPressed;
    bool m_profilePressed;
    bool m_settingsPressed;
    bool m_searchKeyboardPressed;
    bool m_searchUserPressed;
    bool m_otherProfilesPressed;
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
    
    //array pentru sprite/texturi? pentru butoane
   
    sf::Texture m_textureBackground;
    sf::Sprite m_spriteBackground;
    sf::Texture m_textureSettingsButton;
    sf::Sprite m_spriteSettingsButton;
    sf::Texture m_textureSearchUserIcon;
    sf::Sprite m_spriteSearchUserIcon;
    sf::Texture m_textureLogoutIcon;
    sf::Sprite m_spriteLogoutIcon;
    sf::Texture m_textureSettingsIcon;
    sf::Sprite m_spriteSettingsIcon;
    sf::Texture m_textureProfileIcon;
    sf::Sprite m_spriteProfileIcon;
    sf::Texture m_textureSearchIcon;
    sf::Sprite m_spriteSearchIcon;
    sf::Texture m_textureNewPostIcon;
    sf::Sprite m_spriteNewPostIcon;
    sf::Texture m_textureFeedIcon;
    sf::Sprite m_spriteFeedIcon;

    sf::Font m_font;
    std::string m_username;
    std::string m_friendUsername;
    Menu m_mainMenuWindow;
    Menu m_userSearchMenu;
    Menu m_settingsMenu;
    Menu m_scrollbarMenu;
    SearchLogic m_searchLogic;
    UserLogic m_userLogic;
};

