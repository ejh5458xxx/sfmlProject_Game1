#include "Platform/Platform.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Includes/myRectangle.h"
#include <iostream>

using namespace std;

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	cout << "Hello World!" << endl;

	myRectangle rect;
	rect.set_values(3, 4);
	int curArea = rect.area();
	cout << "area: " << curArea << endl
		 << endl;
#endif

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());

	// Use the screenScalingFactor
	window.create(sf::VideoMode(700.0f * screenScalingFactor,
								700.0f * screenScalingFactor),
				  "SFML Tutorial");
	platform.setIcon(window.getSystemHandle());

	sf::CircleShape shape(window.getSize().x / 2);
	shape.setFillColor(sf::Color::White);

	sf::RectangleShape player(sf::Vector2f(100.0f, 150.0f));
	//player.setFillColor(sf::Color::Green);
	player.setOrigin(50.0f, 75.0f);
	player.setPosition(100.0f, 100.0f);

	sf::Texture shapeTexture;
	//if (!myTexture.loadFromFile("content/sfml.png"))
	//if (!myTexture.loadFromFile("content/star-wars-backgrounds-25.jpg"))
	if (!shapeTexture.loadFromFile("content/DarkSkull.jpg"))
		return EXIT_FAILURE;
	shape.setTexture(&shapeTexture);

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("content/2000px-TUX_G2.svg.png"))
		return EXIT_FAILURE;
	player.setTexture(&playerTexture);

	/*
	sf::Vector2u playerTextureSize = playerTexture.getSize();
	cout << "playerTextureSize, width = " << playerTextureSize.x
		 << ", height = " << playerTextureSize.y << endl;
	player.setTextureRect(sf::IntRect(playerTextureSize.x, playerTextureSize.y,
									  playerTextureSize.x, playerTextureSize.y));
									  */

	sf::Event event;
	sf::Clock clock; // Starts the clock

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		while (window.pollEvent(event))
		{

			// check the type of the event...
			switch (event.type)
			{
			// Close window: exit
			case sf::Event::Closed:
				window.close();
				break;

			// Window is resized
			case sf::Event::Resized:
#if defined(_DEBUG)
				cout << "new width: " << event.size.width << endl;
				cout << "new height: " << event.size.height << endl;
#endif
				break;

			// Capturing user text input
			case sf::Event::TextEntered:
#if defined(_DEBUG)
				if (event.text.unicode < 128)
					cout << "Inside TextEntered, ASCII character typed: "
						 << static_cast<char>(event.text.unicode) << endl;
#endif

				break; // case sf::Event::TextEntered:

			// key pressed
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					// move left...
					player.move(-1.0f, 0.0f);
#if defined(_DEBUG)
					cout << "Left keyboard button hit" << endl;
#endif
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					// move right...
					player.move(1.0f, 0.0f);
#if defined(_DEBUG)
					cout << "Right keyboard button hit" << endl;
#endif
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					// move up...
					player.move(0.0f, -1.0f);
#if defined(_DEBUG)
					cout << "Up keyboard button hit" << endl;
#endif
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					// move up...
					player.move(0.0f, 1.0f);
#if defined(_DEBUG)
					cout << "Up keyboard button hit" << endl;
#endif
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					// quit...
#if defined(_DEBUG)
					cout << "Escape keyboard button hit" << endl;
#endif
				}

				break; // case sf::Event::KeyPressed:

			// Mouse button pressed
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					// shoot
					//gun.fire();
					sf::Vector2i position = sf::Mouse::getPosition(window);
					player.setPosition(static_cast<float>(position.x),
									   static_cast<float>(position.y));
#if defined(_DEBUG)
					// get window mouse position
					cout << "Mouse position: (" << position.x << ", "
						 << position.y << ")" << endl;
#endif
				}
				break; // case sf::Event::MouseButtonPressed:

			// we don't process other types of events
			default:
				break;
			} // end switch (event.type)
		}	  //while (window.pollEvent(event))

		// Clear screen
		window.clear();

		// Draw the objects
		window.draw(shape);
		window.draw(player);

		// Update the window
		window.display();

	} // End the game loop

#if defined(_DEBUG)
	sf::Time elapsed = clock.getElapsedTime();
	cout << "Elapsed time (in seconds): " << elapsed.asSeconds() << endl;
#endif

	return EXIT_SUCCESS;
}
