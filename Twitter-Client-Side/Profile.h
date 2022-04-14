#pragma once
#include <iostream>
#include <ctime>
#include <unordered_set>
#include <string>
#include <vector>
#include "Post.h"


class Profile
{
public:
	Profile();
	std::string GetM_firstName()const;
	std::string GetM_lastName()const;
	std::string GetM_nameID()const;
	bool GetM_photo()const;
	bool GetM_coverPhoto()const;
	time_t GetM_registerDate()const;
	int GetM_followersNumber()const;
	int GetM_followingsNumber()const;
	int GetM_tweetsNumber()const;
	void SetM_firstName(std::string firstName);
	void SetM_lastName(std::string lastName);
	void SetM_nameID(std::string nameID);
	void SetM_photo(bool photo);
	void SetM_coverPhoto(bool coverPhoto);
	void SetM_registerDate(time_t registerDate);
	Profile(const Profile& profile1);
	Profile(Profile&& profile2);
	Profile& operator =(const Profile& profile3);
	~Profile();

private:
	std::string m_firstName;
	std::string m_lastName;
	std::string m_nameID;
	bool m_photo;
	bool m_coverPhoto;
	time_t m_registerDate;
	std::unordered_set<std::string> m_followers;
	std::unordered_set<std::string> m_following;//same 
	std::vector<Post> m_tweets;
};