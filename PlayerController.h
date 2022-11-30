#pragma once
#include "Item.h"
#include <vector>

class PlayerController
{
public:
	void mainloop(double x, double y, Player& player, float time, std::vector<Item>& items, std::map<int, int>& it_ht, double& timer);
};

class IIController
{
public:
	void mainloop(Player& player, II& ii, float time);
};

