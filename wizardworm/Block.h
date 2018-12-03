#pragma once
#include "Drawable.h"

#include <vector>

class Block :
	public Drawable
{
public:
	
	Block(sf::RenderWindow *w);
	Block(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w);
	Block(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w, int n, std::vector<sf::Vector2f> p);
	
	~Block();
	void draw();
	std::string write_data();
	bool caught_by_expl(sf::Vector2f expl , float r);
	bool is_alive();
protected:
	sf::RenderWindow *window;
	std::vector<sf::ConvexShape*> convex_v;  //
	float height;
	float width;
	float Xmin , Xmax , Ymin, Ymax;
	

	void modify_coords(sf::Vector2f expl, float & newx, float & newy, sf::Vector2f pos, float r);
private:
	bool Alive;
	static int ID;
	int currID;
	void del_point(int i, std::vector<bool> delablepoints);
	//void split_shape(size_t i);
	float check_bound(float _x, int p , float old); //most nem használom
	void refresh_bounds(int i);
	void set_res(int res);
	void set_block_point(size_t i, size_t j, float _x, float _y);
	

};

