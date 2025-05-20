#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void createFile(string fileName)
{
    ofstream file(fileName);
    if(file){
        cout << "File created successfully!" << endl;
        file.close();
    }
    else{
        cout << "Failed to create file!" << endl;
    }
}

void writeFile(string fileName, string data){
    ofstream file(fileName);
    if(file){
        file << data;
        cout << "Successfully written!" << endl;
        file.close();
    }
    else{
        cout << "File not opened!" << endl;
    }
}

void deleteFile(string fileName)
{
    if(remove(fileName.c_str()) == 0){
        cout << "File deleted successfully!" << endl;
    }
    else{
        cout << "Failed to delete file!" << endl;
    }
}

void copyFile(string sourceFileName, string destFileName){
    string line;
    ifstream ini_file(sourceFileName);
    ofstream out_file(destFileName);

    if(ini_file && out_file){
        while(getline(ini_file, line)){
            out_file << line << "\n";
        }
        cout << "Successfully copied!" << endl;
    }
    else {
        cout << "Failed to copy file!" << endl;
    }
}

void moveFile(string sourceFileName, string destFileName){
    copyFile(sourceFileName, destFileName);
    deleteFile(sourceFileName);
}

void renameFile(string oldName, string newName){
    if(rename(oldName.c_str(), newName.c_str()) == 0){
        cout << "File renamed successfully!" << endl;
    }
    else{
        cout << "Failed to rename file!" << endl;
    }
}

int main()
{
    int flag = 1;
    string fileName, destFileName, data;
    while(true){
        cout<< "\nOptions:\n";
        cout << "1. Create File\n";
        cout << "2. Write File\n";
        cout << "3. Copy File\n";
        cout << "4. Move File\n";
        cout << "5. Delete File\n";
        cout << "6. Rename File\n";
        cout << "0. Exit\n";

        cin >> flag;
        cin.ignore(); // To handle leftover newline

        if(flag == 1){
            cout << "Enter file name to create: ";
            getline(cin, fileName);
            createFile(fileName);
        }
        else if(flag == 2){
            cout << "Enter file name to write to: ";
            getline(cin, fileName);
            cout << "Enter your text: ";
            getline(cin, data);
            writeFile(fileName, data);
        }
        else if(flag == 3){
            cout << "Enter source file name: ";
            getline(cin, fileName);
            cout << "Enter destination file name: ";
            getline(cin, destFileName);
            copyFile(fileName, destFileName);
        }
        else if(flag == 4){
            cout << "Enter source file name: ";
            getline(cin, fileName);
            cout << "Enter destination file name: ";
            getline(cin, destFileName);
            moveFile(fileName, destFileName);
        }
        else if(flag == 5){
            cout << "Enter file name to delete: ";
            getline(cin, fileName);
            deleteFile(fileName);
        }
        else if(flag == 6){
            cout << "Enter current file name: ";
            getline(cin, fileName);
            cout << "Enter new file name: ";
            getline(cin, destFileName);
            renameFile(fileName, destFileName);
        }
        else if(flag == 0){
            cout << "Exiting program." << endl;
            break;
        }
        else{
            cout << "Invalid option. Try again." << endl;
        }
    }
    return 0;
}
