#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <SDL.h>


int main(int argc, char** argv)
{
	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script("print('bark bark bark!')");
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Hello!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);

	bool isRunning = true;
	while (isRunning)
	{
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}