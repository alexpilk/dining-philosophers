#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <ncurses.h>
#include "Philosopher.h"
#include "Waiter.h"

using namespace std;

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


int main(int argc, char** argv)
{
    auto* waiter = new Waiter();

    const int PHILOSOPHERS = 5;
    int thinking_sleeping[PHILOSOPHERS][2] = {{200, 250}, {300, 300}, {400, 350}, {500, 100}, {600, 200}};
    thread threads[PHILOSOPHERS];
    for (int i =0; i < PHILOSOPHERS; i++) {
        Philosopher* p = waiter->add_philosopher(thinking_sleeping[i][0], thinking_sleeping[i][1]);
        threads[i] = thread(&Philosopher::loop, p);
    }

//    initscr();			/* Start curses mode 		  */
    thread w(&Waiter::release_from_queue, waiter);
//    mvprintw(0, 0, "Hello World 1 !!!");	/* Print Hello World		  */
//    a->display("cool", 2);
//    refresh();			/* Print it on to the real screen */
//    getch();			/* Wait for user input */
//    mvprintw(0, 0, "Hello World 2 !!!");	/* Print Hello World		  */
//    refresh();			/* Print it on to the real screen */
    exit_handler(waiter);
    w.join();
    for (auto &thread : threads) {
        thread.join();
    }
//    endwin();			/* End curses mode		  */

    return 0;
}