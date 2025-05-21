#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int bufferSize;
int items = 0;  // shared variable (buffer count)

void producer() {
    for (int i = 0; i < 1000; ++i) {
        if (items < bufferSize) {
            items++;  // increment shared variable
            cout << "Produced item: " << items << endl;
        } else {
            cout << "Buffer full, producer waiting...\n";
        }
        // Sleep to simulate work and allow context switch
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

void consumer() {
    for (int i = 0; i < 1000; ++i) {
        if (items > 0) {
            cout << "Consumed item: " << items << endl;
            items--;  // decrement shared variable
        } else {
            cout << "Buffer empty, consumer waiting...\n";
        }
        // Sleep to simulate work and allow context switch
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

int main() {
    cout << "Enter buffer size: ";
    cin >> bufferSize;

    // Start producer and consumer threads concurrently
    thread t1(producer);
    thread t2(consumer);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    cout << "Final items count: " << items << endl;

    return 0;
}
