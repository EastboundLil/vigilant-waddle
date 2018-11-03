#pragma once
#include "Drawable.h"


class Arrow : public Drawable
{

	float deg, force;  
	static float minf, maxf , mind , maxd;
	bool opened;
	sf::RenderWindow *window;
	sf::RectangleShape rect;
	
public:
	Arrow();
	Arrow(float _x, float _y , sf::RenderWindow *w);
	~Arrow();
	void draw();
	bool is_opened();
	void set_opened(bool t);
	void incr_deg(float a);
	void incr_force(float a);

};

