#include "Enemy.h"
#include "Item.h"
#include <iostream>
#include "Inventory.h"

Enemy::Enemy(double x, double y,double h, double st, double sp, bool isMove = false)
{
	this->herosprite.setPosition(x, y);
	this->max_health = h;
	this->SetHealth(h);
	this->SetSpeed(sp);
	this->SetMove(isMove);
	this->SetNapr(x, y);
}

double Enemy::GetHealth()
{
	return this->health;
}

double Enemy::GetSpeed()
{
	return this->speedx;
}

double Enemy::GetMaxHealth()
{
	return this->max_health;
}

void Enemy::SetCoordTo(double x, double y)
{
	this->tox = x;
	this->toy = y;
}

void Enemy::SetHealth(double h)
{
	this->health = h;
}

void Enemy::SetSpeed(double s)
{
	this->speedx = s;
}

void Enemy::SetMove(bool isMove)
{
	this->isMove = isMove;
}

void Enemy::SetNapr(double dx, double dy)
{
	double x = this->getplayercoordinateX(), y = this->getplayercoordinateY();
	this->napr = sf::Vector2f(dx-x, dy-y);
}

void Enemy::Move(double x, double y, float time)
{
	int TempX = this->getplayercoordinateX();
	int TempY = this->getplayercoordinateY();
	this->CurrentFrame += 0.1 * time * this->GetSpeed(); //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
	if (this->CurrentFrame > 2) this->CurrentFrame = 0; // если пришли к третьему кадру - откидываемся назад.
	this->herosprite.setTextureRect(sf::IntRect(64 * int(this->CurrentFrame), 0, 64, 64)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
	this->herosprite.setRotation((atan2(TempY-y, TempX-x)) * 180 / 3.14159265 - 180);
	double distance = sqrt((x - TempX) * (x - TempX) + (y - TempY) * (y - TempY));//считаем дистанцию (длину от точки А до точки Б). формула длины вектора
	if (distance > 5) {//этим условием убираем дергание во время конечной позиции спрайта
		double tx = this->GetSpeed() * time * (x - TempX) / distance, ty = this->GetSpeed() * time * (y - TempY) / distance;
		this->herosprite.move(tx, ty);//идем
	}
	else { this->SetMove(false);}//говорим что уже никуда не идем и выводим веселое сообщение в консоль
}

void Enemy::update(float time)
{
	int TempX = this->getplayercoordinateX();
	int TempY = this->getplayercoordinateY();
	int X = this->herosprite.getPosition().x;
	int Y = this->herosprite.getPosition().y;
	this->herosprite.move(TempX - X, TempY - Y);
}

void Enemy::debug()
{
	//std::cout << "Health: " << this->GetHealth() << "\n";
}

double Enemy::getplayercoordinateX() {
	return this->herosprite.getPosition().x;
}

double Enemy::getplayercoordinateY() {
	return this->herosprite.getPosition().y;
}

double Enemy::getplayercoordinateToX()
{
	return this->tox;
}

double Enemy::getplayercoordinateToY()
{
	return this->toy;
}

sf::Vector2f Enemy::getnapr()
{
	return this->napr;
}

bool Enemy::isMovef()
{
	return this->isMove;
}

Player::Player(double x, double y, double h, double st, double sp, bool isMove)
	: Enemy(x,y,h,st,sp,isMove)
{
	this->herotexture.loadFromFile("images/Hero.png");
	this->herosprite.setTexture(this->herotexture);
	this->herosprite.setTextureRect(sf::IntRect(0, 0, 64, 64));//получили нужный нам прямоугольник с котом
	this->herosprite.setOrigin(32, 32);
	CurrentFrame = 0;
	this->SetisTaking(false);
	this->SetIsWin(false);
}

void Player::TakeUp(std::vector<Item>& items)
{
	for (auto it = std::begin(items); it != std::end(items); ++it)
		if ((*it).herosprite.getGlobalBounds().intersects(this->herosprite.getGlobalBounds())) //добавить проверку есть ли место для фрукта
		{
			if((*it).num_item == 1 && this->inv.n1<16) this->inv.Inc1();
			if ((*it).num_item == 2 && this->inv.n2 < 16) this->inv.Inc2();
			if ((*it).num_item == 3 && this->inv.n3 < 16) this->inv.Inc3();
			if ((*it).num_item == 4 && this->inv.n4 < 16) this->inv.Inc4();
			if ((*it).num_item == 5 && this->inv.n5 < 16) this->inv.Inc5();
			items.erase(it);
			break;
		}
	this->SetisTaking(false);
}

void Player::Set0()
{
	this->SetisTaking(false);
	this->SetMove(false);
	this->SetIsEat(0);
}

void Player::Eat(int number, std::map<int, int> it_ht)
{
	//проверка и удаление хавчика
	if (number == 1 && inv.n1 == 0) return;
	if (number == 2 && inv.n2 == 0) return;
	if (number == 3 && inv.n3 == 0) return;
	if (number == 4 && inv.n4 == 0) return;
	if (number == 5 && inv.n5 == 0) return;
	if (number == 1) inv.Minus1(1);
	if (number == 2) inv.Minus2(1);
	if (number == 3) inv.Minus3(1);
	if (number == 4) inv.Minus4(1);
	if (number == 5) inv.Minus5(1);
	this->SetHealth(this->GetHealth() + it_ht[number]);
	if (this->GetHealth() > this->GetMaxHealth()) this->SetHealth(this->GetMaxHealth());
}

bool Player::isTakingf()
{
	return this->isTaking;
}

void Player::SetisTaking(bool a)
{
	this->isTaking = a;
}

bool Player::GetIsWin() { return this->IsWin; }

void Player::SetIsWin(bool a) { this->IsWin = a; }

int Player::IsEatf() { return this->isEat; }

void Player::SetIsEat(int n) { this->isEat = n; }

void Player::CycleOfLife(double time)
{
	if(this->GetHealth()>0) this->SetHealth(this->GetHealth() - 0.01 * time);
}

II::II(double x, double y, double h, double st, double sp, bool isMove)
	: Enemy(x,y,h, st, sp, isMove)
{
	CurrentFrame = 0;
	this->herotexture.loadFromFile("images/ii.png");
	this->herosprite.setTexture(this->herotexture);
	this->herosprite.setTextureRect(sf::IntRect(0, 0, 64, 64));//получили нужный нам прямоугольник с котом
	this->herosprite.setOrigin(32, 32);
	SetCoordTo(300, 50);
}

void II::Attack()
{
}
