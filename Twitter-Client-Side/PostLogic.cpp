#include "PostLogic.h"
#include <iomanip>      
#include <ctime>        
#include <chrono>


PostLogic::PostLogic(int ClientHandle) :
	Logic(ClientHandle)
{
}

bool PostLogic::SendPostToServer(const std::string& username, const std::string& text, const int& PostID)
{
	std::string PostToSend = "NEWPOST;" + username + ';' + text + ';';
	PostToSend += std::to_string(PostID) + ';';
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm ttm;
	localtime_s(&ttm, &t);
	std::stringstream timeNow;
	timeNow << std::put_time(&ttm, "%c");
	PostToSend += timeNow.str();
	Client::SendMsg(m_clientHandle, PostToSend);
	std::string errorCheck;
	Client::RecieveMessage(m_clientHandle, errorCheck);
	if (errorCheck == "FAIL") return false;
	else return true;
}

int PostLogic::GetNumberOfPostsFromUser(const std::string& username)
{
	std::string request = "POSTS;" + username;
	Client::SendMsg(m_clientHandle, request);
	std::string response;
	Client::RecieveMessage(m_clientHandle, response);
	return stoi(response);
}

std::vector<std::pair<Post, int>> PostLogic::GetPostsFromUser(const int& size)
{
	std::vector<std::pair<Post, int>> toSend;
	for (int index = 0; index < size; index++)
	{
		std::string request = "POSTREQ;" + std::to_string(index);
		Client::SendMsg(m_clientHandle, request);
		std::string response;
		Client::RecieveMessage(m_clientHandle, response);
		std::vector<std::string> tokens = TokenizeString(response);
		Post p;
		p.SetAuthor(tokens[1]);
		p.SetTime(tokens[3]);
		p.SetPost(tokens[2]);
		p.SetLikes(stoi(tokens[5]));
		p.SetDislikes(stoi(tokens[6]));
		p.SetRetweets(stoi(tokens[7]));
		int j = 9;
		for (int i = 0; i < stoi(tokens[8]); i++)
			p.AddComment(tokens[j++], tokens[j++]);
		if (tokens[4] != "0")
		{
			p.SetIDToRetweet(stoi(tokens[4]));
			std::string request = "POSTREQID;" + tokens[4];
			Client::SendMsg(m_clientHandle, request);
			std::string response;
			Client::RecieveMessage(m_clientHandle, response);
			std::vector<std::string> tokensRetweet = TokenizeString(response);
			p.SetRetweetPostInfo(std::pair(tokensRetweet[0] + " " + tokensRetweet[1], tokensRetweet[2]));
		}
		toSend.push_back(std::pair(p, stoi(tokens[0])));
	}
	return toSend;
}

std::vector<std::string>PostLogic::GetPostViaID(const int& postID)
{
	std::string request;
	request = "POSTREQID;" + std::to_string(postID);
	Client::SendMsg(m_clientHandle, request);
	std::string response;
	Client::RecieveMessage(m_clientHandle, response);
	return TokenizeString(response);
}

bool PostLogic::SendLikeToServer(const std::string& username, const int& ID)
{
	std::string request;
	request += "LIKE;" + username + ';' + std::to_string(ID);
	Client::SendMsg(m_clientHandle, request);
	std::string response;
	Client::RecieveMessage(m_clientHandle, response);
	if (response == "LIKED")
		return true;
	return false;
}

bool PostLogic::SendDislikeToServer(const std::string& username, const int& ID)
{
	std::string request;
	request += "DISLIKE;" + username + ';' + std::to_string(ID);
	Client::SendMsg(m_clientHandle, request);
	std::string response;
	Client::RecieveMessage(m_clientHandle, response);
	if (response == "LIKED")
		return true;
	return false;
}

void PostLogic::SendCommentToServer(const std::string& author, const std::string& text, const int& ID)
{
	std::string request = "NEWCOMMENT;" + author + ';' + text + ';' + std::to_string(ID);
	Client::SendMsg(m_clientHandle, request);
	std::string response;
	Client::RecieveMessage(m_clientHandle, response);
}

std::vector<std::pair<Post, int>> PostLogic::HandleFeed(const std::string& username)
{
	std::vector<std::pair<Post, int>> toSend;
	std::string request = "FEED;" + username;
	Client::SendMsg(m_clientHandle, request);
	std::string response;
	Client::RecieveMessage(m_clientHandle, response);
	if (response == "NONE")
		return toSend;
	std::vector<std::string> tokensID = TokenizeString(response);
	std::vector<std::string> tokens;
	for (int i = 0; i < tokensID.size(); i++)
	{
		std::string request2 = "POSTINTREQID;" + tokensID[i];
		Client::SendMsg(m_clientHandle, request2);
		std::string response2;
		Client::RecieveMessage(m_clientHandle, response2);
		tokens = TokenizeString(response2);
		Post p;
		p.SetAuthor(tokens[1]);
		p.SetTime(tokens[3]);
		p.SetPost(tokens[2]);
		p.SetLikes(stoi(tokens[5]));
		p.SetDislikes(stoi(tokens[6]));
		p.SetRetweets(stoi(tokens[7]));
		int j = 9;
		for (int i = 0; i < stoi(tokens[8]); i++)
			p.AddComment(tokens[j++], tokens[j++]);
		if (tokens[4] != "0")
		{
			p.SetIDToRetweet(stoi(tokens[4]));
			std::string request = "POSTREQID;" + tokens[4];
			Client::SendMsg(m_clientHandle, request);
			std::string response;
			Client::RecieveMessage(m_clientHandle, response);
			std::vector<std::string> tokensRetweet = TokenizeString(response);
			p.SetRetweetPostInfo(std::pair(tokensRetweet[0] + " " + tokensRetweet[1], tokensRetweet[2]));
		}
		toSend.push_back(std::pair(p, stoi(tokens[0])));
	}
	return toSend;
}

std::pair<Post, int> PostLogic::GetAllPostInfoViaID(const int& postID)
{
	std::string request;
	std::pair<Post, int> toSend;
	request = "POSTINTREQID;" + std::to_string(postID);
	Client::SendMsg(m_clientHandle, request);
	std::string response;
	Client::RecieveMessage(m_clientHandle, response);
	std::vector<std::string> tokens = TokenizeString(response);
	Post p;
	p.SetAuthor(tokens[1]);
	p.SetTime(tokens[3]);
	p.SetPost(tokens[2]);
	p.SetLikes(stoi(tokens[5]));
	p.SetDislikes(stoi(tokens[6]));
	p.SetRetweets(stoi(tokens[7]));
	int j = 9;
	for (int i = 0; i < stoi(tokens[8]); i++)
		p.AddComment(tokens[j++], tokens[j++]);
	if (tokens[4] != "0")
	{
		p.SetIDToRetweet(stoi(tokens[4]));
		std::string request = "POSTREQID;" + tokens[4];
		Client::SendMsg(m_clientHandle, request);
		std::string response;
		Client::RecieveMessage(m_clientHandle, response);
		std::vector<std::string> tokensRetweet = TokenizeString(response);
		p.SetRetweetPostInfo(std::pair(tokensRetweet[0] + " " + tokensRetweet[1], tokensRetweet[2]));
	}
	toSend = std::pair(p, stoi(tokens[0]));
	return toSend;
}
