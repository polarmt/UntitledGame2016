#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "Hero.h"
#include "Environment.h"
#include "TextureManager.h"
#include "Foreign.h"

int main()
{
	//Render Window
	float height = 1080;
	float width = 540;
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window;
	window.create(sf::VideoMode(height, width, desktop.bitsPerPixel), "Untitled Game");
	window.setFramerateLimit(60);

	//Textures
	TextureManager textures;
	textures.addTexture("dud.png");
	textures.addTexture("sample_spritesheet.png");
	sf::Sprite block(textures.loadTexture("dud.png"));
	sf::Sprite test(textures.loadTexture("sample_spritesheet.png"), sf::IntRect(0, 0, 64, 64));
	test.setPosition(150, 150);
	block.setPosition(150, 150);

	//Objects (size, position)
	sf::Clock cl;

	Hero p({ 0, 250 }, textures.loadTexture("sample_spritesheet.png"));

	std::vector<Block> blocks;
	Block b({ 1000, 50 }, { 0, 500 });
	Block c({ 100, 30 }, { 300, 480 });
	Block platform({ 100, 100 }, { 540, 400 });
	Block platform1({ 300, 50 }, { 520, 250 });
	Block platform2({ 300, 50 }, { 200, 400 });
	blocks.push_back(b);
	blocks.push_back(platform);
	blocks.push_back(platform1);
	blocks.push_back(platform2);

	Foreign missile({ 500, 460 });

	//Logic variables
	bool fall = true;
	bool jumping = false;
	int animation = 0;
	int delayCounter = 0;
	int curr = 0;			//Block index

	float jumpSpeed = -0.01;
	float fallSpeed = 0;
	const float gravity = 1.0;
	const float moveSpeed = 4.5;


	while (window.isOpen()) {
		bool collisions = false;	//collision?
		bool move = true;			//can he move?

// -- Events -- 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !jumping) {
			p.move({ 0, jumpSpeed });
			jumping = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			p.setTextureRect(sf::IntRect(animation * 64, 0, 64, 64));
			p.move({ moveSpeed, 0 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			p.setTextureRect(sf::IntRect(animation * 64, 64, 64, 64));
			p.move({ -moveSpeed, 0 });
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

// -- Logic --
		
	//Animation
		delayCounter++;
		if (delayCounter % 5 == 0) {
			animation++;
		}
		if (animation == 2) {
			animation = 0;
		}

	//Gravity
		if (cl.getElapsedTime().asMicroseconds() > 800.0f) {
			if (!jumping) {
				if (p.getY() < b.getY()) {
					fallSpeed += gravity;
					p.move({ 0, fallSpeed });
				}
				else {
					fallSpeed = 0;
				}
			}
			else {
				if (p.getY() < b.getY()) {
					jumpSpeed += gravity;
					p.move({ 0, jumpSpeed });
				}
				else {
					p.setY(b.getY());
					jumpSpeed = -10;
					jumping = false;
				}
			}
		}

	//Foreign Collisions
		missile.fire();
		if (p.foreignInteract(missile)) {
			p.takeDamage(5);
		}

	//Clock
		p.update(cl.getElapsedTime().asMicroseconds());
		//std::cout << cl.getElapsedTime().asMicroseconds() << std::endl;
		cl.restart();

// -- Draw --
		window.clear();

		window.draw(block);
		window.draw(test);
		platform.draw(window);
		platform1.draw(window);
		platform2.draw(window);
		missile.draw(window);
		b.draw(window);
		p.draw(window);

		window.display();
	}

	return 0;
}