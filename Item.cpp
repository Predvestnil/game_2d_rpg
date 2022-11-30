#include "Item.h"
#include <iostream>

Item::Item(int num_item, int x, int y, sf::Texture& texture)
{
	this->num_item = num_item;
	this->herosprite.setPosition(x, y);
	this->herosprite.setTexture(texture);
	this->herosprite.setTextureRect(sf::IntRect((num_item - 1) * 32, 0, 32, 32));
}

Item::~Item()
{
}

bool operator==(const Item& lhs, const Item& rhs)
{
	double distance = sqrt((lhs.herosprite.getPosition().x - rhs.herosprite.getPosition().x) * (lhs.herosprite.getPosition().x - rhs.herosprite.getPosition().x) + (lhs.herosprite.getPosition().y - rhs.herosprite.getPosition().y) * (lhs.herosprite.getPosition().y - rhs.herosprite.getPosition().y));
	return (distance<100);
}
