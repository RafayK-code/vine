#pragma once

#include <string>
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
}