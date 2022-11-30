#include "Inventory.h"

void Inventory::Draw(sf::RenderWindow& window)
{
	sf::Vector2f center = window.getView().getCenter();
	sf::Vector2f size = window.getView().getSize();

	s1 = s_Inv;
	s2 = s_Inv;
	s3 = s_Inv;
	s4 = s_Inv;
	s5 = s_Inv;
	s1.setPosition(center.x - 160, size.y - 64);
	s2.setPosition(center.x - 96, size.y - 64);
	s3.setPosition(center.x - 32, size.y - 64);
	s4.setPosition(center.x + 32, size.y - 64);
	s5.setPosition(center.x + 96, size.y - 64);
	if (n1 > 0) { s1.setTextureRect(sf::IntRect(0, 0, 64, 64));  } else { s1.setTextureRect(sf::IntRect(0, 64, 64, 64)); }
	if (n2 > 0) { s2.setTextureRect(sf::IntRect(64, 0, 64, 64)); } else { s2.setTextureRect(sf::IntRect(64, 64, 64, 64)); }
	if (n3 > 0) { s3.setTextureRect(sf::IntRect(128, 0, 64, 64)); } else { s3.setTextureRect(sf::IntRect(128, 64, 64, 64)); }
	if (n4 > 0) { s4.setTextureRect(sf::IntRect(192, 0, 64, 64)); } else { s4.setTextureRect(sf::IntRect(192, 64, 64, 64)); }
	if (n5 > 0) { s5.setTextureRect(sf::IntRect(256, 0, 64, 64)); } else { s5.setTextureRect(sf::IntRect(256, 64, 64, 64)); }

	t1.setString(std::to_string(n1));
	t1.setPosition(center.x - 155, size.y - 22);
	t2.setString(std::to_string(n2));
	t2.setPosition(center.x - 91, size.y - 22);
	t3.setString(std::to_string(n3));
	t3.setPosition(center.x - 27, size.y - 22);
	t4.setString(std::to_string(n4));
	t4.setPosition(center.x + 37, size.y - 22);
	t5.setString(std::to_string(n5));
	t5.setPosition(center.x + 105, size.y - 22);

	window.draw(s1);
	window.draw(t1);
	window.draw(s2);
	window.draw(t2);
	window.draw(s3);
	window.draw(t3);
	window.draw(s4);
	window.draw(t4);
	window.draw(s5);
	window.draw(t5);
}

void Inventory::Inc1()
{
	n1++;
}

void Inventory::Inc2()
{
	n2++;
}

void Inventory::Inc3()
{
	n3++;
}

void Inventory::Inc4()
{
	n4++;
}

void Inventory::Inc5()
{
	n5++;
}

void Inventory::Minus1(int n)
{
	if (this->n1 > n) { this->n1 -= n; }	else { this->n1 = 0; }
}

void Inventory::Minus2(int n)
{
	if (this->n2 > n) {this->n2 -= n;}	else { this->n2 = 0; }
}

void Inventory::Minus3(int n)
{
	if (n3 > n) { n3 -= n; }	else { n3 = 0; }
}

void Inventory::Minus4(int n)
{
	if (n4 > n) { n4 -= n; } else { n4 = 0; }
}

void Inventory::Minus5(int n)
{
	if (n5 > n) { n5 -= n; } else { n5 = 0; }
}

Inventory::Inventory()
{
	n1 = 0; n2 = 0; n3 = 0; n4 = 0; n5 = 0;

	Inv.loadFromFile("images/Fruits_GUI.png");
	s_Inv.setTexture(Inv);

	font.loadFromFile("Font/CyrilicOld.ttf");
	t1.setCharacterSize(20);
	t1.setFont(this->font);
	t1.setFillColor(sf::Color::Blue);
	t2.setCharacterSize(20);
	t2.setFont(this->font);
	t2.setFillColor(sf::Color::Blue);
	t3.setCharacterSize(20);
	t3.setFont(this->font);
	t3.setFillColor(sf::Color::Blue);
	t4.setCharacterSize(20);
	t4.setFont(this->font);
	t4.setFillColor(sf::Color::Blue);
	t5.setCharacterSize(20);
	t5.setFont(this->font);
	t5.setFillColor(sf::Color::Blue);
}
