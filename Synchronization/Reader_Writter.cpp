#include <iostream>

using namespace std;

int writing = 0; // none is writing at the start
int reading = 0; // none is reading at the start
int readerCount = 0; // checks number of readers
int mutex = 1;

void read() {
    mutex = 0;
    reading = 1;
    readerCount++;
    cout << "\nReader(" << readerCount << ") is reading...\n";
    mutex = 1;
}

void write() {
    mutex = 0;
    writing = 1;
    cout << "\nWriter(" << writing << ") is writing...\n";
    mutex = 1;
}

int main() {
    int choice;

    do {
        cout << "\n\n     SELECT OPERATION\n"
             << "-----------------------------\n"
             << "1) Read\n"
             << "2) Write\n"
             << "3) Delete last reader\n"
             << "4) Delete last writer\n"
             << "5) Exit\n"
             << "-----------------------------\n"
             << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) { // read
            if (writing == 0 && mutex == 1) {
                read();
            } else {
                cout << "\nCannot read, a writer is currently writing...\n";
            }
        } else if (choice == 2) { // write
            if (reading == 0 && mutex == 1 && writing == 0) {
                write();
            } else if (writing == 1) {
                cout << "\nCannot write, a writer is currently writing...\n";
            } else {
                cout << "\nCannot write, a reader is currently reading...\n";
            }
        } else if (choice == 3) { // delete reader
            if (readerCount == 0) {
                cout << "\nNo readers are reading!\n";
            } else {
                cout << "\nA reader(" << readerCount << ") is removed\n";
                readerCount--;
                if (readerCount == 0) {
                    reading = 0;
                }
            }
        } else if (choice == 4) { // delete writer
            if (writing == 0) {
                cout << "\nCurrently none is writing...\n";
            } else {
                cout << "\nThe writer is removed!\n";
                writing = 0;
            }
        } else if (choice == 5) {
            cout << "\nExiting code...\n\n";
        } else {
            cout << "\nInvalid choice. Please select again.\n";
        }

    } while (choice != 5);

    return 0;
}
