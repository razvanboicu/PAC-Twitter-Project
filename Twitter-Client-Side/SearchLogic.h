#pragma once
#include "Logic.h"
#include "Post.h"
#include "PostLogic.h"

class SearchLogic:
	public Logic
{
public:
	SearchLogic(int ClientHandle);
	std::vector<std::string> HandleUserSearch(const std::string& user, const std::string& currentUser);
	std::vector<std::pair<std::vector<std::string>, int>> HandleKeyWordSearch(const std::string& keyword);
};

