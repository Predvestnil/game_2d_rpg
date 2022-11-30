#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>



class Item
{
public:
	int num_item;
	sf::Sprite herosprite;
	Item(int num_item, int x, int y, sf::Texture& texture);
	~Item();
	friend bool operator==(const Item& lhs, const Item& rhs);
};

