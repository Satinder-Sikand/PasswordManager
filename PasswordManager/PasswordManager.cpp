// PasswordManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "PasswordManager.h"

void help() {
    cout << "-help -- Returns a list of commands that can be used by the system." << endl <<
        "-save -- Saves all current changes made to the system" << endl <<
        "-add {Website} {Username} {Password} -- Add a new username and password entry to the database. Add in specified order or be prompted later." << endl <<
        "-exit -- Close the app" << endl <<
        "-listAll -- Returns a table/list of all current websites and their saved user data" << endl <<
        "-listWeb {Website} -- Returns a table/list of all entries under the specified website. Add in specified website or be prompted later." << endl <<
        "-listWebNames -- Returns a table/list of all the websites in the database." << endl <<
        "-listNames {Username} Returns a table/list of all matching entries with the given username. Add the username as shown or be prompted later." << endl <<
        "-editWeb {Original Website} {New Website} -- Change the name of an existing website. Add in specified order or be prompted later" << endl <<
        "-editUsername {Website} {Original Username} {New Username} -- Change the name of an existing username. Add in specified order or be prompted later" << endl << 
        "-editPassword {Website} {Username} {Original Password} {New Password} -- Change the name of an existing password. Add in specified order or be prompted later" << endl <<
        "-deleteWeb {Website} -- Delete a website and all associated entries. Add in specified order or be prompted later" << endl <<
        "-deleteEntry {Website} {Username} {Password} -- Delete an existing entry. Add in specified order or be prompted later" << endl <<
        endl << endl;
}

vector<string> splitResponse(string& response, vector<string>& split) {
    cout << "--";
    getline(cin, response);
    system("cls");
    size_t position = 0;
    string token = " ";
    split.clear();
    while ((position = response.find(token)) != string::npos) {
        split.push_back(response.substr(0, position));
        response.erase(0, position + token.length());
    }
    split.push_back(response);
    return split;
}

bool checkValidInput(const string& inputstring) {
    //check if empty
    if (inputstring.empty()) {
        cout << "Error: Input cannot be empty." << endl;
        return false;
    }
    else if (inputstring.size() == 1 && inputstring[0]==' ') {
        cout << "Error: Input cannot be a single space." << endl;
        return false;
    }
    return true;
}

//Only valid for indexes 1-3
string getArguementType(int index) {
    switch (index)
    {
    case 1:
        return "Website";
    case 2:
        return "Username";
    case 3:
        return "Password";
    default:
        return "Website";
    }
}

