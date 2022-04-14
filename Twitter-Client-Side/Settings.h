#pragma once
#include <iostream>
//#include "Profile.h"
#include "User.h"

//O LASAM LA URMA .. IN BAREM NU SE SPECIFICA Settings, si nu ne va puncta nimeni daca o facem 

class Settings
{
public:
	Settings() = default;
	void setNewLanguage(std::string newLanguage);
	void setNewPassword(std::string newPassword);
	void setNewFirstName(std::string newFirstName);
	void setNewLastName(std::string newLastName);
	void setNewID(std::string newID);
	void setNewEmail(std::string newEmail);
	std::string getNewLanguage();
	std::string getNewPassword();
	std::string getNewFirstName();
	std::string getNewLastName();
	std::string getNewID();
	std::string setNewEmail();

private:
	std::string m_language;
	User m_newUser;
	//putem adauga o optiune pt a dezactiva contul
};

