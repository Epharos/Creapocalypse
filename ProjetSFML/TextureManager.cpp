#include "TextureManager.hpp"

std::map<std::string, sf::Texture*> TextureManager::m_textures;

void TextureManager::LoadTexture(const std::string& _key, const std::string& _path)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(_path);
	m_textures[_key] = texture;
}

sf::Texture* TextureManager::GetTexture(const std::string& _key)
{
	return m_textures[_key];
}