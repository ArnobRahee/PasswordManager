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
    User(string name_, string password_): name_(name_), password_(password_) {};

     // Checks exsistence of the user
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
    }
    void writePasswords(string website,string password){
        bool found=false;
       ofstream outdata;
       std::ifstream fin;
       string filename = GetName();
       filename += ".txt";
       fin.open(filename.c_str());
       while(getline(fin,line)){
         if (line.find(website) != std::string::npos){
            found=true;
         }
       }
       if(found){
        cout<<"Password already exsist"<<endl;
       }else{
           outdata.open(filename.c_str(), std::ios_base::app);
           outdata << website<<" "<<password << endl;
           cout<<"Password added sucessfully"<<endl;
       }

       outdata.close();

    }
    void changePassword(std::string website,std::string password){
      bool found=false;
      string usertxt=GetName()+".txt";
      std::ifstream fin;
    fin.open(usertxt.c_str());
     if (fin.fail()) {
    std::cerr << "Failed to change"<<endl;

}else{
       std::ofstream temp;
       temp.open("temp.txt");
       while (getline(fin, line)) {
    if (line.find(website) != std::string::npos) {
        // replace the password on the line that contains the website name
        line = website + " " + password;
         temp << line << std::endl;
        found = true;
    }else{
         temp << line << std::endl;
    }
    // write the line to the temp file

}

      temp.close();
      fin.close();

    // required conversion for remove and rename functions
    std::remove(usertxt.c_str());
    std::rename("temp.txt", usertxt.c_str());
     if(found){
        cout<<"Your password has been changed"<<endl;
     }else{
         cout<<"Please make sure that the website name is spelled correctly or use View Password option to see if you saved it"<<endl;
     }

    //
    }
    }
    bool user_exists(){
        ifstream file;
        string name=GetName()+".txt";
        file.open(name.c_str());
        return file;

    }

    void signup(string email,bool premium){


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

                if(premium){
                    status="premium";
                }else{
                     status="free";
                }
                outdata << name_ << " " << email << " "<<status<<endl;
                outdata.close();

        }

    }

private:
    string name_;
    string password_;
public:
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
    }
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

            infile.close();
        }
    }
};

int main() {
    int determine;
    string adminPass = "";
    const char* adminfile = "admin.txt";
    string userfiles = "users.txt";
    bool exsists;
    string website;
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
                User* user=new User(username,password);
                exsists=user->Existence();

                if(exsists){
                    cout<<"Welcome to our password manager what do you want to do today \n1. View your passwords \n2. Write down new passwords \n3. Change passwords\n4. Logout\n";
                    while(true){
                         cin >> determine;
                    if(determine==1){
                        user->ViewPassword();
                    }
                    else if(determine==2){
                        cout<<"Enter website name"<<endl;
                        cin>>website;
                        cout<<"Enter password"<<endl;
                        cin>>password;
                        user->writePasswords(website,password);
                    }
                    else if(determine==3){
                       cout<<"Name of website you want to change"<<endl;
                       cin>>username;
                       cout<<"Type your desired password"<<endl;
                       cin>>password;
                       user->changePassword(username,password);
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
                User* user=new User(username,password);
                if(user->user_exists()){
                    cout<<"User already exsist"<<endl;
                }else{
                cout <<"Do you wish to become a premium user? if so enter\n1. Free\n2. Premium"<<endl;
                cin >> determine;
                if(determine==1){
                     user->signup(email,false);
                }else if(determine==2){

                      user->signup(email,true);
                }

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

