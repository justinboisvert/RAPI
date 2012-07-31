#ifndef SUBREDDIT_H
#define SUBREDDIT_H
#include <iostream>
class SubReddit {
public:
	SubReddit(std::string URL_);
	void setTitle(std::string title_);
	void setSubscribers(int subs);
	void setMaturity(bool mat);
	void setDescription(std::string desc);
	std::string getDescription();
	int getSubscribers();
	bool over18();
	std::string getURL();
	std::string getTitle();
private:
	std::string URL;
	std::string title;
	std::string description;
	bool mature;
	int subscribers;

};
#endif