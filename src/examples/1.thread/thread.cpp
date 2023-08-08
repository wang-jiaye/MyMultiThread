#include <iostream>
#include <thread>

void test(int a) {//创建的子线程干活
    while (true)
    {
        std::cout << "call test" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
}

int main() {
    int a = 0;
    std::thread thread1(test, a);
    thread1.join();//join会等待子线程干完后再执行后方的代码，这边子线程为死循环所以不会往下走
     std::cout << "thread id" <<  thread1.get_id() << std::endl;
    while (true)//主线程干活
    {
        std::cout << "call main" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));//添加延时死循环高cpu占用
    }
    
}