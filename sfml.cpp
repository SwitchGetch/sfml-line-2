#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <thread>
#include <chrono>
using namespace std;
using namespace sf;
using namespace chrono;

double length(Vector2f first, Vector2f second)
{
	return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}

void oneLine(RenderWindow& window, RectangleShape& line, RectangleShape object)
{
	line.setPosition(Vector2f(Mouse::getPosition().x - window.getPosition().x, Mouse::getPosition().y - window.getPosition().y));

	line.setSize(Vector2f(length(line.getPosition(), object.getPosition()), 1));

	line.setRotation((180 / 3.1415926) * acos(abs(line.getPosition().x - object.getPosition().x) / line.getSize().x));
}

void allLines(RenderWindow& window, RectangleShape& line1, RectangleShape& line2, RectangleShape& line3, RectangleShape& line4, RectangleShape object)
{
	line1.setPosition(Vector2f(Mouse::getPosition().x - window.getPosition().x - 7, Mouse::getPosition().y - window.getPosition().y - 30));
	line2.setPosition(Vector2f(Mouse::getPosition().x - window.getPosition().x - 7, Mouse::getPosition().y - window.getPosition().y - 30));
	line3.setPosition(Vector2f(Mouse::getPosition().x - window.getPosition().x - 7, Mouse::getPosition().y - window.getPosition().y - 30));
	line4.setPosition(Vector2f(Mouse::getPosition().x - window.getPosition().x - 7, Mouse::getPosition().y - window.getPosition().y - 30));

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

	double angle1 = (180 / 3.1415926) * atan(tan1);
	double angle2 = (180 / 3.1415926) * atan(tan2);
	double angle3 = (180 / 3.1415926) * atan(tan3);
	double angle4 = (180 / 3.1415926) * atan(tan4);

	if (line1.getPosition().x >= object.getPosition().x) angle1 += 180;
	if (line2.getPosition().x >= object.getPosition().x + object.getSize().x) angle2 += 180;
	if (line3.getPosition().x >= object.getPosition().x) angle3 += 180;
	if (line4.getPosition().x >= object.getPosition().x + object.getSize().x) angle4 += 180;

	line1.setRotation(angle1);
	line2.setRotation(angle2);
	line3.setRotation(angle3);
	line4.setRotation(angle4);

	line1.setSize(Vector2f(line1.getSize().x + window.getSize().x, 1));
	line2.setSize(Vector2f(line2.getSize().x + window.getSize().x, 1));
	line3.setSize(Vector2f(line3.getSize().x + window.getSize().x, 1));
	line4.setSize(Vector2f(line4.getSize().x + window.getSize().x, 1));
}

int main()
{
	int winX = 800, winY = 600;

	RenderWindow window(VideoMode(winX, winY), "My window");
	window.setFramerateLimit(60);

	RectangleShape object(Vector2f(100, 100));
	object.setPosition(Vector2f((winX - object.getSize().x) / 2, (winY - object.getSize().y) / 2));
	object.setFillColor(Color::White);

	RectangleShape line1, line2, line3, line4;

	line1.setFillColor(Color::Red);
	line2.setFillColor(Color::Green);
	line3.setFillColor(Color::Blue);
	line4.setFillColor(Color::Yellow);

	Font font;
	Text text;

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
		}

		window.clear(sf::Color::Black);

		string text_str =
			"x: " + to_string(Mouse::getPosition().x) + "\n" +
			"y: " + to_string(Mouse::getPosition().y) + "\n";

		allLines(window, line1, line2, line3, line4, object);

		text.setString(text_str);

		window.draw(object);

		window.draw(line1);
		window.draw(line2);
		window.draw(line3);
		window.draw(line4);

		window.draw(text);

		window.display();
	}
}