#pragma once
#include "Button.h"
class ChangeButton :
	public Button
{
	void change(bool t);
	
	std::string t2;
	sf::Color c2;
	bool chooser = true;
public:
	ChangeButton(float posx, float posy, float width, float height, sf::Color color, sf::Color c2, std::string t1, std::string t2, sf::RenderWindow *w, std::function<bool()> action);
	~ChangeButton();
	void make_action();

	void draw();

		
	
};

