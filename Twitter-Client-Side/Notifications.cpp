#include "Notifications.h"

Notifications::Notifications():
	m_newMessage(false),
	m_friendRequest(false),
	m_newTag(false),
	m_newComment(false),
	m_dateAndTime(0),
	m_notificationsNumber(0)
{
}

bool Notifications::GetNewMessage() const
{
	return m_newMessage;
}

bool Notifications::GetFriendRequest() const
{
	return m_friendRequest;
}

bool Notifications::GetNewTag() const
{
	return m_newTag;
}

bool Notifications::GetNewComment() const
{
	return m_newComment;
}

int Notifications::GetNotificationNumber() const
{
	return m_notificationsNumber;
}

void Notifications::SetNotificationNumber(const int& notificationsNumber)
{
	m_notificationsNumber = notificationsNumber;
}

void Notifications::NotificationsMessages()
{
	if (m_newMessage == true)
		std::cout << "You have a new message!";
	if (m_friendRequest == true)
		std::cout << "You have a friend request!";
	if (m_newTag == true)
		std::cout << "Someone tagged you!";
}

time_t Notifications::Get_dateAndTime() const
{
	return m_dateAndTime;
}

void Notifications::SetDateAndTime(const time_t& dateAndTime)
{
	m_dateAndTime = dateAndTime;
}