int main()
{
    PasswordManager manager = PasswordManager();
    help();

    //Get User input
    string response;
    vector<string> resparr = vector<string>();
    splitResponse(response, resparr);
    // Loop until user says they want to leave
        while (true) {
            if (resparr.at(0) == "exit()") {
                // Check if changes made need to be saved
                if (manager.isEdited()) {
                    cout << "Changes you made may not be saved. Do you want to save before leaving? (y/n/c) " << endl;
                    string leaveres;
                    getline(cin, leaveres);
                    // Loop for valid input
                    while (true) {
                        // Save changes
                        if (leaveres == "y") {
                            manager.saveToJSON();
                            cout << "Saved" << endl;
                            exit(0);
                        } //Don't save
                        else if (leaveres == "n")
                            exit(0);
                        else if (leaveres == "c" || leaveres == "back") { //Cancel the exit and continue
                            splitResponse(response, resparr);
                            break;
                        }
                        else {
                            cout << "Invalid command. Changes you made may not be saved. Do you want to save before leaving? (y/n/c) " << endl;
                            getline(cin, leaveres);
                        }
                    }
                }
                else
                    exit(0);
            }
            else if (resparr.at(0) == "help") {
                // Print commands
                help();
                splitResponse(response, resparr);
            }
            else if (resparr.at(0) == "listAll") {
                // List all entries
                manager.listEntries();
                splitResponse(response, resparr);
            }
            else if (resparr.at(0) == "listWeb")
            {
                // List all entries with the specified website
                if (resparr.size() > 2) {
                    cout << "listWeb takes only one argument. {website} Using first only." << endl;
                }
                if (resparr.size() == 1) {
                    cout << "Enter " + getArguementType(1) + ": ";
                    string temp;
                    getline(cin, temp);
                    resparr.push_back(temp);
                    cout << endl;
                }
                while (!checkValidInput(resparr.at(1)))
                {
                    cout << "Enter " + getArguementType(1) + " again: ";
                    getline(cin, resparr.at(1));
                    cout << endl;
                }
                manager.listFromWeb(resparr.at(1));
                splitResponse(response, resparr);
            }
            else if (resparr.at(0) == "listWebNames")
            {
                // List all website names
                manager.listAllWebEntryNames();
                splitResponse(response, resparr);
            }
            else if (resparr.at(0) == "listNames") {
                // List all the names that matches user input
                if (resparr.size() > 2) {
                    cout << "listNames takes only one argument. {username} Using first only." << endl;
                }
                if (resparr.size() == 1) {
                    cout << "Enter " + getArguementType(2) + ": ";
                    string temp;
                    getline(cin, temp);
                    resparr.push_back(temp);
                    cout << endl;
                }
                while (!checkValidInput(resparr.at(1)))
                {
                    cout << "Enter " + getArguementType(2) + " again: ";
                    getline(cin, resparr.at(1));
                    cout << endl;
                }
                manager.listAllWithName(resparr.at(1));
                splitResponse(response, resparr);
            }
            else if (resparr.at(0) == "add") {
                // Add new entry
                if (resparr.size() > 4) {
                    cout << "Add takes only three arguments. {website} {username} {password}. Using first three only." << endl;
                }
                vector<string*> arguements = vector<string*>();
                for (int i = 1; i < 4; i++) {
                    if (i < resparr.size()) {
                        while (!checkValidInput(resparr.at(i))) {
                            cout << "Enter " + getArguementType(i) + " again: ";
                            getline(cin, resparr.at(i));
                            cout << endl;
                        }
                        // use the address-of operator to get a pointer to the string
                        arguements.push_back(&resparr.at(i));
                    }
                    else {
                        // use a unique_ptr to manage the memory of the string
                        std::unique_ptr<string> temp = std::make_unique<string>();
                        cout << getArguementType(i) + ": ";
                        getline(cin, *temp);
                        while (!checkValidInput(*temp)) {
                            cout << "Enter " + getArguementType(i) + " again: ";
                            getline(cin, *temp);
                            cout << endl;
                        }
                        // use the release method to transfer the ownership of the pointer
                        arguements.push_back(temp.release());
                    }
                }
                cout << "Confirm new entry details (y/n = correct/incorrect, resubmit)." << endl << "Website: " + *arguements.at(0) 
                    << std::setw(30) << "Username: " + *arguements.at(1) <<
                    std::setw(30) << "Password: " + *arguements.at(2) << endl;
                string resp;
                getline(cin, resp);
                while (resp != "y" && resp != "n") {
                    cout << "Invalid command. Please use (y/n)." << endl;
                    getline(cin, resp);
                }
                if (resp == "n") {
                    resparr.clear();
                    resparr.push_back("add");
                    continue;
                }
                manager.addEntry(*arguements.at(0), *arguements.at(1), *arguements.at(2));
                splitResponse(response, resparr);
            } 
            else if (resparr.at(0) == "editWeb") {
                // List all the names that matches user input
                if (resparr.size() > 3) {
                    cout << "editWeb takes only two arguments. {Old website} {New website} Using first two only." << endl;
                }
                vector<string*> arguements = vector<string*>();
                for (int i = 1; i < 3; i++) {
                    if (i < resparr.size()) {
                        while (!checkValidInput(resparr.at(i))) {
                            cout << "Enter " + getArguementType(1) + " again: ";
                            getline(cin, resparr.at(i));
                            cout << endl;
                        }
                        // use the address-of operator to get a pointer to the string
                        arguements.push_back(&resparr.at(i));
                    }
                    else {
                        // use a unique_ptr to manage the memory of the string
                        std::unique_ptr<string> temp = std::make_unique<string>();
                        cout << ((i == 1) ? "Old " : "New ") << getArguementType(1) + ": ";
                        getline(cin, *temp);
                        while (!checkValidInput(*temp)) {
                            cout << "Enter " + getArguementType(1) + " again: ";
                            getline(cin, *temp);
                            cout << endl;
                        }
                        // use the release method to transfer the ownership of the pointer
                        arguements.push_back(temp.release());
                    }
                }
                manager.editWeb(*arguements.at(0), *arguements.at(1));
                splitResponse(response, resparr);
            }
            else if (resparr.at(0) == "editPassword") {
                // List all the names that matches user input
                if (resparr.size() > 5) {
                    cout << "editWeb takes only four arguments. {Website} {Username} {Old password} {New password} Using first four only." << endl;
                }
                vector<string*> arguements = vector<string*>();
                for (int i = 1; i < 5; i++) {                        
                    int argtype = (i == 4) ? i : 3;
                    if (i < resparr.size()) {
                        while (!checkValidInput(resparr.at(i))) {
                            cout << "Enter " + getArguementType(argtype) + " again: ";
                            getline(cin, resparr.at(i));
                            cout << endl;
                        }
                        // use the address-of operator to get a pointer to the string
                        arguements.push_back(&resparr.at(i));
                    }
                    else {
                        // use a unique_ptr to manage the memory of the string
                        std::unique_ptr<string> temp = std::make_unique<string>();
                        string text [4] = {"", "", "Old ", "New "};
                        cout << text[i - 1] << getArguementType(argtype) + ": ";
                        getline(cin, *temp);
                        while (!checkValidInput(*temp)) {
                            cout << "Enter " + getArguementType(argtype) + " again: ";
                            getline(cin, *temp);
                            cout << endl;
                        }
                        // use the release method to transfer the ownership of the pointer
                        arguements.push_back(temp.release());
                    }
                }
                manager.editPassword(*arguements.at(0), *arguements.at(1), *arguements.at(2), *arguements.at(3));
                splitResponse(response, resparr);
            } 
            else if (resparr.at(0) == "editUsername") {
                // List all the names that matches user input
                if (resparr.size() > 4) {
                    cout << "editWeb takes only three arguments. {Website} {Old username} {New username} Using first three only." << endl;
                }
                vector<string*> arguements = vector<string*>();
                for (int i = 1; i < 4; i++) {
                    int argtype = (i == 1) ? i : 2;
                    if (i < resparr.size()) {
                        while (!checkValidInput(resparr.at(i))) {
                            cout << "Enter " + getArguementType(argtype) + " again: ";
                            getline(cin, resparr.at(i));
                            cout << endl;
                        }
                        // use the address-of operator to get a pointer to the string
                        arguements.push_back(&resparr.at(i));
                    }
                    else {
                        // use a unique_ptr to manage the memory of the string
                        std::unique_ptr<string> temp = std::make_unique<string>();
                        string text[3] = { "", "Old ", "New " };
                        cout << text[i - 1] << getArguementType(argtype) + ": ";
                        getline(cin, *temp);
                        while (!checkValidInput(*temp)) {
                            cout << "Enter " + getArguementType(argtype) + " again: ";
                            getline(cin, *temp);
                            cout << endl;
                        }
                        // use the release method to transfer the ownership of the pointer
                        arguements.push_back(temp.release());
                    }
                }
                manager.editUsername(*arguements.at(0), *arguements.at(1), *arguements.at(2));
                splitResponse(response, resparr);
            }
            else if (resparr.at(0) == "deleteWeb")
            {
                // List all entries with the specified website
                if (resparr.size() > 2) {
                    cout << "deleteWeb takes only one argument. {website} Using first only." << endl;
                }
                if (resparr.size() == 1) {
                    cout << "Enter " + getArguementType(1) + ": ";
                    string temp;
                    getline(cin, temp);
                    resparr.push_back(temp);
                    cout << endl;
                }
                while (!checkValidInput(resparr.at(1)))
                {
                    cout << "Enter " + getArguementType(1) + " again: ";
                    getline(cin, resparr.at(1));
                    cout << endl;
                }
                manager.deleteWebsite(resparr.at(1));
                splitResponse(response, resparr);
            }
            else if (resparr.at(0) == "deleteEntry") {
                // Add new entry
                if (resparr.size() > 4) {
                    cout << "deleteEntry takes only three arguments. {website} {username} {password}. Using first three only." << endl;
                }
                vector<string*> arguements = vector<string*>();
                for (int i = 1; i < 4; i++) {
                    if (i < resparr.size()) {
                        while (!checkValidInput(resparr.at(i))) {
                            cout << "Enter " + getArguementType(i) + " again: ";
                            getline(cin, resparr.at(i));
                            cout << endl;
                        }
                        // use the address-of operator to get a pointer to the string
                        arguements.push_back(&resparr.at(i));
                    }
                    else {
                        // use a unique_ptr to manage the memory of the string
                        std::unique_ptr<string> temp = std::make_unique<string>();
                        cout << getArguementType(i) + ": ";
                        getline(cin, *temp);
                        while (!checkValidInput(*temp)) {
                            cout << "Enter " + getArguementType(i) + " again: ";
                            getline(cin, *temp);
                            cout << endl;
                        }
                        // use the release method to transfer the ownership of the pointer
                        arguements.push_back(temp.release());
                    }
                }
                cout << "Confirm entry details (y/n = correct/incorrect, resubmit)." << endl << "Website: " + *arguements.at(0)
                    << std::setw(30) << "Username: " + *arguements.at(1) <<
                    std::setw(30) << "Password: " + *arguements.at(2) << endl;
                string resp;
                getline(cin, resp);
                while (resp != "y" && resp != "n") {
                    cout << "Invalid command. Please use (y/n)." << endl;
                    getline(cin, resp);
                }
                if (resp == "n") {
                    resparr.clear();
                    resparr.push_back("add");
                    continue;
                }
                manager.deleteEntry(*arguements.at(0), *arguements.at(1), *arguements.at(2));
                splitResponse(response, resparr);
            }
            // Save changes
            else if (resparr.at(0) == "save") {
                manager.saveToJSON();
                splitResponse(response, resparr);
            }
            else {
                // Not a valid command so repeat loop
                cout << resparr.at(0) << endl;
                cout << "Improper arguments. Check -help for list of commands." << endl;
                splitResponse(response, resparr);
            }

        }
}

