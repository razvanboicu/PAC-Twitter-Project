#pragma once
#include "Logic.h"
class UserLogic :
    public Logic
{
public:
    using Credentials = std::pair < std::string, std::string>;
    using RegisterCredentials = std::tuple<std::string, std::string, std::string, std::string, std::string>;
public:
    UserLogic(int ClientHandle);

    bool HandleLogin(const Credentials&);
    bool HandleRegister(const RegisterCredentials&);

    bool UpdateFollowStatus(const std::string& currentUser, const std::string& otherUser);
    bool CheckIfFollowing(const std::string& currentUser, const std::string& otherUser);
    bool DeleteAccount(const std::string& username);
    
    std::vector<std::string> GetFriendsListForUser(const std::string& username);
};

