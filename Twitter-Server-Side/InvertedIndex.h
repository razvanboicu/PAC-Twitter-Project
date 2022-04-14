#pragma once
#include <map>
#include <string>
#include <vector>


class InvertedIndex
{
	using WordPair = std::pair<int, int>;
public:
	InvertedIndex();
	void LoadInvertedIndex(const std::vector<std::string>& toAdd);

	void AddPostToInvertedIndex(const std::string& post, const int& postID);

	std::vector<int> GetPostIDBySearch(const std::string& word);

private:
	std::map<WordPair,std::string> m_invertedMap;
};

