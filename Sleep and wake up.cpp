#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

mutex mtx;
condition_variable cv;
bool resourceAvailable = true; // critical region availability

// Sleep and wakeup model
void process(string name) {
    while (true) {
        unique_lock<mutex> lock(mtx);

        // Sleep if resource is not available
        while (!resourceAvailable) {
            cout << name << " is sleeping, waiting for the resource...\n";
            cv.wait(lock);  // Sleep (block until notified)
        }

        // Acquire resource
        resourceAvailable = false;
        cout << name << " enters the critical region...\n";
        lock.unlock();

        // Simulate critical section
        this_thread::sleep_for(chrono::milliseconds(1000));

        // Exit section
        lock.lock();
        cout << name << " leaves the critical region...\n";
        resourceAvailable = true;

        // Wake up one waiting process
        cv.notify_one();  // wakeup
        lock.unlock();

        // Remainder section
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    thread lowPriority(process, "LowPriorityProcess");
    thread highPriority(process, "HighPriorityProcess");

    lowPriority.join();
    highPriority.join();

    return 0;
}
