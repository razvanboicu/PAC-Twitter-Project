#include "Settings.h"

void Settings::setNewLanguage(std::string newLanguage)
{
	m_language = newLanguage;
}

void Settings::setNewPassword(std::string newPassword)
{
	m_newUser.SetPassword(newPassword);
}

void Settings::setNewFirstName(std::string newFirstName)
{
	m_newUser.SetFirstName(newFirstName);
}

void Settings::setNewLastName(std::string newLastName)
{
	m_newUser.SetSecondName(newLastName);
}

void Settings::setNewID(std::string newID)
{
	m_newUser.SetId(newID);
}

void Settings::setNewEmail(std::string newEmail)
{
	m_newUser.SetEmail(newEmail);
}

std::string Settings::getNewLanguage()
{
	return m_language;
}

std::string Settings::getNewPassword()
{
	return m_newUser.GetPassword();
}

std::string Settings::getNewFirstName()
{
	return m_newUser.GetFirstName();
}

std::string Settings::getNewLastName()
{
	return m_newUser.GetSecondName();
}

std::string Settings::getNewID()
{
	return m_newUser.GetUsername();
}

std::string Settings::setNewEmail()
{
	return m_newUser.GetEmail();
}

