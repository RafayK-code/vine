#pragma once

#include <vine/renderer/backend/Shader.h>
#include <vine/util/Singleton.h>

#include <unordered_map>

namespace vine
{
    class ShaderCache : public Singleton<ShaderCache>
    {
        friend class Singleton<ShaderCache>;
    public:
        ~ShaderCache();

        static void init();
        static void shutdown();

        void add(const std::string& name, const ShaderRef& shader);
        void add(const ShaderRef& shader);

        ShaderRef load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);

        ShaderRef get(const std::string& name) const;

        bool exists(const std::string& name) const;

    private:
        ShaderCache();

    private:
        std::unordered_map<std::string, ShaderRef> shaders_;
    };
}