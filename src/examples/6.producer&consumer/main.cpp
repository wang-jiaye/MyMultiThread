// 1.队列满了，生产者停止生产。生产者wait条件变量
// 2.队列空了，消费者停止取。消费者wait条件变量
// 3.队列，正常
//消费者生产者模型
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::queue<int> dataQueue;
const int kmaxsize = 5;
std::mutex mtx;
std::condition_variable not_empty_cv;
std::condition_variable not_full_cv;
int i = 1;

void producer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        if(dataQueue.size() >= kmaxsize) 
        {      
            std::cout << "dataQueue is full!" << std::endl;    
            not_full_cv.wait(lock);
        }
        else {//生产者会先生产一个放入保证不为空，然后再去随机通知一个消费者。所以不会有问题
            dataQueue.push(i++);
            std::cout << "Produced: " << i << std::endl;
            not_empty_cv.notify_one(); // Notify consumers
        }        
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void consumer(int id)
{
    while (true)
    {
        std::unique_lock<std::mutex> ulock(mtx);
        if(dataQueue.empty()) {
            std::cout << "dataQueue is empty!" << std::endl;
            not_empty_cv.wait(ulock);
        }
        else {//消费者会先消费一个保证不为满，然后再去随机通知一个生产者。所以不会有问题
            int data = dataQueue.front();
            dataQueue.pop();
            ulock.unlock();
            std::cout << "Consumer " << id << " consumed: " << data << std::endl;
            not_full_cv.notify_one(); // Notify producer    
        }      
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main()
{
    std::thread prodThread(producer);
    std::thread consThread1(consumer, 1);
    std::thread consThread2(consumer, 2);
    std::thread consThread3(consumer, 3);
    std::thread consThread4(consumer, 4);
    std::thread consThread5(consumer, 5);

    prodThread.join();
    consThread1.join();
    consThread2.join();
        consThread3.join();
    consThread4.join();
        consThread5.join();
    return 0;
}