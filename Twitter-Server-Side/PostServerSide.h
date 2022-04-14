#pragma once
#include "Tokenize.h"
#include <unordered_set>
#include <tuple>
#include <optional>



class Post
{
public:
	using Comments = std::pair<std::string, std::string>;
public:
	Post(std::string, std::string, std::string, int ID);
	Post(std::string, std::string, std::string, int, std::unordered_set<std::string>, std::unordered_set<std::string>, std::unordered_set<std::string>);

	std::string GetPostInfoAsString();
	std::string GetPostTextAsString();
	std::string GetCommentsAsString();
	std::string GetInteractionsAsString();

	std::string GetInfoForClient();

	void AddNewComment(const std::string& author, const std::string& text);
	bool AddNewLike(const std::string& whoLiked);
	bool AddNewDislike(const std::string& whodisliked);
	void AddNewRetweet(const std::string& whoRT);

	bool HasInteracted(const std::string& username) const;

	std::string GetUsername() const;

private:
	std::string m_author;
	std::string m_text;
	std::string m_timePosted;
	std::unordered_set<std::string> m_likes;
	std::unordered_set<std::string> m_dislikes;
	std::unordered_set<std::string> m_retweets;
	std::vector<Comments> m_comments;
	std::optional<int> m_retweetedPost;
};

class PostServerSide
{
public:
	using PostWithID = std::pair<Post, int>;
public:
	PostServerSide();

	void LoadPostsFromFile();
	void LoadCommentsFromFile();
	void LoadLikesAndDislikesFromFile();

	std::vector<std::string> GetPostText() const;
	int GetNumberOfPosts() const;
	void AddNewPost(std::tuple<std::string, std::string, std::string, int>);
	void AddComment(const int& PostID, const std::string& author, const std::string& text);
	bool AddLike(const int& PostID, const std::string& whoLiked);
	bool AddDislike(const int& PostID, const std::string& whoDisliked);
	void AddRetweet(const int& PostID, const std::string& whoRT);
	std::vector<PostWithID> GetPostsFromUser(std::string username) const;
	std::vector<PostWithID> GetPostsFromUserFriends(const std::unordered_set<std::string>& username) const;
	PostWithID GetPostViaID(const int& ID) const;
	void UpdateFile();
private:
	std::vector<PostWithID> m_posts;
};

