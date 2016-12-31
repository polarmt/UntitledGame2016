#include "TextureManager.h"

const void TextureManager::addTexture(const std::string &fileName) {
	sf::Texture* temp = new sf::Texture;
	if (!temp->loadFromFile("sprites/" + fileName)) {
		std::cout << "Cannot load texture " + fileName << std::endl;
		delete temp;
	}
	else {
		textureMap[fileName] = temp;
	}
}

const sf::Texture &TextureManager::loadTexture(const std::string &fileName) {
	std::map<std::string, sf::Texture *>::const_iterator searchTexture = textureMap.find(fileName);
	if (searchTexture != textureMap.end())
		return *searchTexture->second;
	else {
		std::cout << "Texture does not exist" << std::endl;
	}
}
