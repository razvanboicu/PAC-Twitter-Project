#include "PostServerSide.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <array>
#include <Logger/Logger.h>


using PostWithID = std::pair<Post, int>;

PostServerSide::PostServerSide()
{
}

void PostServerSide::LoadPostsFromFile()
{
	//Posts: author;text;time;ID to retweeted post(0 if none)|(end of post object)
	std::ifstream fin("posts.txt");
	std::string post;
	while (std::getline(fin >> std::ws, post, '|'))
	{
		std::vector<std::string> tokens = Tokenize::TokenizeString(post);
		if (tokens.size() == 4)
		{
			m_posts.push_back(std::make_pair(Post(tokens[0], tokens[1], tokens[2], std::stoi(tokens[3])), GetNumberOfPosts() + 1));
		}
	}
	fin.close();
}

void PostServerSide::LoadCommentsFromFile()
{
	std::ifstream fin("comments.txt");
	//Comments format:Post ID;Author;Text|
	std::string comment;
	while (std::getline(fin >> std::ws, comment, '|'))
	{
		std::vector<std::string> tokens = Tokenize::TokenizeString(comment);
		int aindex = 1;
		int cindex = 2;
		while (aindex < tokens.size() - 1 && tokens.size() != 1)
		{
			AddComment(std::stoi(tokens[0]), tokens[aindex], tokens[cindex]);
			aindex += 2;
			cindex += 2;
		}
	}
}

void PostServerSide::LoadLikesAndDislikesFromFile()
{
	//Likes dislikes retweets format: post ID;no of likes;dislikes;retweets;who liked..|(end of object)
	std::ifstream fin("likesdislikesrt.txt");
	std::string PostInteractions;
	while (std::getline(fin >> std::ws, PostInteractions, '|'))
	{
		std::vector<std::string> tokens = Tokenize::TokenizeString(PostInteractions);
		if (tokens.size() > 3)
		{
			int PostID = std::stoi(tokens[0]);
			int index = 4;
			for (int i = 0; i < std::stoi(tokens[1]); i++)
				AddLike(PostID, tokens[index++]);
			for (int i = 0; i < std::stoi(tokens[2]); i++)
				AddDislike(PostID, tokens[index++]);
			for (int i = 0; i < std::stoi(tokens[3]); i++)
				AddRetweet(PostID, tokens[index++]);
		}
	}
}

std::vector<std::string> PostServerSide::GetPostText() const
{
	std::vector<std::string> toSend;
	for (auto post : m_posts)
		toSend.push_back(post.first.GetPostTextAsString());
	return toSend;
}

int PostServerSide::GetNumberOfPosts() const
{
	return m_posts.size();
}

void PostServerSide::AddNewPost(std::tuple<std::string, std::string, std::string, int> p)
{
	std::ofstream out("logs.txt", std::ios::app);
	Logger logger(out);
	const auto& [author, text, time, ID] = p;
	logger.Log(Logger::Level::Info, author, " added a post\n");
	m_posts.push_back(std::make_pair(Post(author, time, text, ID), GetNumberOfPosts() + 1));
	UpdateFile();
}

void PostServerSide::AddComment(const int& PostID, const std::string& author, const std::string& text)
{
	std::ofstream out("logs.txt", std::ios::app);
	Logger logger(out);
	logger.Log(Logger::Level::Info, author, " added a comm\n");
	if (author != "" && text != "")
		m_posts[PostID - 1].first.AddNewComment(author, text);
}

bool PostServerSide::AddLike(const int& PostID, const std::string& whoLiked)
{
	std::ofstream out("logs.txt", std::ios::app);
	Logger logger(out);
	logger.Log(Logger::Level::Info, whoLiked, " liked a post\n");
	return m_posts[PostID - 1].first.AddNewLike(whoLiked);
}

bool PostServerSide::AddDislike(const int& PostID, const std::string& whoDisliked)
{
	std::ofstream out("logs.txt", std::ios::app);
	Logger logger(out);
	logger.Log(Logger::Level::Info, whoDisliked, " disliked a post\n");
	return m_posts[PostID - 1].first.AddNewDislike(whoDisliked);
}

void PostServerSide::AddRetweet(const int& PostID, const std::string& whoRT)
{
	std::ofstream out("logs.txt", std::ios::app);
	Logger logger(out);
	logger.Log(Logger::Level::Info, whoRT, " retweeted a post\n");
	m_posts[PostID - 1].first.AddNewRetweet(whoRT);
}

std::vector<PostWithID> PostServerSide::GetPostsFromUser(std::string username) const
{
	std::vector<PostWithID> PostsUser;
	for (int i = 0; i < m_posts.size(); i++)
	{
		if (username == m_posts[i].first.GetUsername())
		{
			PostsUser.push_back(m_posts[i]);
		}
	}
	return PostsUser;
}

