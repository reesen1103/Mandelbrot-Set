#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <complex>
#include <valarray>
#include <cstdlib>
#include <cmath>

#include "ComplexPlane.h";

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_aspectRatio = (pixelWidth) / pixelHeight;
	m_plane_center = {0,0};
	m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
	m_zoomCount = 0;
	m_State = State::CALCULATING;
	VertexArray = Points; // Resize it to pixelWidth* pixelHeight??
	return 0;
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states)
{
	target.draw(m_vArray);
	return 0;
}

void ComplexPlane::updateRender()
{
	return 0;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	int x = BASE_WIDTH * (pow(BASE_ZOOM, m_ZoomCount));
	int y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_ZoomCount));

	return 0;
}

void ComplexPlane::zoomOut()
{
	return 0;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
	return 0;
}

void ComplexPlane::loadText(Text& text)
{
	return 0;
}

int size_t ComplexPlane::countIterations(Vector2f coord)
{
	return 0;
}


void iterationsToRGB(size_t cont, Uint8& r, Uint8& g, Uint8& b)
{
	return 0;
}

Vector2f mapPixelToCoord(Vector2i mousePixel)
{
	return 0;
}
