#pragma once

#include "Block.h"
#include "MinorMap.h"
#include <vector>

class Map {
	std::vector<std::shared_ptr<MinorMap>> minormap_v;
public:

	Map();
	Map(std::shared_ptr<MinorMap> minormap);


	~Map();

	void explosion_happened(sf::Vector2i pos);
	void draw();
	std::vector<std::string> write_data();
	void write_data_to_file(std::string filename);
	void load_from_file(std::string filename);
	
	

	void make_solid(sf::Vector2i pos);
	void make_destructible(sf::Vector2i pos);

};

