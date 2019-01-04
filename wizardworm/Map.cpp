#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>

Map::Map(sf::RenderWindow *w)
{
	window = w;
	sf::Vector2u windowsize = window->getSize();
	
	
		for (int i = 0; i < windowsize.x; i++) {
			screen_matrix.push_back(std::vector<int>());
			for (int j = 0; j < windowsize.y; j++) {
				screen_matrix[i].push_back(0);
			}			
		}


}

Map::Map(std::shared_ptr<MinorMap> minormap , sf::RenderWindow *w)

{
	
	window = w;
	minormap_v.push_back(minormap);

	sf::Vector2u windowsize = window->getSize();
	for (int i = 0; i < windowsize.x; i++) {
		screen_matrix.push_back(std::vector<int>());
		for (int j = 0; j < windowsize.y; j++) {
			screen_matrix[i].push_back(0);
		}
	}

	
	
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


void Map::laserExp_happened(Wizard* wiz, std::vector<std::shared_ptr<Player>> player_v, float deg) {

	for (int i = 0; i < player_v.size(); i++) {
		for (int j = 0; j < player_v[i]->getWizardsVectSize(); j++) {
			if(wiz!= player_v[i]->getWizard(j))
			minormap_v[i]->laserExp_happened(wiz,player_v[i]->getWizard(j),deg);
		}
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

std::stringstream Map::write_data_from_matrix() {

	std::stringstream ss;


	for (int i = 0; i < screen_matrix.size(); i++) {
		for (int j = 0; j < screen_matrix[i].size(); j++) {
			ss << screen_matrix[i][j] << " ";
		}
	}

	return ss;
	

}

void Map::write_data_to_file(std::string filename)
{
	std::ofstream of(filename);
	
	
	of << write_data().str();
	//std::cout << "kiirtam ide: "<<filename << "\n";

	of.close();
	write_data_to_file_from_matrix(filename.substr(0, filename.size() - 4) + "_matrix.txt");

}

void Map::write_data_to_file_from_matrix(std::string filename)
{
	std::ofstream of(filename);

	std::stringstream ss;


	for (int i = 0; i < screen_matrix.size(); i++) {
		for (int j = 0; j < screen_matrix[i].size(); j++) {
			of << screen_matrix[i][j] << " ";
			
		}
		of << "\n";

	}

	of.close();
}




void Map::load_from_ss(std::stringstream &ss) {



	if (minormap_v.empty()) {
		std::cout << "uresa map";
	}


	minormap_v.push_back(std::make_shared<MinorMap>(window));
	//std::cout << ss.str()<<"minorvege \n";

	minormap_v[minormap_v.size() - 1]->load(ss.str());
	ss.clear();
	ss << "";

		

	
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
		if (w == "begin") {
			
			continue;

		}else {
			//std::cout << "minormap: \n";
			//ss.clear();
			//ss.str("");
			

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
			//std::cout <<"minormap: "<< ss.str()<<"\n";
			ss.clear();
			ss << "";
		
		}

	}
	//std::cout << "loadfile: " << filename.substr(0, filename.size() - 4) + "_matrix.txt";
	load_from_file_from_matrix(filename.substr(0, filename.size() - 4) + "_matrix.txt");

}

void Map::load_from_file_from_matrix(std::string filename)
{
	std::ifstream file(filename);
	if (file.fail()) {
		std::cout << "rossz fájlnév a loadfromfilfrommatrixban,  \n";
		return;
	}

	std::stringstream ss;
	std::string line;
	screen_matrix.clear();
	std::string stringtoint;
	while (getline(file, line)) {
		screen_matrix.push_back(std::vector<int>());
		ss << line;
		for (int i = 0; i < window->getSize().y; i++) {
			 ss>>stringtoint;
			 screen_matrix[screen_matrix.size() - 1].push_back(std::stoi(stringtoint));
		}
		ss.clear();
		ss.str("");

	}


}

void Map::write_data_to_file_system()
{
	std::string systemfile("mapsystem.txt");
	
	std::ifstream ifile(systemfile);
	std::stringstream ss;
	std::string line;
	int counter = 1;
	while (getline(ifile, line)) {
	
		ss << line;
		ss << "\n";
		counter++;
	}
	ss << "map_no_" << counter<<".txt\n";

	ifile.close();
	std::ofstream of(systemfile ,std::ofstream::out | std::ofstream::trunc);
	of << ss.str();
	of.close();

	ss.clear();
	ss.str("");
	
	ss << "map_no_" << counter << ".txt";
	std::cout << "stringstream tatalma: \n" << ss.str() << "\nvege\n";
	write_data_to_file(ss.str());
	



}

void Map::make_empty()
{
	minormap_v.clear();
}

bool is_point_inside_an_ellipse(sf::Vector2f p, sf::Vector2f c, sf::Vector2f r) {

	return (powf(p.x - c.x, 2) / powf(r.x, 2)) + (powf(p.y - c.y, 2) / powf(r.y, 2)) <= 1;

}


void Map::set_matrix(int x, int y, int ex, int ey, bool isrect, bool issolid)
{
	sf::Vector2f c = sf::Vector2f(static_cast<float>(x + ((ex-x) / 2)), static_cast<float>(y + ((ey-y) / 2)));
	sf::Vector2f r = sf::Vector2f(static_cast<float>(((ex - x) / 2)), static_cast<float>(((ey - y) / 2)));
	std::cout << "set_matrix: " << x << " " << y << " " << ex << " " << ey << "\n";


	for (int i = x; i <= ex; i++) {
		for (int j = y; j <= ey; j++) {
			if (!isrect && is_point_inside_an_ellipse(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), c, r)) {
				if (issolid) {
					screen_matrix[i][j] = 2;
					//std::cout << "2 = " << screen_matrix[i][j] << "\n";
				}
				else {
					screen_matrix[i][j] = 1;
					//std::cout << "1 = " << screen_matrix[i][j] << "\n";
				}


			}
			else {
				if (issolid) {
					screen_matrix[i][j] = 2;
					//std::cout << "2 = "<< screen_matrix[i][j]<<"\n";
				}
				else {
					screen_matrix[i][j] = 1;
					//std::cout << "1 = " << screen_matrix[i][j] << "\n";
				}
			}
		}
	}
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

std::vector<std::shared_ptr<Block>> Map::get_all_blocks()
{
	std::vector<std::shared_ptr<Block>> returningvector;
	for (int i = 0; i < minormap_v.size(); i++) {
		for (int j = 0; j < minormap_v[i]->get_block_v().size(); j++) {
			returningvector.push_back(minormap_v[i]->get_block_v()[j]);
		}
	}

	return returningvector;
}
