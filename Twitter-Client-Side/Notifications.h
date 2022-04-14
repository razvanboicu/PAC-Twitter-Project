#pragma once
#include <iostream>


class Notifications
{
public:
	Notifications();
	bool GetNewMessage() const;
	bool GetFriendRequest() const;
	bool GetNewTag() const;
	bool GetNewComment() const;
	int GetNotificationNumber() const;
	void SetNotificationNumber(const int& notificationsNumber);
	void NotificationsMessages();
	time_t Get_dateAndTime() const;
	void SetDateAndTime(const time_t& dateAndTime);

private:
	bool m_newMessage;
	bool m_friendRequest;
	bool m_newTag;
	bool m_newComment;
	int m_notificationsNumber;
	time_t m_dateAndTime;
};

