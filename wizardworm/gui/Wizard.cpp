#include "stdafx.h"
#include "Wizard.h"
#include "Animation.h"


#include<iostream>
#include<vector>


Wizard::Wizard(float x_ , float y_ , float _id , sf::RenderWindow *w,std::string image_name)
	:Drawable(x_, y_)
{
	//set_value(1); //�l e m�g a var�zsl� 
	set_pos(x_ , y_ ); //Var�zsl� kezdeti poz�ci�ja
	window = w;
	
	lifebar = new Bar(x_,y_-25 , sf::Color::Red ,50 , window); //A var�zsl� �lete
	manabar = new Bar(x_, y_-20 , sf::Color::Blue , 50 , window); //A var�zsl� man�ja
	arrow_v.push_back( new Arrow(x_ + 47, y_ + 21, window , "firebolt"));
	arrow_v.push_back( new Arrow(x_ + 47, y_ + 21, window, "laserbeam"));
	arrow = arrow_v[0];
	id = _id;
	texture.loadFromFile(image_name);
	texture.setSmooth(true);

	wormImage.setSize(sf::Vector2f(100.0f, 100.0f));
	wormImage.setTexture(&texture);
	animation = new Animation(&texture, sf::Vector2u(4, 2), 10);

	wormImage.setPosition(x_, y_);
	wormImage.setScale(0.50f, 0.50f);
	wormImage.setTextureRect(animation->uvRect);
	deltaTime = 2.f;
	wizAnimationUpdate();
	wizAnimationUpdate();
	wizAnimationUpdate();

}


Wizard::~Wizard(){
	delete lifebar;
	delete manabar;
	delete animation;
}


void Wizard::draw() {

	wormImage.setPosition(x+X_OFFSET, y);
	window->draw(wormImage);
	
	lifebar->draw();
	manabar->draw();
	if (arrow != nullptr) {
		arrow->draw();
	}

}

void Wizard::set_Pos(sf::Vector2f pos ) {
	
	
	if ((pos.x ) > this->x)
	{
		X_OFFSET = 0;
		wormImage.setScale(0.50f, 0.50f);
	}
	else if(pos.x<this->x)
	{
		X_OFFSET = 50;
		wormImage.setScale(-0.50f, 0.50f);
	}

	if (pos.x != this->x || pos.y != this->y) {
		if (pos.y == this->y) {
			this->wizAnimationUpdate();
		}
		

			set_pos(pos.x, pos.y);

			for (Arrow * a : arrow_v) {
				a->set_pos(x + 47, y + 21);
			}

			lifebar->set_pos(x, y - 25);
			manabar->set_pos(x, y - 20);
		
	}




}

void Wizard::move(float x, float y , float deltatime) {

	if ((x + this->x) > this->x)
	{
		X_OFFSET = 0;
		wormImage.setScale(0.50f, 0.50f);
	}
	else
	{	
		X_OFFSET = 50;
		wormImage.setScale(-0.50f, 0.50f);
	}

	if (this->x != x) {
		wizAnimationUpdate();
		incr_pos(x, y);

		for (Arrow * a : arrow_v) {
			a->incr_pos(x, y);
		}

		lifebar->incr_pos(x, y);
		manabar->incr_pos(x, y);
	}
}

void Wizard::set_life(float l)
{
	//TODO: catchelni kell az exceptiont
	
	lifebar->set_val(l);

}

void Wizard::set_mana(float m)
{
	//TODO: catchelni kell az exceptiont
	manabar->set_val(m);
}

void Wizard::incr_life(float l)
{
	//TODO: catchelni kell az exceptiont
	lifebar->incr_val(l);
}

void Wizard::incr_mana(float m)
{
	//TODO: catchelni kell az exceptiont
	manabar->incr_val(m);
}

Arrow* Wizard::get_arrow() {

	
	if (arrow->is_opened() ) {

		return arrow;
	}
	return nullptr;

}

void Wizard::open_arrow()
{
	//std::cout << arrow->get_type() << "kinyit \n";
	arrow->set_opened(true);
}

