#include "RedditUser.h"

RedditUser::RedditUser(std::string username_, std::string cookie_, std::string modHash_){
    username = username_;
    cookie = cookie_;
    modHash = modHash_;
}

int RedditUser::getKarma(){
    return karma;
}

int RedditUser::getLinkKarma(){
    return lkarma;
}

bool RedditUser::hasNewMail(){
    return hasMail;
}

bool RedditUser::isModerator(){
    return isMod;
}

std::string RedditUser::getCookie(){
    return cookie;
}

std::string RedditUser::getModHash(){
    return modHash;
}

std::string RedditUser::getUserName(){
    return username;
}

void RedditUser::setKarma(int karm){
    karma = karm;
}

void RedditUser::setLinkKarma(int karml){
    lkarma = karml;
}

void RedditUser::setMailStatus(bool has){
    hasMail = has;
}

void RedditUser::setMod(bool ismod){
    isMod = ismod;
}