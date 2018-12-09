#pragma once
#include "Drawable.h"

#include <vector>

class Block :
	public Drawable
{
public:
	
	Block(sf::RenderWindow *w);
	Block(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w );
	Block(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w, int n, std::vector<sf::Vector2f> p , bool d);
	
	~Block();
	void draw();
	std::string write_data();
	bool caught_by_expl(sf::Vector2f expl , float r);
	bool is_alive();
	void set_destructible( bool destr);
	bool contains(sf::Vector2f point);
	bool check_bound(sf::Vector2f pos); //most nem használom
	bool inside_an_ellipse(sf::Vector2f c, sf::Vector2f r);
protected:
	sf::RenderWindow *window;
	std::shared_ptr<sf::ConvexShape> convex_v;  //
	float height;
	float width;
	float Xmin , Xmax , Ymin, Ymax;
	

	void modify_coords(sf::Vector2f expl, float & newx, float & newy, sf::Vector2f pos, float r);
private:
	bool Alive;
	bool destructible;
	static int ID;
	int currID;
	void del_point( std::vector<bool> delablepoints);
	//void split_shape(size_t i);
	
	void refresh_bounds();
	void set_res(int res);
	void set_block_point(size_t i, size_t j, float _x, float _y);
	

};

