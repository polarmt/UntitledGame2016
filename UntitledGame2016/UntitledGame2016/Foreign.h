#ifndef FOREIGN_H
#define FOREIGN_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Foreign {
	sf::RectangleShape hitbox; //hitbox 
	sf::Texture objectTexture;
	sf::Sprite objectSprite;
public:
	Foreign(sf::Vector2f newPos) {
		hitbox.setSize({ 15, 5});
		hitbox.setPosition(newPos);
		hitbox.setFillColor(sf::Color::Green);
	}

	sf::FloatRect getGlobalBounds() {
		return hitbox.getGlobalBounds();
	}

	void fire() {
		hitbox.move({ -1.0f, 0 });
	}

	void draw(sf::RenderTarget &window) {
		window.draw(hitbox);
	}
};

#endif 