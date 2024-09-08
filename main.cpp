#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h> 
using namespace std;

// Abstract Base Class
class User {
public:
    virtual void setId(const string& id) = 0;
    virtual void setPassword(const string& password) = 0;
    virtual string getId() const = 0;
    virtual string getPassword() const = 0;
    virtual bool authenticate(const string& id, const string& password) const = 0;
    virtual ~User() {}
};

// Concrete Class: SimpleUser
class SimpleUser : public User {
private:
    string id;
    string password;

public:
    void setId(const string& id) override {
        this->id = id;
    }

    void setPassword(const string& password) override {
        this->password = password;
    }

    string getId() const override {
        return id;
    }

    string getPassword() const override {
        return password;
    }

    bool authenticate(const string& id, const string& password) const override {
        return this->id == id && this->password == password;
    }
};

// Registration function
void registration(User& user) {
    system("clear"); 
    string id, psw;
    cout << "Enter login ID: ";
    cin >> id;
    user.setId(id);

    while (true) {
        cout << "Enter a strong password: ";
        cin >> psw;
        
        if (psw.length() >= 8) {
            user.setPassword(psw); 
            break; 
        } else {
            cout << "Password must be at least 8 characters long. Please try again." << endl;
        }
    }

    ofstream outfile("file.txt", ios::app); 
    if (!outfile) {
        cout << "Error opening file for writing." << endl;
    } else {
        outfile << user.getId() << ";" << user.getPassword() << endl;
        cout << "Registration successful!" << endl;
    }
    outfile.close();
    sleep(3); 
}

// Login function
void performlog(const User& user) {
    system("clear");
    string id, pw;
    cout << "Enter Login ID: ";
    cin >> id;

    cout << "Enter Password: ";
    cin >> pw;

    ifstream infile("file.txt");
    if(!infile){
        cout << "\tError: File Can't Open!" << endl;
    } else {
        string line;
        bool found = false;
        while (getline(infile, line)) {
            stringstream ss(line);
            string userID, userPW;
            char delimiter;
            ss >> userID >> delimiter >> userPW;

            if (user.authenticate(userID, userPW)) {
                found = true;

                cout << "Please Wait";
                for (int i = 0; i < 3; i++) {
                    cout << ".";
                    sleep(1);
                }
                system("clear");
                cout << "Welcome To This Page!" << endl;
                break;
            }
        }
        if (!found) {
            cout << "Error: Incorrect Login ID Or Password!" << endl;
        }
    }
    infile.close();
    sleep(3);
}

int main() {
    SimpleUser user;
    int val;
    bool exit = false;

    while (!exit) {
        system("clear"); 
        cout << "Registration Form" << endl;
        cout << "1. Click 1 for registration" << endl;
        cout << "2. Click 2 for login" << endl;
        cout << "3. Click 3 for exit" << endl;
        cout << "Enter the value: ";
        cin >> val;

        if (val == 1) {
            registration(user);
        } else if (val == 2) {
            performlog(user);
        } else if (val == 3) {
            system("clear");
            exit = true;
            cout << "\tGood Luck!" << endl;
            sleep(3);
        }
        sleep(3);
    }

    return 0;
}
