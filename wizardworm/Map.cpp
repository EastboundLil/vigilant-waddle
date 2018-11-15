#include "Map.h"

#include <iostream>

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
		if (block_v[i]->caught_by_expl(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
			
		}
	}
}

void Map::draw()
{
	for (int i = 0; i < block_v.size(); i++) {
		block_v[i]->draw();
	}
}
