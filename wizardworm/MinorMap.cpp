#include "MinorMap.h"



#include <iostream>
#include <fstream>
#include <sstream>

MinorMap::MinorMap(sf::RenderWindow *w)
{
	width = 0;
	height = 0;
	
	window = w;

}

MinorMap::MinorMap(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow * w)
	:Drawable(_x, _y, c)
{
	width = _w;
	height = _h;
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

MinorMap::MinorMap(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow * w, float mbh, float mbw)
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



MinorMap::~MinorMap()
{
}

void MinorMap::explosion_happened(sf::Vector2i pos , float r)
{
	m.lock();
	for (int i = 0; i < block_v.size(); i++) {
		if (block_v[i]->caught_by_expl(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)), r)) {

		}
	}

	if (!block_v.empty()) {
		for (int i = block_v.size() - 1; i >= 0; i--) {
			if (!block_v[i]->is_alive()) {
				block_v.erase(block_v.begin() + i);
			}
		}
	}
	m.unlock();
}

#define PI 3.14159265




void makenormal(sf::Vector2f& p,float deg) {

	sf::Vector2f t = p;

	p.x = cos(PI*deg / 180)*t.x - sin(PI*deg / 180)*t.y;
	p.y = sin(PI*deg / 180)*t.x + cos(PI*deg / 180)*t.y;

}

void MinorMap::laserExp_happened(Wizard* shooterwiz,Wizard* slavewiz, float deg) {
	
	std::vector<sf::Vector2f> points;
	points.push_back(sf::Vector2f(0, -25));
	points.push_back(sf::Vector2f(0, 25));
	points.push_back(sf::Vector2f(1000, 25));
	points.push_back(sf::Vector2f(1000, -25));

	s.setPointCount(4);
	for (int i = 0; i < points.size(); i++) {
		makenormal(points[i], deg);
		points[i]= points[i]+ shooterwiz->get_pos()+sf::Vector2f(50 , 25);
		s.setPoint(i, points[i]);
	}


	if (slavewiz->wizard_in_shape(s)) {
		std::cout << "lel \n";
	}

}



void MinorMap::expThread()
{
	float y;
	for (float i = 0; i < 500; i += 25) {
		//int i = 0;
			//std::cout << deg << " degree" << std::endl;
		y = (tan(PI*deg/180)*i);
		//std::cout << y << " y position" << y + pos.y << " y plus worm positon" << std::endl;
		explosion_happened(sf::Vector2i(static_cast<float>(pos.x + i + 25), static_cast<float>(pos.y + y)) , 30);
	}
}

void MinorMap::draw()
{
	m.lock();
	for (int i = 0; i < block_v.size(); i++) {
		block_v[i]->draw();
	}
	/*s.setFillColor(sf::Color::Transparent);
	s.setOutlineColor(sf::Color::Blue);
	s.setOutlineThickness(-5);*/

	//window->draw(s);
	m.unlock();
}

std::stringstream MinorMap::write_data()
{
	std::stringstream data_ss;
	data_ss << "begin" << " " << block_v.size()<<"\n";
	for (int i = 0; i < block_v.size(); i++) {
		data_ss<<(block_v[i]->write_data());
	}
	data_ss << "end " << "\n";
	return data_ss;
}

void MinorMap::write_data_to_file(std::string filename)
{
	std::ofstream of(filename);


	for (int i = 0; i < block_v.size(); i++) {
		of << block_v[i]->write_data() << std::endl;
	}
	std::cout << "kiirtam ide: " << "\n";
	of.close();

}



void MinorMap::load(std::string to_load)
{
	

	std::vector<std::shared_ptr<Block>> old_v = block_v;

	block_v.clear();

	std::string line;
	std::stringstream ss;
	std::stringstream ssfull;
	std::string temp;

	float posx, posy, h, w;
	int r, g, b, n;
	bool d;
	std::vector<sf::Vector2f> points;
	ssfull << to_load;
	//std::cout << "ebbol epitkezek: " << ssfull.str() << "\n";
	//std::getline(ssfull, line);
	std::cout << "loadablemap: \n" << to_load << " \n";
	while (std::getline(ssfull, line) ) {
		
		//block_v.push_back(make_new_block(line));
		//if (line=="end ")break;

		ss << line;
		
		
		ss >> temp;
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
			points[i].x = std::stof(temp);
			ss >> temp;
			points[i].y = std::stof(temp);

		}
		


		ss.clear();
		ss.str("");
	
		block_v.push_back(std::make_unique<Block>(posx, posy, sf::Color(r, g, b), h, w, window, n, points, d));
		points.clear();


	}

	//std::cout << "az egyik minornak " << block_v.size() <<" eleme van \n";


}

void MinorMap::make_me_round()
{
	if (height != 0 && width != 0) {
		
		sf::Vector2f c = sf::Vector2f(static_cast<float>(x + width / 2), static_cast<float>(y + height / 2));
		sf::Vector2f r = sf::Vector2f(static_cast<float>(width / 2), static_cast<float>(height / 2));



		for (int i = block_v.size()-1; i >=0 ; i--) {		
			if (!block_v[i]->inside_an_ellipse(c , r)) {				
				block_v.erase(block_v.begin() + i);				
				//block_v[i]->set_destructible(false);
			}
		}
	}
}

void MinorMap::make_solid(sf::Vector2i pos)
{
	
	for (int i = 0; i < block_v.size(); i++) {
		if (block_v[i]->check_bound(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
			//std::cout << "benne a boundingboxban \n";
			if (block_v[i]->contains(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
				for (int j = 0; j < block_v.size(); j++) {
					block_v[j]->set_destructible(false);
				}
				return;
			}
		}
	}
	

}

void MinorMap::make_solid()
{
		
				for (int j = 0; j < block_v.size(); j++) {
					block_v[j]->set_destructible(false);
				}

}



void MinorMap::make_destructible(sf::Vector2i pos)
{
	for (int i = 0; i < block_v.size(); i++) {
		if (block_v[i]->check_bound(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
			//std::cout << "benne a boundingboxban \n";
			if (block_v[i]->contains(sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)))) {
				for (int j = 0; j < block_v.size(); j++) {
					block_v[j]->set_destructible(true);
				}
				return;
			}
		}
	}
		

	
}

std::vector<std::shared_ptr<Block>> MinorMap::get_block_v()
{
	return block_v;
}
