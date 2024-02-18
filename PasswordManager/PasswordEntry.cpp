#include "PasswordEntry.h"
PasswordEntry::PasswordEntry(const string& username, const string& password) {
    //this->website = website;
    this->username = username;
    this->password = password;
    // Initialize other private members if needed
}

PasswordEntry::PasswordEntry(string& username, string& password) {
    this->username = username;
    this->password = password;
    // Initialize other private members if needed
}

string PasswordEntry::getPassword() const {
    return password;
}

string PasswordEntry::getUsername() const{
    return username;
}

//string PasswordEntry::getWebsite() const{
//    return website;
//}

void PasswordEntry::setPassword(string& password) {
    this->password = password;
}

void PasswordEntry::setUsername(string& username) {
    this->username = username;
}

//void PasswordEntry::setWebsite(string& website) {
//    this->website = website;
//}
