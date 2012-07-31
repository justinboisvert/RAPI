#ifndef RedditPortable_RedditThread_h
#define RedditPortable_RedditThread_h
#include <iostream>

enum ThreadTypes {
    RTHREAD_SELF,
    RTHREAD_LINK,
    RTHREAD_IMAGE
};

class RedditThread {

    
public:
    RedditThread(std::string title_, std::string author_, std::string ID_,int comments_, std::string thumburl, std::string subreddit, int ups_, int downs_, int type_, std::string content_);
    std::string getTitle();
    std::string getAuthor();
    std::string getThumbURL();
    std::string getID();
    std::string getSubReddit();
    std::string getContent();
    int getType();
    int getCommentsTotal();
    int getUps();
    int getDowns();
private:
    int ups;
    int downs;
    std::string thumb;
    std::string title;
    std::string author;
    std::string ID;
    std::string subredd;
    int comments;
    int type;
    std::string content;
};

#endif
