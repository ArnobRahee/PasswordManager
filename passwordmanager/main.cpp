#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int USERS = 1000;
string UserList[USERS];
int NoOfUser;
string username;
string password;
string line;
string file_content;
vector<string> new_lines;
class User {
public:
    User(string name, string password): name_(name), password_(password) {}
     bool Exsistence(){
       std::ifstream file;
       string filename=GetName()+".txt";
       file.open(filename.c_str());
       if(file){
        getline(file,line);
        if(line==GetPassword()){
            return true;
        }
       }
       return false;
     }
    string GetName() const {
        return name_;

        }
     string GetPassword() const {
        return password_;
     }
private:
    string name_;
    string password_;

};

class Admin {
public:
    Admin() {};

    void RemoveUser(std::string path, std::string eraseLine) {
    bool found=false;
    int status;
    string userfilename=eraseLine;
    //std::string line;
    std::ifstream fin;
    fin.open(path.c_str());

   if (fin.fail()) {
    std::cerr << "Failed to open file: " << path << std::endl;

}else{
        std::ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line)) {
        // write all lines to temp other than the line marked for erasing
       if (line.find(eraseLine) == std::string::npos){
            temp << line << std::endl;
       }else{
       found=true;
       }

    }
    temp.close();
    fin.close();

    // required conversion for remove and rename functions
    const char * p = path.c_str();
    remove(p);
    rename("temp.txt", p);
    if(found){
        //Delete user file name
        userfilename=userfilename+".txt";
        status=std::remove(userfilename.c_str());

            cout<<"User deleted sucessfully"<<endl;


    }else{
       cout<<"User not found"<<endl;
    }
}

};

    void ViewUsers(string filename) {
        ifstream infile(filename.c_str());
        //Check if the file exsist or not
        if (!infile) {
            cerr << "There was an error in displaying users" << endl;
        } else {
            NoOfUser = 0;
            while (getline(infile, line) && NoOfUser < USERS) {
                UserList[NoOfUser++] = line;
            }

            for (int i = 0; i < NoOfUser; i++) {
                cout<< UserList[i] << endl;
            }
            cout<<"Number of users using the system "<<NoOfUser<<endl;
            infile.close();
        }
    };



private:
    string password_;
    vector<User> users_;
};

int main() {
    int determine;
    string adminPass = "";
    const char* adminfile = "admin.txt";
    string userfiles = "users.txt";

    while (true) {
        cout << "Are you a regular user or an admin?? \n1. Regular user\n2. Admin\n3. Exit\n" << endl;
        cin >> determine;

        if (determine == 1) {
            // User Part
            cout << "Are you a new or an exsisting user \n1. Existing user\n2. New user" << endl;
            cin >> determine;
            //Checking user input
            if(determine==1){
                cout<<"Enter your username or password"<<endl;
                cin>>username;
                cin>>password;
                User user(username,password);
                if(user.Exsistence()){
                    cout<<"Good you exsist";
                }else{
                   cout<<"Sorry username or password not found";
                   //delete user;
                }
            }
           else if(determine==2){
                cout<<"You are a new user"<<endl;
            }else{
               cout<<"Please give proper input"<<endl;
            }
        } else if (determine == 2) {
            // Admin part
            cout << "Enter admin password \n press 3 to exit" << endl;
            cin >> adminPass;
            ifstream file(adminfile);

            // Check login status of admin
            while (getline(file, file_content)) {
                if (file_content == adminPass) {
                    cout << "Successfully Login as admin\n";
                    Admin admin;

                    while (true) {
                        cout << "What do you want to do today?? \n1. View users user\n2. Delete users\n3. Logout\n" << endl;
                        cin >> determine;

                        if (determine == 1) {
                            // View Users
                            admin.ViewUsers("users.txt");
                        } else if (determine == 2) {
                            //Remove users
                            admin.RemoveUser("users.txt","Rahee");
                        } else if (determine == 3) {
                            // Logout
                            break;
                        }
                    }
                } else {
                    cout << "Please enter correct credentials" << endl;
                }
            }
        } else if (determine == 3) {
            // Exit the program
            cout<<"Thank you for using our program"<<endl;
            break;
        }
        username="";
        password="";
    }
}