void Wizard::close_arrow()
{
	//std::cout << arrow->get_type() << "bezár \n";
	arrow->set_opened(false);
}

void Wizard::change_arrow_opening()
{
	if (arrow->is_opened()) {
		
		close_arrow();
	}
	else {
		
		open_arrow();
	}
}

void Wizard::change_curr_arrow(int i)
{
	
	if (i>=0 && i<arrow_v.size()) {
		
		if ((i == 0 && arrow->get_type() == "firebolt") || (i == 1 && arrow->get_type() == "laserbeam")) {
			change_arrow_opening();
			return;
		}
		arrow = arrow_v[i];
		arrow->set_opened(false);
		arrow = arrow_v[i];
		arrow->set_opened(true);

		
		
		
		
	}
}



void Wizard::wizaim(bool up)
{
	if (arrow->is_opened()) {
		if (up) {
			arrow->incr_deg(-10);
		}
		else {
			arrow->incr_deg(10);
		}

	}
}

void Wizard::wizforce()
{
	if (arrow->is_opened()) {	
		
			arrow->incr_force(0.05f);	

	}
	
	
}

void Wizard::wizAnimationUpdate() {

	animation->Update(deltaTime++);
	wormImage.setTextureRect(animation->uvRect);
}

int Wizard::get_id() {
	return id;
}

std::string Wizard::curr_spell()
{

	return std::string();
}

bool Wizard::point_in_wizard(sf::Vector2f p)
{
	return p.x>this->x && p.x<this->x+this->width && p.y>this->y && p.y < this->y + this->height;
}

bool Wizard::wizard_in_block(std::shared_ptr<Block> b)
{
	std::vector<sf::Vector2f> t=b->get_points();

	for (int i = 0; i < t.size(); i++) {
		if (point_in_wizard(t[i])) {
			return true;
		}
	}
	return false;
/*
	//alja
	if (b->check_bound(sf::Vector2f(this->x+width/2, this->y + height))) {
		if (b->contains(sf::Vector2f(this->x + width/2, this->y + height)))
			return true;
	}

	//jobbalso
	if (b->check_bound(sf::Vector2f(this->x + width , this->y + height))) {
		if (b->contains(sf::Vector2f(this->x + width , this->y + height)))
			return true;
	}

	//jobbfelso
	if (b->check_bound(sf::Vector2f(this->x + width, this->y))) {
		if (b->contains(sf::Vector2f(this->x + width, this->y)))
			return true;
	}

	//balalso
	if (b->check_bound(sf::Vector2f(this->x , this->y + height))) {
		if (b->contains(sf::Vector2f(this->x , this->y + height)))
			return true;
	}

	//balfelso
	if (b->check_bound(sf::Vector2f(this->x , this->y ))) {
		if (b->contains(sf::Vector2f(this->x , this->y )))
			return true;
	}

	//jobbja
	if (b->check_bound(sf::Vector2f(this->x+width, this->y + height / 2))) {
		if (b->contains(sf::Vector2f(this->x+width, this->y + height / 2)))
			return true;
	}



	//balja
	if (b->check_bound(sf::Vector2f(this->x, this->y + height / 2))) {
		if(b->contains(sf::Vector2f(this->x, this->y + height / 2)))
			return true;
	}

	//teteje
	if (b->check_bound(sf::Vector2f(this->x+width/2, this->y))) {
		if (b->contains(sf::Vector2f(this->x+width/2, this->y)))
			return true;
	}

	
	return false;*/
}



float distance2(sf::Vector2f p1, sf::Vector2f p2) {
	return pow(pow(p1.x - p2.x, 2.0f) + pow(p1.y - p2.y, 2.0f), 0.5);
}

struct Line {
	sf::Vector2f p1;
	sf::Vector2f p2;

	bool contains(sf::Vector2f point) const {
		float margin = 0.5;
		return std::abs((distance2(p1, point) + distance2(point, p2)) - distance2(p1, p2)) < margin;
	}
};

