//信号量为c++20引入,确保编译器支持g++20
#include <iostream>
#include <deque>
#include <thread>
#include <condition_variable>

#include <semaphore.h>//信号量头文件

//LeastMaxValue
std::counting_semaphore<6> csem(0);//<>代表最大能release的线程数量
std::binary_semaphore bsem(0);//内部传入0代表计数器从0开始，binary_semaphore为特化每次增减1

//semaphore release == condition_variable notify  信号量增加1等价于条件变量的唤醒一个线程
//semaphore acquire == condition_variable wait

void thread_work() {
    std::cout << "ready to recv signal: acquire" << std::endl;
    bsem.acquire();
    //csem.acquire();见下方同注释调用csem
    std::cout << "acquire end" << std::endl;
}

int main() {
    std::thread t(thread_work);
    // std::thread1 t1(thread_work);
    // std::thread2 t2(thread_work);
    // std::thread3 t3(thread_work);

    std::cout << "ready to signal: release" << std::endl;
    bsem.release();
    //csem.release(3);随机唤醒4个线程中的3个，最大不能超过上方声明的
    std::cout << "signal end" << std::endl;

}