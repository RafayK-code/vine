#include <vine/renderer/backend/Shader.h>

#include <vine/core/Logger.h>

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace vine
{
    static std::string getFileContents(const std::string& path)
    {
        std::ifstream file(path, std::ios::binary);

        DBG_ASSERT(file.is_open(), "File could not be opened");

        std::string contents;

        file.seekg(0, std::ios::end);
        contents.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&contents[0], contents.size());
        file.close();

        return contents;
    }

    static uint32_t createShaderProgram(const std::string& vertexCode, const std::string& fragmentCode)
    {
        const char* vertexSrc = vertexCode.c_str();
        const char* fragmentSrc = fragmentCode.c_str();

        uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertexSrc, nullptr);
        glCompileShader(vs);

        uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragmentSrc, nullptr);
        glCompileShader(fs);

        uint32_t shader = glCreateProgram();
        glAttachShader(shader, vs);
        glAttachShader(shader, fs);

        glLinkProgram(shader);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return shader;
    }

    Shader::Shader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
        : name_(name)
    {
        std::string vertexCode = getFileContents(vertexPath);
        std::string fragmentCode = getFileContents(fragmentPath);

        rendererID_ = createShaderProgram(vertexCode, fragmentCode);
    }

    Shader::~Shader()
    {
        glDeleteShader(rendererID_);
    }

    void Shader::bind() const
    {
        glUseProgram(rendererID_);
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }

    void Shader::uploadUniformInt(const std::string& name, int value)
    {
        glUniform1i(getUniformLocation(name), value);
    }

    void Shader::uploadUniformIntArray(const std::string& name, int* values, uint32_t count)
    {
        glUniform1iv(getUniformLocation(name), count, values);
    }

    void Shader::uploadUniformFloat(const std::string& name, float value)
    {
        glUniform1f(getUniformLocation(name), value);
    }

    void Shader::uploadUniformFloat2(const std::string& name, const glm::vec2& value)
    {
        glUniform2f(getUniformLocation(name), value.x, value.y);
    }

    void Shader::uploadUniformFloat3(const std::string& name, const glm::vec3& value)
    {
        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::uploadUniformFloat4(const std::string& name, const glm::vec4& value)
    {
        glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Shader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
        glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    int Shader::getUniformLocation(const std::string& name)
    {
        if (uniformCache_.find(name) == uniformCache_.end())
            uniformCache_[name] = glGetUniformLocation(rendererID_, name.c_str());

        return uniformCache_[name];
    }
}