#include <SFML/Graphics.hpp>


class Drawable
{
protected:
	float x;
	float y;
	sf::Color color;
public:
	Drawable();
	Drawable(float x_, float y_, sf::Color color_);
	Drawable(float x_, float y_);
	~Drawable();

	void set_pos(float x_, float y_);
	void incr_pos(float x_, float y_);
	void set_x(float x_);
	void set_y(float y_);
	float get_x();
	float get_y();
	void incr_x(float x_);
	void incr_y(float y_);

	void set_color(sf::Color c);
	sf::Color  get_color();
	

	virtual void draw() = 0;

};

