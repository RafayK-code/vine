#include <vine/renderer/backend/ShaderCache.h>

#include <vine/core/Logger.h>

namespace vine
{
    void ShaderCache::add(const std::string& name, const RefPtr<Shader>& shader)
    {
        DBG_ASSERT(!exists(name), "Shader already exists");
        shaders_[name] = shader;
    }

    void ShaderCache::add(const RefPtr<Shader>& shader)
    {
        add(shader->getName(), shader);
    }

    RefPtr<Shader> ShaderCache::load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
    {
        RefPtr<Shader> shader = makeRef<Shader>(name, vertexPath, fragmentPath);
        add(name, shader);
        return shader;
    }

    RefPtr<Shader> ShaderCache::get(const std::string& name) const
    {
        DBG_ASSERT(exists(name), "Shader does not exist");

        return shaders_.find(name)->second;
    }

    bool ShaderCache::exists(const std::string& name) const
    {
        return shaders_.find(name) != shaders_.end();
    }
}