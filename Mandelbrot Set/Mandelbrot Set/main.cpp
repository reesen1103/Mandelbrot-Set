#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <complex>
#include <valarray>
#include <cstdlib>
#include <cmath>

#include "ComplexPlane.h"


// read all comments for code notes and necessary fixes, changes etc. //



using namespace std;

int main() {
	VideoMode vm(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2);

// construct renderwindow
RenderWindow window(vm, "Mandelbrot Set", Style::Default);
// construct complex plane
ComplexPlane complexPlane(vm.width, vm.height);

// construct text and font objects
Font font;
if (!font.loadFromFile("neuropolitical rg.otf"))
{
	cout << "Error with font" << endl;
	return EXIT_FAILURE;
}

Text text;
text.setFont(font);
text.setCharacterSize(20);
text.setFillColor(Color::White);
text.setPosition(10.f, 10.f);
text.setString("***insert necessary text***"); // insert any text deemed necessary for project

//begin main loop 
//Handle Input segment
//Poll Windows queue events

//Check if Keyboard::isKeyPressed(Keyboard::Escape) to close the window
while (window.isOpen())
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)//Handle Event::Closed event to close the window
		{
			// Quit the game when the window is closed
			window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed)//Handle Event::MouseButtonPressed
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//Left click will zoomIn and 
				//call setCenter on the ComplexPlane object with the(x, y) pixel 
				//location of the mouse click
				complexPlane.zoomIn(event.mouseButton.x, event.mouseButton.y);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				//Right click will zoomOut and call setCenter on 
				// the ComplexPlane object with the(x, y) pixel location of the mouse click
				complexPlane.zoomOut(event.mouseButton.x, event.mouseButton.y);
			}
			if (event.type == sf::Event::MouseMoved)
			{
				//Handle Event::MouseMoved
				//Call setMouseLocation on the ComplexPlane object to store the(x, y) pixel location
				//  of the mouse click
				//This will be used later to display the mouse coordinates as it moves
				complexPlane.setMouseLocation(event.mouseMove.x, event.mouseMove.y);
			}
			//Check if Keyboard::isKeyPressed(Keyboard::Escape) to close the window
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		
		}
		//Update Scene segment
		//Call updateRender on the ComplexPlane object
		//Call loadText on the ComplexPlane object
		complexPlane.updateRender();
		complexPlane.loadText(text);

		//Draw Scene segment
		//Clear the RenderWindow object
		//draw the ComplexPlane object
		//draw the Text object
		//Display the RenderWindow object
		window.clear();
		window.draw(complexPlane);
		window.draw(text);
		window.display();
	}

	return 0;
}
