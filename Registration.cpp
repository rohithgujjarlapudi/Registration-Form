#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

// Base class to represent a user
class User {
protected:
    string LoginID, Password;

public:
    User(): LoginID(""), Password("") {}
    
    virtual void setID(string id) {
        LoginID = id;
    }
    
    virtual void setPW(string pw) {
        Password = pw;
    }

    virtual string getID() const {
        return LoginID;
    }

    virtual string getPW() const {
        return Password;
    }
    
    // Virtual functions for polymorphism
    virtual void registerUser() = 0;
    virtual void loginUser() = 0;
};

// Derived class for regular login
class Login : public User {
public:
    Login() : User() {}

    void registerUser() override {
        system("cls");
        string id, pw;
        cout << "\tEnter Login ID: ";
        cin >> id;
        setID(id);

        // Password validation
        start:
        cout << "\tEnter A Strong Password: ";
        cin >> pw;
        if (pw.length() >= 8) {
            setPW(pw);
        } else {
            cout << "\tEnter Minimum 8 Characters!" << endl;
            goto start;
        }

        // Save to file
        ofstream outfile("D:/Login.txt", ios::app);
        if (!outfile) {
            cout << "\tError: File Can't Open!" << endl;
        } else {
            outfile << "\t" << getID() << " : " << getPW() << endl << endl;
            cout << "\tUser Registered Successfully!" << endl;
        }
        outfile.close();
        Sleep(3000);
    }

    void loginUser() override {
        system("cls");
        string id, pw;
        cout << "\tEnter Login ID: ";
        cin >> id;
        cout << "\tEnter Password: ";
        cin >> pw;

        ifstream infile("D:/Login.txt");
        if (!infile) {
            cout << "\tError: File Can't Open!" << endl;
        } else {
            string line;
            bool found = false;
            while (getline(infile, line)) {
                stringstream ss;
                ss << line;
                string userID, userPW;
                char delimiter;
                ss >> userID >> delimiter >> userPW;

                if (id == userID && pw == userPW) {
                    found = true;

                    cout << "\tPlease Wait";
                    for (int i = 0; i < 3; i++) {
                        cout << ".";
                        Sleep(800);
                    }
                    system("cls");
                    cout << "\tWelcome To This Page!" << endl;
                }
            }
            if (!found) {
                cout << "\tError: Incorrect Login ID Or Password!" << endl;
            }
        }
        infile.close();
        Sleep(5000);
    }
};

// Main Function
int main() {
    Login login;
    bool exit = false;

    while (!exit) {
        system("cls");
        int val;
        cout << "\tWelcome To Registration & Login Form" << endl;
        cout << "\t************************************" << endl;
        cout << "\t1. Register." << endl;
        cout << "\t2. Login." << endl;
        cout << "\t3. Exit." << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            login.registerUser();
        } else if (val == 2) {
            login.loginUser();
        } else if (val == 3) {
            system("cls");
            exit = true;
            cout << "\tGood Luck!" << endl;
            Sleep(3000);
        }
        Sleep(3000);
    }
}
