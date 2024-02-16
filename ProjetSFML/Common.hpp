#ifndef COMMON__H
#define COMMON__H

#include <iostream>
#include <time.h>
#include <list>
#include <vector>
#include <string>
#include <random>

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/OpenGL.hpp"

#define TILE_SCALE 32

sf::Sprite LoadSprite(const std::string _path, bool _isCentered);
void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _angle, sf::RenderWindow& _window);

float ToRadians(float _degrees);
float ToDegrees(float _radians);

#endif