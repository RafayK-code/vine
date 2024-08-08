#pragma once

#include <vine/renderer/backend/Shader.h>
#include <vine/core/Base.h>

#include <unordered_map>

namespace vine
{
    class ShaderCache
    {
    public:
        void add(const std::string& name, const RefPtr<Shader>& shader);
        void add(const RefPtr<Shader>& shader);

        RefPtr<Shader> load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);

        RefPtr<Shader> get(const std::string& name) const;

        bool exists(const std::string& name) const;

    private:
        std::unordered_map<std::string, RefPtr<Shader>> shaders_;
    };
}