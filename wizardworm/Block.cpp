#include "Block.h"

#include <iostream>
#include <algorithm>

Block::Block(sf::RenderWindow *w)
{

	window = w;
	convex_v.push_back(new sf::ConvexShape());
	convex_v[0]->setPointCount(5);
	currID = ++ID;

	// define the points
	convex_v[0]->setPoint(0, sf::Vector2f(0, 0));
	convex_v[0]->setPoint(1, sf::Vector2f(150, 10));
	convex_v[0]->setPoint(2, sf::Vector2f(120, 90));
	convex_v[0]->setPoint(3, sf::Vector2f(30, 100));
	convex_v[0]->setPoint(4, sf::Vector2f(0, 50));
}



Block::Block(float _x, float _y, sf::Color c, float _h, float _w , sf::RenderWindow *w)
	:Drawable(_x, _y, c)
{
	height = _h;
	width = _w;
	currID = ++ID;
	window = w;
	// resize it to 5 points
	convex_v.push_back(new sf::ConvexShape());


	convex_v[0]->setPointCount(8);
	
	// define the points
	convex_v[0]->setPoint(0, sf::Vector2f(x, y ));
	convex_v[0]->setPoint(1, sf::Vector2f(x+width/2, y));
	convex_v[0]->setPoint(2, sf::Vector2f(x+width, y));
	convex_v[0]->setPoint(3, sf::Vector2f(x+width, y+height/2));
	convex_v[0]->setPoint(4, sf::Vector2f(x+width, y+height));
	convex_v[0]->setPoint(5, sf::Vector2f(x+width/2, y+height));
	convex_v[0]->setPoint(6, sf::Vector2f(x, y+height));
	convex_v[0]->setPoint(7, sf::Vector2f(x, y+height/2));
	Xmin = x;
	Xmax = x + width;
	Ymin = y;
	Ymax = y + height;

	//convex.setOrigin(x + width / 2, y + height / 2);

	convex_v[0]->setFillColor(c);
	/*convex_v[0]->setOutlineColor(sf::Color::Red);
	convex_v[0]->setOutlineThickness(-1);*/
}

Block::~Block()
{

}


void Block::draw() {
	for (int i = 0; i < convex_v.size(); i++) {
		window->draw(*convex_v[i]);
	}
	
}

void Block::split_shape(size_t i) {

	int n = convex_v[0]->getPointCount();
	int s = (i + n / 2);
	if (s >= n) {
		s -= n;
	}
	std::cout << "i: " << i << "s: " << s << "\n";

	if (s < i) {
		int t = i;
		i = s;
		s = t;
	}

	sf::ConvexShape* c1=new sf::ConvexShape();
	sf::ConvexShape* c2= new sf::ConvexShape();
	c1->setPointCount(i + 1 + n - s);
	c2->setPointCount(s-i+1);
	for (int k = 0; k <= i; k++) {
		c1->setPoint(k, convex_v[0]->getPoint(k));
	}
	for (int k = 0; k <= s-i; k++) {
		c2->setPoint(k, convex_v[0]->getPoint(i + k));
	}
	//c nek a 
	for (int k =0 ; k <n-s ; k++) {
		c1->setPoint(i + 1 + k, convex_v[0]->getPoint(s + k));
	}

	c1->setFillColor(sf::Color::Green);
	c2->setFillColor(sf::Color::Green);
	c1->setOutlineColor(sf::Color::Red);
	c2->setOutlineColor(sf::Color::Red);
	c1->setOutlineThickness(3);
	c2->setOutlineThickness(3);
	sf::ConvexShape* d = convex_v[0];
	convex_v.pop_back();
	convex_v.push_back(c1);
	convex_v.push_back(c2);
	delete d;

}


void Block::set_block_point(size_t i, size_t j ,  float _x , float _y)
{
	//std::cout << "x: " << _x << " _y. " << _y << std::endl;

	//if (_x > x && _x<x+width &&  _y> y && _y < y+height) {

		convex_v[i]->setPoint(j, sf::Vector2f(_x, _y));
		/*if (_y > y + height / 2) {
			split_shape(i);
			std::cout << "split \n";
		}*/
	//}

}
int d_to_center(sf::Vector2f blocpoint, sf::Vector2f expl) {
	
	return  pow((pow((blocpoint.x - expl.x), 2) + pow((blocpoint.y - expl.y), 2)), 0.5f);
	
	
}

float Block::check_bound(float _x , int p , float old) { //itt azt nézem hogy a pontok kimozdulnak-e az eredeti négyzetbõl, de rosszul. ki kell számolni hogy meddig mozoghat el egy pont mindig.
											// kezd túl bonyi lenni, biztos hogy megéri számolgatni? 	
	if (p == 1) {
		if (_x >= x && _x <= x + width) {
			return _x;
		}
		else {
			return old;
		}

	}
	else {
		if (_x >= y && _x <= y + height) {
			return _x;
		}
		else {
			return old;
		}
	}

}

