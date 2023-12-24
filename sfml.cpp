#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;
using namespace sf;

#define RadToDeg 180 / 3.1415926
#define DegToRad 3.1415926 / 180

double length(Vector2f first, Vector2f second)
{
	return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

void oneLine(RenderWindow& window, RectangleShape& line, RectangleShape object)
{
	line.setPosition(Vector2f(Mouse::getPosition().x - window.getPosition().x, Mouse::getPosition().y - window.getPosition().y));

	line.setSize(Vector2f(length(line.getPosition(), object.getPosition()), 1));

	line.setRotation(RadToDeg * acos(abs(line.getPosition().x - object.getPosition().x) / line.getSize().x));
}

void allLines(RenderWindow& window, RectangleShape& line1, RectangleShape& line2, RectangleShape& line3, RectangleShape& line4, RectangleShape object)
{
	line1.setPosition((Vector2f)Mouse::getPosition(window));
	line2.setPosition((Vector2f)Mouse::getPosition(window));
	line3.setPosition((Vector2f)Mouse::getPosition(window));
	line4.setPosition((Vector2f)Mouse::getPosition(window));

	line1.setSize(Vector2f(length(line1.getPosition(), object.getPosition()), 2));
	line2.setSize(Vector2f(length(line2.getPosition(), Vector2f(object.getPosition().x + object.getSize().x, object.getPosition().y)), 2));
	line3.setSize(Vector2f(length(line3.getPosition(), Vector2f(object.getPosition().x, object.getPosition().y + object.getSize().y)), 2));
	line4.setSize(Vector2f(length(line4.getPosition(), Vector2f(object.getPosition().x + object.getSize().x, object.getPosition().y + object.getSize().y)), 2));

	Vector2f side1 = Vector2f(line1.getPosition().x - object.getPosition().x, line1.getPosition().y - object.getPosition().y);
	Vector2f side2 = Vector2f(line2.getPosition().x - (object.getPosition().x + object.getSize().x), line2.getPosition().y - object.getPosition().y);
	Vector2f side3 = Vector2f(line3.getPosition().x - object.getPosition().x, line3.getPosition().y - (object.getPosition().y + object.getSize().y));
	Vector2f side4 = Vector2f(line4.getPosition().x - (object.getPosition().x + object.getSize().x), line4.getPosition().y - (object.getPosition().y + object.getSize().y));

	double tan1 = side1.y / side1.x;
	double tan2 = side2.y / side2.x;
	double tan3 = side3.y / side3.x;
	double tan4 = side4.y / side4.x;

	double angle1 = RadToDeg * atan(tan1);
	double angle2 = RadToDeg * atan(tan2);
	double angle3 = RadToDeg * atan(tan3);
	double angle4 = RadToDeg * atan(tan4);

	if (line1.getPosition().x >= object.getPosition().x) angle1 += 180;
	if (line2.getPosition().x >= object.getPosition().x + object.getSize().x) angle2 += 180;
	if (line3.getPosition().x >= object.getPosition().x) angle3 += 180;
	if (line4.getPosition().x >= object.getPosition().x + object.getSize().x) angle4 += 180;

	line1.setRotation(angle1);
	line2.setRotation(angle2);
	line3.setRotation(angle3);
	line4.setRotation(angle4);

	/*line1.setSize(Vector2f(line1.getSize().x + window.getSize().x, 2));
	line2.setSize(Vector2f(line2.getSize().x + window.getSize().x, 2));
	line3.setSize(Vector2f(line3.getSize().x + window.getSize().x, 2));
	line4.setSize(Vector2f(line4.getSize().x + window.getSize().x, 2));*/
}

int main()
{
	int winX = 1000, winY = 750;

	RenderWindow window(VideoMode(winX, winY), "My window");
	window.setFramerateLimit(60);

	RectangleShape object(Vector2f(190, 140));
	object.setPosition(Vector2f((winX - object.getSize().x) / 2, (winY - object.getSize().y) / 2));
	object.setFillColor(Color(194, 194, 194));

	Vector2f speed_direction(1, 1);
	double speed_module = 1;

	RectangleShape line1, line2, line3, line4;

	line1.setFillColor(Color::Red);
	line2.setFillColor(Color::Green);
	line3.setFillColor(Color::Blue);
	line4.setFillColor(Color::Yellow);

	Font font;
	Text text;
	bool stats_output = false;

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
				}
			}
		}

		window.clear(sf::Color::Black);


		allLines(window, line1, line2, line3, line4, object);

		window.draw(object);

		window.draw(line1);
		window.draw(line2);
		window.draw(line3);
		window.draw(line4);

		if (stats_output)
		{
			string text_str =
				"mouse:\nx: " + to_string(Mouse::getPosition().x) + "\n" +
				"y: " + to_string(Mouse::getPosition().y) + "\n" +
				"object:\nx: " + to_string(object.getPosition().x) + "\n" +
				"y: " + to_string(object.getPosition().y) + "\n" +
				"speed direction:\nx: " + to_string(speed_direction.x) + "\n" +
				"y: " + to_string(speed_direction.y) + "\n" +
				"speed module: " + to_string(speed_module) + "\n" +
				"object points:\n";

			for (int i = 0; i < object.getPointCount(); i++)
			{
				text_str += to_string(object.getPosition().x + object.getPoint(i).x) + " " + to_string(object.getPosition().y + object.getPoint(i).y) + "\n";
			}

			text.setString(text_str);

			window.draw(text);
		}

		window.display();


		for (int i = 0; i < (int)speed_module; i++)
		{
			object.move(speed_direction);

			if (
				object.getPosition().x <= 0 || object.getPosition().x + object.getSize().x >= winX ||
				object.getPosition().y <= 0 || object.getPosition().y + object.getSize().y >= winY
				)
			{
				if (object.getPosition().x <= 0 || object.getPosition().x + object.getSize().x >= winX) speed_direction.x *= -1;

				if (object.getPosition().y <= 0 || object.getPosition().y + object.getSize().y >= winY) speed_direction.y *= -1;

				speed_module += 0.1;
			}
		}
	}
}
