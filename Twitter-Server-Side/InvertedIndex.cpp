#include "InvertedIndex.h"
#include <sstream>
#include <iostream>

InvertedIndex::InvertedIndex()
{
}

void InvertedIndex::LoadInvertedIndex(const std::vector<std::string>& toAdd)
{
	int word_number = 0;
	int post_ID = 1;
	std::string post;
	for (const auto& posts : toAdd)
	{
		word_number = 0;
		std::stringstream ss(posts);
		while (ss >> post)
		{
			m_invertedMap[std::pair(post_ID, word_number++)] = post;
		}
		post_ID++;
	}
}

void InvertedIndex::AddPostToInvertedIndex(const std::string& post, const int& postID)
{
	std::stringstream ss(post);
	std::string add;
	int word_number = 0;
	while (ss >> add)
	{
		m_invertedMap[std::pair(postID, word_number++)] = post;
	}
}

std::vector<int> InvertedIndex::GetPostIDBySearch(const std::string& word)
{
	std::vector<int> toSend;
	for (const auto& mapElement : m_invertedMap)
	{
		if (mapElement.second == word)
			toSend.push_back(mapElement.first.first);
	}
	return toSend;
}