PasswordManager::PasswordManager()
{
    fileName = "./Managerdb.txt";
    sitemap = unordered_map<string, vector<PasswordEntry>>();
    loadFromJSON();
}

bool PasswordManager::isEdited() {
    return this->changeInfo;
}

bool PasswordManager::isValidEntry(const string& website, const string& username, const string& password) {
    //check if the string is null or empty
    return true;
}

///////////////////////////////////////////////////////////////// LIST RELATED CODE ////////////////////////////

void PasswordManager::listEntries() 
{
    // Simple for loop to go through each website entry and print it
    for (auto item = sitemap.begin(); item != sitemap.end(); ++item) {
        cout << "Website: " << item->first << endl;
        
        for (PasswordEntry entry : item->second) {
            cout << std::setw(30) << "Username: " << entry.getUsername() << std::setw(30) << "Password: " << entry.getPassword()<< endl;
        }
    }
}

void PasswordManager::listAllWebEntryNames() {
    // Simple loop to print out all the website names
    for (auto item = sitemap.begin(); item != sitemap.end(); item++)
    {
        cout << item->first << endl;
    }
}

void PasswordManager::listFromWeb(const string& website) {
    unordered_map<string, vector<PasswordEntry>>::iterator webEntry = sitemap.find(website);
    // Check if there is any match
    if (webEntry == sitemap.end()) {
        // Ask user if we want a list of websites returned that contain their requested website name
        cout << "There are no records recorded with this website. Do you want to show a list of the websites that contain \""+website+"\"? (y/n): ";
        string ans;
        getline(cin, ans);
        // Loof for valid response
        while (ans != "y" && ans != "n") {
            cout << "Invalid command. Please answer with (y/n)." << endl;
            getline(cin, ans);
        }
        // No need to continue if they say no
        if (ans == "n") {
            return;
        }
        else {
            // Print containing websites
            for (webEntry = sitemap.begin(); webEntry != sitemap.end(); webEntry++) {
                if (webEntry->first == website)
                    cout << webEntry->first << endl;
            }
        }
    } else {
        // Print all entries that have the matching website
        for (PasswordEntry entry : webEntry->second) {
            cout << std::setw(30) << website << std::setw(30) << "Username: " << entry.getUsername() << std::setw(30) << "Password: " << entry.getPassword() << endl;
        }
    }
}

