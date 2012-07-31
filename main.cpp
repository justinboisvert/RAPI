#include <iostream>
#include "RAPI.h"
#include "application_storage.h"
int main(int argc, char *argv[]){
	RAPI::init("C++ reddit client test");
	std::cout << "initiliazed system..\n";
	if(hasLoggedIn()){
		std::string* info = getUserFromFile();
		RAPI::getUserByData(info[0], info[1]);
		std::cout << "You have " << RAPI::getUser()->getLinkKarma() << " link karma\n";
	}
	else {
		std::string user;
		std::cout << "Reddit Username: ";
		std::getline(std::cin,user);
		std::cout << "Reddit Password: ";
		std::string password;
		std::getline(std::cin,password);
		RAPI::login(user,password);
		writeToFile(RAPI::getUser());
		std::cout << "Hello, you have " << RAPI::getUser()->getKarma() << " karma.\n";
	}
	return 0;
}