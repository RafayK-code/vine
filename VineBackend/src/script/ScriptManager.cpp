#include <vine/script/ScriptManager.h>

#include <vine/core/Logger.h>

namespace vine
{
    ScriptManager::ScriptManager()
    {
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

    std::shared_ptr<Script> ScriptManager::addScript(std::shared_ptr<Script> script)
    {
        auto it = scripts_.find(script->getName());
        if (it != scripts_.end())
        {
            DBG_WARN("Script with name {0} already added. Returning existing script", script->getName());
            return it->second;
        }

        scripts_.insert({ script->getName(), script });
        return script;
    }

    std::shared_ptr<Script> ScriptManager::createScript(const std::string& file)
    {
        std::shared_ptr<Script> script = std::make_shared<Script>(file);
        return addScript(script);
    }

    std::shared_ptr<Script> ScriptManager::getScript(const std::string& name)
    {
        auto it = scripts_.find(name);
        if (it == scripts_.end())
            return nullptr;

        return it->second;
    }

    void ScriptManager::removeScript(const std::string& name)
    {
        auto it = scripts_.find(name);
        if (it == scripts_.end())
            return;

        scripts_.erase(name);
    }

    void ScriptManager::runFunction(const std::string& function)
    {
        for (const auto& pair : scripts_)
            pair.second->runFunction(function);
    }
}