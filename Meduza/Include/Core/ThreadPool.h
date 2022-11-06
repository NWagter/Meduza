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
			Worker(uint8_t const a_index, ThreadType const a_type);
			~Worker();

			void StartWorker();
			void StopWorker();
			void AddTasks(std::vector<Task>);
			void Join();
			void AddDependency(ThreadType const i_dependency) { m_dependencies.push_back(i_dependency); }

			uint8_t GetIndex() const { return m_index; }
			size_t TaskCount() const { return m_tasks.size(); }
			ThreadType GetThreadType() const { return m_type; }
			bool IsWorking() const;
		private:
			uint8_t const m_index;
			ThreadType const m_type;
			std::vector<ThreadType> m_dependencies;
			void WaitForDependencies();
			std::thread m_worker;
			bool m_active = false;

			std::vector<Task> m_tasks;
			std::atomic<size_t> m_currentTaskIdx = 0u;

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
			void PushTasks();
			void WaitForWorkersFinished();
			void WaitForWorkersFinishedOfType(ThreadType const a_type);
			void WaitForWorkersFinishedOfTypes(std::vector<ThreadType> const a_types);
		private:
			ThreadPool();
			~ThreadPool();

			static ThreadPool* ms_threadPool;
			uint8_t const m_hardwareMaxThreads;

			std::vector<Worker*> m_workers;
			std::map<uint8_t, std::vector<Task>> m_tasks;
		};
	}
}