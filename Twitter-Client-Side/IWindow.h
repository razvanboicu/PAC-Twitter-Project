#pragma once
#include "Textbox.h"
#include "Button.h"
#include "PostWidget.h"

enum class Windows
{
	eLoginWindow,
	eRegisterWindow,
	eMainMenuWindow,
	ePostWindow,
	eProfileWindow,
	eFeedWindow,
	eOtherProfilesWindow,
	eSearchKeywordWindow,
	eNotYetImplemented
};

class IWindow
{
public:
	sf::RenderWindow m_window;

	virtual void ShowWindow() = 0;
	virtual bool IsShowing() = 0;

	virtual Windows getNextWindowEnum() = 0;

	virtual ~IWindow() = default;
};

