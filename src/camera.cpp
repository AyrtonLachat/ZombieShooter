#include "camera.hpp"

/*************************************************
* \author Ayrton Lachat
* \file camera.cpp
* \date 10.03.22 at 20:49
*************************************************/

Camera::Camera(SDL_FPoint position, SDL_FPoint size) : _position {position}, _ratio {size.x / size.y}, _height {size.y}
{

}



void Camera::setPosition(SDL_FPoint position)
{
	_position = position;
}



void Camera::setRatio(float ratio)
{
	_ratio = ratio;
}



void Camera::setSize(SDL_FPoint size)
{
	_height = size.y;
	_ratio = size.x / _height;
}



void Camera::move(SDL_FPoint delta)
{
	_position = _position + delta;
}



void Camera::updateOnWindowSizeChanges()
{
	if (FWINDOW_WIDTH > _ratio * FWINDOW_HEIGHT)
	{
		// width is too small

		_height = FWINDOW_HEIGHT;
	}

	else
	{
		// height is too small

		_height = FWINDOW_WIDTH / _ratio;
	}
}



SDL_FPoint Camera::getPosition() const noexcept
{
	return _position;
}



float Camera::getRatio() const noexcept
{
	return _ratio;
}



SDL_FPoint Camera::getSize() const noexcept
{
	return {_ratio * _height, _height};
}



SDL_FRect Camera::getDrawingRect() const noexcept
{
	return {
		(FWINDOW_WIDTH - this->getSize().x) / 2.0f,
		(FWINDOW_HEIGHT - _height) / 2.0f,
		this->getSize().x,
		_height
	};
}