#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

bool EXIT_FLAG = false;
const int PHILOSOPHERS = 5;
bool FORKS[PHILOSOPHERS * 2] = { false };
mutex cout_mutex;


void print(const string str){
    cout_mutex.lock();
    cout << str << endl;
    cout_mutex.unlock();
}

void take_fork(int philosopher)
{
    int L = philosopher * 2;
    int R = L + 1;
    FORKS[L] = true;
    FORKS[R] = true;
    print("Philosopher " + to_string(philosopher) + " took forks " + to_string(L) + " and " + to_string(R));
}

void release_fork(int philosopher)
{
    int L = philosopher * 2;
    int R = L + 1;
    FORKS[L] = true;
    FORKS[R] = true;
    print("Philosopher " + to_string(philosopher) + " released forks " + to_string(L) + " and " + to_string(R));
}

void philosopher(int i, int eating_time, int thinking_time)
{
    string philosopher = to_string(i);
    while (true) {
        if (EXIT_FLAG) {
            print("Philosopher " + philosopher + " exiting");
            return;
        }
        print("Philosopher " + philosopher + " started thinking for " + to_string(thinking_time));
        this_thread::sleep_for(std::chrono::milliseconds(thinking_time));
        print("Philosopher " + philosopher + " stopped thinking");
        if (EXIT_FLAG) {
            print("Philosopher " + philosopher + " exiting");
            return;
        }
        take_fork(i);
        print("Philosopher " + philosopher + " started eating for " + to_string(eating_time));
        this_thread::sleep_for(std::chrono::milliseconds(eating_time));
        print("Philosopher " + philosopher + " stopped eating");
        release_fork(i);
    }
}

void exit_handler()
{
    while (true) {
        string key;
        key = to_string(cin.get());
        if (key == "e") {
            cout << "Exit signal received " << key << endl;
            EXIT_FLAG = true;
            break;
        }
    }
}

int main(int argc, char** argv)
{
    int thinking_sleeping[PHILOSOPHERS][2] = { { 700, 700 }, { 350, 350 }, { 1000, 1000 }, { 1000, 1000 }, { 1000, 2000 } };
    thread threads[PHILOSOPHERS];
    for (int i = 0; i < PHILOSOPHERS; i++) {
        threads[i] = thread(philosopher, i, thinking_sleeping[i][0], thinking_sleeping[i][1]);
    }
    exit_handler();
    for (auto &thread : threads) {
        thread.join();
    }
    cout << "Ended" << endl;
    return 0;
}