#pragma once
#include <string>
#include <regex>
#include <fstream>

class User{
public:
	static bool CheckValidEmail(const std::string& toCheck);
	static bool CheckValidFirstName(const std::string& toCheck);
	static bool CheckValidSecondName(const std::string& toCheck);
	static bool CheckValidCity(const std::string& toCheck);
	static bool CheckValidPassword(const std::string& toCheck);
	static bool CheckValidId(const std::string& toCheck);
	void SetId(std::string id);
	void SetEmail(std::string email);
	void SetPassword(std::string password);
	void SetFirstName(std::string firstName);
	void SetSecondName(std::string secondName);
	void SetCity(std::string city);
	std::string GetUsername() const;
	std::string GetPassword() const;
	std::string GetEmail() const;
	std::string GetFirstName() const;
	std::string GetSecondName() const;
	User();
	User(std::string id, std::string password, std::string firstName, std::string secondName, std::string email, std::string city);
private:
	std::string m_id;
	std::string m_email;
	std::string m_password;
	std::string m_firstName;
	std::string m_secondName;
	std::string m_city;
};

