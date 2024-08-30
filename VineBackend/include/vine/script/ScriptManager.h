#pragma once

#include <vine/util/Singleton.h>

#include <sol/sol.hpp>
#include <string>

namespace vine
{
	class ScriptManager : public Singleton<ScriptManager>
	{
		friend class Singleton<ScriptManager>;
	public:
		~ScriptManager();

		static void init();
		static void shutdown();


		void executeScript(const std::string& script);

	private:
		ScriptManager();

		sol::state lua_;
	};
}