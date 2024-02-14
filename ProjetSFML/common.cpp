#include "common.h"

sf::Sprite LoadSprite(const std::string _path, bool _isCentered)
{
	//Cr�ation et chargement de la texture
	sf::Texture* tempTex = new sf::Texture(); //N�cessaire dynamiquement
	tempTex->loadFromFile(_path);

	//Cr�ation et configuration du sprite
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
