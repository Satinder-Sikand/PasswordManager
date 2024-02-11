#pragma once
using namespace std;
#include <string>

class PasswordEntry
{
private:
	string username;
	string password;
	string website;

public:
	PasswordEntry(string& website, string& username, string& password);
	PasswordEntry(const string& website, const string& username, const string& password);
	string getUsername() const, getPassword() const, getWebsite() const;
	void setUsername(string& username), setPassword(string& password), setWebsite(string& website);
};

