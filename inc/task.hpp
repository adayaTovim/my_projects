#pragma once

#include <chrono>
#include <functional>
#include <cstdint> //uint64_t
#include <mutex>
#include <condition_variable>
#include <thread>

namespace mt::implementation_details {

class Task {
public:
    Task();
    explicit Task(std::function<bool()> a_taskFunc, std::chrono::milliseconds a_period);
    explicit Task(std::function<void()> a_taskFunc, std::chrono::milliseconds a_period);
    explicit Task(std::function<void()> a_taskFunc, std::chrono::milliseconds a_period, uint64_t a_repeatCount);
    Task(const Task& a_other);

    Task& operator=(const Task& a_other);
    bool operator<(const Task& a_other) const;

    void updateTime();
    
    bool operator()(std::mutex& a_mtxTask, std::condition_variable& a_cvTask);
    void setRepeatCount(uint64_t a_repeatCount);

private:
    std::function<bool()> m_boolFunc;
    std::function<void()> m_voidFunc;
    std::chrono::milliseconds m_period;
    std::chrono::steady_clock::time_point m_nextExecutionTime;
    mutable uint64_t m_repeatCount;
};

} // namespace mt::implementation_details

