#pragma once
#include "Drawable.h"
#include <functional>

class Button :
	public Drawable
{
protected:
	sf::Text text;
	
	sf::Font font;
	std::string t;
	std::function<bool()> action;
	float width, height;
	sf::RenderWindow* window;
	sf::RectangleShape rect;
	sf::CircleShape circle;
	
public:
	Button(float posx ,  float posy , float width , float height ,  sf::Color color , std::string text ,sf::RenderWindow *w, std::function<bool()> action = []()->bool {});
	
	bool inside(sf::Vector2i click);
	void make_action();
	virtual void set_action(std::function<bool()> a);
	
	

	~Button();
	void draw();


	
};

