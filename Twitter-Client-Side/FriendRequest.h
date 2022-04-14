#pragma once
#include <iostream>
#include <ctime>


class FriendRequest
{
public:
	FriendRequest() = default;
	std::string Get_firstName() const;
	std::string Get_lastName() const;
	time_t Get_dateAndTime() const;
	void SetDateAndTime(const time_t& dateAndTime);

private:
	std::string m_firstName;
	std::string m_lastName;
	time_t m_dateAndTime;
};

