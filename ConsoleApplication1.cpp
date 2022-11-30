#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enemy.h"
#include "PlayerController.h"
#include "Item.h"
#include "iostream"
#include "map.h"
#include <vector>
#include <time.h>
#include <dos.h>

using namespace sf;

int rand_seed = 0;


void drawMap(RenderWindow& window)
{
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	//Рисовка карты
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(32, 0, 32, 32));  //тайл обычного песка
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(0, 32, 32, 32));  //тайл зыбучего песка
			if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(0, 0, 32, 32));    //тайл контура озера
			if (TileMap[i][j] == 'l') s_map.setTextureRect(IntRect(32, 32, 32, 32));  //тайл озера
			s_map.setPosition(j * 32, i * 32);

			window.draw(s_map);
		}
}

void interactionWithMap(Player& pl, II& ii)//ф-ция взаимодействия с картой
{
	int i = pl.getplayercoordinateX() / 32, j = pl.getplayercoordinateY() / 32;
	if (j < height && i < width && i >= 0 && j >= 0)
		if (TileMap[j][i] == 's')//если персонаж в зыбучих песках
		{
			pl.SetSpeed(1);
		}
		else if (TileMap[j][i] == 'l')//если персонаж в воде
		{
			pl.SetSpeed(2);
		}
		else { pl.SetSpeed(5); }
	i = ii.getplayercoordinateX() / 32, j = ii.getplayercoordinateY() / 32;
	if (j < height && i < width && i >= 0 && j >= 0)
		if (TileMap[j][i] == 's')//если персонаж в зыбучих песках
		{
			ii.SetSpeed(0.3);
		}
		else if (TileMap[j][i] == 'l')//если персонаж в воде
		{
			ii.SetSpeed(0.6);
		}
		else { ii.SetSpeed(1); }
}

void drawMenu(RenderWindow& window)
{
	//�������� ����
	Texture NameOfGame;
	NameOfGame.loadFromFile("images/NameOfGame.png");
	Sprite NOG(NameOfGame);
	NOG.setPosition(300, 30);

	//������ "Play"
	Image Button1_image;
	Button1_image.loadFromFile("images/Button1.png");
	Button1_image.createMaskFromColor(Color(0, 0, 0));
	Texture Button1;
	Button1.loadFromImage(Button1_image);
	Sprite Play;
	Play.setTexture(Button1);
	Play.setPosition(500, 200);

	//������  "About Game"
	Image Button2_image;
	Button2_image.loadFromFile("images/Button2.png");
	Button2_image.createMaskFromColor(Color(0, 0, 0));
	Texture Button2;
	Button2.loadFromImage(Button2_image);
	Sprite AboutGame;
	AboutGame.setTexture(Button2);
	AboutGame.setPosition(500, 350);

	Texture About;
	About.loadFromFile("images/AboutGame.png");
	Sprite TextAboutGame(About);


	//������ "Exit"
	Image Button3_image;
	Button3_image.loadFromFile("images/Button3.png");
	Button3_image.createMaskFromColor(Color(0, 0, 0));
	Texture Button3;
	Button3.loadFromImage(Button3_image);
	Sprite Exit;
	Exit.setTexture(Button3);
	Exit.setPosition(500, 500);

	int Num = 0;
	bool Menu1 = 1;

	while (Menu1)
	{
		drawMap(window);//����� ���� ������ ����� ����

		//������ ���� ������ ��� �������� �������
		if (IntRect(500, 200, 200, 90).contains(Mouse::getPosition(window))) { Play.setColor(Color::Green); Num = 1; }
		else Play.setColor(Color(69, 221, 213));
		if (IntRect(500, 350, 200, 100).contains(Mouse::getPosition(window))) { AboutGame.setColor(Color::Green); Num = 2; }
		else AboutGame.setColor(Color(69, 221, 213));
		if (IntRect(500, 500, 192, 100).contains(Mouse::getPosition(window))) { Exit.setColor(Color::Green); Num = 3; }
		else Exit.setColor(Color(69, 221, 213));

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Num == 1) Menu1 = false;//������ ���� ��� �������
			if (Num == 2) { window.draw(TextAboutGame); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (Num == 3) { window.close(); Menu1 = false; }
		}

		window.draw(NOG);
		window.draw(Play);
		window.draw(AboutGame);
		window.draw(Exit);
		window.display();
	}
}


