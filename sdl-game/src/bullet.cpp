#include "bullet.h"
#include <iostream>

#define PI 3.14159265

// take distance out
Bullet::Bullet(SDL_Renderer* renderer, int w, int h, float start_x, float start_y, float end_x, float end_y, int range, int speed, int distance, std::vector<std::shared_ptr<Sprite>> sprites)
	: Rect(renderer, w, h, (int) start_x, (int) start_y, sprites.at(0)->_texture_path), 
	_start_x(start_x), _start_y(start_y), _end_x(end_x), _end_y(end_y), _range(range), _speed(speed), _distance(distance), _sprites(sprites)
{
	
	_speed = 1500;
	_elapsed = 0.01f;
	distance = v.distance(start, end);
	_direction = v.normalize(v.subtract(end, start));

	

	_x = (int) start._x;
	_y = (int) start._y;

	_moving = true;

	_angle = (float) acos(v.dot_product(_direction, Vector2(1, 0))) * 180 / M_PI;


	position = Vector2(_x, _y);
	// Create surface from image using file path
	auto surface = IMG_Load(_sprites.at(0)->_texture_path.c_str());

	// Check if surface was created successfully
	if (!surface) {
		std::cerr << "Failed to create surface.\n";
	}

	// Create texture from surface
	_texture = SDL_CreateTextureFromSurface(renderer, surface);

	// Check if texture was created successfully
	if (!_texture) {
		std::cerr << "Failed to create texture.\n";
	}

	// Free surface memory
	SDL_FreeSurface(surface);
}

Bullet::~Bullet() {

}

int Bullet::findDirection() {
	if (_angle < 15) {
		return right;
	}

	if (_angle > 15 && _angle < 75) {
		if (_start_y > _end_y) {
			return right_up;
		}
		else {
			return right_down;
		}
	}
	if (_angle > 75 && _angle < 105) {
		if (_start_y > _end_y) {
			return up;
		}
		else {
			return down;
		}
	}

	if (_angle > 105 && _angle < 165) {
		if (_start_y > _end_y) {
			return left_up;
		}
		else {
			return left_down;
		}
	}

	if (_angle > 165) {
		return left;
	}
}

void Bullet::draw(SDL_Renderer* renderer) {
	// Create rectangle using position and dimensions
	SDL_Rect myrect = { _x, _y, _w, _h };

	_index = findDirection();

	if (_sprites.at(0)->_sprite_clips == nullptr) {
		std::cerr << "Clips are empty.\n";
		return;
	}

	// Set the rectangle to be the size of the sprite
	myrect.w = _sprites.at(0)->_sprite_clips[_index].w;
	myrect.h = _sprites.at(0)->_sprite_clips[_index].h;

	// If texture exists, then copy texture to rectangle. 
	if (_texture) {
		SDL_RenderCopy(renderer, _texture, &_sprites.at(0)->_sprite_clips[_index], &myrect);
	}
}

void Bullet::update() {
	
	if (_moving == true)
	{
		position = v.add(position, v.multiply_scalar((_speed * _elapsed), _direction));
	}
	
	_x = position._x;
	_y = position._y;
}