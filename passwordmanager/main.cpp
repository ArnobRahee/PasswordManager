#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int USERS = 1000;
const int freeUser=6;
const int premiumUser=1000;
string UserList[USERS];
int NoOfUser;
string username;
string password;
string email;
string line;
string file_content;
string status;
vector<string> new_lines;
class User {
public:
    User(string name_, string password_, bool premium_): name_(name_), password_(password_), premium_(premium_) {};

    bool Existence(){
        std::ifstream file;
        string filename = GetName() + ".txt";
        file.open(filename.c_str());
        if (file.is_open()) {
            string line;
            getline(file, line);
            if (line == GetPassword()) {
                file.close();
                return true;
            }
            file.close();
        }
        return false;
    };

    string GetName() const {
        return name_;
    };

    string GetPassword() const {
        return password_;
    };

    bool is_premium() const{
        return premium_;
    };

    void ViewPassword() {
        string filename = GetName() + ".txt";
        ifstream infile(filename.c_str());
        if (!infile.is_open()) {
            cerr << "There was an error in displaying passwords" << endl;
        } else {
            string UserList[USERS];
            int counts = 0;
            string line;
            while (getline(infile, line) && counts < USERS) {
                UserList[counts++] = line;
            }

            for (int i = 1; i < counts; i++) {
                cout << UserList[i] << endl;
            }
            cout << "Number of passwords: " << counts-1 << endl;
            infile.close();
        }
    };

    bool user_not_exists(){
        bool found = false;
        string line;
        std::ifstream fin;
        fin.open("users.txt");
        std::ofstream temp;
        temp.open("temp.txt");
        while (getline(fin, line)) {
            if (line.find(GetName()) == std::string::npos){
                temp << line << std::endl;
            } else {
                found = true;
                break;
            }
        }
        fin.close();
        temp.close();
        remove("users.txt");
        rename("temp.txt", "users.txt");
        return found;
    }

    void signup(string email){
        if (!user_not_exists()) {
            string filename = GetName();
            filename += ".txt";
            std::ofstream outfile (filename.c_str());
            outfile << password_ << std::endl;
            ofstream outdata;
            outdata.open("users.txt", std::ios_base::app);
            if (!outdata.is_open()) {
                cerr << "Problem signing up" << endl;
                //exit(1);
            } else {

                if(is_premium()){
                    status="free";
                }else{
                     status="premium";
                }
                outdata << name_ << " " << email << " "<<status<<endl;
                outdata.close();
            }
        } else {
            cout << "User already exists" << endl;
        }
    };

private:
    string name_;
    string password_;
    bool premium_;
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
    bool exsists;
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
                User* user=new User(username,password,false);
                exsists=user->Existence();
                if(exsists){
                    cout<<"Welcome to our password manager what do you want to do today \n1. View your passwords \n2. Write down new passwords \n3. Change passwords or Remove passwords\n4. Logout";
                    while(true){
                         cin >> determine;
                    if(determine==1){
                        user->ViewPassword();
                    }
                    else if(determine==2){
                        cout<<"New passwords"<<endl;
                    }
                    else if(determine==3){
                       cout<<"Remove or change passwords"<<endl;
                    }
                    else if(determine==4){
                        cout<<"It was nice having you bye bye\n"<<endl;
                        break;
                    }
                    else{
                        cout<<"Inappropriate input\n"<<endl;
                    }
                    }

                }else{
                   cout<<"Sorry username or password not found\n";
                   delete user;
                }
            }
           else if(determine==2){
                cout<<"You are a new user please sign up by entering your username, email and password\n"<<endl;
                cout<<"Enter username"<<endl;
                cin>>username;
                cout<<"Enter email"<<endl;
                cin>>email;
                cout<<"Enter password"<<endl;
                cin>>password;
                cout <<"Do you wish to become a premium user? if so enter\n1. Free\n2. Premium"<<endl;
                cin >> determine;
                if(determine==1){
                     User* user=new User(username,password,false);
                     user->signup(email);
                }else if(determine==2){
                      User* user=new User(username,password,true);
                      user->signup(email);
                }

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
                    cout << "What do you want to do today?? \n1. View users user\n2. Delete users\n3. Logout\n" << endl;
                    while (true) {


                             cin >> determine;

                        if (determine == 1) {
                            // View Users
                            admin.ViewUsers("users.txt");
                        } else if (determine == 2) {
                            //Remove users
                            cout<<"Enter name of user you want to remove"<<endl;
                            cin>>username;
                            admin.RemoveUser("users.txt",username);
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

    }
}

