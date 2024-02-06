#pragma once
#include <unordered_map>
#include "PasswordEntry.h"
#include <iostream>
#include <fstream>


class PasswordManager
{
private:
	unordered_map<string, vector<PasswordEntry>> sitemap;
	string fileName;
public:
	PasswordManager();
	void loadFromJSON(), saveToJSON(), addEntry(const PasswordEntry& entry);
	void setSiteMap(), setFileName();
	unordered_map<string, vector<PasswordEntry>> getSiteMap();
	string setFileName(string& filename);
	void listEntries();

};

