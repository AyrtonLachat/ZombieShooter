#include <iostream>
#include <vector>

#include "error.hpp"
#include "global.hpp"

/*************************************************
* \author Ayrton Lachat
* \file global.cpp
* \date 10.03.22 at 20:08
*************************************************/

SDL_Window *window {nullptr};
SDL_Renderer *renderer {nullptr};
int __windowWidth {16 * 70};
int __windowHeight {9 * 70};

unsigned long long __startTicks {0}, __endTicks {0};

int __getWindowWidth()
{
	return __windowWidth;
}



int __getWindowHeight()
{
	return __windowHeight;
}



int capFPS(int framerate)
{
	__endTicks = SDL_GetTicks64();
	
	#define IDEAL_DT (1000 / framerate)
	int dt = (int)(__endTicks - __startTicks);

	if (dt < IDEAL_DT)
	{
		SDL_Delay(IDEAL_DT - dt);
		dt = IDEAL_DT;
	}

	#undef IDEAL_DT

	__startTicks = SDL_GetTicks64();
	return dt;
}



SDL_Surface *createNoTextureSurface(int size)
{
	std::vector<unsigned char> data {};

	for (int y {0}; y < size; y++)
	{
		for (int x {0}; x < size; x++)
		{
			if (x < size / 2 && y < size)
			{
				// left up corner
				data.push_back(255);
				data.push_back(0);
				data.push_back(255);
				data.push_back(255);
			}

			else if (x > size / 2 && y < size)
			{
				// right up corner
				data.push_back(0);
				data.push_back(0);
				data.push_back(0);
				data.push_back(255);
			}

			else if (x < size / 2 && y > size)
			{
				// left down corner
				data.push_back(0);
				data.push_back(0);
				data.push_back(0);
				data.push_back(255);
			}

			else
			{
				// right down corner
				data.push_back(255);
				data.push_back(0);
				data.push_back(255);
				data.push_back(255);
			}
		}
	}

	Uint32 rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		int shift = (req_format == STBI_rgb) ? 8 : 0;
		rmask = 0xff000000 >> shift;
		gmask = 0x00ff0000 >> shift;
		bmask = 0x0000ff00 >> shift;
		amask = 0x000000ff >> shift;
	#else // little endian, like x86
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	SDL_Surface *surface {SDL_CreateRGBSurfaceFrom((void*)data.data(), size, size, 32, 4 * size, rmask, gmask, bmask, amask)};
	if (surface == nullptr)
		throw Error("Can't create the 'no_texture' texture");

	return surface;
}



void __setWindowSize(int w, int h)
{
	__windowWidth = w;
	__windowHeight = h;
}



SDL_FPoint operator+(SDL_FPoint &a, SDL_FPoint &b)
{
	return {a.x + b.x, a.y + b.y};
}



SDL_FPoint operator-(SDL_FPoint &a, SDL_FPoint &b)
{
	return {a.x - b.x, a.y - b.y};
}


