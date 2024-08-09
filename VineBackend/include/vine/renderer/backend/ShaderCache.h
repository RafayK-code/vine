#pragma once

#include <vine/renderer/backend/Shader.h>
#include <vine/core/Base.h>

#include <unordered_map>

namespace vine
{
    class ShaderCache
    {
    public:
        void add(const std::string& name, const ShaderRef& shader);
        void add(const ShaderRef& shader);

        ShaderRef load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);

        ShaderRef get(const std::string& name) const;

        bool exists(const std::string& name) const;

    private:
        std::unordered_map<std::string, ShaderRef> shaders_;
    };
}