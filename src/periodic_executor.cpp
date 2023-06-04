#include <ostream>
#include <iostream>

#include "periodic_executor.hpp"

namespace mt {

PeriodicExecutor::PeriodicExecutor(size_t a_capacity)
: m_tasks(a_capacity + 1)
, m_capacity(a_capacity)
, m_isPaused(false)
, m_stop(false)
, m_thread([this]() { run(); })  
{
}

PeriodicExecutor::~PeriodicExecutor()
{
    {    
        std::unique_lock<std::mutex> lock(m_mtxPause);
        m_stop = true;
        m_isPaused = false;
        m_cvPause.notify_all();
    }
    m_thread.join();
}

void PeriodicExecutor::submit(std::function<bool()> a_taskFunc, std::chrono::milliseconds a_period)
{
    if(m_tasks.size() >= m_capacity) {
        std::cerr << "Task container is full" << std::endl;
        return;
    }
    Task task(a_taskFunc, a_period);
    m_tasks.enqueue(task);
}

void PeriodicExecutor::submit(std::function<void()> a_taskFunc, std::chrono::milliseconds a_period)
{
    if(m_tasks.size() >= m_capacity) {
        std::cerr << "Task container is full" << std::endl;
        return;
    }
    Task task(a_taskFunc, a_period);
    m_tasks.enqueue(task);
}

void PeriodicExecutor::submit(std::function<void()> a_taskFunc, std::chrono::milliseconds a_period, uint64_t a_repeatCount)
{
    if(m_tasks.size() >= m_capacity) {
        std::cerr << "Task container is full" << std::endl;
        return;
    }
    Task task(a_taskFunc, a_period, a_repeatCount);
    m_tasks.enqueue(task);
}

void PeriodicExecutor::pause()
{
    {
        std::unique_lock<std::mutex> lock(m_mtxPause);
        m_isPaused = true;
        m_cvPause.notify_all();
    }
    std::cout<<"in pause"<<std::endl;
}

void PeriodicExecutor::resume()
{
    std::unique_lock<std::mutex> lock(m_mtxPause);
    m_isPaused = false;
    m_cvPause.notify_all();
}


void PeriodicExecutor::stop()
{
    {
        std::unique_lock<std::mutex> lock(m_mtxPause);
        m_stop = true;  
        m_cvPause.notify_all();
    }
    //poisoned apple add empty task 
    Task task{[](){}, std::chrono::milliseconds(0)};
    m_tasks.enqueue(task);
}

void PeriodicExecutor::run()
{
	bool repeatTask = false;
    std::unique_lock<std::mutex> lock(m_mtxPause);
    while(!m_stop) {
		lock.unlock();

        Task task;
        m_tasks.dequeue(task);
        
		//in pause case- wait to resume
        {
            std::unique_lock<std::mutex> lock(m_mtxPause);
            m_cvPause.wait(lock, [this]() {
                return !m_isPaused ;
            });
        }

		try{
			repeatTask = task(m_mtxPause, m_cvPause);
		}
        catch(std::exception const& x){
            task.setRepeatCount(0);
			std::cerr << "Exception in task: " << x.what() << std::endl;

		}
        catch(...){
            task.setRepeatCount(0);
			std::cerr << "Unknow Exception in task. Shame on you!!!\n";
		}

        if(repeatTask) {
            m_tasks.enqueue(task);
        }

		lock.lock();
    }
}

} // namespace mt

