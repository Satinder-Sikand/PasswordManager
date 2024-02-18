#include "EncDec.h"



EncDec::EncDec() {
	// Create a dictionary for encryption
	for (int i = 0; i < all_characters.length(); i++) {
		encrypt_dict[all_characters[i]] = all_characters[(i + key) % all_characters.size()];
		decrypt_dict[all_characters[i]] = all_characters[(i - key) % all_characters.size()];// Create a dictionary for decryption (using the inverse key)

	}
}

std::string EncDec::encrypt(const std::string input)
{
	std::string encrypted = "";
	// Encrypt the plain text
	for (char c : input) {
		if (encrypt_dict.find(c) != encrypt_dict.end()) {
			encrypted += encrypt_dict[c];
		}
		else {
			encrypted += c; // Keep non-substitutable characters unchanged
		}
	}
	return encrypted;
}

std::string EncDec::decrypt(const std::string input)
{
	std::string decrypted = "";
	for (char c : input) {
		if (decrypt_dict.find(c) != decrypt_dict.end()) {
			decrypted += decrypt_dict[c];
		}
		else {
			decrypted += c; // Keep non-substitutable characters unchanged
		}
	}
	return decrypted;
}