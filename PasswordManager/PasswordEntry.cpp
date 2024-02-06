#include "PasswordEntry.h"
PasswordEntry::PasswordEntry(std::string& website, std::string& username, std::string& password) {
    this->website = website;
    // Initialize other private members if needed
}

string PasswordEntry::getPassword() const {
    return password;
}

string PasswordEntry::getUsername() const{
    return username;
}

string PasswordEntry::getWebsite() const{
    return website;
}

void PasswordEntry::setPassword(string& password) {
    this->password = password;
}

void PasswordEntry::setUsername(string& username) {
    this->username = username;
}

void PasswordEntry::setWebsite(string& website) {
    this->website = website;
}
