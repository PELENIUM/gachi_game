#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"
using namespace sf;

#define SPRITE_W 57
#define SPRITE_H 61

class Player {
private:
	bool *is_moving = new bool;
	int *iter_l = new int, *iter_r = new int, *iter_u = new int, *iter_d = new int, *counter_l = new int, *counter_r = new int, *counter_u = new int, *counter_d = new int;
	float *MOVING_SPEED = new float;
	int *death_counter = new int;
	Texture* texture = new Texture;
	Sprite* sprite = new Sprite;
public:
	int* x = new int;
	int* y = new int;
	Player(int X, int Y, String path, float speed) {
		*x = X;
		*y = Y;
		texture->loadFromFile(path);
		sprite->setTexture(*texture);
		sprite->setPosition(*x, *y);
		*MOVING_SPEED = speed;
		*iter_l = 0;
		*iter_r = 0;
		*iter_u = 0;
		*iter_d = 0;
		*counter_l = 0;
		*counter_r = 0;
		*counter_u = 0;
		*counter_d = 0;
		*is_moving = false;
		*death_counter = 5;
	}

	~Player() {
		delete x;
		delete y;
		delete MOVING_SPEED;
		delete is_moving;
		delete iter_l;
		delete iter_r;
		delete iter_u;
		delete iter_d;
		delete counter_l;
		delete counter_r;
		delete counter_u;
		delete counter_d;
		delete sprite;
		delete texture;
	}
	void update(RenderWindow *win, int height, int width) {
		*x = sprite->getPosition().x;
		*y = sprite->getPosition().y;
		if ((*is_moving) == false)
			sprite->setTextureRect(IntRect(0, 0, SPRITE_W, SPRITE_H));
		if (main_active) {
			if (Keyboard::isKeyPressed(Keyboard::A) == true) {
				if (Map[(*y + SPRITE_H - 5) / 32][*x / 32] == '#') {
					*x = 32 * ((*x) / 32) + 33;
				}
				else
					*x += -(*MOVING_SPEED);
				(*counter_l)++;
				if (*counter_l >= 3) {
					(*iter_l)++;
					*counter_l = 0;
				}
				sprite->setTextureRect(IntRect((*iter_l) * SPRITE_W, 122, SPRITE_W, SPRITE_H));
				if (*iter_l == 9)
					*iter_l = 0;
				(*is_moving) = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::D) == true) {
				if (Map[*y / 32][(*x + SPRITE_W) / 32] == '#') {
					*x = 32 * ((*x + SPRITE_W) / 32) - (SPRITE_W);
				}
				else
					*x += (*MOVING_SPEED);
				(*counter_r)++;
				if (*counter_r >= 3) {
					(*iter_r)++;
					*counter_r = 0;
				}
				sprite->setTextureRect(IntRect((*iter_r) * SPRITE_W + SPRITE_W, 122, -SPRITE_W, SPRITE_H));
				if (*iter_r == 9)
					*iter_r = 0;
				(*is_moving) = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::W) == true) {
				if (Map[*y / 32][*x / 32] == '#' or Map[(*y + SPRITE_H) / 32][*x / 32] == '#') {
					*y = 32 * (*y / 32) + 1;
				}
				else
					*y += -(*MOVING_SPEED);
				(*counter_u)++;
				if (*counter_u >= 3) {
					(*iter_u)++;
					*counter_u = 0;
				}
				sprite->setTextureRect(IntRect((*iter_u) * SPRITE_W + SPRITE_W, 184.7, SPRITE_W, SPRITE_H));
				if (*iter_u == 9)
					*iter_u = 0;
				(*is_moving) = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::S) == true) {
				if (Map[(*y + SPRITE_H) / 32][(*x) / 32] == '#') {
					*y = 32 * (*y / 32);
				}
				else
					*y += *MOVING_SPEED;
				(*counter_d)++;
				if (*counter_d >= 3) {
					(*iter_d)++;
					*counter_d = 0;
				}
				sprite->setTextureRect(IntRect((*iter_d) * SPRITE_W + SPRITE_W, 61, -SPRITE_W, SPRITE_H));
				if (*iter_d == 9)
					*iter_d = 0;
				(*is_moving) = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::R) == true or Map[(*y + SPRITE_H - 10) / 32][(*x) / 32] == '@'
				or Map[(*y + SPRITE_H - 10) / 32][(*x + SPRITE_W) / 32] == '@') {
				*x = 1800;
				*y = 1160;
			}
			if (Map[(*y + SPRITE_H) / 32][(*x) / 32] == '%' or Map[(*y + SPRITE_H) / 32][(*x + SPRITE_W) / 32] == '%' or Map[(*y) / 32][(*x) / 32] == '%' or Map[(*y + SPRITE_H) / 32][(*x + SPRITE_W) / 32] == '%') {
				main_active = false;
			}
		}
		if (!main_active) {
			if (Keyboard::isKeyPressed(Keyboard::A) == true) {
				if (Map_gachi[(*y + SPRITE_H - 5) / 32][*x / 32] == '#') {
					*x = 32 * ((*x) / 32) + 33;
				}
				else
					*x += -(*MOVING_SPEED);
				(*counter_l)++;
				if (*counter_l >= 3) {
					(*iter_l)++;
					*counter_l = 0;
				}
				sprite->setTextureRect(IntRect((*iter_l) * SPRITE_W, 122, SPRITE_W, SPRITE_H));
				if (*iter_l == 9)
					*iter_l = 0;
				(*is_moving) = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::D) == true) {
				if (Map_gachi[*y / 32][(*x + SPRITE_W) / 32] == '#') {
					*x = 32 * ((*x + SPRITE_W) / 32) - (SPRITE_W);
				}
				else
					*x += (*MOVING_SPEED);
				(*counter_r)++;
				if (*counter_r >= 3) {
					(*iter_r)++;
					*counter_r = 0;
				}
				sprite->setTextureRect(IntRect((*iter_r) * SPRITE_W + SPRITE_W, 122, -SPRITE_W, SPRITE_H));
				if (*iter_r == 9)
					*iter_r = 0;
				(*is_moving) = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::W) == true) {
				if (Map_gachi[*y / 32][*x / 32] == '#' or Map[(*y + SPRITE_H) / 32][*x / 32] == '#') {
					*y = 32 * (*y / 32) + 1;
				}
				else
					*y += -(*MOVING_SPEED);
				(*counter_u)++;
				if (*counter_u >= 3) {
					(*iter_u)++;
					*counter_u = 0;
				}
				sprite->setTextureRect(IntRect((*iter_u) * SPRITE_W + SPRITE_W, 184.7, SPRITE_W, SPRITE_H));
				if (*iter_u == 9)
					*iter_u = 0;
				(*is_moving) = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::S) == true) {
				if (Map_gachi[(*y + SPRITE_H) / 32][(*x) / 32] == '#') {
					*y = 32 * (*y / 32);
				}
				else
					*y += *MOVING_SPEED;
				(*counter_d)++;
				if (*counter_d >= 3) {
					(*iter_d)++;
					*counter_d = 0;
				}
				sprite->setTextureRect(IntRect((*iter_d) * SPRITE_W + SPRITE_W, 61, -SPRITE_W, SPRITE_H));
				if (*iter_d == 9)
					*iter_d = 0;
				(*is_moving) = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::R) == true or Map_gachi[(*y + SPRITE_H - 10) / 32][(*x) / 32] == '@'
				or Map_gachi[(*y + SPRITE_H - 10) / 32][(*x + SPRITE_W) / 32] == '@') {
				*x = 1800;
				*y = 1160;
			}
			if (Map_gachi[(*y + SPRITE_H - 10) / 32][(*x) / 32] == '%' or Map_gachi[(*y + SPRITE_H - 10) / 32][(*x + SPRITE_W) / 32] == '%') {
				main_active = true;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::S) == false and Keyboard::isKeyPressed(Keyboard::W) == false and Keyboard::isKeyPressed(Keyboard::D) == false and Keyboard::isKeyPressed(Keyboard::A) == false)
			(*is_moving) = false;

		sprite->setPosition(*x, *y);
		(*win).draw(*sprite);
	}
	int givex() {
		return *x;
	}
	int givey() {
		return *y;
	}
};