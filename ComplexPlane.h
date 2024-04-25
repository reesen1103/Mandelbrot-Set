#pragma once
#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <complex>
#include <valarray>
#include <cstdlib>
#include <cmath>

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

enum class State { CALCULATING, DISPLAYING };

class ComplexPlane : public Drawable 
{
public:
	ComplexPlane(int pixelWidth, int pixelHeight);
	void draw(RenderTarget& target, RenderStates states) const override;
	void updateRender();
	void zoomIn(int x, int y);
	void zoomOut(int x, int y);
	void setMouseLocation(int x, int y);
	void setCenter(Vector2i mousePixel);
	void loadText(Text& text);
	int countIterations(Vector2f coord);
	void iterationsToRGB(int cont, Uint8& r, Uint8& g, Uint8& b);
	Vector2f mapPixelToCoord(Vector2i mousePixel);

private:

	VertexArray m_pixelArray;
	State m_state;
	Vector2f m_mouseLocation;
	Vector2i m_pixelSize;
	Vector2f m_planeCenter;
	Vector2f m_planeSize;
	int m_zoomCount;
	float m_aspectRatio;
};
#endif
