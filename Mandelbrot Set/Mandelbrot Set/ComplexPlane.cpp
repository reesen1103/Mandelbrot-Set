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

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixelSize = { pixelWidth, pixelHeight }; // asssign pixel size with parameter values
	m_aspectRatio = static_cast<float> (pixelHeight) / pixelWidth; // calculate aspect ratio. static cast as float to avoid int divide problems
	m_planeCenter = { 0,0 }; // assign plane center with 0,0
	m_planeSize = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio }; // assign plane size
	m_zoomCount = 0; // assign zoom count with 0
	m_state = State::CALCULATING; // assign m_state with State::CALCULATING
	m_pixelArray.setPrimitiveType(sf::Points); // initialize vertex array, set primitive type to Points
	m_pixelArray.resize(pixelWidth * pixelHeight); //resize to pizelWidth * pixelHeight
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_pixelArray); //draw pixel array
}


void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING) //if m state is calculating
	{
		for (int i = 0; i < m_pixelSize.y; i++) // create double for loop to loop through all the pixels on the screen
		{
			for (int j = 0; j < m_pixelSize.x; j++)
			{
				m_pixelArray[j + i * m_pixelSize.x].position = { static_cast<float>(j), static_cast<float>(i) }; // set position variable in the element of vertex array to screen coordinate j,i

				Vector2f coord = mapPixelToCoord(Vector2i(j, i)); // map pixel coords to plane

				int iterations = countIterations(coord); //call countiterations and store number of iterations

				Uint8 r, g, b; //declare 3 Uint8 variables to store the RGB values for current pixel

				iterationsToRGB(iterations, r, g, b); //map iterations to RGB color

				m_pixelArray[j + i * m_pixelSize.x].color = { r, g, b }; // update pixel color to screen coordinates
			}
		}
		m_state = State::DISPLAYING; //set state to displaying after setting the pixel colors
	}
}

void ComplexPlane::zoomIn(int x, int y) // all the code here was fine for the most part, just a couple of misnamed variables.
{
	m_zoomCount++; //increment m_zoomCount
	float newWidth = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount); // local variable for the x size
	float newHeight = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount); //local variable for the y size
	m_planeSize = { newWidth, newHeight }; // assign new size
	//m_planeCenter = mapPixelToCoord(Vector2i(x, y)); //update center location
	m_state = State::CALCULATING; // set state to calculating
}

void ComplexPlane::zoomOut(int x, int y) // same thing here
{
	m_zoomCount--;
	float newWidth = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float newHeight = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_planeSize = { newWidth, newHeight };
	//m_planeCenter = mapPixelToCoord(Vector2i(x, y));
	m_state = State::CALCULATING;

}

void ComplexPlane::setCenter(Vector2i mousePixel) 
{
	Vector2f coord = mapPixelToCoord(mousePixel); // find vector 2f coor in complex plane corresponding to screen location
	m_planeCenter = coord; // assign plane center with this coord
	m_state = State::CALCULATING; // assign m state to calculating
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	Vector2f coord = mapPixelToCoord(mousePixel); // find vector 2f coord in complex plane corresponding to screen location
	m_mouseLocation = coord; // assign mouse location with this coordinate
}

//creates the output which shows coordinates
//and instructions to the game
void ComplexPlane::loadText(Text& text) // replaced '<<' and endl with '\n' inside of setString functions. we want to display these to the user, not output to the terminal
{
	stringstream ss; //use string stream to piece together text
	ss << "Mandelbrot Set \n";
	ss << "Center: (" << m_planeCenter.x << ", " << m_planeCenter.y << ")\n";
	ss << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n";
	ss << "Left-click to Zoom in\n";
	ss << "Right-click to Zoom out\n";

	text.setString(ss.str()); //set string contents to the contents of the string stream
}


//will count the number of iterations of the set for the given coordinate 
size_t ComplexPlane::countIterations(Vector2f coord) const
{
	complex<float> z(0, 0); //complex variables for z and c
	complex<float> c(coord.x, coord.y);

	size_t maxIterations = MAX_ITER;
	for (size_t i = 0; i < maxIterations; i++)
	{
		z = z * z + c;
		if (abs(z) > 2.0) //adjust the threshold if needed
		{
			// Return the number of iterations
			return i;
		}
	}
	return maxIterations; //if threshold wasnt exceeded
}


void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) const
{
	if (count >= MAX_ITER) 
	{
		r = g = b = 0; //color pixel black at max iter
	}
	float normalized = static_cast<float>(count) / MAX_ITER; //normalize count to 0-1
	float hue;

	if (normalized < 0.2f) { // Purple / blue for low iteration counts. just did 240 divided by  5
		hue = normalized * 240.0f; //in hsl
		r = 89;
		g = 0;
		b = 255;
	}
	else if (normalized < 0.4f) { // Turquoise
		hue = normalized * 120.0f + 48.0f; //in hsl
		r = 0;
		g = 255;
		b = 162;
	}
	else if (normalized < 0.6f) { // Green
		hue = normalized * 60.0f + 96.0f; //in hsl
		r = 0;
		g = 255;
		b = 64;
	}
	else if (normalized < 0.8f) { // Yellow
		hue = normalized * 60.0f + 144.0f; //in hsl
		r = 247;
		g = 255;
		b = 0;
	}
	else { // Red for high iteration counts
		hue = normalized * 60.0f + 192.0f; //in hsl
		r = 255;
		g = 0;
		b = 0;
	}
}

Vector2f ComplexPlane::mapPixelToCoord(Vector2i mousePixel) const
{
	float pixelRangeX = m_pixelSize.x;
	float pixelRangeY = m_pixelSize.y; // get range of pixel coordinates on screen

	float planeRangeX = m_planeCenter.x + m_planeSize.x / 2.0; //calculate range of complex plane coordinates
	float planeRangeY = m_planeCenter.y + m_planeSize.y / 2.0;

	float normalizedX = static_cast<float>(mousePixel.x) / pixelRangeX; //normalize pixel coords
	float normalizedY = static_cast<float>(mousePixel.y) / pixelRangeY;

	
	float coordX = m_planeCenter.x - m_planeSize.x / 2.0 + normalizedX * m_planeSize.x; // map coordidnates to complex plane coordinates
	float coordY = m_planeCenter.y - m_planeSize.y / 2.0 + normalizedY * m_planeSize.y;

	return Vector2f(coordX, coordY);
}
