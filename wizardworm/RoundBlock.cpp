#include "RoundBlock.h"








RoundBlock::RoundBlock(sf::RenderWindow * w) : Block(w){
	make_me_round();
}

RoundBlock::RoundBlock(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow * w) : Block(_x,_y,c,_h,_w, w)
{
	make_me_round();
}

RoundBlock::RoundBlock(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow * w, int n, std::vector<sf::Vector2f> p, bool d)
	:Block(_x, _y, c, _h, _w, w, n,p, d)
{
	make_me_round();
}

RoundBlock::~RoundBlock()
{
}

void RoundBlock::make_me_round()
{
}