#include <chrono>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "waitable_queue.hpp"
#include "task.hpp"

namespace mt {

class PeriodicExecutor {
public:
    explicit PeriodicExecutor(size_t a_capacity);
    ~PeriodicExecutor();
    PeriodicExecutor(const PeriodicExecutor& a_other) = default;
    PeriodicExecutor& operator=(const PeriodicExecutor& a_other) = default;

    void submit(std::function<bool()> , std::chrono::milliseconds a_period);
    void submit(std::function<void()> , std::chrono::milliseconds a_period);
    void submit(std::function<void()> , std::chrono::milliseconds a_period, uint64_t a_repeatCount);

    void pause();
    void resume();
    void stop();

private:
    void run();

private:
	using Task = implementation_details::Task;
    advcpp::WaitableQueue<Task, std::priority_queue<Task>> m_tasks;
    size_t m_capacity;
    
    std::mutex m_mtxPause;
    std::condition_variable m_cvPause;
    
    bool m_isPaused;
    bool m_stop;

    std::thread m_thread;
};

} // mt
