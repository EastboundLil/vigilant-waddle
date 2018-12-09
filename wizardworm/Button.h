#pragma once
#include "Drawable.h"
#include <functional>

class Button :
	public Drawable
{

	sf::Text text;
	std::function<void()> action;
	float width, height;
	sf::RenderWindow* window;
	sf::RectangleShape rect;
public:
	Button(float posx ,  float posy , float width , float height ,  sf::Color color , std::string text ,sf::RenderWindow *w, std::function<void()> action = []() {});
	
	bool inside(sf::Vector2i click);
	
	virtual void set_action(std::function<void()> a);
	void make_action();

	~Button();
	void draw();
};

