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
	//convex_v->setOutlineColor(sf::Color::Red);
	//convex_v->setOutlineThickness(-1);


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
	//convex_v->setOutlineColor(sf::Color::Red);
	//convex_v->setOutlineThickness(-1);

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
	for (int i = 0; i < convex_v->getPointCount(); i++) {
		ss <<" "<< convex_v->getPoint(i).x << " " << convex_v->getPoint(i).y;
	}
	ss << "\n";
	return ss.str();
}



int d_to_center(sf::Vector2f blocpoint, sf::Vector2f expl) {
	
	return  pow((pow((blocpoint.x - expl.x), 2) + pow((blocpoint.y - expl.y), 2)), 0.5f);
	
	
}

bool Block::check_bound(sf::Vector2f pos) { 											
	
	return pos.x >= Xmin && pos.x <= Xmax && pos.y <= Ymax && pos.y >= Ymin;
}


bool point_inside_an_ellipse(sf::Vector2f p ,sf::Vector2f c, sf::Vector2f r) {
	
	return ( powf(p.x - c.x, 2) / powf(r.x, 2) ) + (powf(p.y - c.y, 2) / powf(r.y, 2)) <= 1;

}

float distance(sf::Vector2f p1, sf::Vector2f p2) {
	return pow(pow(p1.x - p2.x, 2.0f) + pow(p1.y - p2.y, 2.0f), 0.5);
}

sf::Vector2f new_point(sf::Vector2f old, sf::Vector2f c, sf::Vector2f r) {

	while (!point_inside_an_ellipse(old, c, r)) {
		old.x = old.x +   (c.x - old.x) / distance(old, c);
		old.y = old.y +   (c.y - old.y) / distance(old, c);
	}
	return old;

	/*std::cout << "regi ami kint volt : " << old.x << " " << old.y << " center: " << c.x << " " << c.y << "sugarak: " << r.x << " " << r.y << "\n";
	//1.step: old and c defined line and c,r defined ellipse intersection:
	float m = (old.y-c.y)/(old.x-c.x);
	float bl =c.y-c.x*m;
	float a = 1 + powf((r.x*m) / r.y, 2);
	float be = powf(r.x / r.y, 2) * 2 * m*(bl - c.y) - 2 * c.x;
	float c1 = -powf(r.x, 2) + powf((r.x*c.x) / r.y, 2) - powf(r.x / r.y, 2) * 2 * bl*c.y + powf(c.x, 2) + powf((r.x*bl) / r.y, 2);

	

	sf::Vector2f x(((-be + powf(powf(be, 2) - 4*c1*a, 0.5)) / 2*a), (-be - powf(powf(be, 2) - 4 * c1*a, 0.5)) / 2*a);
	sf::Vector2f y(m*x.x + bl, m*x.y + bl);

	std::cout << "uj lehets�ges pontok: " << x.x << " " << y.x << " es: " << x.y << " " << y.y << "\n";


	if (distance(old, sf::Vector2f(x.x, y.x)) < distance(old, sf::Vector2f(x.y, y.y))) {
		std::cout << "v�lasztott: " << x.x << " " << y.x << "\n";
		return sf::Vector2f(x.x, y.x);
	}
	else {
		std::cout << "v�lasztott: " << x.y << " " << y.y << "\n";
		return sf::Vector2f(x.y, y.y);
	}*/
	
	

	
}

bool Block::inside_an_ellipse(sf::Vector2f c, sf::Vector2f r)
{
	std::vector<int> bad;

	for (int i = 0; i < convex_v->getPointCount(); i++) {
		if (!point_inside_an_ellipse(convex_v->getPoint(i), c, r)) {
			bad.push_back(i);
		}		
	}
	if (bad.size() == convex_v->getPointCount()) { return false; }
	else if (bad.size() == 0) { return true; }

	for (int i = 0; i < bad.size(); i++) {
		convex_v->setPoint(bad[i] , new_point(convex_v->getPoint(bad[i]) , c , r));
	}
	
	//convex_v->setPoint(0, new_point(convex_v->getPoint(0), c, r));


	return true;
}

