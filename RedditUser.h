#ifndef RedditPortable_RedditUser_h
#define RedditPortable_RedditUser_h
#include <iostream>
class RedditUser {
public:
    RedditUser(std::string username, std::string cookie, std::string modHash);
    std::string getCookie();
    std::string getModHash();
    std::string getUserName();
    void setKarma(int karm);
    void setLinkKarma(int karml);
    void setMailStatus(bool has);
    void setMod(bool ismod);
    bool hasNewMail();
    bool isModerator();
    int getKarma();
    int getLinkKarma();
private:
    std::string cookie;
    std::string modHash;
    std::string username;
    bool hasMail;
    bool isMod;
    int karma;
    int lkarma;
    
};

#endif
