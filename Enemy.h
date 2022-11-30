#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"
#include <vector>
#include "Inventory.h"
class Enemy
{
private:
	sf::Vector2f napr;
	double health, speedx,tox,toy, max_health;
	bool isMove;
public:
	float CurrentFrame;
	sf::Texture herotexture;
	sf::Sprite herosprite;
	Enemy(double x, double y, double h, double st, double sp, bool isMove);
	double GetHealth();
	double GetSpeed();
	double GetMaxHealth();
	double getplayercoordinateX();
	double getplayercoordinateY();
	double getplayercoordinateToX();
	double getplayercoordinateToY();
	sf::Vector2f getnapr();
	bool isMovef();
	void SetCoordTo(double x, double y);
	void SetHealth(double h);
	void SetSpeed(double s);
	void SetMove(bool isMove);
	void SetNapr(double dx, double dy);
	//double GetDamage(double damage);
	void Move(double x, double y, float time);
	void update(float time);
	void debug();
};


class Player : public Enemy
{
private:
	bool isTaking, IsWin;
	int isEat;
public:
	Inventory inv;
	Player(double x, double y, double h, double st, double sp, bool isMove);
	void TakeUp(std::vector<Item>& items);
	void Set0();
	void Eat(int number, std::map<int, int> it_ht);
	bool isTakingf();
	void SetisTaking(bool);
	int IsEatf();
	void SetIsEat(int);
	bool GetIsWin();
	void SetIsWin(bool);
	void CycleOfLife(double time);
};

class II : public Enemy
{
public:
	II(double x, double y, double h, double st, double sp, bool isMove);
	void Attack();
};

