//==
// Created by Aleksandar Ristovski on 2.6.26.
//
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User {
protected:
    string username;
    string password;
    string email;
public:
    User() {}

    User(string username,
         string password,
         string email) {
        this->email = email;
        this->password = password;
        this->username = username;
    }

    virtual void printDetail() = 0;

    virtual int checkPasswordStrength() = 0;

};

class RegularUser : public User {
    bool has2FA;
public:
    RegularUser() {}

    RegularUser(string username,
                string password,
                string email, bool has2FA) : User(username, password, email) {
        this->has2FA = has2FA;
    }

    int checkPasswordStrength() override {
        int points = 0;
        if (password.length() >= 6) points += 2;
        for (int i = 0; i < password.length(); i++) {
            if (islower(password[i])) {
                points++;
                break;
            }
        }
        if (!isdigit(password.back())) points++;
        if (has2FA)points++;
        return points;
    }

    void printDetail() override{
        cout << username << " (Regular) - Email: " << email << " - 2FA: " ;
        if(has2FA){
            cout<<"Yes";
        }else{
            cout<<"No";
        }
        cout<< " - Strength: "<< checkPasswordStrength() << endl;
    }
};

class AdminUser : public User {
    string department;
    bool usesPasswordManager;
public:
    AdminUser(){}
    AdminUser(string username,
              string password,
              string email, string department, bool usesPasswordManager) : User(username, password, email) {
        this->department=department;
        this->usesPasswordManager=usesPasswordManager;
    }
    int checkPasswordStrength() override{
        int points=0;
        if(password.length()>=10) points+=2;
        for(int i=0; i<password.length(); i++){
            if(isupper(password[i])) {
                points+=2;
                break;
            }
        }
        if(!isupper(password.front())) points++;
        if(usesPasswordManager) points+=2;
        return points;
    }
    void printDetail() override{
        cout<<username<<" (Admin) - Email: "<<email<<" - Dept: "<<department<<" - PM: ";
        if(usesPasswordManager){
            cout<<"Yes";
        }else{
            cout<<"No";
        }
        cout<<" - Strength: "<<checkPasswordStrength()<<endl;

    }

};
void printAdminUserStats(User** users, int n){

    int sum=0;
    int counter=0;
    for(int i=0; i<n; i++){
        AdminUser* a= dynamic_cast<AdminUser*>(users[i]);
        if(a!= nullptr){
            counter++;
            users[i]->printDetail();
            sum+=users[i]->checkPasswordStrength();
        }
    }
    if(counter==0){
        cout<<"No admin Users found in the array!"<<endl;
        return;
    }
    cout<<"Average Admin Strength: "<<sum/counter<<endl;
}

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    User** users = new User*[n];

    for (int i = 0; i < n; ++i) {
        string username, password, email;
        cin >> type;
        cin.ignore();
        getline(cin, username);
        getline(cin, password);
        getline(cin, email);

        if (type == 1) {
            bool has2FA;
            cin >> has2FA;
            cin.ignore();
            users[i] = new RegularUser(username, password, email, has2FA);
        } else {
            string department;
            bool usesPM;
            getline(cin, department);
            cin >> usesPM;
            cin.ignore();
            users[i] = new AdminUser(username, password, email, department, usesPM);
        }
    }

    if (testCase == 1) {
        cout << "Abstract and child classes OK" << endl;
    } else if (testCase == 2) {
        for (int i = 0; i < n; ++i) {
            cout << users[i]->checkPasswordStrength() << endl;
        }
        cout << "checkPasswordStrength method OK" << endl;
    } else if (testCase == 3) {
        for (int i = 0; i < n; ++i) {
            users[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    } else if (testCase == 4) {
        printAdminUserStats(users, n);
        cout << "printAdminUserStats method OK" << endl;
    }

    for (int i = 0; i < n; ++i) {
        delete users[i];
    }
    delete[] users;

    return 0;
}