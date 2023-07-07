#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct User {
    string username;
    string password;
    double account_balance;
    bool car_borrow_request;
    bool car_return_request;
};

void rentCar(User& user) {
    // Code to handle the car rental functionality
    cout << "Car rental functionality for user: " << user.username << endl;
    // Add your code here to implement the car rental logic
    user.car_borrow_request = true;
}

void returnCar(User& user) {
    // Code to handle the car return functionality
    cout << "Car return functionality for user: " << user.username << endl;
    // Add your code here to implement the car return logic
    user.car_return_request = true;
}

void viewProfile(const User& admin) {
    ifstream infile_usersDB("usersDB.txt");
    string line;
    bool foundUser = false;

    while (getline(infile_usersDB, line)) {
        stringstream ss(line);
        string username, password;
        double account_balance;
        bool car_borrow_request, car_return_request;

        getline(ss, username, ',');
        getline(ss, password, ',');
        ss >> account_balance >> car_borrow_request >> car_return_request;

        cout << "Profile details for user: " << username << endl;
        cout << "Account Balance: " << account_balance << endl;
        cout << "Car Borrow Request: " << (car_borrow_request ? "True" : "False") << endl;
        cout << "Car Return Request: " << (car_return_request ? "True" : "False") << endl;
        cout << "--------------------------" << endl;

        foundUser = true;
    }

    infile_usersDB.close();

    if (!foundUser) {
        cout << "No user profiles found." << endl;
    }
}



void changePassword(User& user) {
    // Code to handle changing the user's password
    cout << "Change Password functionality for user: " << user.username << endl;
    // Add your code here to implement the password change logic
}

void addUser() {
    string username, password;
    double depositAmount;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    cout << "Enter deposit amount: ";
    cin >> depositAmount;

    // Check if the username already exists in the database
    ifstream infile_usersDB("usersDB.txt");
    string line;
    while (getline(infile_usersDB, line)) {
        stringstream ss(line);
        string existingUsername, password;
        double account_balance;
        bool car_borrow_request, car_return_request;

        getline(ss, existingUsername, ',');

        if (depositAmount < 15000) {
            cout << "Account balance must be at least 15000 shillings. User creation refused." << endl;
            return;
        }
        if (existingUsername == username) {
            cout << "Username already exists. Please choose a different username." << endl;
            infile_usersDB.close();
            return;
        }
    }

    infile_usersDB.close();

    // Add the new user to the usersDB file
    ofstream outfile_usersDB("usersDB.txt", ios::app);  // Append mode

    outfile_usersDB << username << "," << password << "," << depositAmount << ",False,False\n";

    outfile_usersDB.close();

    cout << "User added successfully." << endl;
}


void approveBorrowRequest(User& user) {
    // Code to handle approving a user's car borrow request
    cout << "Approve Borrow Request functionality for admin" << endl;
    // Add your code here to implement the approval logic
    user.car_borrow_request = true;
}

void acceptReturn(User& user) {
    // Code to handle accepting the returned car by the user
    cout << "Accept Return functionality for admin" << endl;
    // Add your code here to implement the return acceptance logic
    user.car_return_request = false;
}

void changeAdminPassword(User& admin) {
    // Code to handle changing the admin's password
    cout << "Change Password functionality for admin: " << admin.username << endl;
    // Add your code here to implement the password change logic
}

void fineUser(User& user) {
    // Code to handle fining the user by debiting their account for exceeding the return deadline
    cout << "Fine User functionality for admin" << endl;
    // Add your code here to implement the fine logic
}

int main() {
    ofstream outfile_usersDB("usersDB.txt");
    ofstream outfile_adminDB("adminDB.txt");

    outfile_usersDB << "username,password,account_balance,CarBorrowRequest,CarReturnRequest\n";
    outfile_usersDB << "johndoe,password123,1000,False,False\n";
    outfile_usersDB << "janedoe,password456,2000,False,False\n";

    outfile_adminDB << "username,password\n";
    outfile_adminDB << "admin,password123\n";

    outfile_usersDB.close();
    outfile_adminDB.close();

    string username, password;
    bool is_user = false;
    bool is_admin = false;

    cout << "Enter your username: ";
    cin >> username;

    cout << "Enter your password: ";
    cin >> password;

    ifstream infile_usersDB("usersDB.txt");
    string line;
    while (getline(infile_usersDB, line)) {
        stringstream ss(line);
        string user, pass;
        getline(ss, user, ',');
        getline(ss, pass, ',');

        if (user == username && pass == password) {
            is_user = true;
            break;
        }
    }

    ifstream infile_adminDB("adminDB.txt");
    while (getline(infile_adminDB, line)) {
        stringstream ss(line);
        string user, pass;
        getline(ss, user, ',');
        getline(ss, pass, ',');

        if (user == username && pass == password) {
            is_admin = true;
            break;
        }
    }

    infile_usersDB.close();
    infile_adminDB.close();

    if (is_user) {
        cout << "You are logged in as a user." << endl;
        User currentUser{username, password, 0.0, false, false};
        char choice;
        while (true) {
            cout << "\nMenu:\n";
            cout << "a. View Personal profile details\n";
            cout << "b. Request to rent out a car\n";
            cout << "c. Request to return car in the system\n";
            cout << "d. Change/Update your own login password\n";
            cout << "e. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 'a':
                    viewProfile(currentUser);
                    break;
                case 'b':
                    rentCar(currentUser);
                    break;
                case 'c':
                    returnCar(currentUser);
                    break;
                case 'd':
                    changePassword(currentUser);
                    break;
                case 'e':
                    cout << "Logged out successfully." << endl;
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    } else if (is_admin) {
        cout << "You are logged in as an admin." << endl;
        User currentAdmin{username, password, 0.0, false, false};
        char choice;
        while (true) {
            cout << "\nMenu:\n";
            cout << "a. View Personal profile details\n";
            cout << "b. Register a user/renter to the system\n";
            cout << "c. Approve user request to borrow/rent out car\n";
            cout << "d. Accept returned car and update system\n";
            cout << "e. Change/Update your own admin login password\n";
            cout << "f. Fine the user by debiting their accounts\n";
            cout << "g. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 'a':
                    viewProfile(currentAdmin);
                    // Suspend the program and wait for a keypress
                    system("pause");
                    break;
                case 'b':
                    addUser();
                    break;
                case 'c':
                    approveBorrowRequest(currentAdmin);
                    break;
                case 'd':
                    acceptReturn(currentAdmin);
                    break;
                case 'e':
                    changeAdminPassword(currentAdmin);
                    break;
                case 'f':
                    fineUser(currentAdmin);
                    break;
                case 'g':
                    cout << "Logged out successfully." << endl;
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
            // Prompt user to press any key to continue
            cout << "\nPress any key to continue...";
            cin.ignore();  // Ignore any leftover newline characters
            cin.get();     // Wait for a keypress
        }
    } else {
        cout << "Invalid username or password." << endl;
    }

    return 0;
}
