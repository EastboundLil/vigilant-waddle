#pragma once

#include "Block.h"
#include "MinorMap.h"
#include "Player.h"

#include <vector>

class Map {
	std::vector<std::shared_ptr<MinorMap>> minormap_v;
	sf::RenderWindow *window;
public:

	Map(sf::RenderWindow *w);
	Map(std::shared_ptr<MinorMap> minormap , sf::RenderWindow *w);


	~Map();
	void add_minormap(std::shared_ptr<MinorMap> new_mmap);
	void explosion_happened(sf::Vector2i pos , float r);
	void laserExp_happened(Wizard* pos, std::vector<std::shared_ptr<Player>> player_v, float deg);

	void draw();
	std::stringstream write_data();
	void write_data_to_file(std::string filename);
	void load_from_file(std::string filename);
	void make_empty();
	

	void make_solid(sf::Vector2i pos);
	void make_destructible(sf::Vector2i pos);
	std::vector<std::shared_ptr<Block>> get_all_blocks();

};

