#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "map.h"
#include "player.h"
#include "bot.h"

using namespace sf;

#define WIDTH 1920
#define HEIGHT 1280

RenderWindow window(VideoMode(WIDTH, HEIGHT), "SFML");

Music back_music;
Music back_music_main;

void game() {
    back_music.openFromFile("sounds/back.ogg");
    back_music.setLoop(true);
    back_music.setVolume(0);
    back_music.play();
    back_music_main.openFromFile("sounds/back_main.ogg");
    back_music_main.setLoop(true);
    back_music_main.setVolume(100);
    back_music_main.play();
    Bot *nps = new Bot(150, 300, "images/Sprites/NightBorne.png", 3.5);
    Player *main_player = new Player(1800, 860, "images/Sprites/enemy.png", 4);
    window.setFramerateLimit(60);
    Clock clock;
    float main_timer = 0;
    Texture map_img;
    map_img.loadFromFile("images/sprites.png");
    Sprite map;
    map.setTexture(map_img);
    while (window.isOpen()) {
        float time = (float)clock.getElapsedTime().asMicroseconds() / 800;
        main_timer += time;
        clock.restart();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
        }
        window.clear({ 0, 0, 0 });
        if (main_active){
            for (int i = 0; i < 40; i++) {
                for (int j = 0; j < 60; j++) {
                    if (Map[i][j] == '#') {
                        map.setTextureRect(IntRect(0, 0, 32, 32));
                    }
                    if (Map[i][j] == '.') {
                        map.setTextureRect(IntRect(32, 0, 32, 32));
                    }
                    if (Map[i][j] == '@') {
                        map.setTextureRect(IntRect(64, 0, 32, 32));
                    }
                    if (Map[i][j] == '&') {
                        map.setTextureRect(IntRect(96, 0, 32, 32));
                    }
                    if (Map[i][j] == '%') {
                        map.setTextureRect(IntRect(128, 0, 32, 32));
                    }
                    if (Map[i][j] == '$') {
                        map.setTextureRect(IntRect(160, 0, 32, 32));
                    }
                    map.setPosition(j * 32, i * 32);
                    window.draw(map);
                }
            }
            back_music.setVolume(0);
            back_music_main.setVolume(100);
        }
        
        if (!main_active) {
            for (int i = 0; i < 40; i++) {
                for (int j = 0; j < 60; j++) {
                    if (Map_gachi[i][j] == '#') {
                        map.setTextureRect(IntRect(192, 0, 32, 32));
                    }
                    if (Map_gachi[i][j] == '.') {
                        map.setTextureRect(IntRect(224, 0, 32, 32));
                    }
                    if (Map_gachi[i][j] == '@') {
                        map.setTextureRect(IntRect(256, 0, 32, 32));
                    }
                    if (Map_gachi[i][j] == '%') {
                        map.setTextureRect(IntRect(128, 0, 32, 32));
                    }
                    map.setPosition(j * 32, i * 32);
                    window.draw(map);
                }
            }
            back_music.setVolume(100);
            back_music_main.setVolume(0);
        }
        
        nps->update(&window, main_player);
        main_player->update(&window);
        window.display();
    }
    delete main_player;
}

int main() {
    game();
    return 0;
}