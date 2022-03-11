#include "camera.hpp"

#include <iostream>

/*************************************************
* \author Ayrton Lachat
* \file camera.cpp
* \date 10.03.22 at 20:49
*************************************************/

Camera::Camera(SDL_FPoint position, SDL_FPoint size, float zoom) : _position {position}, _size {size}, _zoom {zoom}
{
	
}



void Camera::setPosition(SDL_FPoint position)
{
	_position = position;
}



void Camera::setRatio(float ratio)
{
	// TO DEV
}



void Camera::setSize(SDL_FPoint size)
{
	_size = size;
}



void Camera::setZoom(float zoom)
{
	_zoom = zoom;
	
}



void Camera::move(SDL_FPoint delta)
{
	_position = _position + delta;
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
		_position.x - _size.x / 2,
		_position.y - _size.y / 2,
		_size.x,
		_size.y
	};
}



float Camera::getZoom() const noexcept
{
	return _zoom;
}



