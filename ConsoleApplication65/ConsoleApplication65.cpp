#include <iostream>
#include <windows.h>
#include <cassert>
#include <string>

using namespace std;

class User {
    string username;
    string password;
    string name;
    string surname;

public:
    User(const string& newUsername, const string& newPassword, const string& newName, const string& newSurname)
        : username(newUsername), password(newPassword), name(newName), surname(newSurname) {
        assert(isupper(username[0]) && "Username must start with an uppercase letter.");
    }

    // Getters
    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    string getName() const {
        return name;
    }

    string getSurname() const {
        return surname;
    }

    // Setters
    void setUsername(const string& newUsername) {
        username = newUsername;
    }

    void setPassword(const string& newPassword) {
        password = newPassword;
    }

    void setName(const string& newName) {
        name = newName;
    }

    void setSurname(const string& newSurname) {
        surname = newSurname;
    }

    void show() const {
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
        cout << "Name: " << name << endl;
        cout << "Surname: " << surname << endl;
        cout << "------------------------\n";
    }
};


class Database {
    User** users;
    int user_count = 0;
    const int max_users = 10;

public:
    Database() {
        users = new User * [max_users];
    }

    ~Database() {
        for (int i = 0; i < user_count; ++i) {
            delete users[i];
        }
        delete[] users;
    }

    void addUser(const User& user) {
        if (getUserByUsername(user.getUsername()) != nullptr) {
            cout << "Add user failed. Username already exists.\n";
            return;
        }

        if (user_count < max_users) {
            users[user_count++] = new User(user);
            cout << "User added successfully.\n";
        }
        else {
            cout << "Database is full. Cannot add more users.\n";
        }
    }

    User* getUserByUsername(const string& username) {
        for (int i = 0; i < user_count; ++i) {
            if (users[i]->getUsername() == username) {
                return users[i];
            }
        }
        return nullptr;
    }

    void updateUser(User* oldUser, const User& newUser) {
        if (oldUser != nullptr) {
            oldUser->setPassword(newUser.getPassword());
            oldUser->setName(newUser.getName());
            oldUser->setSurname(newUser.getSurname());

            cout << "User updated successfully.\n";
        }
        else {
            cout << "Update failed. User not found.\n";
        }
    }

    void deleteUser(User* user) {
        if (user != nullptr) {
            for (int i = 0; i < user_count; ++i) {
                if (users[i] == user) {
                    delete users[i];

                    for (int j = i; j < user_count - 1; ++j) {
                        users[j] = users[j + 1];
                    }

                    user_count--;
                    cout << "User deleted successfully.\n";
                    return;
                }
            }

            cout << "Delete failed. User not found.\n";
        }
        else {
            cout << "Delete failed. User is nullptr.\n";
        }
    }

    void showAllUsers() const {
        if (user_count > 0) {
            cout << "All Users:\n\n";
            for (int i = 0; i < user_count; ++i) {
                users[i]->show();
            }
        }
        else {
            cout << "No users in the database.\n";
        }
    }
};

class Registration {
    Database _database;

public:
    Registration(const Database& database) : _database(database) {}

    bool signIn(string username, string password);
    bool signUp(string username, string password, string name, string surname);
    void addUserFromInput();
};

bool Registration::signIn(string username, string password) {
    return false;
}

bool Registration::signUp(string username, string password, string name, string surname) {
    return false;
}

void Registration::addUserFromInput() {
    string username, password, name, surname;

    cout << "Enter username: ";
    cin >> username;

    if (_database.getUserByUsername(username) != nullptr) {
        cout << "Add user failed. Username already exists.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter surname: ";
    cin >> surname;

    User new_user(username, password, name, surname);
    _database.addUser(new_user);
}

class System {
public:
    static void Control() {
        Database db;
        Registration twitter(db);

        int choice;
        do {
            cout << "1. Show all users\n";
            cout << "2. Sign in\n";
            cout << "3. Sign up\n";
            cout << "4. Update User\n";
            cout << "5. Delete User\n";
            cout << "6. Search User\n";
            cout << "7. Add User\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                db.showAllUsers();
                break;
            case 2: {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                twitter.signIn(username, password);
                break;
            }
            case 3: {
                string username, password, name, surname;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter surname: ";
                cin >> surname;
                twitter.signUp(username, password, name, surname);
                break;
            }
            case 4: {
                string username, password, name, surname;
                cout << "Enter username: ";
                cin >> username;
                User* userToUpdate = db.getUserByUsername(username);
                if (userToUpdate != nullptr) {
                    cout << "Enter new password: ";
                    cin >> password;
                    cout << "Enter new name: ";
                    cin >> name;
                    cout << "Enter new surname: ";
                    cin >> surname;
                    User newUser(username, password, name, surname);
                    db.updateUser(userToUpdate, newUser);
                }
                else {
                    cout << "User not found.n";
                }
                break;
            }
            case 5: {
                string username;
                cout << "Enter username: ";
                cin >> username;
                User* userToDelete = db.getUserByUsername(username);
                if (userToDelete != nullptr) {
                    db.deleteUser(userToDelete);
                    cout << "User deleted successfully.\n";
                }
                else {
                    cout << "User not found. Deletion failed.\n";
                }
                break;
            }
            case 6: {
                string username;
                cout << "Enter username: ";
                cin >> username;
                User* userToSearch = db.getUserByUsername(username);
                if (userToSearch != nullptr) {
                    cout << "User found:\n";
                    userToSearch->show();
                }
                else {
                    cout << "User not found.\n";
                }
                break;
            }
            case 7:
                twitter.addUserFromInput();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    System::Control();
    system("pause");
    return 0;
}