#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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
     /*
    User user1("Alice", true);
    User user2("Bob", false);

    Admin admin("password");
    admin.AddUser(user1);
    admin.AddUser(user2);

    //cout << "Total number of users: " << admin.GetUserCount() << endl;
*/
// Variable declaration
   int determine=0;
   string adminPass="";
   string file_content;
   const char* adminfile="admin.txt";
   while(true){
    cout<< "Are you a regular user or an admin?? \n1. Regular user\n2. Admin\n3. Exit\n"<<endl;
    cin>>determine;
    if(determine==1){
        //User Part
        cout<<"You are a regular user"<<endl;
    }else if(determine==2){
         //Admin part
              cout<<"Enter admin password \n1 press 3 to exit"<<endl;
          cin>>adminPass;
          ifstream file(adminfile);
          //Check login status of admin
          while (getline(file, file_content)) {
    if (file_content == adminPass) {
      cout << "Successfully Login as admin\n";
             //  while (true){
            //}

    }else{
        cout<< "Please enter correct credentials"<<endl;
    }
         }

         //cout<<"You are an admin"<<endl;
    }else if(determine==3){
    // Exit the program
       cout<<"Thank you for using our program"<<endl;
       break;
    }else{
       cout<<"Please give appropriate input"<<endl;
    }
   }
    return 0;
}
