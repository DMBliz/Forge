#pragma once

namespace Forge
{
	enum class ScriptState
	{
		Uninitialized,
		UnStarted,

		Running,
		Paused,

		Destroyed
	};
	
	class Script
	{
	protected:
		ScriptState state;
	public:
		Script();
		~Script();

		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;

		virtual void OnInit() = 0;
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnDestroy() = 0;

		ScriptState GetState() { return state; }

		virtual bool HasUpdate() { return false; }
		virtual bool HasStart() { return false; }
		virtual bool HasInit() { return false; }
		virtual bool HasDestroy() { return false; }
	};

}
