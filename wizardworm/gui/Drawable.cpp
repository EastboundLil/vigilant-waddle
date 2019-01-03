#include "stdafx.h"
#include "Drawable.h"


Drawable::Drawable(float x_ , float y_ , sf::Color color_ )
{
	x = x_;
	y = y_;
	color = color_;

}

Drawable::Drawable() {}

Drawable::Drawable(float x_, float y_) {
	x = x_;
	y = y_;
}


Drawable::~Drawable()
{
}

void Drawable::set_pos(float x_, float y_){	x = x_; y = y_;}

void Drawable::incr_pos(float x_, float y_){	x += x_;	y += y_;}


void Drawable::set_x(float x_) { x = x_; }

void Drawable::set_y(float y_){	y = y_;}

float Drawable::get_x(){	return x;}

float Drawable::get_y(){	return y;}

void Drawable::incr_x(float x_){	x += x_;}

void Drawable::incr_y(float y_){	y += y_;}

sf::Vector2f Drawable::get_pos()
{
	return sf::Vector2f(this->x , this->y);
}

void Drawable::set_color(sf::Color c){	color = c; }

sf::Color Drawable::get_color(){	return  color;}



