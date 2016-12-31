#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

class Block {
	sf::RectangleShape block;
	sf::Sprite blockSprite;
public:
	Block(sf::Vector2f size, sf::Vector2f newPos) {
		block.setSize(size);
		block.setPosition(newPos);
		block.setFillColor(sf::Color::Red);
	}

	void move(sf::Vector2f distance) {
		block.move(distance);
	}

	void draw(sf::RenderWindow &window) {
		window.draw(block);
	}

	int getY() {
		return block.getPosition().y - 64;
	}

	~Block() {
		std::cout << "Block is destroyed" << std::endl;
	}
};