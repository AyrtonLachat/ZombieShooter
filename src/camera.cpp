#include "camera.hpp"
#include "error.hpp"
#include "global.hpp"

/*************************************************
* \author Ayrton Lachat
* \file camera.cpp
* \date 10.03.22 at 20:49
*************************************************/

Camera *camera {nullptr};

Camera::Camera(SDL_FPoint position, SDL_FPoint size, float zoom) : _position {position}, _size {size}, _internalZoom {}, _zoom {zoom}
{
	if (SDL_RenderSetLogicalSize(renderer, _size.x, _size.y) != 0)
		throw Error("Can't change renderer logical size");

	SDL_RenderGetScale(renderer, &_internalZoom.x, &_internalZoom.y);
}



void Camera::setPosition(SDL_FPoint position)
{
	_position = position;
}



void Camera::setRatio(float ratio)
{
	if ((FWINDOW_WIDTH / FWINDOW_HEIGHT) > ratio)
	{
		// width too small
		_size.x = ratio * _size.y;
	}

	else
	{
		// height too small
		_size.y = _size.x / ratio;
	}

	if (SDL_RenderSetLogicalSize(renderer, _size.x, _size.y) != 0)
		throw Error("Can't change renderer logical size");
}



void Camera::setSize(SDL_FPoint size)
{
	_size = size;
	if (SDL_RenderSetLogicalSize(renderer, _size.x, _size.y) != 0)
		throw Error("Can't change renderer logical size");
}



void Camera::setZoom(float zoom)
{
	if (zoom < 1.0f)
		_zoom = 1.0f;
	else
		_zoom = zoom;

	if (SDL_RenderSetScale(renderer, _internalZoom.x * _zoom, _internalZoom.y * _zoom) != 0)
		throw Error("Can't' change renderer scale");
}



void Camera::move(SDL_FPoint delta)
{
	_position = _position + delta;
}



void Camera::drawImage(SDL_Texture *texture, SDL_FRect rect, const SDL_Rect *innerRect)
{
	SDL_RenderCopyF(renderer, texture, innerRect, &rect);
}



void Camera::updateOnWindowSizeChange()
{
	SDL_RenderGetScale(renderer, &_internalZoom.x, &_internalZoom.y);
	
	if (SDL_RenderSetScale(renderer, _internalZoom.x * _zoom, _internalZoom.y * _zoom) != 0)
		throw Error("Can't' change renderer scale");
}



SDL_FPoint Camera::getPosition() const noexcept
{
	return _position;
}



float Camera::getRatio() const noexcept
{
	return _size.x / _size.y;
}



SDL_FPoint Camera::getSize() const noexcept
{
	return _size;
}



SDL_FRect Camera::getDrawingRect() const noexcept
{
	return {
		0,//_position.x - _size.x / 2,
		0,//_position.y - _size.y / 2,
		_size.x,
		_size.y
	};
}



float Camera::getZoom() const noexcept
{
	return _zoom;
}



