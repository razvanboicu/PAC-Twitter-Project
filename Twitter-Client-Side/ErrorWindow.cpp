#include "ErrorWindow.h"

ErrorWindow::ErrorWindow(std::string errorMessage, std::string errorTitle) :
	m_errorMessage(errorMessage),
	m_errorTitle(errorTitle)
{}

void ErrorWindow::ShowError()
{
	MessageBoxA(NULL, m_errorMessage.c_str(), m_errorTitle.c_str(), MB_ICONERROR | MB_OK);
}
