#pragma once
// ======= Copied code from Tim van den Bosch

#include <chrono>

namespace Me
{
	template<typename T = float, typename = typename std::enable_if<
		std::is_same<float, T>::value ||
		std::is_same<double, T>::value || 
		std::is_same<int, T>::value,
	T>::type>
	class Timer
	{
	public:
		using Clock = std::chrono::high_resolution_clock;
		using Seconds = std::chrono::duration<T>;
		using TimePoint = std::chrono::time_point<Clock>;

		Timer()
			: m_startTime(Clock::now()),
			m_prevTime(m_startTime),
			m_currentDuration(T(0))
		{
			
		}

		void SetStartTime(TimePoint a_time)
		{
			m_startTime = a_time;
		}

		void Start(T a_duration, bool a_reset = true)
		{
			if(a_reset)
			{
				Reset();
			}

			m_currentDuration = a_duration;
		}

		void Stop()
		{
			m_currentDuration = T(0);
		}

		void Reset()
		{
			SetStartTime(Clock::now());
			m_prevTime = m_startTime;
		}

		T GetTimeSinceStart() const
		{
			return T(Seconds(Clock::now() - m_startTime).count());
		}

		T GetElapsedTime()
		{
			const T elapsed = Seconds(Clock::now() - m_prevTime).count();
			m_prevTime = Clock::now();
			return elapsed;
		}

		T GetCurrentDuration()
		{
			return m_currentDuration;
		}

		bool IsFinished()
		{
			m_currentDuration -= GetElapsedTime();
			return m_currentDuration <= T(0);
		}
	private:
		TimePoint m_startTime;
		TimePoint m_prevTime;

		T m_currentDuration;
	};
}
