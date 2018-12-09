#pragma once
#include "Drawable.h"
#include <functional>

class Button :
	public Drawable
{

	sf::Text text;
	sf::Font font;
	std::function<bool()> action;
	float width, height;
	sf::RenderWindow* window;
	sf::RectangleShape rect;
	sf::CircleShape circle;
	bool shapechooser=true;
public:
	Button(float posx ,  float posy , float width , float height ,  sf::Color color , std::string text ,sf::RenderWindow *w, std::function<bool()> action = []()->bool {});
	
	bool inside(sf::Vector2i click);
	
	virtual void set_action(std::function<bool()> a);
	void make_action();
	void change_shape(bool t);

	~Button();
	void draw();
};