std::vector<sf::Vector2f> Block::get_points()
{
	std::vector<sf::Vector2f> t;

	for (int i = 0; i<convex_v->getPointCount(); i++) {
		t.push_back(convex_v->getPoint(i));
	}

	return t;
}



struct Line {
	sf::Vector2f p1;
	sf::Vector2f p2;

	bool contains(sf::Vector2f point) const {
		float margin = 0.5;
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
		//newshape->setOutlineColor(sf::Color::Red);
		//newshape->setOutlineThickness(-1);

		newshape->setPointCount(sum);
		int nextcopyable = 0;
		for (int k = 0; k < sum; k++) {

			while (delablepoints[nextcopyable] != false) { //amig nem tal�l egy m�soland�t
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
//regebbi del_point, megtartom ha k�ne
/*void Block::del_point(int i , int j) {
	float elottex;
	float elottey;
	if (j != 0) {

		elottex = convex_v[i]->getPoint(j - 1).x;
		elottey = convex_v[i]->getPoint(j - 1).y;
		std::cout<< "masolas trortenik, ezekr�l: "<< convex_v[i]->getPoint(j).x <<" "<< convex_v[i]->getPoint(j).y <<"erre: "<<elottex<<" "<<elottey<<"\n";
		convex_v[i]->setPoint(j, convex_v[i]->getPoint(j - 1));
		std::cout << "ket pont ugyanolyan lett, a " << j << "pont lett ugyanolyan mint a " << j - 1 << std::endl;
		std::cout << "uj adatok: " << convex_v[i]->getPoint(j).x << " " << convex_v[i]->getPoint(j).y << "\n";
	}
	else {

		elottex = convex_v[i]->getPoint(j + 1).x;
		elottey = convex_v[i]->getPoint(j + 1).y;
		std::cout << "masolas trortenik, ezekr�l: " << convex_v[i]->getPoint(j).x << " " << convex_v[i]->getPoint(j).y << "erre: " << elottex << " " << elottey << "\n";

		convex_v[i]->setPoint(0, convex_v[i]->getPoint(j + 1));
		std::cout << "ket pont ugyanolyan lett, a " << j << "pont lett ugyanolyan mint a " << j + 1 << std::endl;
	
		std::cout << "uj adatok: " << convex_v[i]->getPoint(0).x << " " << convex_v[i]->getPoint(0).y << "\n";
	}
	

}*/


/*

k�rd�s: hogy a faszba kell egy random soksz�get csekkolni hogy benne van e a pont vagy nem? kurva nehezen -> kis kock�k kellenek, maximum a robban�s sugar�nak fele
solution: cs�kkentem a bounding negyzetet-> m�g mindig nem el�g j�, de m�r valami
TODO: talaltam egy j� algoritmust, a belekattint�st m�r azzal n�zem, ha van id�m a modifykoordsot is csin�lom
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

// r most csak constans. spellt�l f�ggetlen m�g 
//random n�ha elsz�llnak pontok, furi

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
				if (d < r) {   //robban�ssug�r
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

/*
bool Block::laser_exp(sf::Vector2f pos,float deg) {

	float y;
	for (float i = 0; i < 100; i+=25) {
		y = tan(deg);
		std::cout << y << " y position" <<y+pos.y<< " y plus worm positon"<< std::endl;
		caught_by_expl(sf::Vector2f((i + pos.x), y + pos.y), 50);
	}
}
*/

bool Block::is_alive()
{
	return Alive;
}


void Block::set_destructible( bool destr)
{
	
		
		destructible = destr;
		if (!destr) {
			convex_v->setFillColor(sf::Color::Black);
		}
		else {
			convex_v->setFillColor(sf::Color(92, 51, 23, 255));
		}
	
}



int Block::ID = 0;