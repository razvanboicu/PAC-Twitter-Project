#pragma once
#include <string>
#include <list>
#include <ctime>
#include <cstdint>
#include <optional>
#include <vector>
#include <set>


class Post{
public:
	std::string GetAuthor() const;
	std::string GetPost() const;
	std::string GetTime() const;
	std::string GetRetweetedPostAuthor();
	void SetRetweetPostInfo(std::pair<std::string, std::string> info);
	std::pair<std::string, std::string> GetRetweetedPostInfo();
	bool HasARetweet();
	void SetIDToRetweet(const int& PostID);
	int GetIDToRetweet();
	std::vector<std::pair<std::string, std::string>> GetComments();

	unsigned int GetLikes() const;
	unsigned int GetDislikes() const;
	unsigned int GetRetweets() const;
	unsigned int GetNumberOfComments() const;

	void AddComment(const std::string& author, const std::string& message);
	void SetAuthor(std::string author);
	void SetTime(std::string time);
	void SetPost(std::string post);
	void SetLikes(const int& like);
	void SetDislikes(const int& dislikes);
	void SetRetweets(const int& retweets);
private:
	std::vector <std::pair<std::string,std::string>> m_comments;
	std::string m_author;  
	std::string m_time;
	std::string m_thePost;
	uint16_t m_retweets;
	uint16_t m_likes;
	uint16_t m_dislikes;
	std::optional<int> m_IDtoRetweet;
	std::optional<std::pair<std::string, std::string>> m_RetweetedPostInfo;
};

