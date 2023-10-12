// #include <iostream>
// #include <thread>
// #include <mutex>
// #include <future>
// #include <condition_variable>

// std::mutex mtx;
// std::condition_variable cv;

// void task(int a, int b, int & ret) {
//     int ret_a = a * a;
//     int ret_b = b * 2;
//     std::unique_lock<std::mutex> lock(mtx);
//     ret = ret_a + ret_b;
//     cv.notify_one();
// }

// int main () {
//     int ret = 0;
//     std::thread t(task, 1, 2, ret);
//     std::unique_lock<std::mutex> lock(mtx);
//     cv.wait(lock);
//     std::cout << "return value is" << ret;
//     t.join();
// }

//promise  future 通过promise和future来代替多线程中主线程获取子线程的值
#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>

void task(int a, int b, std::promise<int> & ret) {
    int ret_a = a * a;
    int ret_b = b * 2;
    ret.set_value(ret_a + ret_b);
}

void task1(int a, std::future<int>& b, std::promise<int> & ret) {
    int ret_a = a * a;
    int ret_b = b.get() * 2;//子线程等待主线程赋值
    ret.set_value(ret_a + ret_b);
}

int main() {
    int ret = 0;
    std::promise<int> p;
    std::future<int> f = p.get_future();//建立联系
    std::thread t(task, 1, 2, std::ref(p));


    // std::promise<int> p_in;
    // std::future<int> f_in = p_in.get_future();//建立联系
    // std::thread t1(task1, 1, std::ref(f_in), std::ref(p));
    // p_in.set_value(2);//主线程晚设值

    std::cout << "return value is" << f.get();//在主线程中来获取子线程的值，只能进行一次get
    t.join();
    // t1.join();
}