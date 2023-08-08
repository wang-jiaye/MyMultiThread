#include <iostream>
#include <deque>
#include <thread>
#include <condition_variable>

std::mutex mtx;
std::deque<int> q;
std::condition_variable cv;

//producer
void test1() {
    int i = 0;
    while(true) {
        std::unique_lock<std::mutex> lock(mtx);
        q.push_back(i);
        cv.notify_one();//唤醒一个线程
        //cv.notify_all();//唤醒全部线程
        i++;
    }
}


//consumer 1
void test2() {
    int data = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        while (q.empty())
        {
            cv.wait(lock);
        }
        data = q.front();
        q.pop_front();
        std::cout << "value: " << data << std::endl;
    } 
}


int main() {
    std::thread thread1(test1);
    std::thread thread2(test2);

    thread1.join();
    thread2.join();
}