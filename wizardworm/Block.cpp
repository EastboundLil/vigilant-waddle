#include "Block.h"
#include <iostream>
#include <algorithm>
#include <sstream>

Block::Block(sf::RenderWindow *w)
{
	window = w;	
	currID = ++ID;	
	Alive = true;
	destructible = true;
}



Block::Block(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w )
	:Drawable(_x, _y, c)
{
	height = _h;
	width = _w;
	currID = ++ID;
	window = w;
	Alive = true;
	destructible = true;
	convex_v=std::make_shared<sf::ConvexShape>();


	
	
	Xmin = x;
	Xmax = x + width;
	Ymin = y;
	Ymax = y + height;

	
	set_res(16);

	convex_v->setFillColor(c);
	convex_v->setOutlineColor(sf::Color::Red);
	convex_v->setOutlineThickness(-1);


}

Block::Block(float _x, float _y, sf::Color c, float _h, float _w, sf::RenderWindow *w , int n , std::vector<sf::Vector2f> p , bool d)
	:Drawable(_x, _y, c)
{
	height = _h;
	width = _w;
	currID = ++ID;
	window = w;
	Alive = true;
	destructible = d;
	convex_v = std::make_shared<sf::ConvexShape>();


	if (p.size() == n) {
		convex_v->setPointCount(n);
		for (int i = 0; i < convex_v->getPointCount(); i++) {
			convex_v->setPoint(i, p[i]);
		}
	}
	
	refresh_bounds();

	convex_v->setFillColor(c);
	convex_v->setOutlineColor(sf::Color::Red);
	convex_v->setOutlineThickness(-1);

}


Block::~Block()
{
	
}

void Block::set_res(int res) {
	if (res == 8) {
		convex_v->setPointCount(8);
		convex_v->setPoint(0, sf::Vector2f(x, y));
		convex_v->setPoint(1, sf::Vector2f(x + width / 2, y));
		convex_v->setPoint(2, sf::Vector2f(x + width, y));
		convex_v->setPoint(3, sf::Vector2f(x + width, y + height / 2));
		convex_v->setPoint(4, sf::Vector2f(x + width, y + height));
		convex_v->setPoint(5, sf::Vector2f(x + width / 2, y + height));
		convex_v->setPoint(6, sf::Vector2f(x, y + height));
		convex_v->setPoint(7, sf::Vector2f(x, y + height / 2));
	}
	else if (res == 16) {
	
		convex_v->setPointCount(16);
		convex_v->setPoint(0, sf::Vector2f(x, y));
		convex_v->setPoint(1, sf::Vector2f(x + width / 4, y));
		convex_v->setPoint(2, sf::Vector2f(x + width / 2, y));
		convex_v->setPoint(3, sf::Vector2f(x + width * 3 / 4, y));
		convex_v->setPoint(4, sf::Vector2f(x + width, y));
		convex_v->setPoint(5, sf::Vector2f(x + width, y + height / 4));
		convex_v->setPoint(6, sf::Vector2f(x + width, y + height / 2));
		convex_v->setPoint(7, sf::Vector2f(x + width, y + 3 * height / 4));
		convex_v->setPoint(8, sf::Vector2f(x + width, y + height));
		convex_v->setPoint(9, sf::Vector2f(x + 3 * width / 4, y + height));
		convex_v->setPoint(10, sf::Vector2f(x + width / 2, y + height));
		convex_v->setPoint(11, sf::Vector2f(x + width / 4, y + height));
		convex_v->setPoint(12, sf::Vector2f(x, y + height));
		convex_v->setPoint(13, sf::Vector2f(x, y + 3 * height / 4));
		convex_v->setPoint(14, sf::Vector2f(x, y + height / 2));
		convex_v->setPoint(15, sf::Vector2f(x, y + height / 4));
	
	
	}


}

void Block::draw() {
		window->draw(*convex_v);	
}





std::string Block::write_data() //returned data: "<posx> <posy> <ndbpont> <width> <height> <color_r> <color_g> <color_b> <destructible> <x1> <y1> <x2> <y2> ... <xn> <yn> "
{
	std::stringstream ss;
	
	ss <<x<<" "<<y<<" "<< convex_v->getPointCount() << " "<<width<<" "<<height<<" "<<(int)convex_v->getFillColor().r <<" "<<(int)convex_v->getFillColor().g << " "<<(int)convex_v->getFillColor().b<<" "<<destructible ;
	for (size_t i = 0; i < convex_v->getPointCount(); i++) {
		ss <<" "<< convex_v->getPoint(i).x << " " << convex_v->getPoint(i).y;
	}

	return ss.str();
}



int d_to_center(sf::Vector2f blocpoint, sf::Vector2f expl) {
	
	return  pow((pow((blocpoint.x - expl.x), 2) + pow((blocpoint.y - expl.y), 2)), 0.5f);
	
	
}

float Block::check_bound(float _x , int p , float old) { 											
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

float distance(sf::Vector2f p1, sf::Vector2f p2) {
	return pow(pow(p1.x - p2.x, 2.0f) + pow(p1.y - p2.y, 2.0f), 0.5);
}

struct Line {
	sf::Vector2f p1;
	sf::Vector2f p2;

	bool contains(sf::Vector2f point) const {
		float margin = 0.01;
		return std::abs((distance(p1, point) + distance(point, p2)) - distance(p1, p2)) < margin;
	}
};

sf::Vector2f intersection(Line lineA, Line lineB) {
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
	catch (std:: exception) {
		
		throw new std::exception("");
	}
}

std::vector<sf::Vector2f> getIntersectionPoints(sf::ConvexShape shape, sf::Vector2f point) {
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
			p = intersection(shapeLine, pointLine);
			if (crossingLine && shapeLine.contains(p))
				intersectPoints.push_back(p);
		}
		catch (std::runtime_error e) {
			std::cout << "error \n";
		}
	}

	return intersectPoints;
}

