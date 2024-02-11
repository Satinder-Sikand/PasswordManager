// PasswordManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "PasswordManager.h"
using namespace std;

void help() {
    cout << "-help -- Returns a list of commands that can be used by the system." << endl <<
        "-save -- Saves all current changes made to the system" << endl <<
        "-list -- Returns a table/list of all current websites and their saved user data" << endl <<
        "-add --Add a new username and password entry to the database" << endl <<
        "-exit --Close the app" << endl <<
        //"-back -- Cancel the curernt command made" <<
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

    //planned commands -help -save -list - add -exit -back
    help();

    //Get User input
    string response;
    vector<string> resparr = vector<string>();
    //getline(cin, response);
    //resparr = splitResponse(response); //split user input
    splitResponse(response, resparr);

        while (true) {
            if (resparr.at(0) == "exit()") {
                if (manager.isEdited()) {
                    cout << "Changes you made may not be saved. Do you want to save before leaving? (y/n/c) " << endl;
                    string leaveres;
                    getline(cin, leaveres);
                    while (true) {
                        if (leaveres == "y") {
                            manager.saveToJSON();
                            cout << "Saved" << endl;
                            exit(0);
                        }
                        else if (leaveres == "n")
                            exit(0);
                        else if (leaveres == "c" || leaveres == "back") {
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
                help();
                splitResponse(response, resparr);
            }
            else if (resparr.at(0) == "list") {
                manager.listEntries();
                splitResponse(response, resparr);
            }
            else if (resparr.at(0) == "add") {
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
                        unique_ptr<string> temp = make_unique<string>();
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
                    << setw(30) << "Username: " + *arguements.at(1) <<
                    setw(30) << "Password: " + *arguements.at(2) << endl;
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
                cout << "Added" << endl;
                splitResponse(response, resparr);
            }
            else if (resparr.at(0) == "save") {
                manager.saveToJSON();
                cout << "Saved" << endl;
                splitResponse(response, resparr);
            }
            else {
                cout << resparr.at(0) << endl;
                cout << "Improper arguments. Check -help for list of commands." << endl;
                splitResponse(response, resparr);
            }

        }
    //manager.listEntries();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


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

void PasswordManager::saveToJSON()
{
    json managerjson = json();
    to_json(managerjson);
    ofstream o(fileName);
    o << setw(4) << managerjson << endl;
    o.close();
    changeInfo = false;
}

void PasswordManager::loadFromJSON()
{
    try
    {
        ifstream readFile(fileName);
        if (readFile.fail()) {
            readFile.close();
            readFile.clear();
            ofstream temp(fileName);
            temp << "";
            temp.close();
            readFile.open(fileName);
        }
        json jsondata;
        //if (json::accept(readFile))
            jsondata = json::parse(readFile);
        readFile.close();
        from_json(jsondata);
    }
    catch (const std::exception&)
    {
        cout << "There was a problem when loading from the database." << endl;
    }
   

}

void PasswordManager::addEntry(const string& website, const string& username, const string& password)
{
    try
    {
        unordered_map<string, vector<PasswordEntry>>::iterator item = sitemap.find(website);
        if (item == sitemap.end()) {
            vector<PasswordEntry> userarray = vector<PasswordEntry>();
            sitemap.emplace(website, userarray);
        }
        sitemap.at(website).emplace_back(website, username, password);
        changeInfo = true;
    }
    catch (const exception&)
    {
        cout << "There was a problem when adding. Please try again." << endl;
    }
}

void PasswordManager::listEntries() 
{
    //cout << "hello";
    for (auto item = sitemap.begin(); item != sitemap.end(); ++item) {
        //vector<vector<string>> userlist;
        cout << "Website: " << item->first << endl;
        
        for (PasswordEntry entry : item->second) {
            cout << setw(30) << "Username: " << entry.getUsername() << setw(30) << "Password: " << entry.getPassword()<< endl;
            //userlist.push_back({ entry.getUsername(), entry.getPassword() });
        }
        //cout << setw(4) << userlist << endl;
    }
}

void PasswordManager::to_json(json& j)
{
    try
    {
        for (auto item = sitemap.begin(); item != sitemap.end(); ++item) {
            vector<vector<string>> userlist = vector<vector<string>>();
            for (PasswordEntry entry : item->second) {
                userlist.push_back({ entry.getUsername(), entry.getPassword() });
            }
            j[item->first] = userlist;
        }
    }
    catch (const std::exception&)
    {
        cout << "There was a problem writing to the database.";
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
                userpassEntries.emplace_back(website, username, pass);
            }
            sitemap.emplace(website, userpassEntries);
        }
}
