#pragma once
#include "Block.h"
class RoundBlock :
	public Block
{

	void make_me_round();
public:
	RoundBlock(sf::RenderWindow *w);
	RoundBlock(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w);
	RoundBlock(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w, int n, std::vector<sf::Vector2f> p, bool d);





	~RoundBlock();
};

