#include "Users.h"
#include <fstream>
#include <iostream>

Users::Users()
{
}

void Users::LoadFromFile()
{
	std::ifstream fin("login.txt");
	std::string id, password;
	unsigned int userId = 0;
	while (fin >> id >> password){
		m_users.push_back(User(id, password, userId));
		userId++;
	}
}

void Users::LoadGraphFromFile()
{
	std::ifstream fin("usersGraph.txt");
	unsigned int userId;
	std::string line;
	while (std::getline(fin,line)) {
		std::unordered_set<std::string> setPerUser;
		std::string friends;
		std::istringstream ss(line);
		ss >> userId;
		while (ss >> friends) {
			setPerUser.insert(friends);
		}
		m_usersGraph.insert(std::make_pair(userId, setPerUser));
	}
	fin.close();
}

void Users::AddUser(const std::string& id, const std::string& password)
{
	int uID = ConvertUserToId(id);
	m_users.push_back(User(id, password, uID));
}

void Users::AddUserToGraph(const std::string& id)
{
	std::unordered_set<std::string> temp;
	unsigned int uID = ConvertUserToId(id);
	m_usersGraph[uID] = temp;
}

bool Users::UserExists(const std::string& username) const
{
	std::cout << username;
	for (const auto& user : m_users)
		if (user.m_id == username)
		{
			std::cout << user.m_id;
			return true;
		}
	return false;
}

bool Users::FindUser(std::string id, std::string password) const
{
	for (const auto& user : m_users)
		if (user.m_id == id && user.m_password == password)
			return true;
	return false;
}

const std::vector<User>& Users::getUserList() const
{
	return m_users;
}

std::unordered_set<std::string> Users::SendFriendsForUser(const std::string& username)
{
	unsigned int usernameId = ConvertUserToId(username);
	return m_usersGraph.at(usernameId);
}

unsigned int Users::ConvertUserToId(const std::string& username)
{
	for (int index = 0; index < m_users.size(); index++) {
		if (username == m_users[index].m_id) {
			return index + 1;
		}
	}
}

bool Users::AreConnected(const std::string& usernameCurrent, const std::string& usernameFriend)
{
	unsigned int usernameId = ConvertUserToId(usernameCurrent);
	for (auto friends : m_usersGraph.at(usernameId)) {
		if (friends == usernameFriend) {
			return true;
		}
	}
	return false;
}

void Users::AddFriendToGraph(const std::string& usernameCurrent, const std::string& usernameFriend)
{
	unsigned int usernameCurrentId = ConvertUserToId(usernameCurrent);
	unsigned int usernameFriendId = ConvertUserToId(usernameFriend);
	m_usersGraph.at(usernameCurrentId).insert(usernameFriend);
	m_usersGraph.at(usernameFriendId).insert(usernameCurrent);
}

void Users::RemoveFriendFromGraph(const std::string& usernameCurrent, const std::string& usernameFriend)
{
	unsigned int usernameCurrentId = ConvertUserToId(usernameCurrent);
	unsigned int usernameFriendId = ConvertUserToId(usernameFriend);
	m_usersGraph.at(usernameCurrentId).erase(m_usersGraph.at(usernameCurrentId).find(usernameFriend));
	m_usersGraph.at(usernameFriendId).erase(m_usersGraph.at(usernameFriendId).find(usernameCurrent));
}

void Users::UpdateLoginFile()
{
	std::fstream fout("login.txt", std::ios::trunc | std::ios::out);
	for (auto &user : m_users)
		fout << user.m_id << " " << user.m_password << '\n';
}

void Users::DeleteAccount(const std::string& username)
{
	int indexToDelete;
	for (size_t index = 0; index < m_users.size(); index++)
	{
		if (m_users[index].m_id == username)
			indexToDelete = index;
	}
	
	m_users.erase(m_users.begin() + indexToDelete);
	UpdateLoginFile();
}

void Users::UpdateGraphFile()
{
	std::fstream fout("usersGraph.txt",std::ios::trunc | std::ios::out);
	for (auto graf : m_usersGraph) {
		fout << graf.first;
		for (auto friends : graf.second) {
			fout << " " << friends;
		}
		fout << "\n";
	}
	
	fout.close();
}
