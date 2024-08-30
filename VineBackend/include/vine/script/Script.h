#pragma once

#include <string>
#include <sol/sol.hpp>

namespace vine
{
	class Script
	{
	public:
		Script(sol::state& lua);
		~Script();

		void loadScript(const std::string& script);

	private:
		const std::string luaFile_;

		sol::state& lua_;
	};
}