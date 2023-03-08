#pragma once
#include <SFML/Graphics.hpp>
#include "map.h"
using namespace sf;

#define SPRITE_W 57
#define SPRITE_H 61

class Player {
protected:
	bool *is_moving = new bool;
	bool move_l = false, move_r = true, move_u = false, move_d = false;
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
///	 sides:
///	     1 - left
///	     2 - right
///	     3 - up
///	     4 - down
	int collision(int *x, int *y, int w, int h, std::string m[], int side) {
		switch (side) {
		case 1:
			if (m[*y / 32][*x / 32] == '#')
				return 1;
			if (m[(*y + h) / 32][*x / 32] == '#')
				return 2;
			if (m[(*y + h) / 32][*x / 32] != '#' and m[(*y + h) / 32][*x / 32] != '#')
				return 0;

		case 2:
			if (m[*y / 32][(*x + 67) / 32] == '#')
				return 1;
			if (m[(*y + h) / 32][(*x + w) / 32] == '#')
				return 2;
			if (m[*y / 32][(*x + w) / 32] != '#' and m[(*y + h) / 32][(*x + w) / 32] != '#')
				return 0;

		case 3:
			if (m[*y / 32][*x / 32] == '#')
				return 1;
			if (m[*y / 32][(*x + w) / 32] == '#')
				return 2;
			if (m[*y / 32][*x / 32] != '#' and m[*y / 32][(*x + w) / 32] != '#')
				return 0;

		case 4:
			if (m[(*y + h) / 32][(*x) / 32] == '#')
				return 1;
			if (m[(*y + h) / 32][(*x + w) / 32] == '#')
				return 2;
			if (m[(*y + h) / 32][(*x) / 32] != '#' and m[(*y + h) / 32][(*x + w) / 32] != '#')
				return 0;

		default:
			return -1;
		}
	}
	void update(RenderWindow *win) {
		std::string *map = new std::string;
		if (main_active)
			map = Map;
		if (!main_active)
			map = Map_gachi;
		*x = sprite->getPosition().x;
		*y = sprite->getPosition().y;
		sprite->setTextureRect(IntRect(0, 67, 48, 67));
		if (Keyboard::isKeyPressed(Keyboard::A) == true) {
			if (((collision(x, y, 67, 67, map, 1) == 1 or collision(x, y, 67, 67, map, 1) == 2) and map[(*y + 67) / 32][*x / 32] != '#' and map[*y / 32][*x / 32] != '#')
				or (map[(*y + 67) / 32][*x / 32] == '#' and map[*y / 32][*x / 32] == '#'))
				*x = (32 * (*x / 32)) + 32;

			else if (collision(x, y, 67, 67, map, 1) == 0 or (map[(*y + 67) / 32][*x / 32] == '#' and map[(*y + 67) / 32][(*x + 67) / 32] == '#' and collision(x, y, 67, 67, map, 1) != 1)
				or (map[*y / 32][*x / 32] == '#' and map[*y / 32][((*x + 67) + 67) / 32] == '#' and collision(x, y, 67, 67, map, 1) != 2))
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
		}
		if (Keyboard::isKeyPressed(Keyboard::D) == true) {
			if (((collision(x, y, 67, 67, map, 2) == 1 or collision(x, y, 67, 67, map, 2) == 2) and map[(*y + 67) / 32][(*x + 67) / 32] != '#' and map[*y / 32][(*x + 67) / 32] != '#')
				or (map[(*y + 67) / 32][(*x + 67) / 32] == '#' and map[*y / 32][(*x + 67) / 32] == '#'))
				*x = 32 * ((*x + 67) / 32) - 67;

			else if (collision(x, y, 67, 67, map, 2) == 0 or (map[(*y + 67) / 32][*x / 32] == '#' and map[(*y + 67) / 32][(*x + 67) / 32] == '#' and collision(x, y, 67, 67, map, 2) != 1)
				or (map[*y / 32][*x / 32] == '#' and map[*y / 32][(*x + 67) / 32] == '#' and collision(x, y, 67, 67, map, 2) != 2))
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
		}
		if (Keyboard::isKeyPressed(Keyboard::W) == true) {
			if ((collision(x, y, 67, 67, map, 3) == 1 or collision(x, y, 67, 67, map, 3) == 2) and (map[*y / 32][*x / 32] != '#' and map[(*y + 67) / 32][*x / 32] != '#') and (map[*y / 32][(*x + 67) / 32] != '#'
				and map[(*y + 67) / 32][(*x + 67) / 32] != '#')) {
				*y = 32 * (*y / 32) + 32;
			}
			else if (collision(x, y, 67, 67, map, 3) == 0 or ((map[*y / 32][*x / 32] != '#' and map[(*y + 67) / 32][*x / 32] != '#') and (map[*y / 32][(*x + 67) / 32] != '#' and map[(*y + 67) / 32][(*x + 67) / 32] != '#')))
				*y -= (*MOVING_SPEED);
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
			if (collision(x, y, 67, 67, map, 4) == 1 or collision(x, y, 67, 67, Map, 4) == 2) {
				*y = 32 * (*y / 32);
			}
			else if (collision(x, y, 67, 67, map, 4) == 0)
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
		if (Keyboard::isKeyPressed(Keyboard::S) == false and Keyboard::isKeyPressed(Keyboard::D) == false
			and Keyboard::isKeyPressed(Keyboard::A) == false and Keyboard::isKeyPressed(Keyboard::W) == false) {
			(*is_moving) = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::R) == true or map[(*y + 57) / 32][(*x) / 32] == '@'
			or map[(*y + 57) / 32][(*x + 67) / 32] == '@') {
			*x = 1750;
			*y = 1130;
		}
		if (map[(*y + 67) / 32][(*x) / 32] == '%' or map[(*y + 67) / 32][(*x + 67) / 32] == '%'
			or map[(*y) / 32][(*x) / 32] == '%' or map[(*y + 67) / 32][(*x + 67) / 32] == '%') {
			main_active = !main_active;
		}
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