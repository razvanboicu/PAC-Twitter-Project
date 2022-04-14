#include "Profile.h"

Profile::Profile() :
    m_nameID("-"),
    m_firstName("-"),
    m_lastName("-"),
    m_photo(false),
    m_coverPhoto(false),
    m_registerDate(0),
    m_followers(0),
    m_following(0),
    m_tweets(0)
{
}

std::string Profile::GetM_firstName()const
{
    return m_firstName;
}

std::string Profile::GetM_lastName()const
{
    return m_lastName;
}

std::string Profile::GetM_nameID()const
{
    return m_nameID;
}

bool Profile::GetM_photo()const
{
    return false;//return true daca am poza de profil, return false daca nu am
}

bool Profile::GetM_coverPhoto()const
{
    return false;//la fel ca la GetM_photo
}

time_t Profile::GetM_registerDate()const
{
    return m_registerDate;
}

int Profile::GetM_followersNumber()const
{
    return m_followers.size();
}

int Profile::GetM_followingsNumber() const
{
    return m_following.size();
}

int Profile::GetM_tweetsNumber() const
{
    return m_tweets.size();
}

void Profile::SetM_firstName(std::string firstName)
{
    m_firstName = firstName;
}

void Profile::SetM_lastName(std::string lastName)
{
    m_lastName = lastName;
}

void Profile::SetM_nameID(std::string nameID)
{
    m_nameID = nameID;
}

void Profile::SetM_photo(bool photo)
{
    m_photo = photo;
}

void Profile::SetM_coverPhoto(bool coverPhoto)
{
    m_coverPhoto = coverPhoto;
}

void Profile::SetM_registerDate(time_t registerDate)
{
    m_registerDate = registerDate;
}

Profile::Profile(const Profile& profile1)
{
    *this = profile1;
}

Profile::Profile(Profile&& profile2)
{
    *this = std::move(profile2);
}

Profile& Profile::operator=(const Profile& profile3)
{
    this->m_firstName = profile3.m_firstName;
    this->m_lastName = profile3.m_lastName;
    this->m_nameID = profile3.m_nameID;
    this->m_registerDate = profile3.m_registerDate;
    this->m_followers = profile3.m_followers;
    this->m_following = profile3.m_following;
    this->m_tweets = profile3.m_tweets;
    this->m_photo = profile3.m_photo;
    this->m_coverPhoto = profile3.m_coverPhoto;
    
    return *this;
}

Profile::~Profile()
{
    delete& m_followers;
    delete& m_following;
    delete& m_tweets;
    delete& m_registerDate;
    delete& m_firstName;
    delete& m_lastName;
    delete& m_nameID;
    delete& m_photo;
    delete& m_coverPhoto;
}

