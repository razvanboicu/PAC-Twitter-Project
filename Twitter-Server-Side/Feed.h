#pragma once
#include <queue>
#include <string>
#include "PostServerSide.h"

struct FeedInfo {
	FeedInfo(int p, int pp)
	{
		priority = p;
		PostID = pp;
	};
	int priority;
	int PostID;
	bool operator>(FeedInfo b) const {
		return priority > b.priority;
	}
	bool operator<(FeedInfo b) const {
		return priority < b.priority;
	}
};

class Feed
{
public:
	Feed();
	std::vector<int> GetFeedOrder(const std::vector<std::pair<Post, int>>& Posts, const std::string& username);
private:
	std::priority_queue<FeedInfo,std::vector<FeedInfo>,std::less<FeedInfo>> m_feedOrder;
};

