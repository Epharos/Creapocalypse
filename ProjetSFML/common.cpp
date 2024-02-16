#include "Common.hpp"

#include "Building.hpp"
#include "GameManager.hpp"
#include "BaseTurret.hpp"
#include "Bullet.hpp"

sf::Sprite LoadSprite(const std::string _path, bool _isCentered)
{
	//Création et chargement de la texture
	sf::Texture* tempTex = new sf::Texture(); //Nécessaire dynamiquement
	tempTex->loadFromFile(_path);

	//Création et configuration du sprite
	sf::Sprite tempSprite;
	tempSprite.setTexture(*tempTex);

	if (_isCentered) //Centrage du sprite
	{
		sf::Vector2u tempTaille = tempTex->getSize();
		sf::Vector2f tempOrigin = sf::Vector2f(tempTaille.x / 2, tempTaille.y / 2);
		tempSprite.setOrigin(tempOrigin);
	}

	return tempSprite;
}

void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _angle, sf::RenderWindow& _window)
{
	_sprite.setRotation(_angle);
	_sprite.setPosition(_pos);
	_window.draw(_sprite);
}

float ToRadians(float _degrees)
{
	return std::fmod(_degrees * 3.14159265359f / 180.f, 2 * 3.14159265359f);
}

float ToDegrees(float _radians)
{
	return std::fmod(_radians * 180.f / 3.14159265359f, 360);
}

bool IsBuilding(Entity* _entity)
{
	return dynamic_cast<Building*>(_entity) != nullptr;
}

bool IsPlayer(Entity* _entity)
{
	return _entity == GameManager::GetInstance()->GetPlayer();
}

bool IsTurret(Entity* _entity)
{
	return dynamic_cast<BaseTurret*>(_entity) != nullptr;
}

bool IsBullet(Entity* _entity)
{
	return dynamic_cast<Bullet*>(_entity) != nullptr;
}