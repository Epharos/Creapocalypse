#ifndef MATHUTIL__HPP
#define MATHUTIL__HPP

#include "Common.hpp"

/// <summary>
/// Returns the squared distance between two points
/// </summary>
/// <param name="_a">First vector</param>
/// <param name="_b">Second vector</param>
/// <returns>A floating number representing the squared distance between _a and _b</returns>
float DistanceSquared(sf::Vector2f _a, sf::Vector2f _b)
{
	return (_a.x - _b.x) * (_a.x - _b.x) + (_a.y - _b.y) * (_a.y - _b.y);
}

/// <summary>
/// Normalize a vector
/// </summary>
/// <param name="_v">The vector to be normalized</param>
/// <returns>A sf::Vector2f normalized</returns>
sf::Vector2f Normalize(sf::Vector2f _v)
{
	float length = sqrt(_v.x * _v.x + _v.y * _v.y);
	return sf::Vector2f(_v.x / length, _v.y / length);
}
#endif