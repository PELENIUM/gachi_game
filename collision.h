#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bot.h"
#include "map.h"
#include "player.h"

using namespace sf;

bool collision(Bot *bot, Player *player, Sound sounds[], bool is_enemy) {
    if (is_enemy) {
        if (((*(bot->x) >= e_x and x <= e_x + 100) and (y >= e_y and y <= e_y + 100)) or ((x + 5 >= e_x and x + 5 <= e_x + 100) and (y >= e_y and y < e_y + 100))) {
            enemy->x = -100;
            enemy->y = -100;
            (*ptr).setFillColor(Color::Transparent);
            counter++;
            (*snd).play();
            return true;
        }
        else
            return false;
    }
    if (!is_enemy) {
        if (((x >= e_x and x <= e_x + 100) and (y >= e_y and y <= e_y + 100)) or ((x >= e_x and x <= e_x + 100) and (y + 100 >= e_y and y + 100 < e_y + 100))
            or ((x + 100 >= e_x and x + 100 <= e_x + 100) and (y + 100 >= e_y and y + 100 <= e_y + 100)) or ((x + 100 >= e_x and x + 100 <= e_x + 100) and (y >= e_y and y < e_y + 100))) {
            enemy->x = -100;
            enemy->y = -100;
            death_counter++;
            if (counter > 0)
                counter--;
            (*snd).play();
            return true;
        }
        else
            return false;
    }
}