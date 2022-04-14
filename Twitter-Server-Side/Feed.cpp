#include "Feed.h"
#include <iostream>

Feed::Feed()
{
}

std::vector<int> Feed::GetFeedOrder(const std::vector<std::pair<Post,int>>& Posts, const std::string& username)
{
	std::vector<int> ToSend;
	int priority;
	for (auto post : Posts)
	{
		if (post.first.HasInteracted(username))
			priority = post.second + 2;
		else priority = post.second;
		m_feedOrder.push(FeedInfo(priority, post.second));
	}
	int size = m_feedOrder.size();
	for (int i = 0; i < size; i++)
	{
		ToSend.push_back(m_feedOrder.top().PostID);
		m_feedOrder.pop();
	}

	return ToSend;
}
