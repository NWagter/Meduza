#pragma once

namespace Me
{
	class ECSSystem;
	namespace Threading
	{
		static std::string GetThreadTypeName(ThreadType const a_type);

		struct Task
		{
			void(*taskFunction)(ECSSystem*, float);
			float m_deltaTime;
			ECSSystem* m_system;

			bool m_completed = false;
		};

		class Worker
		{
		public:
			Worker(uint8_t const a_index, ThreadType const a_type = ThreadType::Unkown);
			~Worker();

			void StartWorker();
			void StopWorker();
			void AddTask(Task);
			void Join();

			size_t TaskCount() const { return m_tasks.size(); }
			ThreadType GetThreadType() const { return m_type; }
		private:
			uint8_t const m_index;
			ThreadType const m_type;
			std::thread m_worker;
			bool m_active = false;

			bool m_waitingForTasks = false;
			std::vector<Task> m_tasks;

			std::mutex m_lock;
			std::condition_variable m_hasTasks;
		};

		class ThreadPool
		{
		public:

			static ThreadPool* CreateThreadPool();
			static void DestroyThreadPool();
			inline static ThreadPool* GetThreadPool() { return ms_threadPool; }
						
			void AddTask(Task a_newTask, ThreadType const a_type = ThreadType::Main);
			void NotifyWorkers();
			void JoinWorkers();
			void JoinWorkersOfType(ThreadType const a_type);
		private:
			ThreadPool();
			~ThreadPool();

			static ThreadPool* ms_threadPool;
			uint8_t const m_hardwareMaxThreads;

			std::vector<Worker*> m_workers;
		};
	}
}