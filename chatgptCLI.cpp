// mini_file_manager.cpp
#include <iostream>
#include <filesystem>
#include <fstream>
using namespace std;
namespace fs = std::filesystem;

class FileManager {
private:
    fs::path current_path;

public:
    FileManager() {
        current_path = fs::current_path(); // Set to current working directory
    }

    void pwd() {
        cout << current_path << endl;
    }

    void ls() {
        for (auto& entry : fs::directory_iterator(current_path)) {
            cout << entry.path().filename() << endl;
        }
    }

    void cd(const string& folder) {
        fs::path new_path = current_path / folder;
        if (fs::exists(new_path) && fs::is_directory(new_path)) {
            current_path = new_path;
        } else {
            cout << "Directory not found.\n";
        }
    }

    void mkdir(const string& folder) {
        fs::create_directory(current_path / folder);
    }

    void touch(const string& filename) {
        ofstream file(current_path / filename);
        file.close();
    }

    void write(const string& filename) {
        ofstream file(current_path / filename, ios::app);
        if (!file) {
            cout << "Failed to open file.\n";
            return;
        }
        cout << "Enter text (end with ~ on a new line):\n";
        string line;
        while (getline(cin, line)) {
            if (line == "~") break;
            file << line << '\n';
        }
        file.close();
    }

    void read(const string& filename) {
        ifstream file(current_path / filename);
        if (!file) {
            cout << "File not found.\n";
            return;
        }
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
    }

    void rm(const string& filename) {
        fs::remove(current_path / filename);
    }

    void rmdir(const string& folder) {
        fs::remove_all(current_path / folder);
    }

    void rename(const string& old_name, const string& new_name) {
        fs::rename(current_path / old_name, current_path / new_name);
    }

    void help() {
        cout << "Commands:\n"
             << "pwd, ls, cd <dir>, mkdir <dir>, touch <file>\n"
             << "write <file>, read <file>, rm <file>, rmdir <dir>\n"
             << "rename <old> <new>, help, exit\n";
    }
};

int main() {
    FileManager fm;
    string input;

    cout << "Mini File Manager. Type 'help' for commands.\n";

    while (true) {
        cout << ">> ";
        getline(cin, input);

        if (input == "exit") break;
        else if (input == "pwd") fm.pwd();
        else if (input == "ls") fm.ls();
        else if (input.substr(0, 3) == "cd ") fm.cd(input.substr(3));
        else if (input.substr(0, 6) == "mkdir ") fm.mkdir(input.substr(6));
        else if (input.substr(0, 6) == "touch ") fm.touch(input.substr(6));
        else if (input.substr(0, 6) == "write ") fm.write(input.substr(6));
        else if (input.substr(0, 5) == "read ") fm.read(input.substr(5));
        else if (input.substr(0, 3) == "rm ") fm.rm(input.substr(3));
        else if (input.substr(0, 6) == "rmdir ") fm.rmdir(input.substr(6));
        else if (input.substr(0, 7) == "rename ") {
            size_t space = input.find(' ', 7);
            if (space != string::npos) {
                string old_name = input.substr(7, space - 7);
                string new_name = input.substr(space + 1);
                fm.rename(old_name, new_name);
            } else {
                cout << "Usage: rename <old> <new>\n";
            }
        }
        else if (input == "help") fm.help();
        else cout << "Unknown command. Type 'help'.\n";
    }

    return 0;
}
