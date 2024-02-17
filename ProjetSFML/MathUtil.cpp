#include "MathUtil.hpp"

float DistanceSquared(sf::Vector2f _a, sf::Vector2f _b)
{
	return (_a.x - _b.x) * (_a.x - _b.x) + (_a.y - _b.y) * (_a.y - _b.y);
}

sf::Vector2f Normalize(sf::Vector2f _v)
{
	float length = sqrt(_v.x * _v.x + _v.y * _v.y);
	return sf::Vector2f(_v.x / length, _v.y / length);
}