void PasswordManager::listAllWithName(const string& name) {
    // Temporary object to combine website name with entries to easily get the website
    struct WebEntry
    {
        const string website;
        const PasswordEntry entry;

        WebEntry(const string& website, const PasswordEntry& entry) : website(website), entry(entry) {};
    };
    vector<WebEntry> containsResults = vector<WebEntry>();
    cout << "Enter 1 to list only exact matches or 2 for matches that contain " + name + " in them (1/2): ";
    bool contains = true, exact = false;
    string line;
    // Determine whether we want exact matches only or contains matches
    while (getline(cin, line)) {
        try
        {
            if (line.size() > 1)
                throw 0;
            else if (line == "1")
                contains = false;
            else if (line == "2")
                contains = true;
            else
                throw 0;
            break;
        }
        catch (const std::exception&)
        {
            cout << "Enter 1 or 2 (1/2): ";
        }
    }
    // Loop through entries for matches
    cout << "Exact matches:" << endl;
    for (auto item = sitemap.begin(); item != sitemap.end(); ++item) {
        for (PasswordEntry entry : item->second) {
            // Print exact match if found
            if (entry.getUsername() == name) {
                exact = true;
                cout << std::setw(30) << item->first << std::setw(30) << "Username: " << entry.getUsername() << std::setw(30) << "Password: " << entry.getPassword() << endl;
            }
            else if (contains && entry.getUsername().find(name) != string::npos) {
                // Add contains match if found
                containsResults.emplace_back(item->first, entry);
            }
        }
    }
    if (!exact)
        cout << "There were no exact matches." << endl;
    if (contains) {
        // Print all contains matches
        cout << endl << "Containing matches:\n";
        if (containsResults.size() > 0)
            for (WebEntry entry : containsResults)
                cout << std::setw(30) << entry.website << std::setw(30) << "Username: " << entry.entry.getUsername() << std::setw(30) << "Password: " << entry.entry.getPassword() << endl;
        else
            cout << "There were no containing matches." << endl;
    }
}

