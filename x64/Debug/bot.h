#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"
#include <cmath>
using namespace sf;

class Bot{
private:
	int* x = new int;
	int* y = new int;
	bool* is_moving = new bool;
	int* iter_l = new int, * iter_r = new int, * iter_u = new int, * iter_d = new int, * counter_l = new int, * counter_r = new int, * counter_u = new int, * counter_d = new int;
	float* MOVING_SPEED = new float;
	int* death_counter = new int;
	Texture* texture = new Texture;
	Sprite* sprite = new Sprite;
	bool move_l = false, move_r = false, move_u = false, move_d = false;
public:
	Bot (int X, int Y, String path, float speed){
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
		*death_counter = 2;
	}
	~Bot(){
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
	void update(RenderWindow *win, Player *pl) {
		sprite->setTextureRect(IntRect(0, 0, SPRITE_W, SPRITE_H));
		if ((*(pl->x) - *(x)) > 0) {
			*x += *MOVING_SPEED;
			move_r = true;
			move_l = false;
			move_u = false;
			move_d = false;
		}
		else if ((*(pl->x) - *(x)) < 0) {
			*x -= *MOVING_SPEED;
			move_l = true;
			move_r = false;
			move_u = false;
			move_d = false;
		}
		if ((*(pl->y) - *(y)) > 0) {
			*y += *MOVING_SPEED;
			move_d = true;
			move_u = false;
		}
		else if ((*(pl->y) - *(y)) < 0) {
			*y -= *MOVING_SPEED;
			move_u = true;
			move_d = false;
		}
		if (main_active) {
			if (move_l) {
				if (Map[(*y + SPRITE_H - 5) / 32][*x / 32] == '#') {
					*x = 32 * ((*x) / 32) + 33 + 2;
				}
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

			if (move_r) {
				if (Map[*y / 32][(*x + SPRITE_W) / 32] == '#') {
					*x = 32 * ((*x + SPRITE_W) / 32) - (SPRITE_W + 2);
				}
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

			if (move_u) {
				if (Map[*y / 32][*x / 32] == '#' or Map[(*y + SPRITE_H) / 32][*x / 32] == '#') {
					*y = 32 * (*y / 32) + 5;
				}
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

			if (move_d) {
				if (Map[(*y + SPRITE_H) / 32][(*x) / 32] == '#') {
					*y = 32 * (*y / 32) - 5;
				}
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
		}
		sprite->setPosition(*x, *y);
		win->draw(*sprite);
	}
};