std::vector<PostWithID> PostServerSide::GetPostsFromUserFriends(const std::unordered_set<std::string>& usernames) const
{
	std::vector<PostWithID> toSend;
	std::vector<PostWithID> temp;
	for (const auto& user : usernames)
	{
		temp = GetPostsFromUser(user);
		for (auto tempElement : temp)
			toSend.push_back(tempElement);
	}
	return toSend;
}

PostWithID PostServerSide::GetPostViaID(const int& ID) const
{
	return m_posts[ID - 1];
}

void PostServerSide::UpdateFile()
{
	std::fstream fout("posts.txt", std::ios::trunc | std::ios::out);
	std::fstream fout2("comments.txt", std::ios::trunc | std::ios::out);
	std::fstream fout3("likesdislikesrt.txt", std::ios::trunc | std::ios::out);
	for (auto post : m_posts)
	{

		fout << post.first.GetPostInfoAsString() << '\n';
		fout2 << std::to_string(post.second) + post.first.GetCommentsAsString() << '\n';
		fout3 << std::to_string(post.second) + ';' + post.first.GetInteractionsAsString() << '\n';
	}
	fout.close();
	fout2.close();
	fout3.close();
}

Post::Post(std::string author, std::string text, std::string time, int ID) :
	m_author(author),
	m_timePosted(time),
	m_text(text)
{
	if (ID != 0)
		m_retweetedPost.emplace(ID);
}

Post::Post(std::string author, std::string time, std::string text, int rt, std::unordered_set<std::string> likes, std::unordered_set<std::string> dislikes, std::unordered_set<std::string> retweets)
{
}

std::string Post::GetPostInfoAsString()
{
	std::string toReturn;
	toReturn = m_author + ';' + m_text + ';' + m_timePosted + ';';
	if (m_retweetedPost.has_value())
		toReturn += std::to_string(m_retweetedPost.value()) + '|';
	else
		toReturn += "0|";
	return toReturn;
}

std::string Post::GetPostTextAsString()
{
	return m_timePosted;
}

std::string Post::GetCommentsAsString()
{
	std::string toReturn;
	for (const auto& comment : m_comments)
		toReturn += ';' + comment.first + ";" + comment.second;
	toReturn += '|';
	return toReturn;
}


std::string Post::GetInteractionsAsString()
{
	std::string toReturn;
	toReturn += std::to_string(m_likes.size());
	toReturn += ';' + std::to_string(m_dislikes.size());
	toReturn += ';' + std::to_string(m_retweets.size());
	for (auto like : m_likes)
		toReturn += ';' + like;
	for (auto dislike : m_dislikes)
		toReturn += ';' + dislike;
	for (auto retweet : m_retweets)
		toReturn += ';' + retweet;
	toReturn += '|';
	return toReturn;
}

std::string Post::GetInfoForClient()
{
	//Format is: author;time;text;nrlikes;dislikes;retweets;authorcomment;comment;.....
	std::string toSend;
	toSend = m_author + ';' + m_timePosted + ';' + m_text + ';';
	if (m_retweetedPost.has_value())
		toSend += std::to_string(m_retweetedPost.value()) + ';';
	else
		toSend += "0;";
	toSend += std::to_string(m_likes.size()) + ';' + std::to_string(m_dislikes.size()) + ';' + std::to_string(m_retweets.size()) + ';' + std::to_string(m_comments.size());
	for (auto comment : m_comments)
		toSend += ";" + comment.first + ';' + comment.second;
	return toSend;
}



void Post::AddNewComment(const std::string& author, const std::string& text)
{
	std::pair<std::string, std::string> p(author, text);
	m_comments.push_back(p);
}

bool Post::AddNewLike(const std::string& whoLiked)
{
	if (m_likes.find(whoLiked) == m_likes.end())
		m_likes.insert(whoLiked);
	else m_likes.erase(whoLiked);
	if (m_dislikes.find(whoLiked) == m_dislikes.end() && !m_dislikes.empty())
		return true;
	else
	{
		m_dislikes.erase(whoLiked);
		return false;
	}
}

bool Post::AddNewDislike(const std::string& whodisliked)
{
	if (m_dislikes.find(whodisliked) == m_dislikes.end())
		m_dislikes.insert(whodisliked);
	else m_dislikes.erase(whodisliked);
	if (m_likes.find(whodisliked) == m_likes.end() && !m_likes.empty())
		return true;
	else
	{
		m_likes.erase(whodisliked);
		return false;
	}
}

void Post::AddNewRetweet(const std::string& whoRT)
{
	m_retweets.insert(whoRT);
}

bool Post::HasInteracted(const std::string& username) const
{
	if (m_likes.find(username) != m_likes.end())
		return true;
	if (m_dislikes.find(username) != m_dislikes.end())
		return true;
	if (m_retweets.find(username) != m_retweets.end())
		return true;
	return false;
}

std::string Post::GetUsername() const
{
	return m_author;
}
