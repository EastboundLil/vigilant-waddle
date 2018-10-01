#include "stdafx.h"
#include "Drawable.h"


Drawable::Drawable(int x_ , int y_ , sf::Color color_ )
{
	x = x_;
	y = y_;
	color = color_;

}

Drawable::Drawable(int x_, int y_) {
	x = x_;
	y = y_;
}


Drawable::~Drawable()
{
}

void Drawable::set_pos(int x_, int y_){	x = x_; y = y_;}

void Drawable::incr_pos(int x_, int y_){	x += x_;	y += y_;}


void Drawable::set_x(int x_) { x = x_; }

void Drawable::set_y(int y_){	y = y_;}

int Drawable::get_x(){	return x;}

int Drawable::get_y(){	return y;}

void Drawable::incr_x(int x_){	x += x_;}

void Drawable::incr_y(int y_){	y += y_;}

void Drawable::set_color(sf::Color c){	color = c; }

sf::Color Drawable::get_color(){	return  color;}


void Drawable::draw(){}
