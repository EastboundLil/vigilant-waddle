#include <SFML/Graphics.hpp>


class Drawable
{
protected:
	int x;
	int y;
	sf::Color color;
public:
	Drawable(int x_, int y_, sf::Color color_);
	Drawable(int x_, int y_);
	~Drawable();

	void set_pos(int x_, int y_);
	void incr_pos(int x_, int y_);
	void set_x(int x_);
	void set_y(int y_);
	int get_x();
	int get_y();
	void incr_x(int x_);
	void incr_y(int y_);

	void set_color(sf::Color c);
	sf::Color  get_color();
	

	virtual void draw();

};

