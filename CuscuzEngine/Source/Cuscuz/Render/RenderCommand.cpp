#include "pch.h"

#include "RenderCommand.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cuscuz
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
