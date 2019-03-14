#pragma once
#include "Header.h"
#include "Field.h"


class Ship
{
protected:
	Sprite spr;
	std::vector<Point> x;
	bool horizontal;
	bool destroyed;
public:
	Ship() : horizontal(false), destroyed(false){}
	Sprite& GetSprite() { return spr; }
	const bool GetDestroyed() { return destroyed; }
	void Rotate() { horizontal = !horizontal; }
	virtual void Set(Point x) = 0;
	bool Destroy(Field& field, Point& delay)
	{
		if (destroyed)
			return false;
		int c = 0;
		for (int i = 0; i < x.size(); i++)
			if (field.GetSquare(x[i] - delay).GetDestroyed())
				c++;
		if (c == x.size())
		{
			destroyed = true;
			for (int i = 0; i<x.size(); i++)
				field.Desroy(x[i] - delay);
			return true;
		}
		return false;
	}
	bool Occupy(Field& field, Point& delay)
	{
		int c = 0;
		for (int i = 0; i < x.size(); i++)
			if (!field.GetSquare(x[i] - delay).GetBusiness())
				c++;
		if (c == x.size())
		{
			for (int i = 0; i < x.size(); i++)
				field.Occupy(x[i] - delay);
			return true;
		}
		return false;
	}
	bool Check(Point& delay)
	{
		if ((!horizontal && x[x.size() -1].x - delay.x  < 10) || (horizontal && x[x.size() - 1].y - delay.y  < 10))
			return true;
		return false;
	}
};

class Gunboat : public Ship
{
public:
	Gunboat() 
	{
		spr.setTexture(Texturepack::b1);
	}
	void Set(Point p)
	{
		x.clear();
		x.push_back(p);
		if (!horizontal)
			spr.setTextureRect(IntRect(0, 0, 80, 80));
		else
			spr.setTextureRect(IntRect(80, 0, 80, 80));
		spr.setPosition(80 * x[0].x, 80 * x[0].y);
	}
};

class Schooner : public Ship
{
public:
	Schooner()
	{
		spr.setTexture(Texturepack::b2);
	}
	void Set(Point p)
	{
		x.clear();
		x.resize(2);
		x[0] = p;
		if (!horizontal)
		{
			spr.setTextureRect(IntRect(0, 0, 160, 80));
			x[1] = p + Point(1, 0);
		}
		else
		{
			spr.setTextureRect(IntRect(160, 0, 80, 160));
			x[1] = p + Point(0, 1);
		}
		spr.setPosition(80 * x[0].x, 80 * x[0].y);
	}
};

class Frigate : public Ship
{
public:
	Frigate()
	{
		spr.setTexture(Texturepack::b3);
	}
	void Set(Point p)
	{
		x.clear();
		x.resize(3);
		x[0] = p;
		if (!horizontal)
		{
			spr.setTextureRect(IntRect(0, 0, 240, 80));
			x[1] = (p + Point(1, 0));
			x[2] = (p + Point(2, 0));
		}
		else
		{
			spr.setTextureRect(IntRect(240, 0, 80, 240));
			x[1] = (p + Point(0, 1));
			x[2] = (p + Point(0, 2));
		}
		spr.setPosition(80 * x[0].x, 80 * x[0].y);
	}
};

class Battleship : public Ship
{
public:
	Battleship()
	{
		spr.setTexture(Texturepack::b4);
	}
	void Set(Point p)
	{
		x.clear();
		x.resize(4);
		x[0] = p;
		if (!horizontal)
		{
			spr.setTextureRect(IntRect(0, 0, 320, 80));
			x[1] = (p + Point(1, 0));
			x[2] = (p + Point(2, 0));
			x[3] = (p + Point(3, 0));
		}
		else
		{
			spr.setTextureRect(IntRect(320, 0, 80, 320));
			x[1] = (p + Point(0, 1));
			x[2] = (p + Point(0, 2));
			x[3] = (p + Point(0, 3));
		}
		spr.setPosition(80 * x[0].x, 80 * x[0].y);
	}
};