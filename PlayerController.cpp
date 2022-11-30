#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "PlayerController.h"


void PlayerController::mainloop(double x, double y, Player& player, float time, std::vector<Item>& items, std::map<int, int>& it_ht, double& timer)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !player.isTakingf() && (x - 1280) < 0 && (y - 640) < 0)
	{
		player.herosprite.setOrigin(player.herosprite.getTextureRect().height / 2., player.herosprite.getTextureRect().width / 2.);
		player.SetMove(true);
		player.SetCoordTo(x, y);
		player.SetNapr(x,y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !player.isMovef())
	{
		player.SetisTaking(true);
		timer = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		player.Set0();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		timer = 0;
		player.SetIsEat(1);
	}
	if(player.IsEatf() == 1 && timer>30)
	{
		player.Eat(1, it_ht);
		player.SetIsEat(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		timer = 0;
		player.SetIsEat(2);
	}
	if (player.IsEatf() == 2 && timer > 30)
	{
		player.Eat(2, it_ht);
		player.SetIsEat(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		timer = 0;
		player.SetIsEat(3);
	}
	if (player.IsEatf() == 3 && timer > 30)
	{
		player.Eat(3, it_ht);
		player.SetIsEat(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		timer = 0;
		player.SetIsEat(4);
	}
	if (player.IsEatf() == 4 && timer > 30)
	{
		player.Eat(4, it_ht);
		player.SetIsEat(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		timer = 0;
		player.SetIsEat(5);
	}
	if (player.IsEatf() == 5 && timer > 30)
	{
		player.Eat(5, it_ht);
		player.SetIsEat(0);
	}
	if (player.isMovef()) { 
		player.Move(player.getplayercoordinateToX(), player.getplayercoordinateToY(), time); 
	}
	if (player.isTakingf()) {
		if (timer > 30) {
			player.TakeUp(items);
			timer = 0;
		}
	}
	if (player.inv.n1 == 16 && player.inv.n2 == 16 && player.inv.n3 == 16 && player.inv.n4 == 16 && player.inv.n5 == 16) player.SetIsWin(true);
	player.CycleOfLife(time);
	player.update(time);
}

void IIController::mainloop(Player& player, II& ii, float time)
{
	if ((ii.getplayercoordinateToX() != player.getplayercoordinateX() && ii.getplayercoordinateToY() != player.getplayercoordinateY()) && sqrt((ii.getplayercoordinateX() - player.getplayercoordinateX()) * (ii.getplayercoordinateX() - player.getplayercoordinateX()) + (ii.getplayercoordinateY() - player.getplayercoordinateY()) * (ii.getplayercoordinateY() - player.getplayercoordinateY())) < 500)
	{
		ii.herosprite.setOrigin(ii.herosprite.getTextureRect().height / 2., ii.herosprite.getTextureRect().width / 2.);
		ii.SetMove(true);
		ii.SetCoordTo(player.getplayercoordinateX(), player.getplayercoordinateY());
		ii.SetNapr(player.getplayercoordinateX(), player.getplayercoordinateY());
	} else	if (ii.isMovef()) {
		ii.Move(ii.getplayercoordinateToX(), ii.getplayercoordinateToY(), time);
	} else
	    if ((sqrt((ii.getplayercoordinateX() - 300) * (ii.getplayercoordinateX() - 300) + (ii.getplayercoordinateY() - 50) * (ii.getplayercoordinateY() - 50)) <= 5)) {
			ii.SetMove(true);
			ii.SetCoordTo(50, 50);
			ii.SetNapr(50, 50);
		}
		else {
			ii.SetMove(true);
			ii.SetCoordTo(300, 50);
			ii.SetNapr(300, 50);
		}
	player.update(time);
}
