#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace advcpp {

template <typename T, typename Q = std::queue<T>>    
class WaitableQueue {
public:
    WaitableQueue() = delete;
    explicit WaitableQueue(size_t a_capcity);
    WaitableQueue(WaitableQueue const& a_other) = delete;
    WaitableQueue& operator=(WaitableQueue const& a_other) = delete;
    ~WaitableQueue() = default;

    bool full() const;
    bool empty() const;
    size_t size() const;
    void enqueue(T const& a_item);
    void dequeue(T& a_element);

private:
    bool innerFull() const noexcept;
    bool innerEmpty() const noexcept;

private:   
    Q m_queue;
    mutable std::mutex m_mtx;
    size_t m_capacity;
    std::condition_variable m_notEmpty;
    std::condition_variable m_notFull;
};

} // namespace advcpp

#include "inl/waitable_queue.hxx"