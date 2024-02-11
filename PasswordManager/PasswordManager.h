#pragma once
#include <unordered_map>
#include "PasswordEntry.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

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
	void listEntries();
	bool isEdited();
	bool isValidEntry(const string&, const string&, const string&);
	void to_json(json& j);
	void from_json(const json& j);

};