void Block::refresh_bounds(int i)
{
	float xmin = convex_v[i]->getPoint(0).x;
	float ymin = convex_v[i]->getPoint(0).y;
	float ymax = ymin;
	float xmax = xmin;

	for (int j = 0; j < convex_v[i]->getPointCount(); j++) {
		if (convex_v[i]->getPoint(j).x > xmax) {
			xmax = convex_v[i]->getPoint(j).x;
		}
		if (convex_v[i]->getPoint(j).x < xmin) {
			xmin = convex_v[i]->getPoint(j).x;
		}
		if (convex_v[i]->getPoint(j).y > ymax) {
			ymax = convex_v[i]->getPoint(j).y;
		}
		if (convex_v[i]->getPoint(j).y < ymin) {
			ymin = convex_v[i]->getPoint(j).y;
		}
	}
	Xmax = xmax;
	Xmin = xmin;
	Ymax = ymax;
	Ymin = ymin;

}

void Block::del_point(int i, std::vector<bool> delablepoints) {

	int sum=0;
	for (int j = 0; j < delablepoints.size(); j++) {
		if (delablepoints[j] == false) { sum++; }
		else { std::cout << "torlendo pont: index=" << j << " koord: " << convex_v[i]->getPoint(j).x << " " << convex_v[i]->getPoint(j).y << "\n"; }
		
	}
	
	if (sum == convex_v[i]->getPointCount()) { return; }
	std::cout << "maradando pontok: " << sum<<"\n";
	if (sum > 2) {
		sf::ConvexShape* newshape = new sf::ConvexShape();
		newshape->setFillColor(sf::Color::Green);
		/*newshape->setOutlineColor(sf::Color::Red);
		newshape->setOutlineThickness(-1);*/

		newshape->setPointCount(sum);
		int nextcopyable = 0;
		for (int k = 0; k < sum; k++) {

			while (delablepoints[nextcopyable] != false) { //amig nem talál egy másolandót
				std::cout << "nem masoljuk bele az ujba:  index=" << nextcopyable << " koord: " << convex_v[i]->getPoint(nextcopyable).x << " " << convex_v[i]->getPoint(nextcopyable).y << "\n";
				nextcopyable++;
			}
			std::cout << "belemasoljuk a " << nextcopyable << " elemet a " << k << ".adik helyre \n";
			if (nextcopyable >= convex_v[i]->getPointCount()) { std::cout << "elbasztad mert tulfutott a copyable \n"; }
			newshape->setPoint(k, convex_v[i]->getPoint(nextcopyable));
			nextcopyable++;

		}
		sf::ConvexShape* temp = convex_v[i];
		convex_v[i] = newshape;
		delete temp;
	}
	else {
		for (int k = 0; k < convex_v[i]->getPointCount(); k++) {
			convex_v[i]->setPoint(k, sf::Vector2f(-1, -1));			
		}
		convex_v[i]->setPointCount(0);
		std::cout << currID << "kocka megsemmisult (igazabol nem) \n";
	
	}
	
}
//regebbi del_point, megtartom ha kéne
/*void Block::del_point(int i , int j) {
	float elottex;
	float elottey;
	if (j != 0) {

		elottex = convex_v[i]->getPoint(j - 1).x;
		elottey = convex_v[i]->getPoint(j - 1).y;
		std::cout<< "masolas trortenik, ezekrõl: "<< convex_v[i]->getPoint(j).x <<" "<< convex_v[i]->getPoint(j).y <<"erre: "<<elottex<<" "<<elottey<<"\n";
		convex_v[i]->setPoint(j, convex_v[i]->getPoint(j - 1));
		std::cout << "ket pont ugyanolyan lett, a " << j << "pont lett ugyanolyan mint a " << j - 1 << std::endl;
		std::cout << "uj adatok: " << convex_v[i]->getPoint(j).x << " " << convex_v[i]->getPoint(j).y << "\n";
	}
	else {

		elottex = convex_v[i]->getPoint(j + 1).x;
		elottey = convex_v[i]->getPoint(j + 1).y;
		std::cout << "masolas trortenik, ezekrõl: " << convex_v[i]->getPoint(j).x << " " << convex_v[i]->getPoint(j).y << "erre: " << elottex << " " << elottey << "\n";

		convex_v[i]->setPoint(0, convex_v[i]->getPoint(j + 1));
		std::cout << "ket pont ugyanolyan lett, a " << j << "pont lett ugyanolyan mint a " << j + 1 << std::endl;
	
		std::cout << "uj adatok: " << convex_v[i]->getPoint(0).x << " " << convex_v[i]->getPoint(0).y << "\n";
	}
	

}*/


