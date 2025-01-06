# Cuscuz Engine

Welcome to the Cuscuz Engine! This is a project I started to learn C++ and how to make games. At first, I used a library called SDL because it’s great for beginners. I learned from tutorials and a book called "Game Programming in C++" by Sanjay Madhav.

As I learned more, I wanted to build something bigger, like a game engine. I watched many videos to understand how game engines work. My first idea was to make a simple 2D engine for basic games. But then, I got interested in graphics programming, so I started using OpenGL with GLEW to make my own rendering system.

Now, the engine can handle 2D and it's about to support 3D graphics, and I plan to learn more and add other rendering APIs in the future.

## The project

I'm using TheCherno's C++ [project template](https://github.com/TheCherno/ProjectTemplate) to help with the inital project organization. This template comes with [Premake](https://github.com/premake/premake-core) as the build configuration tool.

Libraries used:
- SDL2
- glew
- glm
- stb_image
- [spdlog](https://github.com/gabime/spdlog/tree/696db97f672e9082e50e50af315d0f4234c82397)
- [ImGui](https://github.com/TheCherno/imgui/tree/781a4ffc674d98dfd2b4d42747e1cd27887fac36)
- [yaml](https://github.com/TheCherno/yaml-cpp/tree/b5b07c8bbffe029ab929fd61d420d203c30d458d)

## Setup

- Download the project `git clone --recursive https://github.com/FernandaDev/CuscuzEngine.git`
- Run `scripts/Setup.bat`(.bat for windows and .sh for linux).
