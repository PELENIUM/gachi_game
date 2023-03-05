#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"
using namespace sf;

#define SPRITE_W 57
#define SPRITE_H 61

class Player {
private:
	bool *is_moving = new bool;
	bool move_l = false, move_r = true, move_u = false, move_d = false;
	int *iter_l = new int, *iter_r = new int, *iter_u = new int, *iter_d = new int, *iter_s = new int, *counter_l = new int, *counter_r = new int, *counter_u = new int, *counter_d = new int, *counter_s = new int;
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
	bool collision(int x, int y, int ox, int oy, int w, int h) {
		if (((x > ox and x < ox + 32) or (x + w > ox and x + w < ox + 32)) and ((y > oy and y < oy + 32) or (y + h > oy and y + h < oy + 32)))
			return true;
	}
	void update(RenderWindow *win) {
		*x = sprite->getPosition().x;
		*y = sprite->getPosition().y;
		sprite->setTextureRect(IntRect(0, 67, 48, 67));
		if (main_active) {
			if (Keyboard::isKeyPressed(Keyboard::A) == true) {
				if (Map[(*y + SPRITE_H - 5) / 32][*x / 32] == '#') {
					*x = 32 * ((*x) / 32) + 33 + 1;
				}
				else
					*x += -(*MOVING_SPEED);
				(*counter_l)++;
				if (*counter_l >= 4) {
					(*iter_l)++;
					*counter_l = 0;
				}
				sprite->setTextureRect(IntRect((*iter_l) * 67 + 67, 0, -67, 67));
				if (*iter_l == 8)
					*iter_l = 0;
				(*is_moving) = true;
				move_r = false;
				move_l = true;
				move_u = false;
				move_d = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::D) == true) {
				if (Map[*y / 32][(*x + 67) / 32] == '#' or Map[(*y + 67) / 32][(*x + 67) / 32] == '#') {
					*x = 32 * ((*x + 67) / 32) - 67;
				}
				else
					*x += (*MOVING_SPEED);
				(*counter_r)++;
				if (*counter_r >= 4) {
					(*iter_r)++;
					*counter_r = 0;
				}
				sprite->setTextureRect(IntRect((*iter_r) * 67, 0, 67, 67));
				if (*iter_r == 8)
					*iter_r = 0;
				(*is_moving) = true;
				move_r = true;
				move_l = false;
				move_u = false;
				move_d = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::W) == true) {
				if (Map[*y / 32][*x / 32] == '#' or Map[*y / 32][(*x + 67) / 32] == '#') {
					*y = 32 * (*y / 32) + 1;
				}
				else
					*y += -(*MOVING_SPEED);
				(*counter_u)++;
				if (*counter_u >= 3) {
					(*iter_u)++;
					*counter_u = 0;
				}
				if (move_r == true) {
					sprite->setTextureRect(IntRect((*iter_u) * 67, 0, 67, 67));
				}
				if (move_l == true) {
					sprite->setTextureRect(IntRect((*iter_u) * 67 + 67, 0, -67, 67));
				}
				if (*iter_u == 8)
					*iter_u = 0;
				(*is_moving) = true;
				move_d = false;
				move_u = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::S) == true) {
				if (Map[(*y + 67) / 32][(*x) / 32] == '#') {
					*y = 32 * (*y / 32) - 1;
				}
				else
					*y += *MOVING_SPEED;
				(*counter_d)++;
				if (*counter_d >= 3) {
					(*iter_d)++;
					*counter_d = 0;
				}
				if (move_r == true) {
					sprite->setTextureRect(IntRect((*iter_d) * 67, 0, 67, 67));
				}
				if (move_l == true) {
					sprite->setTextureRect(IntRect((*iter_d) * 67 + 67, 0, -67, 67));
				}
				if (*iter_d == 8)
					*iter_d = 0;
				(*is_moving) = true;
				move_d = true;
				move_u = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::S) == false and Keyboard::isKeyPressed(Keyboard::D) == false and Keyboard::isKeyPressed(Keyboard::A) == false and Keyboard::isKeyPressed(Keyboard::W) == false) {
				(*is_moving) = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::R) == true or Map[(*y + 67 - 10) / 32][(*x) / 32] == '@'
				or Map[(*y + 67 - 10) / 32][(*x + 67) / 32] == '@') {
				*x = 1750;
				*y = 1130;
			}
			if (Map[(*y + 67) / 32][(*x) / 32] == '%' or Map[(*y + 67) / 32][(*x + 67) / 32] == '%'
				or Map[(*y) / 32][(*x) / 32] == '%' or Map[(*y + 67) / 32][(*x + 67) / 32] == '%') {
				main_active = false;
			}
		}
		if (!main_active) {
			if (Keyboard::isKeyPressed(Keyboard::A) == true) {
				if (Map_gachi[(*y + 67 - 5) / 32][*x / 32] == '#') {
					*x = 32 * ((*x) / 32) + 33;
				}
				else
					*x += -(*MOVING_SPEED);
				(*counter_l)++;
				if (*counter_l >= 3) {
					(*iter_l)++;
					*counter_l = 0;
				}
				sprite->setTextureRect(IntRect((*iter_l) * 67, 122, 67, 67));
				if (*iter_l == 9)
					*iter_l = 0;
				(*is_moving) = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::D) == true) {
				if (Map_gachi[*y / 32][(*x + 67) / 32] == '#') {
					*x = 32 * ((*x + 67) / 32) - (67);
				}
				else
					*x += (*MOVING_SPEED);
				(*counter_r)++;
				if (*counter_r >= 3) {
					(*iter_r)++;
					*counter_r = 0;
				}
				sprite->setTextureRect(IntRect((*iter_r) * 67 + 67, 122, -67, 67));
				if (*iter_r == 9)
					*iter_r = 0;
				(*is_moving) = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::W) == true) {
				if (Map_gachi[*y / 32][*x / 32] == '#' or Map[(*y + 67) / 32][*x / 32] == '#') {
					*y = 32 * (*y / 32) + 1;
				}
				else
					*y += -(*MOVING_SPEED);
				(*counter_u)++;
				if (*counter_u >= 3) {
					(*iter_u)++;
					*counter_u = 0;
				}
				sprite->setTextureRect(IntRect((*iter_u) * 67 + 67, 184.7, 67, 67));
				if (*iter_u == 9)
					*iter_u = 0;
				(*is_moving) = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::S) == true) {
				if (Map_gachi[(*y + 67) / 32][(*x) / 32] == '#') {
					*y = 32 * (*y / 32);
				}
				else
					*y += *MOVING_SPEED;
				(*counter_d)++;
				if (*counter_d >= 3) {
					(*iter_d)++;
					*counter_d = 0;
				}
				sprite->setTextureRect(IntRect((*iter_d) * 67 + 67, 61, -67, 67));
				if (*iter_d == 9)
					*iter_d = 0;
				(*is_moving) = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::R) == true or Map_gachi[(*y + 67 - 10) / 32][(*x) / 32] == '@'
				or Map_gachi[(*y + 67 - 10) / 32][(*x + 67) / 32] == '@') {
				*x = 1800;
				*y = 1160;
			}
			if (Map_gachi[(*y + 67 - 10) / 32][(*x) / 32] == '%' or Map_gachi[(*y + 67 - 10) / 32][(*x + 67) / 32] == '%') {
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