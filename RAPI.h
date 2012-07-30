#ifndef RedditPortable_RAPI_h
#define RedditPortable_RAPI_h
#include "CurlRetrieve.h"
#include "RedditUser.h"
#include "RedditThread.h"
#include "json.h"
#include "SubReddit.h"
#include <iostream>
#include <vector>
#include <sstream>

class RAPI {
public:
    static void init(std::string agent);
    static bool login(std::string username, std::string password);
    static std::vector<SubReddit*> getSubscriptions();
    static std::vector<RedditThread*> getLatestThreads(std::string subreddit);
    static RedditUser* getUser();
    static bool getUserByData(std::string cookie, std::string modhash);
    static bool userLoggedIn();
    static void logout();
    static void updateUserInfo();
    static void submitLink(std::string title, std::string link, std::string subreddit);
    static void submitStory(std::string title, std::string body, std::string subreddit);
    
private:
    static CurlRetrieve* httpStream;
    static RedditUser* user;
    static Json::Reader* reader;
    static bool userlogin;
        
};
#endif
