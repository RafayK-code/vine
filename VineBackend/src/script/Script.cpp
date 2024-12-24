#include <vine/script/Script.h>

#include <vine/core/Logger.h>

namespace vine
{
    Script::Script(const std::string& file)
        : luaFile_(file)
    {
        luaState_.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
    }

    Script::~Script()
    {
    }

    bool Script::run()
    {
        try
        {
            luaState_.script_file(luaFile_);
            return true;
        }
        catch (const std::exception& e)
        {
            DBG_ERROR("Error running script: {0}", e.what());
            return false;
        }
    }

    bool Script::runFunction(const std::string& function)
    {
        if (!luaState_[function])
        {
            DBG_WARN("Function with given name could not be found");
            return false;
        }

        try
        {
            luaState_[function]();
            return true;
        }
        catch (const std::exception& e)
        {
            DBG_ERROR("Error running function: {0}", e.what());
            return false;
        }
    }
}