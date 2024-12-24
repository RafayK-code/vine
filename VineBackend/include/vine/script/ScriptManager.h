#pragma once

#include <vine/script/Script.h>
#include <vine/util/Singleton.h>

#include <sol/sol.hpp>
#include <string>
#include <unordered_map>
#include <memory>

namespace vine
{
    class ScriptManager : public Singleton<ScriptManager>
    {
        friend class Singleton<ScriptManager>;
    public:
        ~ScriptManager();

        static void init();
        static void shutdown();

        std::shared_ptr<Script> addScript(std::shared_ptr<Script> script);
        std::shared_ptr<Script> createScript(const std::string& file);
        std::shared_ptr<Script> getScript(const std::string& name);
        void removeScript(const std::string& name);

        void runFunction(const std::string& function);

    private:
        ScriptManager();

        sol::state luaState_;
        std::unordered_map<std::string, std::shared_ptr<Script>> scripts_;
    };
}