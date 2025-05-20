#include <iostream>
using namespace std;

int bufferSize;
int items = 0;  // current item count

void producer() {
    if (items < bufferSize) {
        items++;
        cout << "\nProducer produced item-" << items << endl;
    } else {
        cout << "\nThe buffer is full!\n";
    }
}

void consumer() {
    if (items > 0) {
        cout << "\nConsumer consumed item-" << items << endl;
        items--;
    } else {
        cout << "\nThe buffer is empty!\n";
    }
}

void checkFull() {
    if (items == bufferSize)
        cout << "\nThe buffer is full!\n";
    else
        cout << "\nThe buffer has more space...\n";
}

void checkEmpty() {
    if (items == 0)
        cout << "\nThe buffer is empty!\n";
    else
        cout << "\nThe buffer has more items...\n";
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

        switch (choice) {
            case 1: producer(); break;
            case 2: consumer(); break;
            case 3: checkFull(); break;
            case 4: checkEmpty(); break;
            case 5: cout << "\nExiting code...\n"; break;
            default: cout << "\nInvalid choice!\n"; break;
        }

    } while(choice != 5);

    return 0;
}
