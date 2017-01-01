#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Foreign.h"
#include "Collision.h"
#include "TextureManager.h"

class Hero {
	sf::RectangleShape hitbox; //hitbox
	TextureManager textures;
	sf::Texture heroTexture;
	sf::Sprite heroSprite;
	const float cooldown = 500000;
	float delay = 0;
	int health = 100;
public:
	Hero(sf::Vector2f newPos, const std::string& fileName) {
		textures.addTexture(fileName);
		heroTexture = textures.loadTexture(fileName);
		heroSprite.setPosition(newPos);
		heroSprite.setTexture(heroTexture);
		heroSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

		Collision::CreateTextureAndBitmask(heroTexture, fileName);

		hitbox.setSize({30, 59});
		hitbox.setPosition(newPos.x + 17, newPos.y + 5);
		hitbox.setFillColor(sf::Color::Transparent);
	}

	bool collisionTest(const sf::Sprite &obj2) {
		if (Collision::PixelPerfectTest(heroSprite, obj2)) {
			return true;
		}
		return false;
	}

	bool collision(const sf::Sprite &obj2) {
		if (Collision::BoundingBoxTest(heroSprite, obj2)) {
			return true;
		}
		return false;
	}

	//Thinking of implementing pixel perfect collisions with foreign objects instead of hitboxes
	bool fCollisionTest(Foreign &object) {
		if (delay <= 0) {
			if (hitbox.getGlobalBounds().intersects(object.getGlobalBounds())) {
				delay = cooldown;
				return true;
			}
			return false;
		}
		return false;
	}

	sf::FloatRect getGlobalBounds() {
		return hitbox.getGlobalBounds();
	}

	void showHitBox() {
		hitbox.setFillColor(sf::Color::Blue);
	}

	void takeDamage(const int x) {
		health -= x;
		std::cout << "Health: " << health << std::endl;
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