///////////////////////////////////////////// EDIT RELATED CODE/////////////////////////////////////

void PasswordManager::addEntry(const string& website, const string& username, const string& password)
{
    try
    {
        // Check if the website name already exists
        unordered_map<string, vector<PasswordEntry>>::iterator item = sitemap.find(website);
        // If not exist then create new website key and initialze empty PasswordEntry list
        if (item == sitemap.end()) {
            vector<PasswordEntry> userarray = vector<PasswordEntry>();
            sitemap.emplace(website, userarray);
        }
        //Add the entry to the map
        sitemap.at(website).emplace_back(username, password);
        // Flag that content must be saved due to changes to map
        changeInfo = true;
        cout << "Changed Entry details!" << endl;
    }
    catch (const std::exception&)
    {
        cout << "There was a problem when adding. Please try again." << endl;
    }
}

void PasswordManager::editWeb(string& oldweb, string& newweb) {
    // check if the oldweb key exists in the map
    unordered_map<string, vector<PasswordEntry>>::iterator item = sitemap.find(oldweb);
    if (item != sitemap.end()) {
        // get the value associated with the oldweb key
        vector<PasswordEntry> value = item->second;
        // erase the oldweb key from the map
        sitemap.erase(item);
        // insert the newweb key and the value into the map
        sitemap.insert({ newweb, value });
        cout << "Changed " + oldweb + " to " + newweb << endl;
        //Flag that changes made to entries and must be saved
        changeInfo = true;
    }
    else {
        // handle the case when the oldweb key is not found, e.g. throw an exception
        cout << "There was no website key with the name " + oldweb << endl;
    }
}

