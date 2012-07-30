#include "RedditThread.h"

RedditThread::RedditThread(std::string title_, std::string author_, std::string ID_, int comments_, std::string thumburl, std::string subreddit, int ups_, int downs_, int type_, std::string content_){
    title = title_;
    author = author_;
    ID = ID_;
    comments = comments_;
    thumb = thumburl;
    subredd = subreddit;
    ups = ups_;
    downs = downs_;
    type = type_;
    content = content_;
}

int RedditThread::getCommentsTotal(){
    return comments;
}

std::string RedditThread::getTitle(){
    return title;
}

std::string RedditThread::getAuthor(){
    return author;
}

std::string RedditThread::getID(){
    return ID;
}

std::string RedditThread::getThumbURL(){
    return thumb;
}

std::string RedditThread::getSubReddit(){
    return subredd;
}

int RedditThread::getUps(){
    return ups;
}

int RedditThread::getDowns(){
    return downs;
}

int RedditThread::getType(){
    return type;
}

std::string RedditThread::getContent(){
    return content;
}