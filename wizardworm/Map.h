#pragma once
#include "Drawable.h"
#include "Block.h"
#include <vector>

class Map :
	public Drawable
{
	std::vector<std::unique_ptr<Block>> block_v;
	int width, height,numx,numy;
	float max_block_width;
	float max_block_height;
	sf::RenderWindow* window;
public:

	Map();
	Map(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w);
	Map(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w , float mbh , float mbw);

	~Map();

	void explosion_happened(sf::Vector2i pos);
	void draw();
};

