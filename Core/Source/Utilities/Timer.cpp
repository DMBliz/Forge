#include "Timer.h"
#include <chrono>

namespace Forge
{
	float Timer::deltaTime;
	double Timer::currentFrameBegin;
	double Timer::time;
	double Timer::timeSinceStart;

	void Timer::Start()
	{		
		timeSinceStart = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000.0f;
		time = timeSinceStart;
	}

	void Timer::Reset()
	{
		time = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	}

	void Timer::BeginFrame()
	{
		currentFrameBegin = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000.0;
	}

	void Timer::EndFrame()
	{
		double endFrame = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000.0f;
		deltaTime = endFrame - currentFrameBegin;
	}

	float Timer::DeltaTime()
	{
		return deltaTime;
	}

	float Timer::Time()
	{
		
		return std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000.0f - time;
	}

	double Timer::StartTime()
	{
		return std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000.0f - timeSinceStart;
	}
}
