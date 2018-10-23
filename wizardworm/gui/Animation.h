#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	bool isLive;
	float totalTime;
	float switchTime;
public:
	Animation(sf::Texture* texture,sf::Vector2u imageCount,float switchTime);
	~Animation();

	sf::IntRect uvRect;
	void Update(float deltaTime);
};

