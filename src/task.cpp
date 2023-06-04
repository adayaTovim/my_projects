#include "task.hpp"

namespace mt::implementation_details {

Task::Task()
: m_boolFunc(nullptr)
, m_voidFunc(nullptr)
, m_period(std::chrono::milliseconds(0))
, m_repeatCount(0)
{
    m_nextExecutionTime = std::chrono::steady_clock::now();
}

Task::Task(std::function<bool()> a_taskFunc, std::chrono::milliseconds a_period)
: m_boolFunc(a_taskFunc)
, m_voidFunc(nullptr)
, m_period(a_period)
, m_repeatCount(0)
{
    m_nextExecutionTime = std::chrono::steady_clock::now() + m_period;
}

Task::Task(std::function<void()> a_taskFunc, std::chrono::milliseconds a_period)
: m_boolFunc(nullptr)
, m_voidFunc(a_taskFunc)
, m_period(a_period)
, m_repeatCount(0)
{
    m_nextExecutionTime = std::chrono::steady_clock::now() + m_period;
}

Task::Task(std::function<void()> a_taskFunc, std::chrono::milliseconds a_period, uint64_t a_repeatCount)
: m_boolFunc(nullptr)
, m_voidFunc(a_taskFunc)
, m_period(a_period)
, m_repeatCount(a_repeatCount)
{
    m_nextExecutionTime = std::chrono::steady_clock::now() + m_period;
}

Task::Task(const Task& a_other)
: m_boolFunc(a_other.m_boolFunc)
, m_voidFunc(a_other.m_voidFunc)
, m_period(a_other.m_period)
, m_nextExecutionTime(a_other.m_nextExecutionTime)
, m_repeatCount(a_other.m_repeatCount)
{
}

Task& Task::operator=(const Task& a_other)
{
    if (this != &a_other) {
        m_boolFunc = a_other.m_boolFunc;
        m_voidFunc = a_other.m_voidFunc;
        m_period = a_other.m_period;
        m_nextExecutionTime = a_other.m_nextExecutionTime;
        m_repeatCount = a_other.m_repeatCount;
    }
    return *this;  
}

bool Task::operator<(const Task& a_other) const
{
    return m_nextExecutionTime > a_other.m_nextExecutionTime;  
}

bool Task::operator()(std::mutex& a_mtxTask, std::condition_variable& a_cvTask)
{
    std::unique_lock<std::mutex> lock(a_mtxTask);
    a_cvTask.wait_until(lock, m_nextExecutionTime);

    // if the current time is still before the next execution time
    if(std::chrono::steady_clock::now() < m_nextExecutionTime) {
        --m_repeatCount;
        return true;
    }

    if(m_boolFunc) {
        m_boolFunc();
    }

    else if (m_voidFunc) {
        m_voidFunc();        
    }
    
    --m_repeatCount;
    updateTime();
    
    return m_repeatCount > 0;
}

void Task::updateTime()
{
    m_nextExecutionTime = std::chrono::steady_clock::now() + m_period;
}

void Task::setRepeatCount(uint64_t a_repeatCount) {
    m_repeatCount = a_repeatCount;
}



} // namespace mt::implementation_details