/*
todo2: eltolni nem kellene hagyni a kockát. eddig csak az eredeti kockából nem mehet ki, de mindig a saját határain belül kellene módosulnia. 
kérdés: hogy a faszba kell egy random sokszöget csekkolni hogy benne van e a pont vagy nem? kurva nehezen -> kis kockák kellenek, maximum a robbanás sugarának fele
solution: csökkentem a bounding negyzetet-> még mindig nem elég jó, de már valami

*/

void Block::modify_coords(sf::Vector2f expl, float &newx, float &newy, sf::Vector2f pos ,float r ) {
	int d = d_to_center(pos, expl);
	sf::Vector2f firstmodified(expl.x + (pos.x - expl.x)*r / d, expl.y + (pos.y - expl.y)*r / d);
	//std::cout << "firstoffsetek: " << firstoffset.x << " " << firstoffset.y << "\n";
	//std::cout<< "expl: "<<  expl.x << " " << expl.y << "\n";
	if (firstmodified.x > Xmin &&   firstmodified.x < Xmax) { // firstoffset
	
			newx =  firstmodified.x;
		//	std::cout << " az uj x benne van a negyszogben \n";
		if ( firstmodified.y > Ymin &&  firstmodified.y < Ymax) {
			
		//	std::cout << " az uj y benne van a negyszogben \n";
			newy =  firstmodified.y;		
			return;
		}
		else {
		//	std::cout << " az uj y nincs benne  a negyszogben \n";
			newy = pos.y;
			float b = 2 * pos.x - 2 * expl.x;
			float c = powf((pos.x - expl.x) , 2) - powf(r , 2) + powf((pos.y - expl.y) , 2);
			sf::Vector2f roots( (-b+powf( powf(b , 2) - 4*c ,0.5))/2 , (-b - powf(powf(b, 2) - 4*c, 0.5)) / 2);
		//	std::cout << "xbenne y nem -> y gyokok: " << roots.x << " " << roots.y << " b: " << b << " c: " << c << "\n";
			if (firstmodified.x -pos.x> 0) {
				newx = pos.x+fmaxf(roots.x, roots.y);
			}
			else {
				newx= pos.x+fmaxf(roots.x, roots.y);
			}
			if (!(newx >= x && newx <= x + width)) {
				newx = pos.x;
			//	std::cout << " az uj y gyokjei nincsenek benne van a negyszogben \n";
			}
		
		}

	}
	else {
		//std::cout << " az uj x nincsenek benne  a negyszogben \n";
		newx = pos.x;
		float b = 2 * pos.y - 2 * expl.y;
		float c = powf((pos.y - expl.y), 2) - powf(r, 2) + powf((pos.x - expl.x), 2);
		sf::Vector2f roots((-b + powf(powf(b, 2) - 4 * c, 0.5)) / 2, (-b - powf(powf(b, 2) - 4 * c, 0.5)) / 2);
	//	std::cout << "xnincsbenneszelrelettrakva y benne lehet -> y gyokok: " << roots.x << " " << roots.y <<" b: "<<b << " c: "<<c<<"\n";
		if (firstmodified.y-pos.y >= 0) {
			newy =pos.y+ fmaxf(roots.x, roots.y);
		}
		else {
			newy =pos.y+ fminf(roots.x, roots.y);
		}

		if ( newy > Ymin &&  newy < Ymax) {
		//	std::cout << " az uj y benne van a negyszogben \n";			

		}
		else {

		//	std::cout << "  egyikse van a negyszogben \n";
			
			newy = pos.y;
			

		}
	
		
	
	}


}

// r most csak constans. spelltõl független még 
//random néha elszállnak pontok, furi

bool Block::caught_by_expl(sf::Vector2f expl)
{

	int c=0;
	int d = 0;
	int r = 100;
	float newx;
	float newy;
	std::vector<bool> delable;
	for (int i = 0; i < convex_v.size(); i++) {
		delable.clear();
		delable.resize(convex_v[i]->getPointCount(), false);
		for(int j=0 ; j<(int)convex_v[i]->getPointCount();j++){
			d = d_to_center(convex_v[i]->getPoint(j), expl);
			if (d<r) {   //robbanássugár
				modify_coords(expl, newx, newy, convex_v[i]->getPoint(j) , r );
				
				if (newx == convex_v[i]->getPoint(j).x && newy == convex_v[i]->getPoint(j).y) {
					//std::cout << newx << " " << convex_v[i]->getPoint(j).x << " y: " << newy << " " << convex_v[i]->getPoint(j).y << "\n";
					delable[j] = true;
				}
				else {
					set_block_point(i, j, newx, newy);
					refresh_bounds(i);
					std::cout << "modosult a " << currID << ". kocka " << j << ". edik pontja" << newx << " " << newy << std::endl;
				}
				newx = newy = 0;
				
			}			
		}
		del_point(i, delable);
	}
	
	
	
	return c>0;
}

int Block::ID = 0;