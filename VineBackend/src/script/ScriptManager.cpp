#include <vine/script/ScriptManager.h>

namespace vine
{
	ScriptManager::ScriptManager()
	{
		lua_.open_libraries(sol::lib::base);
	}

	ScriptManager::~ScriptManager()
	{
	}

	void ScriptManager::init()
	{
		createSingleton();
	}

	void ScriptManager::shutdown()
	{
		destroySingleton();
	}

	void ScriptManager::executeScript(const std::string& script)
	{
		lua_.script_file(script);
	}
}