#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector> 

using namespace std;
namespace FS = std::filesystem;
class IFileManager {
public:
    virtual void status() = 0;
    virtual void help() = 0;
    virtual void pwd() = 0;
    virtual void ls() = 0;
    virtual void cd(const std::string& folder) = 0;
    virtual void mkdir(const std::string& folder) = 0;
    virtual void rmdir(const std::string& folder) = 0;
    virtual void touch(const std::string& filename) = 0;
    virtual void rm(const std::string& file) = 0;
    virtual void read(const std::string& filename) = 0;
    virtual void write(const std::string& filename) = 0;
    virtual void levelup() = 0;
    virtual void rename(const std::string& s) = 0;
    
    virtual ~IFileManager() = default;
};

class MiniFileManager : public IFileManager {
    private:
        FS::path current_path;
    public:
        
        MiniFileManager(){
            current_path = FS::current_path();
        }
        void status() override{cout<<"\033[34m";
            cout << "~" << current_path <<"$";
            cout<<"\033[0m";
        }
        void help() override{
            cout << "List of all Commands" << endl;
            cout << "pwd, ls, cd <dir>, mkdir <dir>, rmdir <dir>,\n" <<
                  "touch <file>, rm <file>,rename <oldname>  <newname>,\n" <<
                  "cd .., read <file>, write <file>\n";
        }
        void pwd() override{
            cout<<current_path<<endl;
        }
        void ls() override{
            for(auto &content: FS::directory_iterator(current_path)){
                if(content.is_directory())cout<<"📁 ";
                else if(content.is_regular_file())cout<<"📃 ";
                cout<<content.path().filename()<<endl;
            }
        }
        void cd(const string &folder) override{
            //using try will helps us not to crash while running 
            //especially in user facing programs
            
            try{
                FS::path newpath=FS::canonical(current_path/folder);
                //this handles the symlinks like .. for parent folder and . for curr folder
                if(FS::exists(newpath)&&FS::is_directory(newpath)){
                    current_path=newpath;
                } 
                else{
                    cout<<"Directory is not found."<<endl;
                }
            }
            catch(const FS::filesystem_error &e){
                cout << " Error: "<< e.what() << endl;
            }

        }
        void mkdir(const string &folder) override{
            if(!FS::create_directory(current_path/folder))cout<<"📁 Folder already exists";

        }
        void rmdir(const string &folder) override{
            FS::remove_all(current_path/folder);
        }
        void touch(const string&filename) override{
            ofstream file(current_path/filename);
            file.close();
        }
        void rm(const string &file) override{
            FS::remove(current_path/file);

        }
        void read(const string&filename) override{
            string line;
            ifstream file(current_path/filename);
            if(!file){
                cout<<"📃File doesn't exist"<<endl;
                return;
            }
            while(getline(file,line)){
                cout<<line<<endl;
            }

        }
        void write(const string&filename) override{
            ofstream file(current_path/filename);
            string line;
            cout<<"Enter text (end the text with '~' on newline)"<<endl;
            while(getline(cin,line)){
                if(line=="~")break;
                file<<line<<'\n';
            }

        }
        void levelup() override{
            if(current_path.has_parent_path()){
                current_path=current_path.parent_path();
            }
        }
        void rename(const string &s) override{
            vector < string > v;
            stringstream ss(s);
            string word;
            while(ss >> word){
                v.push_back(word);
            }
            if(v.size()!=2){
                cout<< "Unknown commands.Try again.\n";
            }
            else{
                if(FS::exists(current_path / v[0] )){
                    if(FS::exists(current_path / v[1])){
                        cout << "Enter the another new name it already exists.\n";
                    }
                    else{
                        FS::rename(current_path / v[0],current_path / v[1]);
                    }
                }
                else {
                    cout << "No such file exists to rename.\n";
                }
            }
        }
};
int main(){
    MiniFileManager mfm;
    IFileManager &fm=mfm;
    string input;
    cout << "Mini File Manager.\n" << "Type help for commands.\n" ;
    while (true) {
        fm.status();
        // cout << ">>";
        getline(cin,input);
        if(input == "help")fm.help();
        else if(input == "pwd")fm.pwd();
        else if(input == "ls")fm.ls();
        else if(input.substr(0,3) == "cd ") fm.cd(input.substr(3));
        else if(input.substr(0,6) == "mkdir ") fm.mkdir(input.substr(6));
        else if(input.substr(0,6) == "rmdir ") fm.rmdir(input.substr(6));
        else if(input.substr(0,6) == "touch ") fm.touch(input.substr(6));
        else if(input.substr(0,3) == "rm ") fm.rm(input.substr(3));
        else if(input.substr(0,5) == "read ") fm.read(input.substr(5));
        else if(input.substr(0,6) == "write ") fm.write(input.substr(6));
        else if(input.substr(0,7) == "rename ") fm.rename(input.substr(7));
        else if(input == "cd ..")fm.levelup();
        else if(input=="exit")break;
        else {
            cout<< "Unknown Command" << endl;
            cout<< "Try Help"<<endl;
        }
    }
}
