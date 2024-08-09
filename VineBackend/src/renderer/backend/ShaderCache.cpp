#include <vine/renderer/backend/ShaderCache.h>

#include <vine/core/Logger.h>

namespace vine
{
    void ShaderCache::add(const std::string& name, const ShaderRef& shader)
    {
        DBG_ASSERT(!exists(name), "Shader already exists");
        shaders_[name] = shader;
    }

    void ShaderCache::add(const ShaderRef& shader)
    {
        add(shader->getName(), shader);
    }

    ShaderRef ShaderCache::load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
    {
        ShaderRef shader = createShader(name, vertexPath, fragmentPath);
        add(name, shader);
        return shader;
    }

    ShaderRef ShaderCache::get(const std::string& name) const
    {
        DBG_ASSERT(exists(name), "Shader does not exist");
        return shaders_.find(name)->second;
    }

    bool ShaderCache::exists(const std::string& name) const
    {
        return shaders_.find(name) != shaders_.end();
    }
}