void generate_item(std::vector <Item> &a, Texture& tx){
	srand(rand_seed);
	rand_seed+= 100;
	int x = rand() % 1200 + 1, y = rand() % 600 + 1, tip = rand() % 5 + 1;
	Item ai(tip, x, y, tx);
	for (auto i : a) {
		if (ai == i || TileMap[y/32][x/32] == 'l') return;
	}
	a.push_back(ai);
}

int main()
{
	RenderWindow window(sf::VideoMode(1280, 640), "Game Robinzon Ul'yev", sf::Style::Close | sf::Style::Titlebar);


	
	PlayerController PlayControl;
	IIController IIControl;


	std::map<int, std::string> items = {
	{ 1, "Vino"},
	{ 2, "Banana"},
	{ 3, "Vishnya"},
	{ 4, "Watermol"},
	{ 5, "Ananas"},
	};
	std::map<int, int> it_ht = {
		{ 1, 75},
		{ 2, 25},
		{ 3, 50},
		{ 4, 0},
		{ 5, 100},
	};
	Texture txt_fruits;
	txt_fruits.loadFromFile("images/Fruits.png");
	std::vector<Item> its;


	sf::Texture tex;
	tex.loadFromFile("images/win.png");
	sf::Sprite a(tex);
	a.setPosition(0, 0);
	start:
	drawMenu(window);


	Player player(1000, 500, 100, 100, 2, false);
	RectangleShape progressbar_health, progressbar;
	progressbar_health.setFillColor(Color::Red);
	progressbar_health.setOutlineColor(Color::Black);
	progressbar_health.setOutlineThickness(3);
	progressbar.setFillColor(Color(0,0,0,0));
	progressbar.setOutlineColor(Color::Black);
	progressbar.setOutlineThickness(3);
	II ii(50, 50, 100, 100, 1, true);


	Music music;//создаем объект музыки
	music.openFromFile("audio/music.ogg");//загружаем файл
	music.setVolume(50);
	music.play();//воспроизводим музыку
	Music music1;//создаем объект музыки
	music1.openFromFile("audio/death.ogg");//загружаем файл
	music1.setVolume(100);

	Clock clock; //создаем переменную времени, т.о. привязка ко времени(а не мощности/загруженности процессора). 
	double timer = 0, timer_eat = 0, timer_death = 0;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = time / 8000; //скорость игры

		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		timer += time;//прибавляем к нашей переменной time
		timer_eat += time;
		if (timer > 200) { generate_item(its, txt_fruits); timer = 0; } //если таймертелепорта больше 3000 (это примерно 3 секунды), то телепортируем героя и обнуляем таймер телепортации
		if (player.GetHealth() > 0)
		{

		    PlayControl.mainloop(pos.x, pos.y, player, time, its, it_ht, timer_eat);
	    	IIControl.mainloop(player, ii, time);
	    	interactionWithMap(player, ii);

			progressbar_health.setSize(Vector2f(player.GetHealth() * 2, 50));
			progressbar_health.setPosition(0, 590);
			progressbar.setSize(Vector2f(200, 50));
			progressbar.setPosition(0, 590);

	    	window.clear();
    		if (!player.GetIsWin()) {
    			drawMap(window);
	    		for (auto i : its) window.draw(i.herosprite);
	    		window.draw(player.herosprite);
		    	window.draw(ii.herosprite);
		    	player.inv.Draw(window);
				window.draw(progressbar);
				window.draw(progressbar_health);
		     }
		     else { window.draw(a); }
		     window.display();
		     player.debug();
	    } 
		else {
		     music.pause();
			 if(music1.getStatus() != Music::Playing)  music1.play();//воспроизводим музыку
			 timer_death += time;
			 if (timer_death > 400) { music.pause();  goto start; }
		}
	}

	return 0;
}