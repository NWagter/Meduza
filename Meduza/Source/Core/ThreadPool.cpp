#include "MePCH.h"
#include "Core/ThreadPool.h"

//----------------------------------------------------------------
// ThreadPool
//----------------------------------------------------------------

constexpr float g_fractionOfMaxThreadsUsed = 0.8f;
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
        ThreadType::Main,
        ThreadType::Render,
        //ThreadType::Physics,
        //ThreadType::Transformation,
        //ThreadType::Scripting,
    };

    uint8_t const threadsAllowed = 2; // static_cast<uint8_t>(Math::Max(requiredTypes.size(), m_hardwareMaxThreads * g_fractionOfMaxThreadsUsed));
    ME_CORE_LOG("%u threads supported | %u allowedThreads \n", m_hardwareMaxThreads, threadsAllowed);

    //Create Required Workers
    for (uint8_t i = m_workers.size(); i < requiredTypes.size(); i++)
    {
        m_workers.push_back(new Worker(i, requiredTypes.at(i)));
    }

    // Create extra Workers
    for (uint8_t i = m_workers.size(); i < threadsAllowed; i++)
    {
        m_workers.push_back(new Worker(i));
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
        usableWorker->AddTask(a_newTask);
    }
}

void Me::Threading::ThreadPool::JoinWorkers()
{
    for (auto worker : m_workers)
    {
        worker->Join();
    }
}

void Me::Threading::ThreadPool::JoinWorkersOfType(ThreadType const a_type)
{
    for (auto worker : m_workers)
    {
        if (worker->GetThreadType() == a_type)
        {
            worker->Join();
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
    ME_CORE_LOG("Worker%u deleted \n", m_index);
    m_worker.join();
}

void Me::Threading::Worker::StartWorker()
{
    ME_CORE_LOG("Worker%u started | %s \n", m_index, GetThreadTypeName(m_type).c_str());
    m_active = true;

    size_t index = 0;
    while (m_active)
    {
        if (m_tasks.empty() || index >= m_tasks.size())
        {
            std::unique_lock<std::mutex> lk(m_lock);
            m_hasTasks.wait(lk, [this]()
                {
                    return !m_tasks.empty() || !m_active;
                });
            continue;
        }

        m_lock.lock();
        // Run Task
        Task task = m_tasks.at(index);
        task.taskFunction(task.m_system, task.m_deltaTime);
        task.m_completed = true;
        index++;
        m_lock.unlock();
    }

    ME_CORE_LOG("Worker%u stopped \n", m_index);
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

void Me::Threading::Worker::AddTask(Task a_task)
{
    m_tasks.push_back(a_task);

    std::lock_guard<std::mutex> lk(m_lock);
    m_hasTasks.notify_all();
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
    case ThreadType::Physics:
        return "PhysicsThread";
        break;
    case ThreadType::Transformation:
        return "TransformationThread";
        break;
    case ThreadType::Scripting:
        return "ScriptingThread";
        break;
    case ThreadType::Unkown:
        return "UnkownThread";
        break;
    }

    return "";
}