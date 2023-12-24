#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <random>
#include <thread>
using namespace std;
using namespace sf;

#define RadToDeg 180 / 3.1415926
#define DegToRad 3.1415926 / 180

double length(Vector2f first, Vector2f second)
{
	return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

template<typename ShapeType>
void oneLine(RenderWindow& window, RectangleShape& line, ShapeType object, Vector2f point)
{
	//line.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));

	/*if (line.getFillColor() == Color::White)
	{
		switch (rand() % 4)
		{
		case 0: line.setFillColor(Color::Red); break;
		case 1: line.setFillColor(Color::Green); break;
		case 2: line.setFillColor(Color::Blue); break;
		case 3: line.setFillColor(Color::Yellow); break;
		}
	}*/

	line.setPosition((Vector2f)Mouse::getPosition(window));

	line.setSize(Vector2f(length(line.getPosition(), object.getPosition() + point), 1));

	double tan = (line.getPosition().y - (object.getPosition().y + point.y)) / (line.getPosition().x - (object.getPosition().x + point.x));

	double angle = RadToDeg * atan(tan);

	if (line.getPosition().x >= object.getPosition().x + point.x) angle += 180;

	line.setRotation(angle);

	line.setSize(Vector2f(length(line.getPosition(), object.getPosition() + point) + max(window.getSize().x, window.getSize().y), 1));
}

int main()
{
	srand(time(NULL));

	int winX = 1000, winY = 750;

	RenderWindow window(VideoMode(winX, winY), "My window");
	window.setFramerateLimit(60);

	/*RectangleShape object(Vector2f(190, 140));
	object.setPosition(Vector2f((winX - object.getSize().x) / 2, (winY - object.getSize().y) / 2));
	object.setFillColor(Color::White);*/

	CircleShape object(110);
	object.setPosition(Vector2f((winX - object.getRadius()) / 2, (winY - object.getRadius()) / 2));
	object.setFillColor(Color::White);
	object.setPointCount(1000);

	double angle = 45 * DegToRad;
	Vector2f speed(cos(angle), sin(angle));

	/*RectangleShape line1, line2, line3, line4;

	line1.setFillColor(Color::Red);
	line2.setFillColor(Color::Green);
	line3.setFillColor(Color::Blue);
	line4.setFillColor(Color::Yellow);*/

	vector<RectangleShape> lines(object.getPointCount());

	Font font;
	Text text;

	bool stats_output = false;
	bool free_mouse = false;

	font.loadFromFile("arial.ttf");

	text.setFont(font);
	text.setFillColor(Color::White);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::KeyPressed)
			{
				switch (event.key.scancode)
				{
				case Keyboard::Scancode::D:

					stats_output = (stats_output ? false : true);

					break;

				case Keyboard::Scancode::F:

					free_mouse = (free_mouse ? false : true);

					break;
				}
			}
		}

		if (!free_mouse) Mouse::setPosition(Vector2i(object.getPosition().x + object.getRadius(), object.getPosition().y + object.getRadius()), window);

		window.clear(sf::Color::Black);

		window.draw(object);

		for (int i = 0; i < object.getPointCount(); i++)
		{
			oneLine(window, lines[i], object, object.getPoint(i));

			window.draw(lines[i]);
		}

		if (stats_output)
		{
			string text_str =
				"mouse:\nx: " + to_string(Mouse::getPosition().x) + "\n" +
				"y: " + to_string(Mouse::getPosition().y) + "\n" +
				"object:\nx: " + to_string(object.getPosition().x) + "\n" +
				"y: " + to_string(object.getPosition().y) + "\n" +
				"speed:\nx: " + to_string(speed.x) + "\n" +
				"y: " + to_string(speed.y);

			text.setString(text_str);

			window.draw(text);
		}

		window.display();


		object.move(speed);

		if (object.getPosition().x <= 0 || object.getPosition().x + 2 * object.getRadius() >= winX) speed.x *= -1;

		if (object.getPosition().y <= 0 || object.getPosition().y + 2 * object.getRadius() >= winY) speed.y *= -1;
	}
}
