#pragma once
#include "SFML/Graphics.hpp"
#include <ctime>
#include <vector>
using namespace sf;

class Animationclock
{
	static Clock c;
public:
	static float GetTime() {return c.getElapsedTime().asSeconds();}
	static void Restart() {c.restart();}
};

struct Point
{
	int x;
	int y;
	Point(int x, int y) :x(x), y(y){}
	Point() : x(0), y(0){}
	Point&& operator+(Point p)
	{
		return Point(x + p.x, y + p.y);
	}
	Point&& operator-(Point p)
	{
		return Point(x - p.x, y - p.y);
	}
	Point& operator=(int n)
	{
		x = n;
		y = n;
		return *this;
	}
};

struct Texturepack
{
	static Texture water;
	static Texture fire;
	static Texture fog;
	static Texture square;
	static Texture ssquare;
	static Texture bsquare;
	static Texture tsquare;
	static Texture b1;
	static Texture b2;
	static Texture b3;
	static Texture b4;
	static Texture cross;
	static Texture menu;
	static Texture scroll;
	static Texture guide;
	static Font menuFont;
	static Font inGameFont;
	Texturepack()
	{
		Image img;
		Texturepack::water.loadFromFile("images/water.png");
		img.loadFromFile("images/fire.png");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::fire.loadFromImage(img);
		img.loadFromFile("images/Square.png");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::square.loadFromImage(img);
		img.loadFromFile("images/RedSquare.png");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::ssquare.loadFromImage(img);
		img.loadFromFile("images/cloud.png");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::fog.loadFromImage(img);
		img.loadFromFile("images/1.png");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::b1.loadFromImage(img);
		img.loadFromFile("images/2.png");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::b2.loadFromImage(img);
		img.loadFromFile("images/3.png");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::b3.loadFromImage(img);
		img.loadFromFile("images/4.png");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::b4.loadFromImage(img);
		img.loadFromFile("images/YellowSquare.png");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::bsquare.loadFromImage(img);
		img.loadFromFile("images/empty.png");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::tsquare.loadFromImage(img);
		img.loadFromFile("images/cross.png");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::cross.loadFromImage(img);
		menuFont.loadFromFile("images/menufont.otf");
		menu.loadFromFile("images/Menu.jpg");
		img.loadFromFile("images/scroll.jpg");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::scroll.loadFromImage(img);
		inGameFont.loadFromFile("images/ingamefont.ttf");
		img.loadFromFile("images/guide.png");
		img.createMaskFromColor(Color(255, 255, 255));
		Texturepack::guide.loadFromImage(img);
	}
};



class Water
{
	Sprite watersprite;
	float time;
public:
	Water() { watersprite.setTexture(Texturepack::water); }
	void Draw(RenderWindow& window)
	{
		float time = Animationclock::GetTime();
		if (time > 7)
			Animationclock::Restart();
		watersprite.setTextureRect(IntRect(80 * time, 0, 80, 80));
		for (int i = 0; i < 1080 / 80 + 1; i++)
			for (int j = 0; j < 1920 / 80 + 1; j++)
			{
				watersprite.setPosition(80 * j, 80 * i);
				window.draw(watersprite);
			}
	}

};

class Trigger
{
	Clock clock;
	int time;
public:
	bool TriggerKeyPress()
	{
		time = clock.getElapsedTime().asMilliseconds();
		if (time > 175)
		{
			clock.restart();
			return true;
		}
		return false;
	}
	void Restart(){	clock.restart(); }
};