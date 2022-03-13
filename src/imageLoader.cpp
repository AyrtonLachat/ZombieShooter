#include <iostream>

#include <SDL2/SDL_image.h>

#include "camera.hpp"
#include "error.hpp"
#include "global.hpp"
#include "imageLoader.hpp"

/*************************************************
* \author Ayrton Lachat
* \file imageLoader.cpp
* \date 13.03.22 at 21:14
*************************************************/

ImageLoader::Spritesheet::Spritesheet(const SpritesheetInfoWithoutName &info) : _info {info}, _texture {nullptr}, _nbColumn {0}, _noLoadingFail {true}
{
	SDL_Surface *surface {IMG_Load(_info.src.c_str())};
	if (surface == nullptr)
	{
		LOG << "Can't find " << _info.src << " texture, using 'no_texture' instead" << std::endl;
		surface = createNoTextureSurface(_info.spriteSize);
		_noLoadingFail = false;
	}

	_nbColumn = surface->w / _info.spriteSize;

	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (_texture == nullptr)
		throw Error("Can't create texture from the given surface");
}



ImageLoader::Spritesheet::~Spritesheet()
{
	SDL_DestroyTexture(_texture);
}



void ImageLoader::Spritesheet::draw(SDL_FPoint position, int index)
{
	SDL_FRect rect {
		position.x,
		position.y,
		_info.spriteSize,
		_info.spriteSize
	};

	if (_noLoadingFail)
	{
		SDL_Rect innerRect {
			(index % _nbColumn) * _info.spriteSize,
			((int)(index / _nbColumn)) * _info.spriteSize,
			_info.spriteSize,
			_info.spriteSize
		};

		camera->drawImage(_texture, rect, &innerRect);
	}

	else
	{
		camera->drawImage(_texture, rect, nullptr);
	}
}



const SpritesheetInfoWithoutName &ImageLoader::Spritesheet::getInfo() const noexcept
{
	return _info;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////



ImageLoader::ImageLoader(const std::vector<SpritesheetInfo> &spritesheetsToLoad) : _spritesheets {}
{
	for (int i {0}; i < spritesheetsToLoad.size(); i++)
	{
		_spritesheets[spritesheetsToLoad[i].name] = new Spritesheet({spritesheetsToLoad[i].src, spritesheetsToLoad[i].spriteSize, spritesheetsToLoad[i].collisionMap});
	}
}



ImageLoader::~ImageLoader()
{
	for (auto it {_spritesheets.begin()}; it != _spritesheets.end(); ++it)
	{
		delete it->second;
	}
}



void ImageLoader::draw(const std::string &name, SDL_FPoint position, int index)
{
	auto it {_spritesheets.find(name)};
	if (it != _spritesheets.end())
	{
		it->second->draw(position, index);
	}
	
	LOG << "Can't find the spritesheet '" << name << "'" << std::endl;
}



