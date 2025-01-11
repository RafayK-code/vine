#pragma once

#include <string>
#include <memory>
#include <sol/sol.hpp>

namespace vine
{
    class Script
    {
    public:
        Script(const std::string& file);
        ~Script();

        bool run();
        bool runFunction(const std::string& function);

        sol::state& getState() { return luaState_; }
        const std::string& getName() const { return luaFile_; }

    private:
        const std::string luaFile_;
        sol::state luaState_;
    };

    using ScriptRef = std::shared_ptr<Script>;
    ScriptRef createScript(const std::string& file);
}