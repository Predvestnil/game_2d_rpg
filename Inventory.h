#pragma once
#include <SFML/Graphics.hpp>
class Inventory
{
public:
	unsigned int n1, n2, n3, n4, n5;
	Inventory();
	void Draw(sf::RenderWindow& window);
	void Inc1();
	void Inc2();
	void Inc3();
	void Inc4();
	void Inc5();
	void Minus1(int);
	void Minus2(int);
	void Minus3(int);
	void Minus4(int);
	void Minus5(int);

private:
	sf::Texture Inv;
	sf::Sprite s_Inv, s1,s2,s3,s4,s5;
	sf::Font font;
	sf::Text t1, t2, t3, t4, t5;	
};

