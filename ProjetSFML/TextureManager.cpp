#include "TextureManager.hpp"

std::map<std::string, sf::Texture*> TextureManager::m_textures;

void TextureManager::LoadTexture(const std::string& _key, const std::string& _path)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(_path);
	m_textures[_key] = texture;

	std::cout << "Loaded texture: " << _key << " from " << _path << std::endl;
}

sf::Texture* TextureManager::GetTexture(const std::string& _key)
{
	std::cout << "Getting texture: " << _key << std::endl;
	return m_textures[_key];
}