#pragma once
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <string>

namespace engine
{
	class Window
	{
	public:
		Window(const std::string& title, const uint16_t w, const uint16_t h);
		~Window();

		void Clear(const uint16_t r, const uint16_t g, const uint16_t b) const;
		void Present() const;

		bool HasFocus();

	private:
		SDL_Window* mWindow;
		SDL_GLContext mContext;
	};
}