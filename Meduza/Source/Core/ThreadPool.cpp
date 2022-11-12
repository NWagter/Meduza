#include "MePCH.h"
#include "Core/ThreadPool.h"

//----------------------------------------------------------------
// ThreadPool
//----------------------------------------------------------------

Me::Threading::ThreadPool* Me::Threading::ThreadPool::ms_threadPool = nullptr;

Me::Threading::ThreadPool* Me::Threading::ThreadPool::CreateThreadPool()
{
    if (ms_threadPool != nullptr)
    {
        ME_CORE_LOG("ThreadPool alrady exists! \n");
        return ms_threadPool;
    }

    ms_threadPool = new ThreadPool();
    return ms_threadPool;
}

void Me::Threading::ThreadPool::DestroyThreadPool()
{
    delete ms_threadPool;
    ms_threadPool = nullptr;
}

Me::Threading::ThreadPool::ThreadPool() :
    m_hardwareMaxThreads(std::thread::hardware_concurrency())
{
    std::vector<ThreadType> requiredTypes = 
    {
        ThreadType::Render,
        ThreadType::Main,
        ThreadType::Physics_Begin,
        ThreadType::Physics_End,
        ThreadType::Scripting,
    };

    ME_CORE_LOG("%u threads supported | %zu Threads Used \n", m_hardwareMaxThreads, requiredTypes.size());

    //Create Required Workers
    for (uint8_t i = m_workers.size(); i < requiredTypes.size(); i++)
    {
        m_workers.push_back(new Worker(i, requiredTypes.at(i)));
    }

    // Add dependencies where needed
    for (auto worker : m_workers)
    {
        if (worker->GetThreadType() == ThreadType::Scripting)
        {
            worker->AddDependency(ThreadType::Physics_Begin);
        }
        if (worker->GetThreadType() == ThreadType::Physics_End)
        {
            worker->AddDependency(ThreadType::Scripting);
            worker->AddDependency(ThreadType::Physics_Begin);
        }
    }
}

Me::Threading::ThreadPool::~ThreadPool()
{
    for (auto worker : m_workers)
    {
        worker->StopWorker();
        delete worker;
    }
}

void Me::Threading::ThreadPool::AddTask(Task a_newTask, ThreadType const a_type)
{
    Worker* usableWorker = nullptr;
    size_t numberOfTask = 0;
    for (auto worker : m_workers)
    {
        if (worker->GetThreadType() != a_type)
        {
            continue;
        }

        if (!usableWorker || worker->TaskCount() < numberOfTask)
        {
            numberOfTask = worker->TaskCount();
            usableWorker = worker;
        }
    }

    if (usableWorker)
    {
        m_tasks[usableWorker->GetIndex()].push_back(a_newTask);
    }
}

void Me::Threading::ThreadPool::PushTasks()
{
    for (auto worker : m_workers)
    {
        auto it = m_tasks.find(worker->GetIndex());
        if (it != m_tasks.end())
        {
            worker->AddTasks(m_tasks.at(worker->GetIndex()));
            m_tasks.at(worker->GetIndex()).clear();
        }
    }
}

void Me::Threading::ThreadPool::WaitForWorkersFinished()
{
    bool working = true;
    while (working)
    {
        bool stillWorking = false;

        for (auto worker : m_workers)
        {
            stillWorking |= worker->IsWorking();
        }

        if (!stillWorking)
        {
            working = stillWorking;
        }
    }
}

void Me::Threading::ThreadPool::WaitForWorkersFinishedOfType(ThreadType const a_type)
{
    bool working = true;
    while (working)
    {
        bool stillWorking = false;

        for (auto worker : m_workers)
        {
            if (worker->GetThreadType() == a_type)
            {
                stillWorking |= worker->IsWorking();
            }
        }

        if (!stillWorking)
        {
            working = stillWorking;
        }
    }
}

void Me::Threading::ThreadPool::WaitForWorkersFinishedOfTypes(std::vector<ThreadType> const a_types)
{
    bool working = true;
    while (working && !a_types.empty())
    {
        bool stillWorking = false;

        for (auto worker : m_workers)
        {
            for (auto type : a_types)
            {
                if (worker->GetThreadType() == type)
                {
                    stillWorking |= worker->IsWorking();
                }
            }
        }

        if (!stillWorking)
        {
            working = stillWorking;
        }
    }
}

//----------------------------------------------------------------
// Workers
//----------------------------------------------------------------

Me::Threading::Worker::Worker(uint8_t const a_index, ThreadType const a_type) :
    m_index(a_index), m_type(a_type)
{
    auto startWorker = [this]()
    {
        StartWorker();
    };

    m_worker = std::thread(startWorker);
}

Me::Threading::Worker::~Worker()
{
    ME_CORE_LOG("%s:Worker:ID %u deleted \n", GetThreadTypeName(m_type).c_str(), m_index);
    m_worker.join();
}

void Me::Threading::Worker::StartWorker()
{
    ME_CORE_LOG("%s:Worker:ID %u started |  \n", GetThreadTypeName(m_type).c_str(), m_index);
    m_active = true;

    while (m_active)
    {
        WaitForDependencies();

        if (m_currentTaskIdx >= m_tasks.size())
        {
            std::unique_lock<std::mutex> lk(m_lock);
            m_hasTasks.wait(lk, [this]()
                {
                    return (m_currentTaskIdx < m_tasks.size()) || !m_active;
                });
            continue;
        }

        m_lock.lock();
        // Run Task
        Task task = m_tasks.at(m_currentTaskIdx);
        task.taskFunction(task.m_system, task.m_deltaTime);
        task.m_completed = true;
        m_currentTaskIdx.fetch_add(1);
        m_lock.unlock();
    }
}

void Me::Threading::Worker::StopWorker()
{
    std::lock_guard<std::mutex> lk(m_lock);
    m_active = false;
    m_hasTasks.notify_all();
}

void Me::Threading::Worker::Join()
{
    if (m_worker.joinable())
    {
        m_worker.join();
    }
}

void Me::Threading::Worker::AddTasks(std::vector<Task> a_tasks)
{
    std::lock_guard<std::mutex> lk(m_lock);
    m_tasks = a_tasks;
    m_currentTaskIdx = 0u;
    m_hasTasks.notify_all();
}

bool Me::Threading::Worker::IsWorking() const
{
    return !(m_currentTaskIdx >= m_tasks.size());
}

void Me::Threading::Worker::WaitForDependencies()
{
    ThreadPool::GetThreadPool()->WaitForWorkersFinishedOfTypes(m_dependencies);
}

std::string Me::Threading::GetThreadTypeName(ThreadType const a_type)
{
    switch (a_type)
    {
    case ThreadType::Main:
        return "MainThread";
        break;
    case ThreadType::Render:
        return "RenderThread";
        break;
    case ThreadType::Physics_Begin:
        return "Physics_BeginThread";
        break;
    case ThreadType::Physics_End:
        return "Physics_EndThread";
        break;
    case ThreadType::Scripting:
        return "ScriptingThread";
        break;
    }

    return "";
}