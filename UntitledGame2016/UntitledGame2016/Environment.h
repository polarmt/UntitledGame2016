#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Collision.h"

class Block {
	TextureManager textures;
	sf::RectangleShape block;
	sf::Texture blockTexture;
	sf::Sprite blockSprite;
public:
	Block(sf::Vector2f size, sf::Vector2f newPos, const std::string& fileName, float angle = 0) {
		textures.addTexture(fileName);
		blockTexture = textures.loadTexture(fileName);
		blockSprite.rotate(angle);
		blockTexture.setRepeated(true);
		blockSprite.setPosition(newPos);
		blockSprite.setTexture(blockTexture);

		Collision::CreateTextureAndBitmask(blockTexture, fileName);

		block.setSize(size);
		block.setPosition(newPos);
		block.setFillColor(sf::Color::Red);
	}

	sf::Sprite& getSprite() {
		return blockSprite;
	}

	void move(sf::Vector2f distance) {
		block.move(distance);
	}

	void draw(sf::RenderWindow &window) {
		window.draw(blockSprite);
	}

	int getY() {
		return block.getPosition().y - 64;
	}

	~Block() {
		std::cout << "Block is destroyed" << std::endl;
	}
};