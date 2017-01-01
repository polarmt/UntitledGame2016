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

	    // offsets can be adjusted in here for smoother jumping mechanics
    bool colliding(Hero* hero, int speed, char flag) {
        /*if (flag == 't') {
            return hero->getY() + speed >= block.getPosition().y - 64 &&
                hero->getY() + speed < block.getPosition().y &&
                hero->getX() + 45 >= block.getPosition().x &&
                hero->getX() + 20 <= block.getPosition().x + block.getSize().x;
        }
        else if (flag == 'r') {
            return hero->getX() + 20 - 2*speed < block.getPosition().x + block.getSize().x &&
                hero->getX() + 20 > block.getPosition().x + block.getSize().x &&
                hero->getY() > block.getPosition().y - 64 &&
                hero->getY() < block.getPosition().y + block.getSize().y;
        }
        else if (flag == 'l') {
            return hero->getX() + 45 + 2*speed > block.getPosition().x &&
                hero->getX() + 45 < block.getPosition().x &&
                hero->getY() > block.getPosition().y - 64 &&
                hero->getY() < block.getPosition().y + block.getSize().y;
        }
        else if (flag == 'b') {
            return hero->getY() <= block.getPosition().y + block.getSize().y &&
                hero->getY() + 64 >= block.getPosition().y + block.getSize().y &&
                hero->getX() + 45 >= block.getPosition().x &&
                hero->getX() + 20 <= block.getPosition().x + block.getSize().x;
        }
        else {
            return false;
        }*/
		return hero->getGlobalBounds2().intersects(block.getGlobalBounds());
    }

	int getX() {
		return block.getPosition().x;
	}
	sf::Vector2f getSize() {
		return block.getSize();
	}
	int getY() {
		return block.getPosition().y - 64;
	}

	~Block() {
		std::cout << "Block is destroyed" << std::endl;
	}
};