#pragma once
#include "Drawable.h"
#include "Block.h"

class MinorMap :
	public Drawable
{
	std::vector<std::shared_ptr<Block>> block_v;
	int width, height, numx, numy;
	float max_block_width;
	float max_block_height;
	sf::RenderWindow* window;
public:

	MinorMap();
	MinorMap(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w);
	MinorMap(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w, float mbh, float mbw);

	~MinorMap();

	void explosion_happened(sf::Vector2i pos);
	void draw();
	std::vector<std::string> write_data();
	void write_data_to_file(std::string filename);
	void load_from_file(std::string filename);

	/*testre vár még:*/

	void make_solid(sf::Vector2i pos);
	void make_destructible(sf::Vector2i pos);

};

