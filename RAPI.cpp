#include "RAPI.h"
//excessive comment
CurlRetrieve* RAPI::httpStream;
Json::Reader* RAPI::reader;
RedditUser* RAPI::user;
bool RAPI::userlogin;

RedditUser* RAPI::getUser(){
    return user;
}
void RAPI::init(std::string agent){
    httpStream = new CurlRetrieve();
    reader = new Json::Reader();
    httpStream->setAgent(agent);
    userlogin = false;
    user = NULL;
}

bool RAPI::login(std::string username, std::string password){
    httpStream->clearBuffer();
    if(username.size() < 1 || password.size() < 1){
        return false;
    }
    //log on through api and get the modhash and cookie session
    char buffer[100];
    sprintf(buffer,"user=%s&passwd=%s&api_type=json",username.c_str(),password.c_str());
    httpStream->targetURL("http://www.reddit.com/api/login");
    httpStream->setToPOST();
    httpStream->setFieldData(buffer);
    Json::Value root;
    reader->parse(httpStream->grabData(),root);
    if(root["json"]["errors"].size() > 0){
        return false;
    }
    std::string modhash = root["json"]["data"]["modhash"].asString();
    std::string cookie = root["json"]["data"]["cookie"].asString();
    user = new RedditUser(username, cookie, modhash);
    //with cookie and modhash set get info such as karma, mail , link karma and more
    httpStream->setToGET();
    httpStream->targetURL("http://www.reddit.com/api/me.json");
    httpStream->clearBuffer();
    httpStream->setCookie(cookie);
    httpStream->targetURL("http://www.reddit.com/api/me.json");
    std::string response = httpStream->grabData();
    reader->parse(response,root);
    bool hasMail = root["data"]["has_mail"].asBool();
    bool isMod = root["data"]["is_mod"].asBool();
    int linkKarma = root["data"]["link_karma"].asInt();
    int karma = root["data"]["comment_karma"].asInt();
    user->setKarma(karma);
    user->setMailStatus(hasMail);
    user->setLinkKarma(linkKarma);
    user->setMod(isMod);
    httpStream->clearBuffer();
    userlogin = true;
    return true;
}

bool RAPI::getUserByData(std::string cookie, std::string modhash){
    Json::Value root;
    httpStream->setToGET();
    httpStream->setCookie(cookie);
    httpStream->targetURL("http://www.reddit.com/api/me.json");
    reader->parse(httpStream->grabData(),root);
    if(root["json"]["errors"].size() > 0){
        return false;
    }
    std::string username = root["data"]["name"].asString();
    bool hasMail = root["data"]["has_mail"].asBool();
    bool isMod = root["data"]["is_mod"].asBool();
    int linkKarma = root["data"]["link_karma"].asInt();
    int karma = root["data"]["comment_karma"].asInt();
    user = new RedditUser(username,cookie,modhash);
    user->setKarma(karma);
    user->setMailStatus(hasMail);
    user->setLinkKarma(linkKarma);
    user->setMod(isMod);
    httpStream->clearBuffer();
    userlogin = true;
    return true;
}

void RAPI::updateUserInfo(){
    Json::Value root;
    httpStream->setToGET();
    httpStream->setCookie(user->getCookie());
    httpStream->targetURL("http://www.reddit.com/api/me.json");
    reader->parse(httpStream->grabData(),root);
    std::string username = root["data"]["name"].asString();
    bool hasMail = root["data"]["has_mail"].asBool();
    bool isMod = root["data"]["is_mod"].asBool();
    int linkKarma = root["data"]["link_karma"].asInt();
    int karma = root["data"]["comment_karma"].asInt();
    user->setKarma(karma);
    user->setMailStatus(hasMail);
    user->setLinkKarma(linkKarma);
    user->setMod(isMod);
    httpStream->clearBuffer();
}

void RAPI::submitLink(std::string title, std::string link, std::string subreddit){
    char fieldBuffer[1000];
    sprintf(fieldBuffer,"title=%s&url=%s&sr=%s&uh=%s&api_type=json&kind=link&renderstyle=html",title.c_str(),link.c_str(),subreddit.c_str(), user->getModHash().c_str());
    httpStream->setToPOST();
    httpStream->setCookie(user->getCookie());
    httpStream->setFieldData(fieldBuffer);
    httpStream->targetURL("http://www.reddit.com/api/submit");
    std::cout << httpStream->grabData() << "\n";
    httpStream->clearBuffer();
}

void RAPI::submitStory(std::string title, std::string body, std::string subreddit){
    char fieldBuffer[2000];
    sprintf(fieldBuffer,"title=%s&text=%s&sr=%s&uh=%s&api_type=json&kind=self&renderstyle=html",title.c_str(),body.c_str(),subreddit.c_str(), user->getModHash().c_str());
    httpStream->setToPOST();
    httpStream->setCookie(user->getCookie());
    httpStream->setFieldData(fieldBuffer);
    httpStream->targetURL("http://www.reddit.com/api/submit");
    std::cout << httpStream->grabData() << "\n";
    httpStream->clearBuffer();

}

std::vector<SubReddit*> RAPI::getSubscriptions(){
    std::vector<SubReddit*> subbers;
    httpStream->setToGET();
    httpStream->setCookie(user->getCookie());
    httpStream->targetURL("http://www.reddit.com/reddits/mine/.json");
    Json::Value root;
    reader->parse(httpStream->grabData(),root);
    const Json::Value subreddits = root["data"]["children"];
    for(int i = 0; i < subreddits.size(); i++){
        SubReddit *sb = new SubReddit(subreddits[i]["data"]["url"].asString());
        sb->setTitle(subreddits[i]["data"]["title"].asString());
        sb->setSubscribers(subreddits[i]["data"]["subscribers"].asInt());
        sb->setMaturity(subreddits[i]["data"]["over18"].asBool());
        sb->setDescription(subreddits[i]["data"]["description"].asString());
        subbers.push_back(sb);
    }
    httpStream->clearBuffer();
    return subbers;
}

std::vector<RedditThread*> RAPI::getLatestThreads(std::string subreddit){
    std::vector<RedditThread*> thread_bucket;
    std::stringstream full_path;
    full_path << "http://www.reddit.com" << subreddit << ".json";
    httpStream->setToGET();
    httpStream->targetURL(full_path.str().c_str());
    Json::Value root;
    reader->parse(httpStream->grabData(),root);
    Json::Value threads = root["data"]["children"];
    for(int i = 0; i < threads.size(); i++){
        int type;
        bool is_self = threads[i]["data"]["is_self"].asBool();
        if(is_self){
            type = RTHREAD_SELF; 
        }
        else {
            type = RTHREAD_LINK;
        }
        RedditThread* thread = new RedditThread(
             threads[i]["data"]["title"].asString(),
             threads[i]["data"]["author"].asString(),
             threads[i]["data"]["id"].asString(),
             threads[i]["data"]["num_comments"].asInt(),
             threads[i]["data"]["thumbnail"].asString(),
             threads[i]["data"]["subreddit"].asString(),
             threads[i]["data"]["ups"].asInt(),
             threads[i]["data"]["downs"].asInt(),
             type,
             threads[i]["data"]["selftext"].asString()
        );
        thread_bucket.push_back(thread);
    }
    httpStream->clearBuffer();
    return thread_bucket;
}

RedditUser* RAPI::retrieveCurrentUser()  {
    return user;
}
void RAPI::logout(){
    userlogin = false;
    delete user;
    user = NULL;
}

bool RAPI::userLoggedIn(){
    return userlogin;
}

