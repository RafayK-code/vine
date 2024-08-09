#include <vine/renderer/GraphicsContext.h>

#include <vine/core/Logger.h>

#include <glad/glad.h>

namespace vine
{
    GraphicsContext::GraphicsContext()
        : context_(nullptr)
    {
    }

    GraphicsContext::~GraphicsContext()
    {
    }

    void GraphicsContext::createContext(SDL_Window* window)
    {
        context_ = SDL_GL_CreateContext(window);
        int status = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
        DBG_ASSERT(status, "Failed to initialize glad");
    }

    void GraphicsContext::destroyContext()
    {
        SDL_GL_DeleteContext(context_);
    }
}