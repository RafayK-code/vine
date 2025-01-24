#pragma once

#include <vine/resource/Resource.h>
#include <vine/script/Script.h>

namespace vine
{
    /*
    class ResourceScript : public Resource
    {
        friend class ResourceManager;
    public:
        ~ResourceScript();

        virtual void reload() override;
        virtual void unload() override;

        ScriptRef getScript() const { return script_; }

    protected:
        ResourceScript(const ResourceCreationData& data);

    private:
        ScriptRef script_;
    };
    */
}