sf::Vector2f intersection2(Line lineA, Line lineB) {
	int x1 = lineA.p1.x;
	int y1 = lineA.p1.y;
	int x2 = lineA.p2.x;
	int y2 = lineA.p2.y;

	int x3 = lineB.p1.x;
	int y3 = lineB.p1.y;
	int x4 = lineB.p2.x;
	int y4 = lineB.p2.y;

	try {
		if (((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4)) != 0) {
			double retX = ((x1*y2 - y1 * x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3 * x4)) / ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
			double retY = ((x1*y2 - y1 * x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3 * x4)) / ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
			return sf::Vector2f(retX, retY);
		}


		return sf::Vector2f(0, 0);

	}
	catch (std::exception) {

		throw new std::exception("");
	}
}

std::vector<sf::Vector2f> getIntersectionPoints2(sf::ConvexShape shape, sf::Vector2f point) {
	std::vector<sf::Vector2f> intersectPoints;
	sf::Vector2f p;
	bool crossingLine;  // This will be used to avoid duplicated points on special cases

	if (shape.getPointCount() < 3) {
		return intersectPoints;
	}

	sf::FloatRect bounds = shape.getLocalBounds();

	// To determine horizontal line, we use two points, one at leftmost side of the shape (in fact, its bound) and the other at rightmost side
	Line pointLine;
	Line shapeLine;
	pointLine.p1 = sf::Vector2f(bounds.left, point.y);
	pointLine.p2 = sf::Vector2f(bounds.left + bounds.width, point.y);

	unsigned int nPoints = shape.getPointCount();

	for (int i = 0; i < nPoints; ++i) {
		try {
			shapeLine.p1 = shape.getPoint(i % nPoints);         // Last one will be nPoints-1
			shapeLine.p2 = shape.getPoint((i + 1) % nPoints);   // So this one must be 0 in order to check last side (returning to origin)
			crossingLine = (shapeLine.p1.y >= point.y && shapeLine.p2.y <= point.y) || (shapeLine.p2.y >= point.y && shapeLine.p1.y <= point.y);
			p = intersection2(shapeLine, pointLine);
			if (crossingLine && shapeLine.contains(p))
				intersectPoints.push_back(p);
		}
		catch (std::runtime_error e) {
			std::cout << "error \n";
		}
	}

	return intersectPoints;
}

bool inside_the_laser(sf::ConvexShape s,sf::Vector2f point) {

	std::vector<sf::Vector2f> intersectPoints = getIntersectionPoints2(s, point);
	int nodesAtLeft = 0;
	int nodesAtRight = 0;
	for (sf::Vector2f po : intersectPoints) {
		if (po.x < point.x) {
			nodesAtLeft++;
		}
		else if (po.x > point.x) {
			nodesAtRight++;
		}
	}
	return ((nodesAtLeft % 2) == 1) && ((nodesAtRight % 2) == 1);
}



bool Wizard::wizard_in_shape(sf::ConvexShape s)
{

	//alja
	if (inside_the_laser(s , sf::Vector2f(this->x + width / 2, this->y + height))) {
		
			return true;
	}

	//jobbalso
	if (inside_the_laser(s, sf::Vector2f(this->x + width, this->y + height))) {
		
			return true;
	}

	//jobbfelso
	if (inside_the_laser(s, sf::Vector2f(this->x + width, this->y))) {
		
			return true;
	}

	//balalso
	if (inside_the_laser(s, sf::Vector2f(this->x, this->y + height))) {
		
			return true;
	}

	//balfelso
	if (inside_the_laser(s, sf::Vector2f(this->x, this->y))) {
		
			return true;
	}

	//jobbja
	if (inside_the_laser(s, sf::Vector2f(this->x + width, this->y + height / 2))) {
		
			return true;
	}



	//balja
	if (inside_the_laser(s, sf::Vector2f(this->x, this->y + height / 2))) {
		
			return true;
	}

	//teteje
	if (inside_the_laser(s, sf::Vector2f(this->x + width / 2, this->y))) {
		
			return true;
	}




	return false;
}
