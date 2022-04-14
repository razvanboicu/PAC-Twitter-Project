#pragma once
#include <iostream>
#include <stdio.h>
#define NOMINMAX
#include <windows.h>
#pragma comment (lib,"user32.lib")
#include <SFML\Graphics.hpp>

class ErrorWindow{
private:
	std::string m_errorTitle;
	std::string m_errorMessage;
public:
	ErrorWindow(std::string errorMessage, std::string errorTitle);
	void ShowError();
};