void PasswordManager::editUsername(string& website, string& username, string& newusername) {
    unordered_map<string, vector<PasswordEntry>>::iterator it = sitemap.find(website);
    if (it != sitemap.end()) {
        // get the vector of PasswordEntry objects
        vector<PasswordEntry>& entries = it->second;
        // find the element that matches the old username
        vector<vector<PasswordEntry>::iterator> matchpos = vector<vector<PasswordEntry>::iterator>();
        matchpos.push_back(std::find_if(entries.begin(), entries.end(), [&](const PasswordEntry& e) {return e.getUsername() == username; }));

        //Get all elements that match the username
        while (matchpos.at(matchpos.size()-1)!=entries.end())
        {
            matchpos.push_back(std::find_if(matchpos.at(matchpos.size() - 1), entries.end(), [&](const PasswordEntry& e) {return e.getUsername() == username; }));
        }
        // check if the element is found
        if (matchpos.size()>1) {
            // Print username entries to determine which one the user wants to edit
            for (int i = 0; i < matchpos.size() - 1; i++) {
                cout << i+1 + "-> Username: " + username + " Password: " + matchpos.at(i)->getPassword() << endl;
            }
            cout << "Which username do you want to change? Enter a number from the range 1 to " + (matchpos.size() - 1) << ": ";
            string line;
            int resp;
            // Loop to get a proper response from user
            while (true) {
                getline(cin, line);
                std::istringstream tmp(line);
                if (tmp >> resp) {
                    if (resp >= 1 && resp <= 10) {
                        break;
                    } else
                        cout << "Please enter a valid number from 1 to " + (matchpos.size() - 1) << ": ";
                }
                else {
                    cout << "Invalid input. Please enter a valid integer." << endl;
                }
            }
            
            //Change entry username
            matchpos.at(resp - 1)->setUsername(newusername);
            cout << "Changed " + username + " to " + newusername + "!" << endl;
            //Flag that changes made to entries and must be saved
            changeInfo = true;
        }
        else {
            // handle the case when the element is not found
            cout << "No such username in " + website + " entries." << endl;
        }
    }
    else {
        // handle the case when the website key is not found
        cout << "No such website found in the entries." << endl;
    }
}

void PasswordManager::editPassword(string& website, string& username, string& password, string& newpassword) {
    unordered_map<string, vector<PasswordEntry>>::iterator it = sitemap.find(website);
    if (it != sitemap.end()) {
        // get the vector of PasswordEntry objects
        vector<PasswordEntry>& entries = it->second;
        // find the element that matches the username and old password
        vector<PasswordEntry>::iterator matchpos = std::find_if(entries.begin(), entries.end(), [&](const PasswordEntry& x) {return x.getUsername() == username && x.getPassword() == password; });
        
        // Found entry, edit password
        if (matchpos != entries.end()) {
            cout << "If multiple occurences of the username and password, the first one will be changed." << endl;
            matchpos->setUsername(newpassword);
            cout << "Changed password!" << endl;
            //Flag that changes made to entries and must be saved
            changeInfo = true;
        }
        else {
            // handle the case when the element is not found
            cout << "No such password in " + website + " entries." << endl;
        }
    }
    else {
        // handle the case when the website key is not found
        cout << "No such website found in the entries." << endl;
    }
}

