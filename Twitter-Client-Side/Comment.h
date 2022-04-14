#pragma once
#include "User.h"
#include "Profile.h"


class Comment{
public:
	void SetAuthor(Profile author);
	void SetComment(const std::string& comment);
	Comment& operator + (/*getAction clickOnLikeButton?*/);
	void SetHasReplies(const bool& yesOrNo);
private:
	Profile m_author;
	std::string m_comment;
	unsigned int m_likes;
	bool m_hasReplies;
	unsigned int m_nrOfReplies;
};

