#include "SubReddit.h"

SubReddit::SubReddit(std::string URL_){
	URL = URL_;
}

void SubReddit::setTitle(std::string title_){
	title = title_;
}
void SubReddit::setSubscribers(int subs){
	subscribers = subs;
}

void SubReddit::setMaturity(bool mat){
	mature = mat;
}

void SubReddit::setDescription(std::string desc){
	description = desc;
}

std::string SubReddit::getDescription(){
	return description;
}

std::string SubReddit::getTitle(){
	return title;
}

bool SubReddit::over18(){
	return mature;
}

int SubReddit::getSubscribers(){
	return subscribers;
}

std::string SubReddit::getURL(){
	return URL;
}