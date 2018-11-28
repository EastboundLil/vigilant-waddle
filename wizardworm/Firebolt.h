#pragma once
#include "Spell.h"

class Firebolt :public Spell{
	sf::RenderWindow *window;
	float x_pos;
	float y_pos;
	sf::CircleShape FireboltImage;
	//ket animationjanak kell lennie. egy repulo loveg, meg az explosion , ha berobbant az explosion akkr szolni kell a windownak
	//hogy itt a mapot ki kell robbantani. ez lesz furi. talan van ilyen window->makeevent, és csinalunk sajatot


public:
	Firebolt(sf::RenderWindow *window, sf::Vector2f Pos) ;
	Firebolt(const Firebolt& f);
	//TODO: Firebolt(sf::RenderWindow *windom, sf::Vector2f startpos , float deg , float force);
	~Firebolt();
	void draw() override;
};

