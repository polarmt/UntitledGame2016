#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Foreign.h"

class Hero {
	sf::RectangleShape hitbox; //hitbox 
	sf::Texture heroTexture;
	sf::Sprite heroSprite;
	const float cooldown = 500000;
	float delay = 0;
	int health = 100;
public:
	Hero(sf::Vector2f newPos, const sf::Texture& newTexture){
		heroSprite.setPosition(newPos);
		heroTexture = newTexture;
		heroSprite.setTexture(heroTexture);
		heroSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

		hitbox.setSize({30, 59});
		hitbox.setPosition(newPos.x + 17, newPos.y + 5);
		hitbox.setFillColor(sf::Color::Transparent);
	}
	void setTextureRect(sf::IntRect &newRect) {
		heroSprite.setTextureRect(newRect);
	}

	void draw(sf::RenderWindow &window) {
		window.draw(heroSprite);
		window.draw(hitbox);
	}

	void move(sf::Vector2f distance) {
		if (health > 0) {
			heroSprite.move(distance);
			hitbox.move(distance);
		}
	}

	void update(float time) {
		//std::cout << delay << std::endl;
		delay -= time;
	}

	sf::FloatRect getGlobalBounds() {
		return hitbox.getGlobalBounds();
	}
	
	void showHitBox() {
		hitbox.setFillColor(sf::Color::Blue);
	}

	bool foreignInteract(Foreign &object) {
		if (delay <= 0) {
			if (hitbox.getGlobalBounds().intersects(object.getGlobalBounds())) {
				delay = cooldown;
				return true;
			}
			return false;
		}
		return false;
	}

	void takeDamage(const int x) {
		health -= x;
		std::cout << "Health: " << health << std::endl;
	}

	int getY() {
		return heroSprite.getPosition().y;
	}

	int getX() {
		return heroSprite.getPosition().x;
	}

	void setY(float position) {
		heroSprite.setPosition({ heroSprite.getPosition().x, position });
	}
};

#endif