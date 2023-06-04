#include "mu_test.h"

#include <thread>
#include <optional>
#include <algorithm>
#include <chrono>
#include <thread>
#include <iostream>
#include <ostream>

#include "periodic_executor.hpp"
#include "task.hpp"

int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;

bool task1() {
    std::cout << "Task1 count: " << ++count1 << std::endl;
    return true;
}

void task2() {
    std::cout << "Task2 count: " << ++count2 << std::endl;
}

void task3() {
    std::cout << "Task3 count: " << ++count3 << std::endl;
}

void task4() {
    std::cout << "Task4 count: " << ++count4 << std::endl;
    throw std::runtime_error("Test exception");
}

BEGIN_TEST(runTasks)
    using namespace mt;
    count1 = 0;
    count2 = 0;
    count3 = 0;
    PeriodicExecutor executor(10);

    // submit tasks with different periods
    executor.submit(std::function<bool()>(task1), std::chrono::milliseconds(500));
    executor.submit(std::function<void()>(task2), std::chrono::milliseconds(1000));
    executor.submit(std::function<void()>(task3), std::chrono::milliseconds(2000), 5); // repeat 5 times
    std::this_thread::sleep_for(std::chrono::seconds(5)); 

    executor.pause();
    std::this_thread::sleep_for(std::chrono::seconds(3)); 

    executor.resume();
    std::this_thread::sleep_for(std::chrono::seconds(5)); 

    executor.stop();
    ASSERT_PASS();

END_TEST

BEGIN_TEST(emptyQueue)
    using namespace mt;
    PeriodicExecutor executor(10);

    executor.stop();
    ASSERT_PASS();

END_TEST

BEGIN_TEST(throwsException)
    using namespace mt;
    count4 = 0;
    PeriodicExecutor executor(10);

    executor.submit(std::function<void()>(task4), std::chrono::milliseconds(500));
    std::this_thread::sleep_for(std::chrono::seconds(3)); 
    executor.stop();
    ASSERT_PASS();
END_TEST

BEGIN_TEST(testWithVector)
    using namespace mt;

    std::vector<std::chrono::steady_clock::time_point> vector;
    PeriodicExecutor executor(10);
    executor.submit([&vector](){ 
        std::cout << "run task lambda" << std::endl;
        vector.push_back(std::chrono::steady_clock::now());
    }, std::chrono::milliseconds(100), 5);

    std::this_thread::sleep_for(std::chrono::seconds(3)); // pause for 3 seconds
    executor.stop();

    // Check that the task was executed 5 times
    ASSERT_EQUAL(vector.size(), 5);

    // Check that each time is within 20ms of the expected time
    for (size_t i = 1; i < vector.size(); ++i) {
        auto diff = vector[i] - vector[i-1];
        ASSERT_EQUAL(diff >= std::chrono::milliseconds(80) && diff <= std::chrono::milliseconds(120), true);
    }

END_TEST

BEGIN_TEST(testWithVectorException)
    using namespace mt;

    std::vector<std::chrono::steady_clock::time_point> vector;
    PeriodicExecutor executor(10);

    executor.submit([&vector](){ 
        std::cout << "run task lambda" << std::endl;
        vector.push_back(std::chrono::steady_clock::now());
        throw std::runtime_error("Test lambda exception");
    }, std::chrono::milliseconds(100), 5);

    std::this_thread::sleep_for(std::chrono::seconds(3)); // pause for 3 seconds
    executor.stop();
    
    ASSERT_EQUAL(vector.size(), 1);
END_TEST

BEGIN_TEST(fullQueue)
    using namespace mt;
    PeriodicExecutor executor(1);

    // submit more tasks than the capacity
    executor.submit(std::function<bool()>(task1), std::chrono::milliseconds(500));
    executor.submit(std::function<void()>(task2), std::chrono::milliseconds(1000));

    std::this_thread::sleep_for(std::chrono::seconds(5));

    executor.stop();
    ASSERT_PASS();
END_TEST

TEST_SUITE(因果応報 [periodic executor])
    TEST(runTasks)
    TEST(throwsException)
    TEST(emptyQueue)
    TEST(testWithVector)
    TEST(testWithVectorException)
    TEST(fullQueue)
    //TEST(testStop)

END_SUITE
