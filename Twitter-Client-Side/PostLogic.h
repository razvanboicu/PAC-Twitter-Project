#pragma once
#include "Logic.h"
#include "Post.h"

class PostLogic:public Logic
{
public:
	PostLogic(int ClientHandle);

	bool SendPostToServer(const std::string& username, const std::string& text, const int& PostID);

	bool SendLikeToServer(const std::string& username, const int& ID);
	bool SendDislikeToServer(const std::string& username, const int& ID);

	void SendCommentToServer(const std::string& author, const std::string& text, const int& ID);

	std::vector<std::pair<Post, int>> HandleFeed(const std::string& username);
	std::pair<Post, int> GetAllPostInfoViaID(const int& postID);

	int GetNumberOfPostsFromUser(const std::string& username);
	std::vector < std::pair<Post,int> > GetPostsFromUser(const int& size);

	std::vector<std::string> GetPostViaID(const int& postID);

};

