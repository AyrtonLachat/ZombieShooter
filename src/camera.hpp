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
		Camera(SDL_FPoint position = {0, 0}, SDL_FPoint size = {FWINDOW_WIDTH, FWINDOW_HEIGHT}, float zoom = 1.0f);

		void setPosition(SDL_FPoint position);
		void setRatio(float ratio);
		void setSize(SDL_FPoint size);
		/**
		 * \warning If you set zoom smaller than 1.0f, it will stay at 1.0f !
		 */
		void setZoom(float zoom);

		void move(SDL_FPoint delta);

		void drawImage(SDL_Texture *texture, SDL_FRect rect, const SDL_Rect *innerRect);

		void updateOnWindowSizeChange();

		SDL_FPoint getPosition() const noexcept;
		float getRatio() const noexcept;
		SDL_FPoint getSize() const noexcept;
		SDL_FRect getDrawingRect() const noexcept;
		float getZoom() const noexcept;

	private:
		SDL_FPoint _position, _size, _internalZoom;
		float _zoom;
};

extern Camera *camera;

#endif