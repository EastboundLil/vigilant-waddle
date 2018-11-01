#pragma once
#include "Drawable.h"

#include <vector>

class Block :
	public Drawable
{
public:
	Block(sf::RenderWindow *w);
	Block(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w);
	~Block();
	void draw();
	void set_block_point(size_t i, size_t j, float _x , float _y);
	bool caught_by_expl(sf::Vector2f expl);
protected:
	sf::RenderWindow *window;
	std::vector<sf::ConvexShape*> convex_v;
	float height;
	float width;
	void modify_coords(sf::Vector2f expl, float & newx, float & newy, sf::Vector2f pos, float r);
private:
	void del_point(int i, std::vector<bool> delablepoints);
	void split_shape(size_t i);
	float check_bound(float _x, int p , float old); //most nem használom



};

