#include <cmath>
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = Vector2i(pixelWidth, pixelHeight); //UNSURE
	
	m_aspectRatio = pixelHeight / (pixelWidth * 1.0);
	
	m_plane_center = { 0, 0 };
	
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	
	m_zoomCount = 0;
	
	m_state = State::CALCULATING;

	m_vArray.resize(pixelWidth * pixelHeight);
	m_vArray.setPrimitiveType(Points);
	
	/*Initialize VertexArray
We will use this to draw a color for each pixel
Set its primitive type to Points
Resize it to pixelWidth* pixelHeight*/
	
	
} 


void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = Vector2f(x, y);
	m_state = CALCULATING;
}


void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = Vector2f(x, y);
	m_state = CALCULATING;
}


void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = CALCULATING;
}


void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);
}


void ComplexPlane::loadText(Text& text)
{

}


void ComplexPlane::updateRender()
{
	int pixelWidth = m_pixel_size.x;
	int pixelHeight = m_pixel_size.y;
	Vector2f coord;
	int iterations;

	if (m_state == CALCULATING)
	{
		for (int i = 0; i < pixelHeight; i++)
		{
			for (int j = 0; j < pixelWidth; j++)
			{
				m_vArray[j + i * pixelWidth].position = { float(j), float(i) };
				coord = mapPixelToCoords(Vector2i(j, i));
				iterations = countIterations(coord);

				Uint8 r, g, b;
				iterationsToRGB(iterations, r, g, b);
				m_vArray[j + i * pixelWidth].color = { r,g,b };

			}
		}

		m_state = DISPLAYING;
	}
}


int ComplexPlane::countIterations(Vector2f coord)
{
	
	complex<double> z = c;
	int i = 0;
	//while(abs(z) < 2.0 && i < 64)
	while (z * z < 4.0 && i < 64) //z*z executes faster because abs(z) uses sqrt
	{
		c =  coord.x + coord.y;
		z = z * z + c;
		//cout << "z_" << i << "= " << z << endl;
		//cout << "|z| = " << abs(c) << endl;
		i++;
	}

	return i;
}


void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count == MAX_ITER) { rgbVal = { 0, 0, 0 }; }
	else if (count == 0) { rgbVal = { 255, 0, 0 }; }
	else { rgbVal = { (255.0 / count) 0, 0 }; }
}


Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	float coordX = ((mousePixel.x - 0.0) / (1920.0 - 0.0))* m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0);
	float coordY = ((mousePixel.y - 1080.0) / (0 - 1080.0)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0);

	return Vector2f(coordX, coordY);
}
