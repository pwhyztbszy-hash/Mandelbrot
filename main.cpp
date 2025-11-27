#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComplexPlane.h"

using namespace sf;
using namespace std;


int main()

{
	int pixelWidth = VideoMode::getDesktopMode().width;
	int pixelHeight = VideoMode::getDesktopMode().height;

	VideoMode vm(pixelWidth, pixelHeight);

	RenderWindow window(vm, "Rainbow Screen", Style::Default);
	ComplexPlane cPlane(1920, 1080);

	//Construct the Font and Text objects
	Font font;
    if (!font.loadFromFile("fonts/Roboto-Italic.ttf"))
    {
        cout << "ERROR: Could not load fonts/Roboto-Italic.ttf" << endl;
        return 1;
    }

    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setPosition(10, 10);


	while (window.isOpen())

	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Right)
				{
					cPlane.zoomOut();
					cPlane.setCenter(Vector2i(float(event.mouseButton.x), float(event.mouseButton.y)));
					cout << "pixel (" << event.mouseButton.x << "," << event.mouseButton.y << ")" << endl;

				}
				if (event.mouseButton.button == Mouse::Left)
				{
					cPlane.zoomIn();
					cPlane.setCenter(Vector2i(float(event.mouseButton.x), float(event.mouseButton.y)));
					cout << "pixel (" << event.mouseButton.x << "," << event.mouseButton.y << ")" << endl;
				}
			}

			if (event.type == Event::MouseMoved)
			{
				cPlane.setMouseLocation(Vector2i(float(event.mouseButton.x), float(event.mouseButton.y)));
			}
		}

		///Input

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		///Update
		cPlane.updateRender();
		cPlane.loadText(text);


		///Draw

		window.clear();
		window.draw(cPlane);

		window.draw(text);

		window.display();
	}
}