/////////////////////////////////////// DELETE RELATED CODE //////////////////////////////////////
void PasswordManager::deleteEntry(string& website, string& username, string& password) {
    unordered_map<string, vector<PasswordEntry>>::iterator it = sitemap.find(website);
    if (it != sitemap.end()) {
        // get the vector of PasswordEntry objects
        vector<PasswordEntry>& entries = it->second;
        // find the element that matches the username and password
        vector<PasswordEntry>::iterator matchpos = std::find_if(entries.begin(), entries.end(), [&](const PasswordEntry& x) {return x.getUsername() == username && x.getPassword() == password; });

        // Found entry, delete it
        if (matchpos != entries.end()) {
            cout << "If multiple occurences of the username and password, the first one will be deleted." << endl;
            entries.erase(matchpos);
            cout << "Deleted entry!" << endl;
            //Flag that changes made to entries and must be saved
            changeInfo = true;
        }
        else {
            // handle the case when the element is not found
            cout << "No such entry in " + website + " entries." << endl;
        }
    }
    else {
        // handle the case when the website key is not found
        cout << "No such website found in the entries." << endl;
    }
}

void PasswordManager::deleteWebsite(string& website) {
    unordered_map<string, vector<PasswordEntry>>::iterator it = sitemap.find(website);
    if (it != sitemap.end()) {
        sitemap.erase(it);
        cout << "Deleted website!" << endl;
        //Flag that changes made to entries and must be saved
        changeInfo = true;
    }
    else {
        cout << "No such website found in the entries." << endl;
    }
}

/////////////////////////////////////// JSON RELATED CODE ////////////////////////
void PasswordManager::to_json(json& j)
{
    try
    {
        // Go through all websites
        for (auto item = sitemap.begin(); item != sitemap.end(); ++item) {
            //Get username and password from each entry, create a 2D array of them
            vector<vector<string>> userlist = vector<vector<string>>();
            for (PasswordEntry entry : item->second) {
                userlist.push_back({ entry.getUsername(), entry.getPassword() });
            }
            // Make the entries a JSON value with the key being the website
            j[item->first] = userlist;
        }
    }
    catch (const std::exception&)
    {
        cout << "There was a problem writing to the database.";
    }

}

void PasswordManager::saveToJSON()
{
    json managerjson = json();
    to_json(managerjson);
    EncDec encrypt = EncDec();
    string encryptedJSON;
    encryptedJSON = encrypt.encrypt(managerjson.dump());
    std::ofstream o(fileName);
    o << encryptedJSON << endl;
    o.close();
    changeInfo = false;
}

void PasswordManager::loadFromJSON()
{
    try
    {
        std::ifstream readFile(fileName);
        if (readFile.fail()) {
            readFile.close();
            readFile.clear();
            std::ofstream temp(fileName);
            temp << "";
            temp.close();
            readFile.open(fileName);
        }
        json jsondata;
        std::stringstream readStream;
        readStream << readFile.rdbuf();
        EncDec decrypt = EncDec();
        //if (json::accept(readFile))
        //jsondata = json::parse(readFile);
        string result = "";
        result = decrypt.decrypt(readStream.str());
        jsondata = json::parse(result);
        readFile.close();
        from_json(jsondata);
    }
    catch (const std::exception&)
    {
        cout << "There was a problem when loading from the database." << endl;
    }
}

/*
    The default json to PasswordManager converter
*/
void PasswordManager::from_json(const json& jsonData)
{
    for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
            const string& website = it.key();
            const json& userEntryArray = it.value();

            vector<PasswordEntry> userpassEntries = vector<PasswordEntry>();
            for (const auto& userEntry : userEntryArray) {
                const string& username = userEntry[0], pass = userEntry[1];
                userpassEntries.emplace_back(username, pass);
            }
            sitemap.emplace(website, userpassEntries);
        }
}
