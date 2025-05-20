#include <iostream>
using namespace std;

int isLocked = 0;     // for mutual exclusion
int isFull = 0;       // buffer is not full initially
int isEmpty = 1;      // buffer is empty initially
int bufferSize;
int items = 0;        // count of items in buffer

void producer() {
    isLocked = 1;
    isEmpty = 0;
    items++;
    cout << "\nProducer produced item-" << items << endl;
    if(items == bufferSize) {
        isFull = 1; // buffer is full
    }
    isLocked = 0;
}

void consumer() {
    isLocked = 1;
    isFull = 0;
    cout << "\nConsumer consumed item-" << items << endl;
    items--;
    if(items == 0) {
        isEmpty = 1; // buffer is empty
    }
    isLocked = 0;
}

int main() {
    cout << "Enter the buffer size: ";
    cin >> bufferSize;

    int choice;
    do {
        cout << "\n\n     SELECT OPERATION\n"
             << "-----------------------------\n"
             << "1) Produce an item\n"
             << "2) Consume an item\n"
             << "3) Check if full\n"
             << "4) Check if empty\n"
             << "5) Exit\n"
             << "-----------------------------\n"
             << "Enter your choice: ";
        cin >> choice;

        if (choice == 1 && isLocked == 0) {
            if(isFull == 0) {
                producer();
            } else {
                cout << "\nThe buffer is full!\n";
            }
        } else if (choice == 2 && isLocked == 0) {
            if(isEmpty == 0) {
                consumer();
            } else {
                cout << "\nThe buffer is empty!\n";
            }
        } else if (choice == 3) {
            if(isFull == 1) {
                cout << "\nThe buffer is full!\n";
            } else {
                cout << "\nThe buffer has more space..\n";
            }
        } else if (choice == 4) {
            if(isEmpty == 1) {
                cout << "\nThe buffer is empty!\n";
            } else {
                cout << "\nThe buffer has more items..\n";
            }
        } else if (choice == 5) {
            cout << "\nExiting code...\n\n";
        }
    } while(choice != 5);

    return 0;
}
