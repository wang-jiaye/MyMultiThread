#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::mutex mtx;

int globalval = 0;
std::atomic<int> ato_globalval(0);//原子变量，可以直接保证线程安全

void test1() {
    for(int i = 0; i < 10000; i++) { 
      mtx.lock();
      globalval++;
      globalval--;
      //1.如果这边里面有个回调函数直接退出了，没有解锁过程会发生死锁
      //callfunc()
  
      //2.有个if判断然后直接return了，也未解锁会发生死锁

      //3.有两把锁上锁顺序不同，需要保证上锁顺序一致
      mtx.unlock();  
    }
}

void test2() {
    for(int i = 0; i < 10000; i++) { 
      //为了解决上方1，2中未及时解锁的问题，可以用lock_guard来解决
      std::lock_guard<std::mutex> lock(mtx);//就不用管上锁解锁了，类似于一个类在构造上锁析构解锁RAII,离开作用域自动解锁。
      //也可以使用unique_lock<std::mutex> lock_u(mtx);  lock_u.unlock();提供了解锁可以在函数内把握锁力度更加灵活
      globalval++;
      globalval--;
    }
}


int main() {
    std::thread thread1(test1);
    std::thread thread2(test1);

    thread1.join();
    thread2.join();

    std::cout << "globalval:" << globalval << std::endl; 
}