#if !defined(__IMAGE_LOADER_HPP)
#define __IMAGE_LOADER_HPP

#include <map>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

/*************************************************
* \author Ayrton Lachat
* \file imageLoader.hpp
* \date 13.03.22 at 21:06
*************************************************/

struct SpritesheetInfo
{
	std::string name, src;
	int spriteSize;
	std::vector<bool> collisionMap;
};

struct SpritesheetInfoWithoutName
{
	std::string src;
	int spriteSize;
	std::vector<bool> collisionMap;
};


class ImageLoader
{
	public:
		ImageLoader(const std::vector<SpritesheetInfo> &spritesheetsToLoad = {});
		~ImageLoader();

		void draw(const std::string &name, SDL_FPoint position, int index);

	private:

		class Spritesheet
		{
			public:
				Spritesheet(const SpritesheetInfoWithoutName &info);
				~Spritesheet();

				void draw(SDL_FPoint position, int index);

				const SpritesheetInfoWithoutName &getInfo() const noexcept;

			private:
				SpritesheetInfoWithoutName _info;
				SDL_Texture *_texture;
				int  _nbColumn;
				bool _noLoadingFail;
		};


		std::map<std::string, Spritesheet*> _spritesheets;
};

#endif