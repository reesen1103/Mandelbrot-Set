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

using namespace std;
using namespace sf;

ComlexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size(pixelWidth, pixelHeight);
	m_aspectRatio = (pixelWidth) / pixelHeight;
	m_planeCenter = { 0,0 };
	m_planeSize = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	//VertexArray = Points; // Resize it to pixelWidth* pixelHeight??
	m_pixelArray.resize(pixelWidth * pixelHeight);
}

//doesn't this only need only one line of code??
//only commmented the code it was writ
void ComplexPlane::draw(RenderTarget& target, RenderStates states) 
{
	/*if (m_state == State::CALCULATING)
	{
		for (int i = 0; i < m_pixelArray.getVertexCount(); i++)
		{
			float x = m_pixelArray[i].position.x; // get pixel coordinates
			float y = m_pixelArray[i].position.y;

			Vector2f coord = mapPixelToCoord(Vector2i(x, y)); // map pixel coords to plane

			int iterations = countIterations(coord);
			Uint8 r, g, b;
			iterationsToRGB(iterations, r, g, b); //map iterations to RGB color

			m_pixelArray[i].color = Color(r, g, b); // update pixel color
		}
		m_state = State::DISPLAYING; //set state to displaying after setting the pixel colors
	}*/
	target.draw(m_pixelArray, states); //draw pixel array
}

void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		for (int i = 0; i < m_pixelArray.getVertexCount(); i++)
		{
			float x = m_pixelArray[i].position.x; // get pixel coordinates
			float y = m_pixelArray[i].position.y;

			Vector2f coord = mapPixelToCoord(Vector2i(x, y)); // map pixel coords to plane

			int iterations = countIterations(coord);
			Uint8 r, g, b;
			iterationsToRGB(iterations, r, g, b); //map iterations to RGB color

			m_pixelArray[i].color = Color(r, g, b); // update pixel color
		}
		m_state = State::DISPLAYING; //set state to displaying after setting the pixel colors
	}
}

void ComplexPlane::zoomIn() // all the code here was fine for the most part, just a couple of misnamed variables.
{
	m_zoomCount++;
	float newWidth = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float newHeight = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_planeSize = { newWidth, newHeight };
	m_state = State::CALCULATING;
}

void ComplexPlane::zoomOut() // same thing here
{
	m_zoomCount--;
	float newWidth = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float newHeight = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_planeSize = { newWidth, newHeight };
	m_state = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel) // same here, just needed to assign m_mouseLocation and m_state variables
{
	m_mouseLocation = ComplexPlane::mapPixelToCoord(mousePixel);
	m_state = State::CALCULATING;
}

//creates the output which shows coordinates
//and instructions to the game
void ComplexPlane::loadText(Text& text) // replaced '<<' and endl with '\n' inside of setString functions. we want to display these to the user, not output to the terminal
{
	text.setString("Mandelbrot Set\n");
	text.setString("Center: (" + std::to_string(m_planeCenter.x) + ", " + std::to_string(m_planeCenter.y) + ")\n");
	text.setString("Cursor: (" + std::to_string(m_mouseLocation.x) + ", " + std::to_string(m_mouseLocation.y) + ")\n");
	text.setString("Left-click to Zoom in\n");
	text.setString("Right-click to Zoom out\n");
}


//will count the number of iterations of the set for the given coordinate 
int ComplexPlane::countIterations(Vector2f coord)
{
	if (m_state == State::CALCULATING)
	{
		for (int i = 0; i < m_pixelArray.getVertexCount(); i++)
		{
			float x = m_pixelArray[i].position.x; // get pixel coordinates
			float y = m_pixelArray[i].position.y;

			Vector2f coord = mapPixelToCoord(Vector2i(x, y)); // map pixel coords to plane

			int counter = countIterations(coord);
		}
		return counter; //return counter
	}
}


void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	int mapping = MAX_ITER / 5;
	int x = count / region;
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
		return;
	}
	else
	{
		switch (x)
		{
		case 0:
			r = 128;
			g = 0;
			b = 128 + (count % region) * (127 / region);
			break;
		case 1:
			r = 0;
			g = 0;
			b = 128 + (count % region) * (127 / region);
			break;
		case 2:
			r = 0;
			g = 128 + (count % region) * (127 / region);
			b = 0;
			break;
		case 3:
			r = 255 - (count % region) * (127 / region);
			g = 0;
			b = 255 - (count % region) * (127 / region);
			break;
		default:
			r = 255;
			g = 0;
			b = 0;
			break;

		}
	}
}

Vector2f mapPixelToCoord(Vector2i mousePixel)
{
	//see instructions
}
void ComplexPlane::setMouseLocation(int x, int y)
{
	m_mouseLocation.x = x;
	m_mouseLocation.y = y;
}
