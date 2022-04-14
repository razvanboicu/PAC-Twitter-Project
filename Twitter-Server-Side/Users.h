#pragma once
#include <string>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

struct User{
	//un ID numar pentru fiecare user, pentru a fi mai rapid graph-ul

	unsigned int m_userIntID;
	std::string m_id;
	std::string m_password;

	User(std::string id, std::string password , unsigned int userID)
	{
		m_id = id;
		m_password = password;
	}
};

class Users
{
public:
	Users();
	void LoadFromFile();
	void LoadGraphFromFile();
	void AddUser(const std::string& id, const std::string& password);
	void AddUserToGraph(const std::string& id);
	bool UserExists(const std::string& username) const;
	bool FindUser(std::string id, std::string password) const;
	const std::vector<User>& getUserList() const;
	std::unordered_set<std::string> SendFriendsForUser(const std::string& username);
	unsigned int ConvertUserToId(const std::string& username);
	bool AreConnected(const std::string& usernameCurrent, const std::string& usernameFriend);
	void AddFriendToGraph(const std::string& usernameCurrent, const std::string& usernameFriend);
	void RemoveFriendFromGraph(const std::string& usernameCurrent, const std::string& usernameFriend);
	void UpdateLoginFile();
	void DeleteAccount(const std::string& username);
	void UpdateGraphFile();

private:
	std::vector<User> m_users;
	std::unordered_map<unsigned int, std::unordered_set<std::string>> m_usersGraph;
};

