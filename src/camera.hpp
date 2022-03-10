#if !defined(__CAMERA_HPP__)
#define __CAMERA_HPP__

#include "global.hpp"

/*************************************************
* \author Ayrton Lachat
* \file camera.hpp
* \date 10.03.22 at 20:42
*************************************************/

class Camera
{
	public:
		Camera(SDL_FPoint position = {0, 0}, SDL_FPoint size = {(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT});

		void setPosition(SDL_FPoint position);
		void setRatio(float ratio);
		void setSize(SDL_FPoint size);

		void move(SDL_FPoint delta);

		void updateOnWindowSizeChanges();

		SDL_FPoint getPosition() const noexcept;
		float getRatio() const noexcept;
		SDL_FPoint getSize() const noexcept;
		SDL_FRect getDrawingRect() const noexcept;

	private:
		SDL_FPoint _position;
		float _ratio, _height;
};

#endif