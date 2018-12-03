#pragma once
#include "Drawable.h"


class Arrow : public Drawable
{

	float deg, force;  
	static float minf, maxf , mind , maxd;
	bool opened;
	sf::RenderWindow *window;
	sf::RectangleShape rect;
	std::string type;

	sf::Texture texture;
	sf::Sprite sprite;

public:
	Arrow();
	Arrow(float _x, float _y , sf::RenderWindow *w, std::string type);
	~Arrow();
	void draw();
	bool is_opened();
	void set_opened(bool t);
	void incr_deg(float a);
	void incr_force(float a);
	std::string get_type();
	float get_deg();
	float get_force();
};

