#pragma once

namespace Forge
{
	class Engine;

	class Timer
	{
	private:
		friend class Engine;
		static void Start();
		static void Reset();
		static void BeginFrame();
		static void EndFrame();
		
		static double currentFrameBegin;
		static float deltaTime;
		static double time;
		static double timeSinceStart;
	public:
		static float DeltaTime();
		static float Time();
		static double StartTime();
	};

}
