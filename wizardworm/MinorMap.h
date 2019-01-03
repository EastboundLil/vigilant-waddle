#pragma once
#include "Drawable.h"
#include "Block.h"
#include "Wizard.h"

class MinorMap :
	public Drawable
{
	std::vector<std::shared_ptr<Block>> block_v;
	int width, height, numx, numy;
	float max_block_width;
	float max_block_height;
	sf::RenderWindow* window;
	sf::Vector2i pos;
	float deg;
	sf::ConvexShape s;
	sf::Mutex m;
public:

	MinorMap(sf::RenderWindow *w);
	MinorMap(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w );
	MinorMap(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w, float mbh, float mbw );

	~MinorMap();

	void explosion_happened(sf::Vector2i pos , float r);
	void laserExp_happened(Wizard* shooterwiz,Wizard* slavewiz,float deg);
	void expThread();
	void draw();
	std::stringstream write_data();
	void write_data_to_file(std::string filename);
	void load(std::string to_load);

	/*testre vár még:*/
	void make_me_round();
	void make_solid(sf::Vector2i pos);
	void make_solid();
	void make_destructible(sf::Vector2i pos);
	std::vector<std::shared_ptr<Block>> get_block_v();
};

