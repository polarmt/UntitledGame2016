#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <math.h>
#include "Hero.h"
#include "Environment.h"
#include "Foreign.h"
#include "TextureManager.h"

using namespace Collision;

int main()
{
	//Render Window
	float height = 1080;
	float width = 540;
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window;
	window.create(sf::VideoMode(height, width, desktop.bitsPerPixel), "Untitled Game");
	window.setFramerateLimit(60);

	//Logic variables
	sf::Clock cl;
	sf::Clock clock;
	sf::Time elapsed;
	bool fall = true;
	bool jumping = false;
	bool released = true; // to deal with spammable jumps
	bool fallRight = false;
	bool fallLeft = false;
	int animation = 0;
	int delayCounter = 0;
	int curr = 0;			//Block index
	float jumpSpeed = -15;
	float fallSpeed = 0;
	const float gravity = 1.0;
	const float moveSpeed = 3.5; //DONT FUCKING CHANGE THIS

	//Objects (size, position) 

	Hero p({ 0, 250 }, "sample_spritesheet.png");
	p.showHitBox();
	std::vector<Block> blocks;
	Block b({ 1000, 50 }, { 0, 500 }, "box.png");
	//Block c({ 50, 50 }, { 300, 350 }, "box.png", 30);
	blocks.push_back(b);
	//blocks.push_back(c);

	Block platform({ 100, 100 }, { 540, 400 }, "box.png");
	//Block platform1({ 300, 50 }, { 520, 250 });
	//Block platform2({ 300, 50 }, { 200, 400 });
	//blocks.push_back(b);
	blocks.push_back(platform);
	//blocks.push_back(platform1);
	//blocks.push_back(platform2);

	Foreign missile({ 500, 460 });

	while (window.isOpen()) {
		//elapsed = clock.restart();
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
			for (int i = 0; i < blocks.size(); i++) {
				if (curr != i && blocks[i].colliding(&p)) {
					std::cout << "hi" << std::endl;
					move = false;
					p.move({ -moveSpeed, 0 });
					break;
				}
			}
			if (fallLeft) {
				p.move({ -moveSpeed, 0 });
			}
			if (!jumping && !blocks[curr].colliding(&p)) {
				fallRight = true;
				jumpSpeed = 0;
				jumping = true;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			p.setTextureRect(sf::IntRect(animation * 64, 64, 64, 64));
			p.move({ -moveSpeed, 0 });
			for (int i = 0; i < blocks.size(); i++) {
				if (curr != i && blocks[i].colliding(&p)) {
					std::cout << "wut" << std::endl;
					p.move({ moveSpeed, 0 });
					move = false;
					break;
				}
			}
			if (fallRight) {
				p.move({ moveSpeed, 0 });
			}
			if (!jumping && !blocks[curr].colliding(&p)) {
				fallLeft = true;
				jumpSpeed = 0;
				jumping = true;
			}
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

			// to account for the initial fall
			if (fall && !jumping && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				if (p.getY() < b.getY()) {
					fallSpeed += gravity;
					p.move({ 0, fallSpeed });
				}
				else {
					fallSpeed = 0;
					fall = false;
				}
			}
			else if (jumping) {
				// if the hero lands
				for (int i = 0; i < blocks.size(); i++) {
					//Hero temp = p;
					p.move({ 0, jumpSpeed + gravity });
					if (blocks[i].colliding(&p)) {
						p.setY(blocks[i].getY());
						jumpSpeed = -15;
						jumping = false, fallLeft = false, fallRight = false;
						curr = i;
						collisions = true;
						break;
					}
					p.move({ 0, -jumpSpeed - gravity });
				}

				// if the hero is still in the air
				if (!collisions) {
					jumpSpeed += gravity;
					p.move({ 0, jumpSpeed });
				}
			}
		}

	//Foreign Collisions
		//Pixel perfect for pixel perfect images
		/*if (p.collisionTest(b.getSprite())) {
			std::cout << "Pixel Perfect!" << delayCounter << std::endl;
		}

		if (p.collision(b.getSprite())) {
			std::cout << "Bounding box!" << delayCounter << " " << curr << " " << collisions << std::endl;
		}*/

		missile.fire();
		if (p.collisionTest(missile)) {
			p.takeDamage(5);
		}

	//Clock
		p.update(cl.getElapsedTime().asMicroseconds());
		//std::cout << cl.getElapsedTime().asMicroseconds() << std::endl;
		cl.restart();

// -- Draw --
		window.clear();

		platform.draw(window);
		//platform1.draw(window);
		//platform2.draw(window);
		missile.draw(window);
		b.draw(window);
		//c.draw(window);
		p.draw(window);

		window.display();
	}

	return 0;
}