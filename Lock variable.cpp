#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

volatile int lock = 0; // shared variable (0 = free, 1 = locked)

void process(const string& name) {
    while (true) {
        // Entry Section
        while (lock == 1); // busy wait (if locked)

        lock = 1; // set lock (no atomicity — race condition possible)

        // Critical Section
        cout << name << " is using the printer\n";
        this_thread::sleep_for(chrono::milliseconds(500));

        // Exit Section
        lock = 0;

        // Remainder Section
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    thread P0(process, "P0");
    thread P1(process, "P1");

    P0.join();
    P1.join();

    return 0;
}
