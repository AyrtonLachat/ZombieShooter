#include <iostream>

#include "error.hpp"
#define __ENABLE_WINDOW_SIZE_SETTING
#include "global.hpp"
#include "camera.hpp"

int main(int argc, char *argv[])
{
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw Error("Can't init SDL2");


		window = SDL_CreateWindow("Zombie Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == nullptr)
			throw Error("Can't create an SDL2's Window");

		SDL_SetWindowMinimumSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr)
			throw Error("Can't create an SDL2's renderer");


		bool running {true};
		SDL_Event event {};
		int /*dt {0}, */framerate {60};
		Camera cam {};



		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_KEYDOWN:
						if (event.key.keysym.scancode == SDL_SCANCODE_A)
							cam.setZoom(cam.getZoom() + 0.1f);
						else if (event.key.keysym.scancode == SDL_SCANCODE_D)
							cam.setZoom(cam.getZoom() - 0.1f);
						break;

					case SDL_WINDOWEVENT:
						switch (event.window.event)
						{
							case SDL_WINDOWEVENT_RESIZED:
								__setWindowSize(event.window.data1, event.window.data2);

								cam.updateOnWindowSizeChange();
								break;

							default:
								break;
						}

						break;

					case SDL_QUIT:
						running = false;
						break;

					default:
						break;
				}
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_FRect tmp {cam.getDrawingRect()};
			SDL_RenderDrawRectF(renderer, &tmp);

			SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
			SDL_FRect tmp2 {600, 400, 1600, 1400};
			SDL_RenderDrawRectF(renderer, &tmp2);

			SDL_RenderPresent(renderer);


			/*dt = */capFPS(framerate);
		}
	}

	catch (std::exception &e)
	{
		std::cerr << "ERROR : " << e.what() << std::endl;
	}


	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}