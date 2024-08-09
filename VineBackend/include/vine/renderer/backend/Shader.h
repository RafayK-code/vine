#pragma once

#include <string>
#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>

namespace vine
{
    class Shader
    {
    public:
        Shader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);

        ~Shader();

        void bind() const;
        void unbind() const;

        const std::string& getName() { return name_; }

        void uploadUniformInt(const std::string& name, int value);
        void uploadUniformIntArray(const std::string& name, int* values, uint32_t count);

        void uploadUniformFloat(const std::string& name, float value);
        void uploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void uploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void uploadUniformFloat4(const std::string& name, const glm::vec4& value);

        void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
        void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);

    private:
        int getUniformLocation(const std::string& name);

    private:
        uint32_t rendererID_;
        std::string name_;

        std::unordered_map<std::string, int> uniformCache_;
    };

    using ShaderRef = std::shared_ptr<Shader>;
    ShaderRef createShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
}