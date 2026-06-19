/* Basic Thread Example */
// #include <iostream>
// #include <thread>
// using namespace std;

// void sayHello(int id){
//     cout << "Hello from thread" << id << "\n";
// }

// int main(void){
//    thread t1(sayHello, 1);
//    thread t2(sayHello, 2);

//    t1.join();
//    t2.join();
//    return 0;
// }

/* 🔷 2. The Problem — Race Conditions
What if two threads touch the same variable at the same time? */
// #include <iostream>
// #include <thread>

// using namespace std;

// int counter = 0;

// void increment(){
//     for (int i = 0; i < 100000; i++)
//          counter++;
// }

// int main(){
//     thread t1(increment);
//     thread t2(increment);

//     t1.join();
//     t2.join();

//     cout << counter << "\n";
// }


/* 
🔷 3. Mutex — The Lock
A mutex (mutual exclusion) is a lock. Only one thread can hold it at a time. Others wait.*/

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int counter = 0;
mutex mtx;

void increment(){
    for (int i = 0; i < 100000; i++){
        mtx.lock();
        counter++;
        mtx.unlock();
    }
}

int main(){
    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();

    cout << counter << "\n";
}