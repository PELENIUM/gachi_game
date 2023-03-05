#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"
#include <math.h>
using namespace sf;

class Bot : private Player{
private:
	bool in_zone = false;
	bool attack_zone = false;
public:
	int* x = new int;
	int* y = new int;
	Bot (int X, int Y, String path, float speed):Player(X, Y, path, speed){
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
		if (!in_zone and main_active)
			sprite->setTextureRect(IntRect(0, 0, 35, 28));
		if (sqrt(pow(*(pl->x) - (*(x) + 36), 2) + pow(*(pl->y) - (*(y) + 28), 2)) <= 150)
			in_zone = true;
		if (in_zone) {
			if ((*(pl->x) - *(x)) > 0) {
				if ((*(pl->x) - *(x)) >= *MOVING_SPEED) {
					move_r = true;
					move_l = false;
				}
				if ((*(pl->x) - *(x)) < *MOVING_SPEED) {
					move_l = false;
					move_r = true;
				}
			}
			else if ((*(pl->x) - *(x)) < 0) {
				if (-(*(pl->x) - *(x)) >= (*MOVING_SPEED)) {
					move_l = true;
					move_r = false;
				}
				if (-(*(pl->x) - *(x)) < (*MOVING_SPEED)) {
					move_l = false;
					move_r = true;
				}
			}
			else if ((*(pl->x) - *(x)) == 0) {
				move_l = false;
				move_r = true;
			}

			if ((*(pl->y) + 32 - *(y)) > 0) {
				if ((*(pl->y) + 32 - *(y)) >= *MOVING_SPEED) {
					move_d = true;
					move_u = false;
				}
				if ((*(pl->y) + 32 - *(y)) < *MOVING_SPEED) {
					move_u = true;
					move_d = false;
				}
			}
			else if ((*(pl->y) + 32 - *(y)) < 0) {
				if (-(*(pl->y) + 32 - *(y)) >= *MOVING_SPEED) {
					move_u = true;
					move_d = false;
				}
				if (-(*(pl->y) + 32 - *(y)) < *MOVING_SPEED) {
					move_u = true;
					move_d = false;
				}
			}
			else if ((*(pl->y) + 32 - *(y)) == 0) {
				move_u = true;
				move_d = false;
			}

			if (main_active) {
				if (move_l) {
					if (Map[(*y) / 32][*x / 32] == '#' or Map[(*y + 28) / 32][*x / 32] == '#') {
						*x = 32 * ((*x) / 32) + 1;
					}
					if (Map[(*y) / 32][*x / 32] != '#' and Map[(*y + 28) / 32][*x / 32] != '#') {
						*x -= *MOVING_SPEED - 0.5;
					}
					(*counter_l)++;
					if (*counter_l >= 3) {
						(*iter_l)++;
						*counter_l = 0;
					}
					sprite->setTextureRect(IntRect((*iter_l) * 36 + 36, 29, -36, 28));
					if (*iter_l == 6)
						*iter_l = 0;
				}

				if (move_r) {
					if (Map[*y / 32][(*x + 36) / 32] == '#' or Map[(*y + 28) / 32][(*x + 36) / 32] == '#') {
						*x = 32 * ((*x + 36) / 32) - 37;
					}
					if (Map[*y / 32][(*x + 36) / 32] != '#' and Map[(*y + 28) / 32][(*x + 36) / 32] != '#') {
						*x += *MOVING_SPEED;
					}

					(*counter_r)++;
					if (*counter_r >= 3) {
						(*iter_r)++;
						*counter_r = 0;
					}
					sprite->setTextureRect(IntRect((*iter_r) * 36, 29, 36, 28));
					if (*iter_r == 6)
						*iter_r = 0;
				}

				if (move_u) {
					if (Map[*y / 32][*x / 32] == '#' or Map[*y / 32][(*x + 36) / 32] == '#') {
						*y = 32 * (*y / 32) + 1;
					}
					if (Map[*y / 32][*x / 32] != '#' and Map[*y / 32][(*x + 36) / 32] != '#') {
						*y -= *MOVING_SPEED - 0.5;
					}

					(*counter_u)++;
					if (*counter_u >= 3) {
						(*iter_u)++;
						*counter_u = 0;
					}
					if (move_r)
						sprite->setTextureRect(IntRect((*iter_u) * 36, 29, 36, 28));
					if (move_l)
						sprite->setTextureRect(IntRect((*iter_u) * 36 + 36, 29, -36, 28));
					if (*iter_u == 6)
						*iter_u = 0;
				}

				if (move_d) {
					if (Map[(*y + 28) / 32][(*x) / 32] == '#' or Map[(*y + 28) / 32][(*x + 36) / 32] == '#') {
						*y = 32 * (*y / 32) - 1;
					}
					if (Map[(*y + 28) / 32][(*x) / 32] != '#' and Map[(*y + 28) / 32][(*x + 36) / 32] != '#') {
						*y += *MOVING_SPEED;
					}

					(*counter_d)++;
					if (*counter_d >= 3) {
						(*iter_d)++;
						*counter_d = 0;
					}
					if (move_r)
						sprite->setTextureRect(IntRect((*iter_d) * 36, 29, 36, 28));
					if (move_l)
						sprite->setTextureRect(IntRect((*iter_d) * 36 + 36, 29, -36, 28));
					if (*iter_d == 6)
						*iter_d = 0;
				}

				if (Map[(*y + 28 - 10) / 32][(*x) / 32] == '@' or Map[(*y + 28 - 10) / 32][(*x + 28) / 32] == '@') {
					*x = 1800;
					*y = 1160;
				}
				
			}
			
		}
		sprite->setPosition(*x, *y);
		if (main_active)
			win->draw(*sprite);
	}
};