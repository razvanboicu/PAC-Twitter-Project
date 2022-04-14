#include "FriendRequest.h"

std::string FriendRequest::Get_firstName() const
{
	return m_firstName;
}

std::string FriendRequest::Get_lastName() const
{
	return m_lastName;
}

time_t FriendRequest::Get_dateAndTime() const 
{
	return m_dateAndTime;
}

void FriendRequest::SetDateAndTime(const time_t& dateAndTime)
{
	m_dateAndTime = dateAndTime;
}