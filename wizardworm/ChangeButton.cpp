#include "ChangeButton.h"



ChangeButton::ChangeButton(float posx, float posy, float width, float height, sf::Color color, sf::Color c2, std::string t1,std::string t2 ,  sf::RenderWindow *w, std::function<bool()> action)
	:Button(posx, posy,width,height,color,t1,w,action) , t2(t2) , c2(c2)
{
	text.setPosition(posx+width/2 - 0.4*fmax(t.size(), t2.size())*width / fmax(t.size(), t2.size()), posy + height / 2 - 1.6 * width / fmax(t.size(), t2.size()));
	text.setCharacterSize(2 * width / fmax(t.size(),t2.size()));
	circle.setFillColor(c2);
}



ChangeButton::~ChangeButton()
{
}

void ChangeButton::change(bool t) {
	chooser = t;
}

void ChangeButton::make_action() {

	change(action());
}

void ChangeButton::draw() {

	if (chooser) {
		
		window->draw(rect);
		text.setString(t);
		text.setFont(font);
		window->draw(text);

	}
	else {
		window->draw(circle);
		text.setString(t2);
		text.setFont(font);
		window->draw(text);
	
	}

}