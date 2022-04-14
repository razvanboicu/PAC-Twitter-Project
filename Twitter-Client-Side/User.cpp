#include "User.h"
#include <iostream>
#include "ErrorWindow.h"

bool User::CheckValidEmail(const std::string& toCheck)
{
	//sa respecte pattern-ul name@yahoo.com sau gmail
	std::regex isValid("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+$");
	if (!std::regex_match(toCheck, isValid))
	{
		ErrorWindow error("Error-Email was invalid.", "ERROR-REGISTER");
		error.ShowError();
	}
	return std::regex_match(toCheck, isValid);
}

bool User::CheckValidFirstName(const std::string& toCheck)
{
	//Numele sa fie compus doar din litere mici, mari, fara caractere speciale 
	std::regex isValid("^[a-zA-Z]{3,15}$");
	if (!std::regex_match(toCheck, isValid))
	{
		ErrorWindow error("Error-Firstname was invalid.", "ERROR-REGISTER");
		error.ShowError();
	}
	return std::regex_match(toCheck, isValid);
}

bool User::CheckValidSecondName(const std::string& toCheck)
{
	//Numele sa fie compus doar din litere mici, mari, fara caractere speciale 
	std::regex isValid("^[a-zA-Z]{3,15}$");
	if (!std::regex_match(toCheck, isValid))
	{
		ErrorWindow error("Error-Lastname was invalid.", "ERROR-REGISTER");
		error.ShowError();
	}
	return std::regex_match(toCheck, isValid);
}

bool User::CheckValidCity(const std::string& toCheck)
{
	//Orasul sa fie compus doar din litere mici, mari, fara caractere speciale 
	std::regex isValid("^[a-zA-Z]{3,20}$");
	if (!std::regex_match(toCheck, isValid))
	{
		ErrorWindow error("Error-City was invalid.", "ERROR-REGISTER");
		error.ShowError();
	}
	return std::regex_match(toCheck, isValid);
}

bool User::CheckValidPassword(const std::string& toCheck)
{
	//Minimum eight characters, at least one uppercase letter, one lowercase letterand one number
	std::regex isValid("(?!^[0-9]*$)(?!^[a-zA-Z]*$)^([a-zA-Z0-9]{8,15})$");;
	if (!std::regex_match(toCheck, isValid))
	{
		ErrorWindow error("Error-Password was invalid.", "ERROR-REGISTER");
		error.ShowError();
	}
	return regex_match(toCheck, isValid);
}

bool User::CheckValidId(const std::string& toCheck)
{
	//!!!!!!!! trebuie corectez aici, imi ia id cu # ca fiind valid !!!!!!!!!!!
	//fara caractere speciale #@, sunt permise DOAR: ".", "-", "_"
	std::regex isValid("^[a-zA-Z0-9]([._-](?![._-])|[a-zA-Z0-9]){3,18}[a-zA-Z0-9]$");
	if (!std::regex_match(toCheck, isValid))
	{
		ErrorWindow error("Error-Username was invalid.", "ERROR-REGISTER");
		error.ShowError();
	}
	return std::regex_match(toCheck, isValid);
}

User::User() :
	m_id(""),
	m_email(""),
	m_password(""),
	m_firstName(""),
	m_secondName(""),
	m_city("")
{
}

User::User(std::string id, std::string password, std::string firstName, std::string secondName, std::string email, std::string city)
{
	m_id = id;
	m_password = password;
	m_firstName = firstName;
	m_secondName = secondName;
	m_email = email;
	m_city = city;
	std::fstream out("login.txt", std::ios::out);
	out << m_id << " " << m_password << " " << m_firstName << " " << m_secondName << " " << m_email << " " << m_city << "\n";
	out.close();
}

void User::SetId(std::string id)
{
	m_id = id;
}

void User::SetEmail(std::string email)
{
	m_email = email;
}

void User::SetPassword(std::string password)
{
	m_password = password;
}

void User::SetFirstName(std::string firstName)
{
	m_firstName = firstName;
}

void User::SetSecondName(std::string secondName)
{
	m_secondName = secondName;
}


void User::SetCity(std::string city)
{
	m_city = city;
}

std::string User::GetUsername() const
{
	return m_id;
}

std::string User::GetPassword() const
{
	return m_password;
}

std::string User::GetEmail() const
{
	return m_email;
}

std::string User::GetFirstName() const
{
	return m_firstName;
}

std::string User::GetSecondName() const
{
	return m_secondName;
}
