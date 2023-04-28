#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
const int USERS = 1000;
string UserList[USERS];
int NoOfUser;
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
    Admin();


    void RemoveUser(int index) { users_.erase(users_.begin() + index); }

    void ViewUsers(string filename){
        ifstream infile(filename.c_str());
        if (!infile) {
        cerr << "There was an error in displaying users" <<  endl;

    }else{
        NoOfUser=0;
       string line;
       while (getline(infile, line) && NoOfUser < USERS) {
        UserList[NoOfUser++] = line;
    }

    for (int i = 0; i < NoOfUser; i++) {
        cout << "Line " << i+1 << ": " << UserList[i] << endl;
    }
    }

    };
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
   int determine;
   string adminPass="";
   string file_content;
   const char* adminfile="admin.txt";
   string userfiles="users.txt";
   while(true){
    cout<< "Are you a regular user or an admin?? \n1. Regular user\n2. Admin\n3. Exit\n"<<endl;
    cin>>determine;
    if(determine==1){
        //User Part
        cout<<"You are a regular user"<<endl;
    }else if(determine==2){
         //Admin part
              cout<<"Enter admin password \n press 3 to exit"<<endl;
          cin>>adminPass;
          ifstream file(adminfile);
          //Check login status of admin
          while (getline(file, file_content)) {
    if (file_content == adminPass) {
      cout << "Successfully Login as admin\n";
               while (true){
                    Admin admin;
                     cout<< "What do you want to do today?? \n1. View users user\n2. Delete users\n3. Logout\n"<<endl;
                     cin>>determine;
                     if(determine==1){
                        //View Users
                        admin.ViewUsers("users.txt");
                     }
                     if(determine==2){
                        //Delete Users
                     }
                     if(determine==3){
                        //Logout
                        break;
                     }
                     }

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