bool Block::contains( sf::Vector2f point) {
	
	std::vector<sf::Vector2f> intersectPoints = getIntersectionPoints(*convex_v, point);
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










void Block::refresh_bounds()
{
	float xmin = convex_v->getPoint(0).x;
	float ymin = convex_v->getPoint(0).y;
	float ymax = ymin;
	float xmax = xmin;

	for (int j = 0; j < convex_v->getPointCount(); j++) {
		if (convex_v->getPoint(j).x > xmax) {
			xmax = convex_v->getPoint(j).x;
		}
		if (convex_v->getPoint(j).x < xmin) {
			xmin = convex_v->getPoint(j).x;
		}
		if (convex_v->getPoint(j).y > ymax) {
			ymax = convex_v->getPoint(j).y;
		}
		if (convex_v->getPoint(j).y < ymin) {
			ymin = convex_v->getPoint(j).y;
		}
	}
	Xmax = xmax;
	Xmin = xmin;
	Ymax = ymax;
	Ymin = ymin;

}

void Block::del_point( std::vector<bool> delablepoints) {

	int sum=0;
	for (int j = 0; j < delablepoints.size(); j++) {
		if (delablepoints[j] == false) { sum++; }
		//else { std::cout << "torlendo pont: index=" << j << " koord: " << convex_v[i]->getPoint(j).x << " " << convex_v[i]->getPoint(j).y << "\n"; }
		
	}
	
	if (sum == convex_v->getPointCount()) { return; }
	//std::cout << "maradando pontok: " << sum<<"\n";
	if (sum > 2) {
		std::shared_ptr<sf::ConvexShape> newshape = std::make_shared<sf::ConvexShape>();
		newshape->setFillColor(color);
		newshape->setOutlineColor(sf::Color::Red);
		newshape->setOutlineThickness(-1);

		newshape->setPointCount(sum);
		int nextcopyable = 0;
		for (int k = 0; k < sum; k++) {

			while (delablepoints[nextcopyable] != false) { //amig nem talál egy másolandót
				//std::cout << "nem masoljuk bele az ujba:  index=" << nextcopyable << " koord: " << convex_v[i]->getPoint(nextcopyable).x << " " << convex_v[i]->getPoint(nextcopyable).y << "\n";
				nextcopyable++;
			}
			//std::cout << "belemasoljuk a " << nextcopyable << " elemet a " << k << ".adik helyre \n";
			if (nextcopyable >= convex_v->getPointCount()) { std::cout << "elbasztad mert tulfutott a copyable \n"; }
			newshape->setPoint(k, convex_v->getPoint(nextcopyable));
			nextcopyable++;

		}
		std::shared_ptr<sf::ConvexShape> temp = convex_v;
		convex_v = newshape;
		
	}
	else {
		for (int k = 0; k < convex_v->getPointCount(); k++) {
			convex_v->setPoint(k, sf::Vector2f(-1, -1));			
		}
		convex_v->setPointCount(0);

		
			if (convex_v->getPointCount() != 0) {
				return;
			}
		
		Alive = false;
		
		
	
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

kérdés: hogy a faszba kell egy random sokszöget csekkolni hogy benne van e a pont vagy nem? kurva nehezen -> kis kockák kellenek, maximum a robbanás sugarának fele
solution: csökkentem a bounding negyzetet-> még mindig nem elég jó, de már valami
TODO: talaltam egy jó algoritmust, a belekattintást már azzal nézem, ha van idõm a modifykoordsot is csinálom
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

bool Block::caught_by_expl(sf::Vector2f expl , float r)
{
	if (destructible) {
		int c = 0;
		int d = 0;
		float newx;
		float newy;
		std::vector<bool> delable;
		
			delable.clear();
			delable.resize(convex_v->getPointCount(), false);
			for (int j = 0; j < (int)convex_v->getPointCount(); j++) {
				d = d_to_center(convex_v->getPoint(j), expl);
				if (d < r) {   //robbanássugár
					modify_coords(expl, newx, newy, convex_v->getPoint(j), r);

					if (newx == convex_v->getPoint(j).x && newy == convex_v->getPoint(j).y) {
						//std::cout << newx << " " << convex_v[i]->getPoint(j).x << " y: " << newy << " " << convex_v[i]->getPoint(j).y << "\n";
						delable[j] = true;
					}
					else {
						convex_v->setPoint(j , sf::Vector2f(newx,newy));
						refresh_bounds();
						//std::cout << "modosult a " << currID << ". kocka " << j << ". edik pontja" << newx << " " << newy << std::endl;
					}
					newx = newy = 0;

				}
			}
			del_point( delable);
		

		return c > 0;
	}
	return false;
}

bool Block::is_alive()
{
	return Alive;
}


void Block::set_destructible(sf::Vector2i pos, bool destr)
{
	
		std::cout << "Benne \n";
		destructible = destr;
		if (!destr) {
			convex_v->setFillColor(sf::Color::Black);
		}
		else {
			convex_v->setFillColor(sf::Color(92, 51, 23, 255));
		}
	
}



int Block::ID = 0;