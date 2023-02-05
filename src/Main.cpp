#include <unordered_map>
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "utils/Utils.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>

#include <glm/glm.hpp>
#include <vector>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"
#include "Camera.h"
#include "Renderer.h"

int GetRandom(int min, int max)
{
    return rand() % ((max - min) + 1) + min;
}

int screenWidth = 800;
int screenHeight = 450;

int main(int argc, char* argv[])
{
	engine::Window window("3D Engine", screenWidth, screenHeight);
    engine::Shader shader("data/graphics/shaders/def.vert", "data/graphics/shaders/def.frag");

    engine::Texture tex("data/graphics/tex/gun.bmp");
    engine::Mesh mesh("data/graphics/models/gun.txt");
    engine::Mesh kidNamedThumb("data/graphics/models/white.txt");
    engine::Texture kidNamedThumbTex("data/graphics/tex/white.bmp");

    engine::Camera cam(90, (float)screenWidth / screenHeight, 0.01, 1000.0f);

    SDL_GL_SetSwapInterval(0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    //engine::Renderer()
    engine::Renderer renderer(cam, shader);
    
    glm::vec3 rotation = glm::vec3(0, 0, 90);

    SDL_SetRelativeMouseMode(SDL_TRUE);

    float lastTime = 0.0;

	bool running = true;
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}

            if (e.type == SDL_WINDOWEVENT)
            {
                if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    glViewport(0, 0, e.window.data1, e.window.data2);
                    cam = engine::Camera(90, (float)screenWidth / screenHeight, 0.01, 1000.0f);

                    screenWidth = e.window.data1;
                    screenHeight = e.window.data2;

                    window.Clear(18, 18, 18);
                }
            }

            if (e.type == SDL_MOUSEMOTION)
            {
                if (window.HasFocus() && SDL_GetRelativeMouseMode())
                {
                    float mouseSense = 0.1f;

                    static float yaw = screenWidth / 2.0f;
                    static float pitch = screenHeight / 2.0f;
                    yaw += e.motion.xrel * mouseSense;
                    pitch += -e.motion.yrel * mouseSense;

                    if (pitch > 89.0f)
                    {
                        pitch = 89.0f;
                    }

                    if (pitch < -89.0f)
                    {
                        pitch = -89.0f;
                    }

                    cam.Rotate(yaw, pitch);
                }
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_SetRelativeMouseMode(SDL_TRUE);
                }
            }
		}
        
        float currentTime = SDL_GetTicks64() / 1000.0f;
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        const Uint8* keys = SDL_GetKeyboardState(nullptr);

        float camSpeed = 100.0f * deltaTime;

        if (window.HasFocus())
        {
            if (keys[SDL_SCANCODE_ESCAPE])
            {
                SDL_SetRelativeMouseMode(SDL_FALSE);
            }

            if (keys[SDL_SCANCODE_W])
            {
                cam.Position += camSpeed * cam.GetDirection();
            }
            if (keys[SDL_SCANCODE_S])
            {
                cam.Position -= camSpeed * cam.GetDirection();
            }
            if (keys[SDL_SCANCODE_A])
            {
                cam.Position -= cam.GetRight() * camSpeed;

            }
            if (keys[SDL_SCANCODE_D])
            {
                cam.Position += cam.GetRight() * camSpeed;
            }
        }

        cam.Update();

		window.Clear(18, 18, 18);
        
        renderer.Begin(shader);

        for (size_t i = 0; i < 200; i++)
        {
            renderer.Draw(mesh, tex, glm::vec3(i * 100, 0, 0), glm::vec3(0, 0, 0), glm::vec3(20, 20, 20));
        }

        renderer.End();

		window.Present();
	}

	return 0;
}