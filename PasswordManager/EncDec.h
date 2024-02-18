#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

class EncDec
{
private:
	// Change this to include all letter + numbers + other characters you want to make code secure and ambigous, minimum of 5 characters
	std::string all_characters = "";
	int key = 5;
	//Encryption dictionaries
	std::unordered_map<char, char> encrypt_dict, decrypt_dict;


public:
	std::string encrypt(const std::string input);
	std::string decrypt(const std::string input);
	EncDec();
};

