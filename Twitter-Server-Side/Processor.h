#pragma once
#include "Users.h"
#include "PostServerSide.h"
#include "Tokenize.h"
#include <fstream>
#include "Feed.h"
#include "InvertedIndex.h"

class Processor{
public:
	Processor();
	std::string ProcessRequest(const std::string& request);
	std::vector<std::string> TokenizeRequest(const std::string& request);
	std::string ProcessLogin(const std::string& id, const std::string& password);
	std::string ProcessRegister(const std::vector<std::string>& credentials);
	std::string ProcessUserSearch(const std::string& user, const std::string& currentUser);
	std::string ProcessSendFriendsList(const std::string& currentUser);
	std::string ProcessNewPost(const std::vector<std::string>& tokens);
	std::string ProcessFollowUpdate(const std::string& currentUser, const std::string& otherUser);
	std::string ProcessCheckingFollowStatus(const std::string& currentUser, const std::string& otherUser);
	std::string SendNumberOfPosts(const std::string& username);
	std::string SendPostToClient(const std::string& index);
	std::string SendPostWithoutInteractionsViaID(const std::string& ID);
	std::string SendPostWithInteractionsViaID(const std::string& ID);
	std::string HandleDeleteAccount(const std::string& username);
	std::string UpdateLikes(const std::string& username, const int& postID);
	std::string UpdateDislikes(const std::string& username, const int& postID);
	std::string UpdateComments(const std::string& author, const std::string& text, const int& postID);
	std::string SendKeywordIDs(const std::string& word);
	std::string ProcessFeed(const std::string& username);
	int CalculateLevenshteinDistance(const std::string& inputWord, const std::string& checkWord);
private:
	std::vector<std::pair<Post,int>> m_tempPosts;
	Users m_users;
	PostServerSide m_posts;
	Feed m_Feed;
	InvertedIndex m_invertedIndex;
};

