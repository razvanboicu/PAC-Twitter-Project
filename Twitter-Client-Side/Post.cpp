#include "Post.h"
#include <iostream>
#include <sstream>

std::string Post::GetAuthor() const
{
    return m_author;
}

std::string Post::GetPost() const
{
    return m_thePost;
}

std::string Post::GetTime() const
{
    return m_time;
}

std::string Post::GetRetweetedPostAuthor()
{
    if (m_RetweetedPostInfo.has_value())
    {
        std::string ToSend;
        std::stringstream ss(m_RetweetedPostInfo.value().first);
        std::getline(ss, ToSend, ' ');
        return ToSend;
    }
}

void Post::SetRetweetPostInfo(std::pair<std::string, std::string> info)
{
    m_RetweetedPostInfo.emplace(info);
}

std::pair<std::string, std::string> Post::GetRetweetedPostInfo()
{
    return m_RetweetedPostInfo.value();
}

bool Post::HasARetweet()
{
    return m_RetweetedPostInfo.has_value();
}

void Post::SetIDToRetweet(const int& PostID)
{
    m_IDtoRetweet.emplace(PostID);
}

int Post::GetIDToRetweet()
{
    if (m_IDtoRetweet.has_value())
        return m_IDtoRetweet.value();
    else return 0;
}

std::vector<std::pair<std::string, std::string>> Post::GetComments()
{
    return m_comments;
}

unsigned int Post::GetLikes() const
{
    return m_likes;
}

unsigned int Post::GetDislikes() const
{
    return m_dislikes;
}

unsigned int Post::GetRetweets() const
{
    return m_retweets;
}

unsigned int Post::GetNumberOfComments() const
{
    return m_comments.size();
}

void Post::AddComment(const std::string& author, const std::string& message)
{
    m_comments.push_back(std::make_pair(author, message));
}

void Post::SetAuthor(std::string author)
{
    m_author = author;
}

void Post::SetTime(std::string time)
{
    m_time = time;
}

void Post::SetPost(std::string post)
{
    m_thePost = post;
}

void Post::SetLikes(const int& like)
{
    m_likes = like;
}

void Post::SetDislikes(const int& dislikes)
{
    m_dislikes = dislikes;
}

void Post::SetRetweets(const int& retweets)
{
    m_retweets = retweets;
}
