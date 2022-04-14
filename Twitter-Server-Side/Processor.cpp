#include "Processor.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "../Logger/Logger.h"

std::ofstream out("logs.txt", std::ios::app);
Logger logger(out);

Processor::Processor(){
	m_users.LoadFromFile();
	m_users.LoadGraphFromFile();
	m_posts.LoadPostsFromFile();
	m_posts.LoadCommentsFromFile();
	m_posts.LoadLikesAndDislikesFromFile();
	m_invertedIndex.LoadInvertedIndex(m_posts.GetPostText());
}

std::string Processor::ProcessRequest(const std::string& request){
	std::vector<std::string> tokens = TokenizeRequest(request);
	if (tokens[0] == "LOGIN")
		return ProcessLogin(tokens[1], tokens[2]);
	if (tokens[0] == "REGISTER")
		return ProcessRegister(tokens);
	if (tokens[0] == "USERSEARCH")
		return ProcessUserSearch(tokens[1],tokens[2]);
	if (tokens[0] == "FRIENDSLIST")
		return ProcessSendFriendsList(tokens[1]);
	if (tokens[0] == "NEWPOST")
		return ProcessNewPost(tokens);
	if (tokens[0] == "UPDATEFOLLOWSTATUS")
		return ProcessFollowUpdate(tokens[1], tokens[2]);
	if (tokens[0] == "CHECKFOLLOWSTATUS")
		return ProcessCheckingFollowStatus(tokens[1], tokens[2]);
	if (tokens[0] == "POSTS")
		return SendNumberOfPosts(tokens[1]);
	if (tokens[0] == "POSTREQ")
		return SendPostToClient(tokens[1]);
	if (tokens[0] == "DELETEACCOUNT")
		return HandleDeleteAccount(tokens[1]);
	if (tokens[0] == "LIKE")
		return UpdateLikes(tokens[1], stoi(tokens[2]));
	if (tokens[0] == "DISLIKE")
		return UpdateDislikes(tokens[1], stoi(tokens[2]));
	if (tokens[0] == "NEWCOMMENT")
		return UpdateComments(tokens[1], tokens[2], stoi(tokens[3]));
	if (tokens[0] == "POSTREQID")
		return SendPostWithoutInteractionsViaID(tokens[1]);
	if (tokens[0] == "POSTINTREQID")
		return SendPostWithInteractionsViaID(tokens[1]);
	if (tokens[0] == "KEYWORDSEARCH")
		return SendKeywordIDs(tokens[1]);
	if (tokens[0] == "FEED")
		return ProcessFeed(tokens[1]);
}

std::vector<std::string> Processor::TokenizeRequest(const std::string& request)
{
	std::vector<std::string> tokens;
	std::stringstream stream(request);
	std::string temp;
	while (std::getline(stream, temp, ';'))
	{
		tokens.push_back(temp);
	}
	return tokens;
}

std::string Processor::ProcessLogin(const std::string& id, const std::string& password)
{
	if (m_users.FindUser(id, password)) {
		logger.Log(Logger::Level::Info, "User '", id, "' has successfully logged in");
		return "SUCCES";
	}
		
	return "FAIL";
}

std::string Processor::ProcessRegister(const std::vector<std::string>& credentials)
{
	if (!m_users.UserExists(credentials[1]))
	{
		std::fstream out2("login.txt", std::ios::app);
		std::fstream out("credentials.txt", std::ios::app);
		std::fstream out3("usersGraph.txt", std::ios::app);
		out << '\n';
		out2 << "\n" << credentials[1] << " " << credentials[2];
		out3 << "\n" << m_users.getUserList().size() + 1;
		m_users.AddUser(credentials[1], credentials[2]);
		m_users.AddUserToGraph(credentials[1]);
		return "SUCCES";
	}
	else return "FAILED";
}

std::string Processor::ProcessUserSearch(const std::string& user, const std::string& currentUser)
{
	int maxdist = user.length();
	int currdist;
	int sumMaxDist;

	std::string checkWord;
	std::string matchString;
	for (const auto& word : m_users.getUserList())
	{
		checkWord = word.m_id;
		currdist = CalculateLevenshteinDistance(user, checkWord);
		sumMaxDist = maxdist + currdist;
		if (sumMaxDist == checkWord.length() && checkWord!=currentUser)
			matchString += checkWord + ';';
	}
	if (matchString == "")
		matchString = "NONE";
	return matchString;
}

std::string Processor::ProcessSendFriendsList(const std::string& currentUser)
{
	std::string response;
	if (m_users.SendFriendsForUser(currentUser).size() > 0) {
		for (const auto& friends : m_users.SendFriendsForUser(currentUser)) {
			response += friends + ";";
		}
	}
	else {
		response = "EMPTY";
	}
	return response;
}

