#ifndef STATE_H
#define STATE_H
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

enum class State(CALCULATING, DISPLAYING)
{
public:
	ComplexPlane(int pixelWidth, int pixelHeight);
	void draw(RenderTarget & target, RenderStates states);
	void updateRender();
	void zoomIn();
	void zoomOut();
	void setCenter(Vector2i mousePixel);
	void loadText(Text& text);
	int size_t countIterations(Vector2f coord);
	void iterationsToRGB(size_t cont, Uint8& r, Uint8& g, Uint8& b);
	Vector2f mapPixelToCoord(Vector2i mousePixel);

private:

	VertexArray m_pixel_size;
	State m_state;
	Vector2f m_mouseLocation;
	Vector2i m_pixel_size;
	Vector2f m_plane_center;
	Vector2f m_plane_size;
	int m_zoomCount;
	float m_aspectRatio;




};
#endif
