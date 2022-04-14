#include "UserLogic.h"
#include <tuple>


UserLogic::UserLogic(int ClientHandle) :
	Logic(ClientHandle)
{
}

bool UserLogic::HandleLogin(const Credentials& credentials)
{
	auto& [id, pass] = credentials;
	std::string request = "LOGIN;" + id + ';' + pass, response;
	Client::SendMsg(m_clientHandle, request);
	Client::RecieveMessage(m_clientHandle, response);
	if (response == "SUCCES")
		return true;
	else
		return false;
}

bool UserLogic::HandleRegister(const RegisterCredentials& Register)
{
	if (!(get<0>(Register).empty() && get<1>(Register).empty() && get<2>(Register).empty()))
	{
		auto& [id, pass, email, firstName, secondName] = Register;
		std::string request = "REGISTER;" + id + ";" + pass + ";" + email + ";" + firstName + ";" + secondName;
		Client::SendMsg(m_clientHandle, request);
		std::string response;
		Client::RecieveMessage(m_clientHandle, response);
		if (response == "SUCCES")
			return true;
		else return false;
	}
	else return false;
}

bool UserLogic::UpdateFollowStatus(const std::string& currentUser, const std::string& otherUser)
{
	Client::SendMsg(m_clientHandle, std::string("UPDATEFOLLOWSTATUS;" + currentUser + ";" + otherUser));
	std::string response;
	Client::RecieveMessage(m_clientHandle, response);
	if (response == "FOLLOWED")
		return true;
	else if (response == "UNFOLLOWED")
		return false;
}

bool UserLogic::CheckIfFollowing(const std::string& currentUser, const std::string& otherUser)
{
	Client::SendMsg(m_clientHandle, std::string("CHECKFOLLOWSTATUS;" + currentUser + ";" + otherUser));
	std::string response;
	Client::RecieveMessage(m_clientHandle, response);
	if (response == "FOLLOWING") {
		return true;
	}
	else if (response == "NOTFOLLOWING")
		return false;
}

bool UserLogic::DeleteAccount(const std::string& username)
{
	Client::SendMsg(m_clientHandle, std::string("DELETEACCOUNT;" + username));
	std::string response;
	Client::RecieveMessage(m_clientHandle, response);
	if (response == "SUCCES")
		return true;
	else
		return false;
}

std::vector<std::string> UserLogic::GetFriendsListForUser(const std::string& username)
{
	Client::SendMsg(m_clientHandle, std::string("FRIENDSLIST;" + username));
	std::string response;
	Client::RecieveMessage(m_clientHandle, response);
	return TokenizeString(response);
}