std::string Processor::ProcessNewPost(const std::vector<std::string>& tokens)
{
	std::tuple<std::string, std::string, std::string,int> postInfo;
	postInfo = std::make_tuple(tokens[1], tokens[2], tokens[4],std::stoi(tokens[3]));
	m_posts.AddNewPost(postInfo);
	m_invertedIndex.AddPostToInvertedIndex(tokens[1], stoi(tokens[3]));
	return "SUCCES";
}

int Processor::CalculateLevenshteinDistance(const std::string& inputWord, const std::string& checkWord)
{
	std::vector<std::vector<int>> distanceMatrix;
	distanceMatrix.resize(inputWord.size() + 1);
	for (int i = 0; i < distanceMatrix.size(); i++)
	{
		distanceMatrix[i].resize(checkWord.size() + 1);
	}
	for (int i = 0; i <= inputWord.length(); i++) {
		distanceMatrix[i][0] = i;
	}

	for (int j = 0; j <= checkWord.length(); j++) {
		distanceMatrix[0][j] = j;
	}
	for (int i = 1; i < distanceMatrix.size(); i++)
	{
		for (int j = 1; j < distanceMatrix[i].size(); j++)
			if (inputWord[i - 1] == checkWord[j - 1])
				distanceMatrix[i][j] = distanceMatrix[i - 1][j - 1];
			else
			{
				int temp = std::min(distanceMatrix[i - 1][j] + 1, distanceMatrix[i - 1][j - 1] + 1);
				distanceMatrix[i][j] = std::min(temp, distanceMatrix[i][j-1] + 1);
			}
	}
	return distanceMatrix[inputWord.length()][checkWord.length()];
}

std::string Processor::ProcessFollowUpdate(const std::string& currentUser, const std::string& otherUser)
{
	std::string response;
	if (m_users.AreConnected(currentUser, otherUser)) {
		m_users.RemoveFriendFromGraph(currentUser, otherUser);
		m_users.UpdateGraphFile();
		response = "UNFOLLOWED";
	}
	else {
		m_users.AddFriendToGraph(currentUser, otherUser);
		m_users.UpdateGraphFile();
		response = "FOLLOWED";
	}
	return response;
}

std::string Processor::ProcessCheckingFollowStatus(const std::string& currentUser, const std::string& otherUser)
{
	std::string response;
	if (m_users.AreConnected(currentUser, otherUser)) {
		response = "FOLLOWING";
	}
	else {
		response = "NOTFOLLOWING";
	}
	return response;
}

std::string Processor::SendNumberOfPosts(const std::string& username)
{
	m_tempPosts=m_posts.GetPostsFromUser(username);
	return std::to_string(m_tempPosts.size());
}

std::string Processor::SendPostToClient(const std::string& index)
{
	std::string response;
	response=std::to_string(m_tempPosts[stoi(index)].second)+';'+m_tempPosts[stoi(index)].first.GetInfoForClient();
	return response;
}

std::string Processor::SendPostWithoutInteractionsViaID(const std::string& ID)
{
	std::pair<Post,int> p = m_posts.GetPostViaID(stoi(ID));
	return p.first.GetPostInfoAsString();
}

std::string Processor::SendPostWithInteractionsViaID(const std::string& ID)
{
	std::pair<Post, int> p = m_posts.GetPostViaID(stoi(ID));
	return std::to_string(p.second)+';'+p.first.GetInfoForClient();
}

std::string Processor::HandleDeleteAccount(const std::string& username)
{
	std::string response;
	response = "SUCCES";
	m_users.DeleteAccount(username);
	return "SUCCES";
}

std::string Processor::UpdateLikes(const std::string& username, const int& postID)
{
	if (m_posts.AddLike(postID, username))
	{
		m_posts.UpdateFile();
		return "DIDNT";
	}
	else {
		m_posts.UpdateFile();
		return "LIKED";
	}
}

std::string Processor::UpdateDislikes(const std::string& username, const int& postID)
{
	if (m_posts.AddDislike(postID, username)) {
		m_posts.UpdateFile();
		return "DIDNT";
	}
	else {
		m_posts.UpdateFile();
		return "LIKED";
	}
}

std::string Processor::UpdateComments(const std::string& author, const std::string& text, const int& postID)
{
	m_posts.AddComment(postID, author, text);
	m_posts.UpdateFile();
	return "ADDED";
}

std::string Processor::SendKeywordIDs(const std::string& word)
{
	std::vector<int> postids = m_invertedIndex.GetPostIDBySearch(word);
	std::string toSend;
	for (auto postid : postids)
		toSend += std::to_string(postid) + ';';
	if (postids.empty())
		toSend = "NONE";
	return toSend;
}

std::string Processor::ProcessFeed(const std::string& username)
{
	std::string toSend;
	std::vector<int> postIDs;
	postIDs=m_Feed.GetFeedOrder(m_posts.GetPostsFromUserFriends(m_users.SendFriendsForUser(username)), username);
	for (const auto& postID : postIDs)
		toSend += std::to_string(postID) + ';';
	if (toSend == "")
		toSend = "NONE";
	return toSend;
}
