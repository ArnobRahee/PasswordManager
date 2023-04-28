#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User {
public:
    User(string name, bool is_premium) : name_(name), is_premium_(is_premium) {}

    string GetName() const { return name_; }
    bool IsPremium() const { return is_premium_; }

private:
    string name_;
    bool is_premium_;
};

class Admin {
public:
    Admin(string password) : password_(password) {}

    void AddUser(User user) { users_.push_back(user); }
    void RemoveUser(int index) { users_.erase(users_.begin() + index); }
    int GetUserCount() const { return users_.size(); }

private:
    string password_;
    vector<User> users_;
};

int main() {
    User user1("Alice", true);
    User user2("Bob", false);

    Admin admin("password");
    admin.AddUser(user1);
    admin.AddUser(user2);

    cout << "Total number of users: " << admin.GetUserCount() << endl;

    return 0;
}
