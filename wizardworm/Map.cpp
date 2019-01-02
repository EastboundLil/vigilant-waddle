#include "Map.h"

#include <iostream>
#include <fstream>
#include <sstream>

Map::Map(sf::RenderWindow *w)
{
	window = w;
	
	
}

Map::Map(std::shared_ptr<MinorMap> minormap , sf::RenderWindow *w)

{
	
	window = w;
	minormap_v.push_back(minormap);
	
}





Map::~Map()
{
}

void Map::add_minormap(std::shared_ptr<MinorMap> new_mmap)
{
	minormap_v.push_back(new_mmap);
}

void Map::explosion_happened(sf::Vector2i pos , float r)
{
	for (int i = 0; i < minormap_v.size(); i++) {
		minormap_v[i]->explosion_happened(pos , r);
	}

}

void Map::laserExp_happened(sf::Vector2i pos, float deg) {
	for (int i = 0; i < minormap_v.size(); i++) {
		minormap_v[i]->laserExp_happened(pos,deg);
	}
}


void Map::draw()
{
	for (int i = 0; i < minormap_v.size(); i++) {
		minormap_v[i]->draw();
	}

}

std::stringstream Map::write_data()
{
	std::stringstream ss;
	
	for (int i = 0; i < minormap_v.size(); i++) {
		ss<<(minormap_v[i]->write_data()).str();
		ss << "\n";
	}

	

	return ss;
}

void Map::write_data_to_file(std::string filename)
{
	std::ofstream of(filename);
	
	
	of << write_data().str();
	std::cout << "kiirtam ide: " << "\n";
	of.close();

}



void Map::load_from_file(std::string filename)
{
	

	std::ifstream f(filename);
	std::stringstream ss;
	std::string line;

	

	if (f.fail()) {
		std::cout << "rossz a fajl \n";
		return;
	}
	

	if (minormap_v.empty()) {
		std::cout << "uresa map";
	}

	while (getline(f, line)) {
		
		ss.clear();
		ss.str("");
		ss << line;
		std::string w;
		ss >> w;
		if (w != "begin") {
			
			continue;

		}else {
			//std::cout << "minormap: \n";
			ss.clear();
			ss.str( "");
			
			while(getline(f, line)){

				
				
				
				if ( line.substr(0, line.find(" ")) == "end") {
					
					
					break;
				}
				else {
					ss << line << "\n";
				}
					
					
				
			}
			
			minormap_v.push_back(std::make_shared<MinorMap>(window));
			//std::cout << ss.str()<<"minorvege \n";

			minormap_v[minormap_v.size() - 1]->load(ss.str());
			ss.clear();
			ss << "";
		
		}

	}
	
	
	std::cout << "a mapnak " << minormap_v.size() << " eleme van";


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

void Map::make_empty()
{
	minormap_v.clear();
}

void Map::make_solid(sf::Vector2i pos)
{
	for (int i = 0; i < minormap_v.size(); i++) {

		minormap_v[i]->make_solid(pos);

		/*if (block_v[i]->check_bound(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
			//std::cout << "benne a boundingboxban \n";
			if (block_v[i]->contains(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
				block_v[i]->set_destructible(pos, false);
			}
		}*/
	}

}

void Map::make_destructible(sf::Vector2i pos)
{
	for (int i = 0; i < minormap_v.size(); i++) {
		
		minormap_v[i]->make_destructible(pos);

		/*if (block_v[i]->check_bound(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
			//std::cout << "benne a boundingboxban \n";
			if (block_v[i]->contains(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
				
				block_v[i]->set_destructible(pos, true);
			}
		}*/
	
	}
}
