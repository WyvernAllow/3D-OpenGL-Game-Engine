#include "Window.h"
#include <iostream>

namespace engine
{
	Window::Window(const std::string& title, const uint16_t w, const uint16_t h)
	{


		mWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (!mWindow)
		{
			std::cerr << "Could not create window: " << SDL_GetError() << "\n";
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		mContext = SDL_GL_CreateContext(mWindow);
		if (!mContext)
		{
			std::cerr << "Could not create OpenGL context: " << SDL_GetError() << "\n";
		}

		if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
		{
			std::cerr << "Could not load OpenGL extensions.\n";
		}
	}

	Window::~Window()
	{
		SDL_DestroyWindow(mWindow);
		SDL_GL_DeleteContext(mContext);
	}

	void Window::Clear(const uint16_t r, const uint16_t g, const uint16_t b) const
	{
		glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Present() const
	{
		SDL_GL_SwapWindow(mWindow);
	}

	bool Window::HasFocus()
	{
		return SDL_GetWindowFlags(mWindow) & SDL_WINDOW_MOUSE_FOCUS;
	}
}
