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
	window.create(sf::VideoMode(500.0f * screenScalingFactor, 500.0f * screenScalingFactor), "SFML works!");
	platform.setIcon(window.getSystemHandle());

	sf::CircleShape shape(window.getSize().x / 2);
	shape.setFillColor(sf::Color::White);

	sf::Texture shapeTexture;
	//if (!shapeTexture.loadFromFile("content/sfml.png"))
	//if (!shapeTexture.loadFromFile("content/star-wars-backgrounds-25.jpg"))
	if (!shapeTexture.loadFromFile("content/DarkSkull.jpg"))
		return EXIT_FAILURE;
	shape.setTexture(&shapeTexture);

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

			// key pressed
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					// move left...
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					// move right...
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					// quit...
				}

				break;

			// Mouse button pressed
			case sf::Event::MouseButtonPressed:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					// left mouse button is pressed: shoot
					//gun.fire();

#if defined(_DEBUG)
					// get window mouse position
					sf::Vector2i position = sf::Mouse::getPosition(window);
					cout << "Mouse position: (" << position.x << ", " << position.y << ")" << endl;
#endif
				}
				break;

			// we don't process other types of events
			default:
				break;
			} // end switch (event.type)
		}	  //while (window.pollEvent(event))

		// Clear screen
		window.clear();

		// Draw the shape
		window.draw(shape);

		// Update the window
		window.display();

	} // End the game loop

#if defined(_DEBUG)
	sf::Time elapsed = clock.getElapsedTime();
	cout << "Elapsed time (in seconds): " << elapsed.asSeconds() << endl;
#endif

	return EXIT_SUCCESS;
}
