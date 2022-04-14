#include "SearchLogic.h"
#include <sstream>

SearchLogic::SearchLogic(int ClientHandle):
	Logic(ClientHandle)
{
}

std::vector<std::string> SearchLogic::HandleUserSearch(const std::string& user,const std::string& currentUser)
{
	Client::SendMsg(m_clientHandle, std::string("USERSEARCH;" + user+';'+currentUser));
	std::string response;
	Client::RecieveMessage(m_clientHandle, response);
	return TokenizeString(response);
}

std::vector<std::pair<std::vector<std::string>, int>> SearchLogic::HandleKeyWordSearch(const std::string& keyword)
{
	std::stringstream ss(keyword);
	std::string word;
	std::vector<std::pair<std::vector<std::string>, int>> toSend;
	while (std::getline(ss, word, ' '))
	{
		std::string request = "KEYWORDSEARCH;" + word;
		Client::SendMsg(m_clientHandle, request);
		std::string response;
		Client::RecieveMessage(m_clientHandle, response);
		if (response == "NONE")
			continue;
		std::vector<std::string> tokens = TokenizeString(response);
		for (int i = 0; i < tokens.size(); i++)
		{
			std::string request2 = "POSTREQID;" + tokens[i];
			Client::SendMsg(m_clientHandle, request2);
			std::string response2;
			Client::RecieveMessage(m_clientHandle, response2);
			toSend.push_back(std::pair(TokenizeString(response2), stoi(tokens[i])));
		}
	}
	return toSend;
}

