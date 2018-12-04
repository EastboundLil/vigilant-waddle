#include "Map.h"

#include <iostream>
#include <fstream>
#include <sstream>

Map::Map()
{
	width = 0;
	height = 0;
	
}

Map::Map(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow * w)
	:Drawable(_x,_y,c)
{
	width=_w;
	height=_h;
	window = w;
	max_block_height = 50.0;
	max_block_width = 50.0;
	 numx = static_cast<int>(width) / max_block_width;
	 numy = static_cast<int>(height) / max_block_height;
	int rx = fmodf(width, max_block_width);
	float ry = fmodf(height, max_block_height);
	if (rx > 0) { numx++; };
	if (ry > 0) { numy++; };
	//std::cout << "numx: " << numx << " numy: " << numy << " rx: " << rx << " ry: " << ry;
	for (int i = 0; i < numx; i++) {
		for (int j = 0; j < numy; j++) {

			if ( j+1 < numy && i+1<numx) {
				block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, max_block_height, max_block_width, window));
			}
			else {
				if (i+1 == numx && j+1 == numy) {
					if(rx>0 && ry >0){
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, ry, rx, window));
					}
					else if(rx>0 && ry==0){
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, max_block_height, rx, window));
					}
					else if(rx==0 && ry > 0) {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, ry, max_block_width, window));
					}
					else {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, max_block_height, max_block_width, window));
					}
					
				}
				else if (j + 1 == numy) { //utso oszlop: 
					if (ry > 0) {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, ry , max_block_width, window));
					}
					else {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, max_block_height, max_block_width, window));
					}
				
				}
				else if (i + 1 == numx) {
					if (rx > 0) {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, max_block_height, rx, window));
					}
					else {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, max_block_height, max_block_width, window));
					}

				}

			}
		}
		
		
	}
	
}

Map::Map(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow * w, float mbh, float mbw)
	:Drawable(_x, _y, c)
{
	max_block_height = mbh;
	max_block_width = mbw;
	width = _w;
	height = _h;
	window = w;
	numx = static_cast<int>(width) / max_block_width;
	numy = static_cast<int>(height) / max_block_height;
	int rx = fmodf(width, max_block_width);
	float ry = fmodf(height, max_block_height);
	if (rx > 0) { numx++; };
	if (ry > 0) { numy++; };
	//std::cout << "numx: " << numx << " numy: " << numy << " rx: " << rx << " ry: " << ry;
	for (int i = 0; i < numx; i++) {
		for (int j = 0; j < numy; j++) {

			if (j + 1 < numy && i + 1 < numx) {
				block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, max_block_height, max_block_width, window));
			}
			else {
				if (i + 1 == numx && j + 1 == numy) {
					if (rx > 0 && ry > 0) {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, ry, rx, window));
					}
					else if (rx > 0 && ry == 0) {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, max_block_height, rx, window));
					}
					else if (rx == 0 && ry > 0) {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, ry, max_block_width, window));
					}
					else {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, max_block_height, max_block_width, window));
					}

				}
				else if (j + 1 == numy) { //utso oszlop: 
					if (ry > 0) {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, ry, max_block_width, window));
					}
					else {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, max_block_height, max_block_width, window));
					}

				}
				else if (i + 1 == numx) {
					if (rx > 0) {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, max_block_height, rx, window));
					}
					else {
						block_v.push_back(std::make_unique<Block>(x + i * max_block_width, y + j * max_block_height, color, max_block_height, max_block_width, window));
					}

				}

			}
		}


	}

}



Map::~Map()
{
}

void Map::explosion_happened(sf::Vector2i pos)
{
	for (int i = 0; i < block_v.size(); i++) {
		if (block_v[i]->caught_by_expl(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)) , 50)) {
			
		}
	}

	if (!block_v.empty()) {
		for (int i = block_v.size() - 1; i >= 0; i--) {
			if (!block_v[i]->is_alive()) {
				block_v.erase(block_v.begin()+i);
			}
		}
	}



}

void Map::draw()
{
	for (int i = 0; i < block_v.size(); i++) {
		block_v[i]->draw();
	}
}

std::vector<std::string> Map::write_data()
{
	std::vector<std::string> data_v;
	for (int i = 0; i < block_v.size(); i++) {
		data_v.push_back(block_v[i]->write_data());
	}

	return data_v;
}

void Map::write_data_to_file(std::string filename)
{
	std::ofstream of(filename);
	
	
	for (int i = 0; i < block_v.size(); i++) {
		of<<block_v[i]->write_data()<<std::endl;
	}
	std::cout << "kiirtam ide: " << "\n";
	of.close();

}



void Map::load_from_file(std::string filename)
{
	std::ifstream f(filename);
	if (f.fail()) {
		std::cout << "rossz a fajl \n";
		return;
	}

	std::vector<std::shared_ptr<Block>> old_v=block_v;

	block_v.clear();

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
