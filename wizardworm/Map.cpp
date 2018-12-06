#include "Map.h"

#include <iostream>
#include <fstream>
#include <sstream>

Map::Map()
{
	
	
}

Map::Map(std::shared_ptr<MinorMap> minormap)

{
	minormap_v.push_back(minormap);
	
}





Map::~Map()
{
}

void Map::explosion_happened(sf::Vector2i pos)
{
	for (int i = 0; i < minormap_v.size(); i++) {
		minormap_v[i]->explosion_happened(pos);
	}



}

void Map::draw()
{
	for (int i = 0; i < minormap_v.size(); i++) {
		minormap_v[i]->draw();
	}

}

std::vector<std::string> Map::write_data()
{
	std::vector<std::string> data_v;
	std::vector<std::string> temp;
	for (int i = 0; i < minormap_v.size(); i++) {
		temp=(minormap_v[i]->write_data);
		for (int j = 0; j < temp.size(); j++) {
			data_v.push_back(temp[j]);
		}
	}

	

	return data_v;
}

void Map::write_data_to_file(std::string filename)
{
	std::ofstream of(filename);
	std::vector<std::string> temp;
	
	for (int i = 0; i < minormap_v.size(); i++) {
		
		temp = minormap_v[i]->write_data();
		for (int j = 0; j < temp.size(); j++) {
			of<<temp[i]<<std::endl;
		}
	}
	std::cout << "kiirtam ide: " << "\n";
	of.close();

}



void Map::load_from_file(std::string filename)
{
	/*std::ifstream f(filename);
	if (f.fail()) {
		std::cout << "rossz a fajl \n";
		return;
	}
	*/
	//TODO: egy fájl van az egész mapra, ezért valszeg a fájlszerkezetet meg kell változtatni. itt dolgozom fel a fajlt, és a loadot a minormapoknak adom

	/*minormap_v.clear();

	std::string line;	
	std::stringstream ss;
	std::string temp;

	float posx, posy, h, w;
	int r, g, b , n;
	bool d;
	std::vector<sf::Vector2f> points;

	while (getline(f ,line)) {
		//std::cout << line << "\n";
		//block_v.push_back(make_new_block(line));
		

		
		ss << line;
		
		ss>>temp;
		posx = std::stof(temp);
		ss >> temp;
		posy = std::stof(temp);
		ss >> temp;
		n = std::stoi(temp);
		ss >> temp;
		w = std::stof(temp);
		ss >> temp;
		h = std::stof(temp);
		ss >> temp;
		r = std::stoi(temp);
		ss >> temp;
		g = std::stoi(temp);
		ss >> temp;
		b = std::stoi(temp);
		ss >> temp;
		d = (bool)std::stoi(temp);

		
		for (int i = 0; i < n; i++) {
			points.push_back(sf::Vector2f(0, 0));
			ss >> temp;
			points[i].x=std::stof(temp);
			ss >> temp;
			points[i].y = std::stof(temp);
			
		}
		std::cout << posx <<" "<<posy << " " <<n <<" "<< w << " " <<h << " " <<r << " " <<g << " " <<b<<" ";
		for (int i = 0; i < points.size(); i++) {
			std::cout << points[i].x << " " << points[i].y << " ";
		}
		std::cout << "\n \n";

		
		ss.clear();
		ss.str("");

		block_v.push_back(std::make_unique<Block>(posx, posy, sf::Color(r, g, b), h, w,  window , n, points , d ));
		points.clear();
		

	}
	*/

	

}

void Map::make_solid(sf::Vector2i pos)
{
	for (int i = 0; i < block_v.size(); i++) {
		if (block_v[i]->check_bound(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
			//std::cout << "benne a boundingboxban \n";
			if (block_v[i]->contains(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
				block_v[i]->set_destructible(pos, false);
			}
		}
	}

}

void Map::make_destructible(sf::Vector2i pos)
{
	for (int i = 0; i < block_v.size(); i++) {
		
		if (block_v[i]->check_bound(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
			//std::cout << "benne a boundingboxban \n";
			if (block_v[i]->contains(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
				
				block_v[i]->set_destructible(pos, true);
			}
		}
	
	}
}
