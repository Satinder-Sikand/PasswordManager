#pragma once
#include "PasswordEntry.h"
#include "json.hpp"
#include "EncDec.h"
#include <iostream>
#include <fstream>
#include <sstream>
#define endl std::endl
#define unordered_map std::unordered_map
#define vector std::vector
#define getline std::getline
#define cin std::cin

using json = nlohmann::json;
auto& cout = std::cout;

class PasswordManager
{
private:
	unordered_map<string, vector<PasswordEntry>> sitemap;
	string fileName;
	bool changeInfo = false;
public:
	PasswordManager();
	void loadFromJSON(), saveToJSON(), addEntry(const string& website, const string& username, const string& password);
	void setSiteMap(), setFileName();
	unordered_map<string, vector<PasswordEntry>> getSiteMap();
	string setFileName(string& filename);
	void listEntries(), listAllWebEntryNames(), listFromWeb(const string&), listAllWithName(const string&);
	bool isEdited();
	bool isValidEntry(const string&, const string&, const string&);
	void to_json(json& j);
	void editWeb(string& oldweb, string& newweb);
	void editUsername(string& website, string& username, string& newusername);
	void editPassword(string& website, string& username, string& password, string& newpassword);
	void deleteEntry(string& website, string& username, string& password);
	void deleteWebsite(string& website);
	void from_json(const json& j);

};

