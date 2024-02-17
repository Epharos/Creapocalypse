#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "Common.hpp"

class TextureManager
{
private:
	static std::map<std::string, sf::Texture*> m_textures;
public:
	static void LoadTexture(const std::string& _key, const std::string& _path);
	static sf::Texture* GetTexture(const std::string& _key);
};

#endif