#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <ncurses.h>
#include "Philosopher.h"
#include "Waiter.h"
//#include "../../.CLion2019.1/system/.remote/10.42.77.48_22/135844fd-e843-4f56-850c-5ac626575793/usr/include/c++/6/mutex"

using namespace std;

const int PHILOSOPHERS = 5;
bool FORKS[PHILOSOPHERS * 2] = { false };
//bool EXIT_F = false;
mutex cout_mutex;

bool EXIT_FLAG;

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

void exit_handler(Waiter* waiter)
{
    while (true) {
        cout << "EXIT HANDLER" << endl;
        string key;
        key = cin.get();
        cout << key << " yup" << endl;
        if (key == "e") {
            cout << "Exit signal received " << key << endl;
            waiter->EXIT = true;
            break;
        }
    }
}

void test(){
//    mutex m1;
//    mutex m2;
//    m1.try_lock();
//    std::scoped_lock try_lock(m1, m2, std::try_to_lock);
////    cout << m1.try_lock() << endl;
////    cout << m2.try_lock() << endl;
//    this_thread::sleep_for(std::chrono::milliseconds(1000));
////    m1.unlock();
////    m2.unlock();

}
int main(int argc, char** argv)
{
//    thread t(test);
//    t.join();
    auto* waiter = new Waiter(4);
    Philosopher* p = waiter->add_philosopher(2000, 2000);
    Philosopher* p2 = waiter->add_philosopher(2000, 2000);
    Philosopher* p3 = waiter->add_philosopher(2000, 2000);
    Philosopher* p4 = waiter->add_philosopher(2000, 2000);
//    initscr();			/* Start curses mode 		  */
    thread w(&Waiter::release_from_queue, waiter);
    thread t(&Philosopher::loop, p);
    thread t2(&Philosopher::loop, p2);
    thread t3(&Philosopher::loop, p3);
    thread t4(&Philosopher::loop, p4);
//    mvprintw(0, 0, "Hello World 1 !!!");	/* Print Hello World		  */
//    a->display("cool", 2);
//    refresh();			/* Print it on to the real screen */
//    getch();			/* Wait for user input */
//    mvprintw(0, 0, "Hello World 2 !!!");	/* Print Hello World		  */
//    refresh();			/* Print it on to the real screen */
//    getch();
    exit_handler(waiter);
    w.join();
    t.join();
    t2.join();
    t3.join();
    t4.join();
//    endwin();			/* End curses mode		  */
//
//    return 0;


//    int thinking_sleeping[PHILOSOPHERS][2] = { { 700, 700 }, { 350, 350 }, { 1000, 1000 }, { 1000, 1000 }, { 1000, 2000 } };
//    thread threads[PHILOSOPHERS];
//    for (int i = 0; i < PHILOSOPHERS; i++) {
//        threads[i] = thread(philosopher, i, thinking_sleeping[i][0], thinking_sleeping[i][1]);
//    }
//    exit_handler();
//    for (auto &thread : threads) {
//        thread.join();
//    }
//    cout << "Ended" << endl;
    return 0;
}