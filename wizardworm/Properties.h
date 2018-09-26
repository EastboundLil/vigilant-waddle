#pragma once
#include <SFML/Graphics.hpp>



struct pos {
private:
	int x;
	int y;
public:
	void set_x(int x_) { x = x_; };
	void set_y(int y_) { y = y_; };
	int get_x() { return x; };
	int get_y() { return y; };
	void incr_x(int x_) { x += x_; };
	void incr_y(int y_) { y += y_; };


};


class Properties
{
	pos position;
	int value;
	sf::RenderWindow* window;
public:
	Properties();

	Properties(sf::RenderWindow* window);
	~Properties();

	void set_position(int x, int y);
	void move(int x, int y);
	pos get_position();

	void set_value(int val);
	int get_value();

	void draw(sf::Color color);


};

