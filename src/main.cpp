#include <iostream>
#include <SFML/Graphics.hpp>

struct cube
{
	sf::RectangleShape shape;
	bool isActive;

	cube(sf::Vector2f size, float x, float y)
	{
		shape.setSize(size);
		shape.setFillColor(sf::Color(186, 45, 68));
		isActive = false;
		shape.setOrigin(size / 2.f);
		shape.setPosition(x, y);
	}

	void reset()
	{
		shape.setFillColor(sf::Color(186, 45, 68));
		isActive = false;
	}
};

struct selecter
{
	sf::RectangleShape shape;
	bool selected;
	bool fixed;

	sf::Vector2f start;

	selecter()
	{
		selected = false;
		fixed = false;
		shape.setFillColor(sf::Color(54, 81, 217, 70));
		shape.setOutlineThickness(3.f);
		shape.setOutlineColor(sf::Color(35, 62, 196, 70));
	}

	void reset()
	{
		shape.setSize(sf::Vector2f(0.f, 0.f));
		shape.setPosition(0.f, 0.f);
	}
};

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(800u, 600u), "What");
	window.setFramerateLimit(60);

	cube c1(sf::Vector2f(100.f, 50.f), 100.f, 300.f);
	cube c2(sf::Vector2f(100.f, 50.f), 600.f, 300.f);

	selecter s;

	while (window.isOpen())
	{
		//event handler
		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
				case sf::Event::Closed:
				{
					window.close();
				}break;
				case sf::Event::MouseButtonPressed:
				{
					if (c1.isActive)
						c1.reset();
					if (c2.isActive)
						c2.reset();
				}break;
			}
		}

		//update
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			s.selected = true;
			if (!s.fixed)
			{
				s.start = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
				s.shape.setPosition(s.start);
				s.fixed = true;
			}
			s.shape.setSize(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - s.start);

			if (s.shape.getGlobalBounds().intersects(c1.shape.getGlobalBounds()))
				c1.isActive = true;
			else
				c1.reset();
			if (s.shape.getGlobalBounds().intersects(c2.shape.getGlobalBounds()))
				c2.isActive = true;
			else
				c2.reset();
		}
		else
		{
			s.fixed = false;
			s.selected = false;
		}

		if(c1.isActive)
			c1.shape.setFillColor(sf::Color(107, 9, 25, 150));

		if(c2.isActive)
			c2.shape.setFillColor(sf::Color(107, 9, 25, 150));

		//render
		window.clear(sf::Color::White);

		window.draw(c1.shape);
		window.draw(c2.shape);
		if (s.selected)
			window.draw(s.shape);

		window.display();
	}

	return 0;
}