#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
//#if defined(_GLIBCXX_HAS_GTHREADS) && defined(_GLIBCXX_USE_C99_STDINT_TR1)


using namespace std;

int D = 0;
bool EXIT = false;
const int PHILOSOPHERS = 5;
bool FORKS[PHILOSOPHERS*2] = {false};
mutex mtx;

void task1(string t) {
    // do stuff
    for (int i = 0; i < 40; ++i) {
        if (EXIT) {
            return;
        }
        this_thread::sleep_for(std::chrono::milliseconds(200));
        mtx.lock();
        D++;
        mtx.unlock();
        cout << t << " " << D <<endl;
    }
}

void take_fork(int philosopher){
    mtx.lock();
    int L = philosopher * 2;
    int R = L + 1;
    FORKS[L] = true;
    FORKS[R] = true;
    mtx.unlock();
    cout << "Philosopher " << philosopher << " took forks " << L << " and " << R << endl;
}

void release_fork(int philosopher){
    mtx.lock();
    int L = philosopher * 2;
    int R = L + 1;
    FORKS[L] = true;
    FORKS[R] = true;
    mtx.unlock();
    cout << "Philosopher " << philosopher << " released forks " << L << " and " << R << endl;
}

void philosopher(int i, int eating_time, int thinking_time) {
    // do stuff
    while (true) {
        if (EXIT) {
            cout << "Philosopher " << i << " exiting";
            return;
        }
        cout << "Philosopher " << i << " started thinking for " << thinking_time << endl;
        this_thread::sleep_for(std::chrono::milliseconds(thinking_time));
        cout << "Philosopher " << i << " stopped thinking";
        mtx.lock();
        take_fork(i);
        cout << "Philosopher " << i << " started eating";
        this_thread::sleep_for(std::chrono::milliseconds(eating_time));
        cout << "Philosopher " << i << " stopped eating";
        release_fork(i);
        mtx.unlock();
    }
}

void exit_handler() {
    while (true) {
        int key = cin.get();
        if (key) {
            EXIT = true;
            break;
        }
    }
}

int main (int argc, char ** argv) {
    int thinking_sleeping[PHILOSOPHERS][2] = {{200, 250}, {300, 300}, {400, 350}, {500, 100}, {600, 200}};
    thread threads[PHILOSOPHERS];
    for (int i =0; i < PHILOSOPHERS; i++) {
        threads[i] = thread(philosopher, i, thinking_sleeping[i][0], thinking_sleeping[i][1]);
    }
//    thread thread_1 = thread(philosopher, 0, 200, 200);
//    thread thread_2 = thread(task1, "T2");
    exit_handler();
    // do other stuff
//    thread_2.join();
//    thread_1.join();
    for (int i =0; i < PHILOSOPHERS; i++) {
        threads[i].join();
    }
    cout << "Ended" << endl;
    return 0;
}