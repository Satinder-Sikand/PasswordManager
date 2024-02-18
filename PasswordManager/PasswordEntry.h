#pragma once
//using namespace std;
#include <string>

using string = std::string;

class PasswordEntry
{
private:
	string username;
	string password;
	string website;

public:
	PasswordEntry( string& username, string& password);
	PasswordEntry(const string& username, const string& password);
	string getUsername() const, getPassword() const;
	void setUsername(string& username), setPassword(string& password);
};

